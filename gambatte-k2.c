#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <sched.h>
#include <errno.h>
#include <poll.h>
#include <linux/input.h>
#include <sys/stat.h>
#include <dlfcn.h>
#include <arm_neon.h>
#include <glib.h>
#include <gtk/gtk.h>
#include <gdk/gdkx.h>
#include <gdk-pixbuf/gdk-pixbuf.h>
#include "libretro.h"
#include "fbink.h"
#include "file_picker.h"
#include "main_ui.h"
#include "gray_shm.h"

void retro_init(void), retro_deinit(void);
bool retro_load_game(const struct retro_game_info *);
void retro_unload_game(void);
void retro_run(void);
void retro_reset(void);
void retro_set_environment(retro_environment_t);
void retro_set_video_refresh(retro_video_refresh_t);
void retro_set_audio_sample_batch(retro_audio_sample_batch_t);
void retro_set_input_poll(retro_input_poll_t);
void retro_set_input_state(retro_input_state_t);
void retro_get_system_av_info(struct retro_system_av_info *);

static char internal_game_name[17];

// GTK widgets
static GtkWidget *window, *border_box, *drawing_area, *drawing_area_container, *joystick_area;
static GtkWidget *load_btn, *save_btn;
static GtkWidget *gtk_toggle, *fbink_toggle, *options_box;
static volatile gint drawing_area_abs_x = 0, drawing_area_abs_y = 0;
static volatile gint joystick_area_abs_x = 0, joystick_area_abs_y = 0;
static int PIXBUF_WIDTH = 0, PIXBUF_HEIGHT = 0;

// Framebuffer/FBInk
int fbfd = FBFD_AUTO, fbfd_refresh = FBFD_AUTO;
FBInkConfig fbink_cfg = {0}, fbink_cfg_refresh = {0};

// Mutexes
GMutex *pixbuf_mutex = NULL, *slots_mutex = NULL, *game_loop_mutex = NULL;
static GAsyncQueue *frame_queue;

// Audio
typedef struct AudioBackend {
    void *mixer_handle;
} AudioBackend;
static AudioBackend *ab;

int16_t *MixerOpenPlay(int _, int __, int ___, const char *____);
uint8_t *MixerGetBufPlay(void *_, int *__, int *___);
void MixerWaitTillAudioProcessed(void *_);
void MixerDrain(void *_);
void MixerClose(void *_);
void MixerReleaseBufPlay(void *_, int __, uint8_t *___);
int MixerGetNumBytes(void *_);

typedef struct {
    GrayShm *presenter;
} MainState;
static MainState *state;

// Buffers
static GdkPixbuf *pixbuf = NULL, *pixbuf_dithered = NULL;
static GdkGC *gc = NULL;
static guchar *grayscale_frame_ptr = NULL;

static uint8_t grayscale_lut[65536] = {0};  // for RGB565 -> RGB888 -> grayscale
static struct retro_game_info game = {0};
// 
typedef struct { uint16_t *data; unsigned width, height; size_t pitch; } FrameJob;
typedef struct { int x, y, w, h, frame_width, frame_height; } DirtyRect;

typedef enum { DRAW_MODE_GTK, DRAW_MODE_FBINK } DrawMode;
static DrawMode draw_mode = DRAW_MODE_GTK;

typedef enum { STYLE_MODE_DARK, STYLE_MODE_LIGHT } StyleMode;
static StyleMode style_mode = STYLE_MODE_DARK;
static volatile gint refresh_screen = 0;
////// JOYSTICK
typedef enum { GB_BUTTON_ARC, GB_BUTTON_RECT } GbButtonGeometry;

typedef struct { float rel_x, rel_y, rel_r, rel_w, rel_h; gint x, y, r, w, h, active; GbButtonGeometry geometry; const char *label; } GbButtonRegion;

enum { GB_UP, GB_DOWN, GB_LEFT, GB_RIGHT, GB_A, GB_B, GB_SELECT, GB_START, GB_BUTTON_COUNT };

static GbButtonRegion gb_button_regions[GB_BUTTON_COUNT] = {
//    rel_x  rel_y  rel_r  rel_w  rel_h  x   y   r   w   h   active geometry        label 
    { 0.24,  0.15,  0.10,  0.14,  0.14,  0,  0,  0,  0,  0,  0,     GB_BUTTON_RECT, ""       }, // UP
    { 0.24,  0.65,  0.10,  0.14,  0.14,  0,  0,  0,  0,  0,  0,     GB_BUTTON_RECT, ""       }, // DOWN
    { 0.10,  0.40,  0.10,  0.14,  0.14,  0,  0,  0,  0,  0,  0,     GB_BUTTON_RECT, ""       }, // LEFT
    { 0.38,  0.40,  0.10,  0.14,  0.14,  0,  0,  0,  0,  0,  0,     GB_BUTTON_RECT, ""       }, // RIGHT
    { 0.89,  0.24,  0.08,  0.00,  0.00,  0,  0,  0,  0,  0,  0,     GB_BUTTON_ARC,  "A"      },
    { 0.67,  0.43,  0.08,  0.00,  0.00,  0,  0,  0,  0,  0,  0,     GB_BUTTON_ARC,  "B"      },
    { 0.39,  0.87,  0.07,  0.13,  0.07,  0,  0,  0,  0,  0,  0,     GB_BUTTON_RECT, "SELECT" },
    { 0.61,  0.87,  0.07,  0.13,  0.07,  0,  0,  0,  0,  0,  0,     GB_BUTTON_RECT, "START"  }
};

static int gb_button_state[GB_BUTTON_COUNT] = {0};

#define MAX_TOUCHES 2
typedef struct { bool active; int x, y; } TouchSlot;
static TouchSlot slots_snap[MAX_TOUCHES];
///////

// Global state
#define MAX_STATE_FILES 5
#define MAX_FILENAME_LEN 256

typedef struct {
    char filename[MAX_FILENAME_LEN];
    char modified_time[2048];
    int exists;
} StateFileEntry;

enum { STATE_MODE_LOAD, STATE_MODE_SAVE };
static gboolean running = TRUE;
static gboolean ready = FALSE;

static float brightness = 0; // TODO settings on gui
static float contrast = 1.5;

static double audio_sample_rate = 32000;
static double video_fps = 60;
static int   frame_interval_us = 16742;

static int SCALE_FACTOR_A = 3;

static int SCREEN_BORDER = 5; // px

static int kill_the_ghost = 0;

static uint8_t bayer16[16][16] = {
    {  0,  64,  16,  80,   4,  68,  20,  84,   1,  65,  17,  81,   5,  69,  21,  85 },
    {128, 192, 144, 208, 132, 196, 148, 212, 129, 193, 145, 209, 133, 197, 149, 213 },
    { 32,  96,  48, 112,  36, 100,  52, 116,  33,  97,  49, 113,  37, 101,  53, 117 },
    {160, 224, 176, 240, 164, 228, 180, 244, 161, 225, 177, 241, 165, 229, 181, 245 },
    {  8,  72,  24,  88,  12,  76,  28,  92,   9,  73,  25,  89,  13,  77,  29,  93 },
    {136, 200, 152, 216, 140, 204, 156, 220, 137, 201, 153, 217, 141, 205, 157, 221 },
    { 40, 104,  56, 120,  44, 108,  60, 124,  41, 105,  57, 121,  45, 109,  61, 125 },
    {168, 232, 184, 248, 172, 236, 188, 252, 169, 233, 185, 249, 173, 237, 189, 253 },
    {  2,  66,  18,  82,   6,  70,  22,  86,   3,  67,  19,  83,   7,  71,  23,  87 },
    {130, 194, 146, 210, 134, 198, 150, 214, 131, 195, 147, 211, 135, 199, 151, 215 },
    { 34,  98,  50, 114,  38, 102,  54, 118,  35,  99,  51, 115,  39, 103,  55, 119 },
    {162, 226, 178, 242, 166, 230, 182, 246, 163, 227, 179, 243, 167, 231, 183, 247 },
    { 10,  74,  26,  90,  14,  78,  30,  94,  11,  75,  27,  91,  15,  79,  31,  95 },
    {138, 202, 154, 218, 142, 206, 158, 222, 139, 203, 155, 219, 143, 207, 159, 223 },
    { 42, 106,  58, 122,  46, 110,  62, 126,  43, 107,  59, 123,  47, 111,  63, 127 },
    {170, 234, 186, 250, 174, 238, 190, 254, 171, 235, 187, 251, 175, 239, 191, 255 }
};

// 2) Pre‑load 16 NEON threshold vectors—run once at init
static uint8x16_t t_vecs[16];

void init_bayer16_thresholds(void) {
    for (int r = 0; r < 16; r++) {
        t_vecs[r] = vld1q_u8(bayer16[r]);
    }
}

void init_grayscale_lut(float contrast, float brightness) {
    for (uint32_t i = 0; i < 65536; i++) {
        // Convert RGB565 to RGB888
        int r = ((i >> 11) & 0x1F) << 3;
        int g = ((i >> 5) & 0x3F) << 2;
        int b = (i & 0x1F) << 3;
        // BT.601 luminance approx
        int L = (r*77 + g*150 + b*29) >> 8;
        // brightness & contrast
        int La = (L - 128) * contrast + 128 + brightness * 255;
        grayscale_lut[i] = (uint8_t)(La < 0 ? 0 : La > 255 ? 255 : La);
    }
}

// https://github.com/koreader/koreader/blob/c3352ee171aa8ea695f64518a38c03b759e7cb24/frontend/device/kindle/device.lua#L477
const char *detect_touch_device() {
    static char detected_touch_path[256] = "/dev/input/event1"; // fallback default
    size_t dev_count = 0;
    INPUT_DEVICE_TYPE_T match_mask = INPUT_TOUCHSCREEN | INPUT_SCALED_TABLET;
    FBInkInputDevice *devices = fbink_input_scan(match_mask, 0, 0, &dev_count);
    if (devices && dev_count > 0) {
        for (size_t i = 0; i < dev_count; ++i) {
            if (devices[i].matched) {
                strncpy(detected_touch_path, devices[i].path, sizeof(detected_touch_path) - 1);
                detected_touch_path[sizeof(detected_touch_path) - 1] = '\0';
                break;
            }
        }
        free(devices);
    }
    fprintf(stdout, "Detected touch device: %s\n", detected_touch_path);
    return detected_touch_path;
}

// touchscreen thread
static gpointer touch_thread_fn(gpointer data) {

    struct sched_param param;
    param.sched_priority = 70;

    if (pthread_setschedparam(pthread_self(), SCHED_RR, &param) != 0) {
        perror("pthread_setschedparam for touch_thread_fn");
    }

    const char *touch_path = detect_touch_device();
    int fd = open(touch_path, O_RDONLY | O_NONBLOCK);
    if (fd < 0) { perror("open"); return NULL; }

    struct input_event ev;
    struct pollfd fds = { .fd = fd, .events = POLLIN };
    TouchSlot slots[MAX_TOUCHES];
    int current_slot = 0;

    while (1) { // we may gracefully exit from here
        int ret = poll(&fds, 1, 50);
        if (ret <= 0) continue;
        while (read(fd, &ev, sizeof(ev)) == sizeof(ev)) {

            if (ev.type == EV_ABS) {
                switch (ev.code) {
                    case ABS_MT_SLOT:
                        current_slot = ev.value;
                        break;
                    case ABS_MT_TRACKING_ID: {
                        slots[current_slot].active = (ev.value != -1);
                        break;
                    }
                    case ABS_MT_POSITION_X: {
                        slots[current_slot].x = ev.value;
                        break;
                    }
                    case ABS_MT_POSITION_Y: {
                        slots[current_slot].y = ev.value;
                        break;
                    }
                }
            }
            else if (ev.type == EV_SYN && (ev.code == SYN_REPORT || ev.code == SYN_MT_REPORT)) {

                // fprintf(stderr, "Event: type=%d code=%d value=%d slot=%d\n", 
                //     ev.type, ev.code, ev.value, current_slot);
                // snapshot atomically
                g_mutex_lock(slots_mutex);
                memcpy(slots_snap, slots, sizeof(slots));
                g_mutex_unlock(slots_mutex);
            }
            ///
        }
    }
    close(fd);
    return NULL;
}

// input callbacks | gambatte thread
static void input_poll(void){
    // fprintf(stdout, "input_poll\n");
    // Clear all buttons
    for (int i = 0; i < GB_BUTTON_COUNT; ++i)
        gb_button_state[i] = 0;

    // Snapshot touch slots
    TouchSlot slots[MAX_TOUCHES];

    g_mutex_lock(slots_mutex);
    memcpy(slots, slots_snap, sizeof(slots));
    g_mutex_unlock(slots_mutex);

    // For each active touch, set the corresponding button
    for (int s = 0; s < MAX_TOUCHES; ++s) {
        if (!slots[s].active)
            continue;

        int rel_x = slots[s].x - g_atomic_int_get(&joystick_area_abs_x);
        int rel_y = slots[s].y - g_atomic_int_get(&joystick_area_abs_y);

        for (int i = 0; i < GB_BUTTON_COUNT; ++i) {
            int x = g_atomic_int_get(&gb_button_regions[i].x); // cx
            int y = g_atomic_int_get(&gb_button_regions[i].y); // cy
            int r = g_atomic_int_get(&gb_button_regions[i].r);  

            int dx = rel_x - x;
            int dy = rel_y - y;
            // circle equation
            if (dx * dx + dy * dy <= r * r) {
                gb_button_state[i] = 1;
            }
        }
    }
}

// input state | gambatte thread
static int16_t input_state(unsigned port, unsigned device, unsigned index, unsigned id) {
    if (device == RETRO_DEVICE_JOYPAD && port == 0) {
        switch (id) {
            case RETRO_DEVICE_ID_JOYPAD_UP:     return gb_button_state[GB_UP];
            case RETRO_DEVICE_ID_JOYPAD_DOWN:   return gb_button_state[GB_DOWN];
            case RETRO_DEVICE_ID_JOYPAD_LEFT:   return gb_button_state[GB_LEFT];
            case RETRO_DEVICE_ID_JOYPAD_RIGHT:  return gb_button_state[GB_RIGHT];
            case RETRO_DEVICE_ID_JOYPAD_A:      return gb_button_state[GB_A];
            case RETRO_DEVICE_ID_JOYPAD_B:      return gb_button_state[GB_B];
            case RETRO_DEVICE_ID_JOYPAD_SELECT: return gb_button_state[GB_SELECT];
            case RETRO_DEVICE_ID_JOYPAD_START:  return gb_button_state[GB_START];
        }
    }
    return 0;    
}

// gtk thread
static void on_area_configure_event(GtkWidget *widget, GdkEvent *event, gpointer user_data) {
    GdkWindow *gdk_win = gtk_widget_get_window(widget);
    int abs_x = 0, abs_y = 0;
    if (gdk_win)
        gdk_window_get_origin(gdk_win, &abs_x, &abs_y);

    if (widget == drawing_area) {
        g_atomic_int_set(&drawing_area_abs_x, abs_x);
        g_atomic_int_set(&drawing_area_abs_y, abs_y);

        fprintf(stdout, "drawing_area area abs pos: %4d %4d\n", abs_x, abs_y);

    } else if (widget == joystick_area) {
        g_atomic_int_set(&joystick_area_abs_x, abs_x);
        g_atomic_int_set(&joystick_area_abs_y, abs_y);

        GtkAllocation allocation;
        gtk_widget_get_allocation(widget, &allocation);
        int w = allocation.width;
        int h = allocation.height;
 
        // scale and position buttons proportionally
        for (int i = 0; i < GB_BUTTON_COUNT; ++i) {
            g_atomic_int_set(&gb_button_regions[i].x, (gint) (gb_button_regions[i].rel_x * w));
            g_atomic_int_set(&gb_button_regions[i].y, (gint) (gb_button_regions[i].rel_y * h));
            g_atomic_int_set(&gb_button_regions[i].r, (gint) (gb_button_regions[i].rel_r * w));
            g_atomic_int_set(&gb_button_regions[i].w, (gint) (gb_button_regions[i].rel_w * w));
            g_atomic_int_set(&gb_button_regions[i].h, (gint) (gb_button_regions[i].rel_h * w));
        }

        fprintf(stdout, "joystick_area area abs pos: %4d %4d (w:%4d h:%4d)\n", abs_x, abs_y, w, h);
    }
}

static gboolean gb_controls_draw(GtkWidget * widget, GdkEventExpose *event, gpointer data) {
    // Draw Gameboy background
    fprintf(stdout, "gb_controls_draw\n");

    GtkAllocation alloc;
    gtk_widget_get_allocation(widget, &alloc);
    int width = alloc.width;
    int height = alloc.height;    

    cairo_t *cr = gdk_cairo_create(widget->window);
    if (style_mode == STYLE_MODE_LIGHT) {
        cairo_set_source_rgb(cr, 255, 255, 255);
    } else {
        cairo_set_source_rgb(cr,   0,   0,   0);
    }
    cairo_paint(cr);

    // Draw buttons
    for (int i = 0; i < GB_BUTTON_COUNT; ++i) {
        GbButtonRegion *btn = &gb_button_regions[i]; // TODO thread safety.
        // if (gb_buttons[i])  // we could highlight the button if pressed but slows down the refreshing
        cairo_new_path(cr);
        cairo_set_source_rgb(cr, 255, 255, 255);

        if (btn->geometry == GB_BUTTON_RECT) {
            cairo_rectangle(cr, btn->x - btn->w / 2, btn->y - btn->h / 2, btn->w, btn->h);
        } else {
            cairo_arc(cr, btn->x, btn->y, btn->r, 0, 2*G_PI);
        }
        cairo_fill_preserve(cr);

        if (style_mode == STYLE_MODE_LIGHT) {
            cairo_set_source_rgb(cr,   0,   0,   0);
        } else {
            cairo_set_source_rgb(cr, 255, 255, 255);
        }
        cairo_set_line_width(cr, 5.0);     // border thickness
        cairo_stroke(cr);

        // Draw label
        cairo_text_extents_t te;
        cairo_text_extents (cr, btn->label, &te);

        cairo_set_source_rgb(cr, 0, 0, 0);
        cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
        cairo_set_font_size(cr, width * 0.03);
        cairo_move_to(cr,
            btn->x - te.width / 2 - te.x_bearing,
            btn->y + te.height / 2);            
        cairo_show_text(cr, btn->label);
    }
    return FALSE;
}

static AudioBackend *audio_backend_init(const int sample_rate) {
    AudioBackend *ab = calloc(1, sizeof(AudioBackend));
    ab->mixer_handle = MixerOpenPlay(sample_rate, 2, 16, "Music");
    if (!ab->mixer_handle) {
        fprintf(stderr, "MixerOpenPlay failed\n");
        free(ab);
        return NULL;
    }
    return ab;
}

static void audio_backend_deinit(AudioBackend **pab) {
    if (!pab || !*pab) return;
    AudioBackend *ab = *pab;
    if (ab->mixer_handle) {
        MixerWaitTillAudioProcessed(ab->mixer_handle);
        MixerDrain(ab->mixer_handle);
        MixerClose(ab->mixer_handle);
        ab->mixer_handle = NULL;
    }
    free(ab);
    *pab = NULL;
}

static size_t audio_sample_batch(const int16_t *data, size_t frames) {
    int64_t start = g_get_monotonic_time();  
    
    if (!ab || !ab->mixer_handle || MixerGetNumBytes(ab->mixer_handle) > frames * 40 ) return frames;

    int r, s; uint8_t *b = MixerGetBufPlay(ab->mixer_handle, &r, &s);
    if (!b || r != 0 || s <= 0) return frames;
    
    frames = frames > s/4 ? s/4 : frames;
    
    memcpy(b + 1, data + 1, frames * 4 - 1);
    
    MixerReleaseBufPlay(ab->mixer_handle, frames * 4, b);
    
    int64_t elapsed = g_get_monotonic_time() - start;
    
    if ( ((double) (elapsed) / 1000.0) > 2 ){
        g_print("audio slow, elapsed: %f\n", (double) (elapsed) / 1000.0);
    }
    return frames;
}

// STEP 2
static gpointer process_frame_job(gpointer user_data) {
    FrameJob *job = user_data;
    
    // DEBUG SECTION START
    static int skipped_frame_fps_count;
    static int skipped_frame_mutex_count;
    
    static struct timespec last_frame_time = {0, 0};
    static struct timespec now_time;
    clock_gettime(CLOCK_MONOTONIC, &now_time);
    double elapsed = (now_time.tv_sec - last_frame_time.tv_sec) +
                    (now_time.tv_nsec - last_frame_time.tv_nsec) / 1e9;

    clock_t t = clock(); 
    // --- FPS  ---
    static int frame_count = 0;
    static time_t last_time = 0;
    time_t now = time(NULL);
    double time_taken;
    // DEBUG SECTION END

    if (!state->presenter) {
        return NULL;
    }

    const uint16_t *emulator_frame_ptr = job->data;   // Pointer to RGB565 uint16_t data emulator_frame 
    int emulator_frame_width     = job->width;          // Width of the emulator frame: 160px
    int emulator_frame_height    = job->height;         // Height of the emulator frame: 144px
    int emulator_frame_rowstride = job->pitch / sizeof(uint16_t);

    int scaled_frame_width     = emulator_frame_width  * SCALE_FACTOR_A; // refactor, already set
    int scaled_frame_height    = emulator_frame_height * SCALE_FACTOR_A; // refactor, already set
    int scaled_frame_channels  = 1;                                      // 8 bit per pixel (0-255) = 1 channel grayscale = Y8
    int scaled_frame_rowstride = scaled_frame_width * scaled_frame_channels;

    int min_x = scaled_frame_width, min_y = scaled_frame_height, max_x = -1, max_y = -1, dirty_count = 0;

    // TODO refactor, there will be no more size changes.
    if (!grayscale_frame_ptr || PIXBUF_WIDTH != scaled_frame_width || PIXBUF_HEIGHT != scaled_frame_height) {
        fprintf(stderr, "ensure pixbuf size: %d vs %d\n", PIXBUF_WIDTH, scaled_frame_width);
        if (grayscale_frame_ptr) {
            free(grayscale_frame_ptr);
        }
        PIXBUF_WIDTH        = scaled_frame_width;  // global
        PIXBUF_HEIGHT       = scaled_frame_height; // global
        grayscale_frame_ptr = malloc(scaled_frame_height * scaled_frame_rowstride); // 1-channel grayscale buffer
    }

    const uint8_t *dithered_frame_ptr = gray_shm_get_buffer(state->presenter); // 830Kb

    uint16_t *emu_row_ptr = emulator_frame_ptr;
    // scale frame to the final pixbuf size
    for (int y = 0, y_scaled = 0; y < emulator_frame_height; y++, y_scaled += SCALE_FACTOR_A) { // 144

        const uint16_t *emulator_src_row = emulator_frame_ptr + y * emulator_frame_rowstride;
        uint8_t *grayscale_dst_row = grayscale_frame_ptr + y_scaled * scaled_frame_rowstride;

        int line_min_x = emulator_frame_width, line_max_x = -1;

        for (int x = 0, x_scaled_base = 0; x < emulator_frame_width; x++, x_scaled_base += SCALE_FACTOR_A) { // 160
            uint8_t gray = grayscale_lut[emulator_src_row[x]];
            uint8_t prev = grayscale_dst_row[x_scaled_base];                    
            // Check if pixel changed compared to previous grayscale_frame
            if (gray == prev) continue;
            if (x < min_x) min_x = x;
            if (x > max_x) max_x = x;
            if (y < min_y) min_y = y;
            if (y > max_y) max_y = y;
            if (x < line_min_x) line_min_x = x;
            if (x > line_max_x) line_max_x = x;
            memset(&grayscale_dst_row[x_scaled_base], gray, SCALE_FACTOR_A);
            dirty_count++;
        }

        if (line_max_x < 0) continue;

        int rx0 = (line_min_x * SCALE_FACTOR_A) & ~0xF;
        int rx1 = (line_max_x * SCALE_FACTOR_A) + (SCALE_FACTOR_A - 1);

        // Vertical scaling (nearest neighbor)
        for (int sy = 0; sy < SCALE_FACTOR_A; sy++) {       // (0 is the source)
            uint8_t *dst_row = grayscale_dst_row + sy * scaled_frame_rowstride;
            
            if (sy > 0) {
                memcpy(dst_row, grayscale_dst_row, scaled_frame_rowstride);
            }

            uint8x16_t thresh = t_vecs[(y_scaled + sy) & 15];

            uint8_t *dithered_row = dithered_frame_ptr + ((y_scaled + sy) * scaled_frame_rowstride);
            
            for (int rx = rx0; rx <= rx1; rx += 16) {
                vst1q_u8( dithered_row + rx, vcgeq_u8(vld1q_u8(dst_row + rx), thresh) );
            }  
        }
    }

    // 6 (960x864): 190.080 iterations, like 435x435 | 3 480x432: 82.080 iterations, like 286x286
    // 6 (960x864): 74.880|22.040+51.840

    if (!dirty_count && !g_atomic_int_get(&refresh_screen)) {
        return NULL;
    }

    min_x = min_x * SCALE_FACTOR_A;
    max_x = max_x * SCALE_FACTOR_A;
    min_y = min_y * SCALE_FACTOR_A;
    max_y = max_y * SCALE_FACTOR_A;

    int rect_x = min_x;
    int rect_y = min_y;
    int rect_w = max_x - min_x + SCALE_FACTOR_A;
    int rect_h = max_y - min_y + SCALE_FACTOR_A;

    

    // use dirt rect
    // for (int y = rect_y; y < rect_y + rect_h; y++) { 
    //     uint8x16_t t = t_vecs[y & 15];
    //     const uint8_t *src_row = grayscale_frame_ptr + y * scaled_frame_rowstride;
    //     uint8_t *dst_row       = dithered_frame_ptr  + y * scaled_frame_rowstride;

    //     for (int x = rect_x & ~0xF; x < rect_x + rect_w; x += 16) {
    //         vst1q_u8(dst_row + x, vcgeq_u8(vld1q_u8(src_row + x), t));
    //     }
    // }
    
    // int w = gray_shm_get_width(&state->presenter);
    // int h = gray_shm_get_height(&state->presenter);

    if ( g_atomic_int_get(&refresh_screen) > 0 ) {
        g_atomic_int_add(&refresh_screen, -1);
        rect_x = 0;
        rect_y = 0;
        rect_w = scaled_frame_width;
        rect_h = scaled_frame_height;          
    }

    if (draw_mode == DRAW_MODE_GTK) {

        gray_shm_commit_rect(state->presenter, rect_x, rect_y, rect_w, rect_h);
        //gray_shm_commit_rect(state->presenter, 0, 0, w, h);

    } else if (draw_mode == DRAW_MODE_FBINK) {

        // int ret = fbink_print_raw_data(
        //     fbfd,
        //     frame,
        //     scaled_frame_width,
        //     scaled_frame_height,
        //     scaled_frame_width * scaled_frame_height,
        //     g_atomic_int_get(&drawing_area_abs_x), // x_off
        //     g_atomic_int_get(&drawing_area_abs_y), // y_off
        //     &fbink_cfg
        // );

        // Pointer to the start of the region
        const uint8_t *region_pixels = dithered_frame_ptr + (rect_y * scaled_frame_rowstride) + (rect_x * scaled_frame_channels);

        // Allocate a buffer for the region (fbink expects packed, contiguous data)
        const size_t region_len = rect_w * rect_h * scaled_frame_channels;

        const uint8_t *region_buf = malloc(region_len);

        for (int y = 0; y < rect_h; ++y) {
            memcpy(region_buf + y * rect_w * scaled_frame_channels,
                region_pixels + y * scaled_frame_rowstride,
                                    rect_w * scaled_frame_channels);
        }

        int ret = fbink_print_raw_data(
            fbfd,
            region_buf,
            rect_w,
            rect_h,
            region_len,
            g_atomic_int_get(&drawing_area_abs_x) + rect_x,
            g_atomic_int_get(&drawing_area_abs_y) + rect_y,
            &fbink_cfg
        );

        free(region_buf);    
        
        if (ret < 0) {
            fprintf(stderr, "fbink_print_raw_data failed: %d\n", ret);
        }        

    }

    // DEBUG SECTION START
    t = clock() - t; 
    time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds 
    frame_count++;
    if (now > last_time) { // Print FPS every 5 seconds
        fprintf(stdout,"refresh FPS: %2d ttaken: %.4f dirty: %5d min_x: %3d min_y: %3d max_x: %3d max_y: %3d rect_x: %3d rect_y: %3d rect_w: %3d rect_h: %3d | w:%3d h:%3d\n",
            frame_count, time_taken, dirty_count,
            min_x, min_y, max_x, max_y,
            rect_x, rect_y, rect_w, rect_h,
            scaled_frame_width, scaled_frame_height);

        frame_count = skipped_frame_fps_count = skipped_frame_mutex_count = 0;
        last_time = now;
    }
    // DEBUG SECTION END    
    clock_gettime(CLOCK_MONOTONIC, &last_frame_time);

    return NULL;
}

static gboolean should_process_frame(void) {
    static int64_t last_frame_time = 0;
    const int FRAME_INTERVAL_US = 1000000 / 30; // 
    int64_t current_time = g_get_monotonic_time();

    if ((current_time - last_frame_time) > FRAME_INTERVAL_US) {
        last_frame_time = current_time;
        return TRUE;
    }
    return FALSE;
}

// frame thread
static gpointer frame_thread_loop(gpointer data){

    struct sched_param param;
    param.sched_priority = 70;

    if (pthread_setschedparam(pthread_self(), SCHED_RR, &param) != 0) {
        perror("pthread_setschedparam for frame_thread_loop");
    }

    while (running) { 
        FrameJob *job = g_async_queue_pop(frame_queue);
        // check sentinel here
        if (job) {
            if (should_process_frame()) {
                process_frame_job(job);
            }
            free(job->data);
            free(job);
        }
    }
   
    return NULL;
}

// emulator thread
static void video_refresh(const void *data, unsigned width, unsigned height, size_t pitch) {
    if (!data) return;

    FrameJob *job = malloc(sizeof(FrameJob));

    job->width  = width;
    job->height = height;
    job->pitch  = pitch;

    if (draw_mode == DRAW_MODE_GTK) {
        if (should_process_frame()){
            job->data = data;
            process_frame_job(job);
            free(job);
        }
        return;
    }

    uint16_t *frame_copy = malloc(height * pitch);
    memcpy(frame_copy, data, height * pitch);
    job->data = frame_copy;

    // queue frame precessing and exit asap to prevent core slow down
    // drop any old frame waiting in the queue and push the newest frame atomically
    g_async_queue_lock(frame_queue);
    FrameJob *old = g_async_queue_try_pop_unlocked(frame_queue);
    if (old) {
        free(old->data); free(old);
    }
    g_async_queue_push_unlocked(frame_queue, job);
    g_async_queue_unlock(frame_queue);

}

static bool environment_cb(unsigned cmd, void *data) {
    // fprintf(stderr, "environment_cb: %i\n", cmd);
    switch (cmd) {
        
        case RETRO_ENVIRONMENT_GET_VARIABLE: {
            struct retro_variable *var = (struct retro_variable *)data;

            // if (strcmp(var->key, "gambatte_gb_colorization") == 0) {
            //     fprintf(stdout, "gambatte_gb_colorization: internal\n");
            //     var->value = "internal";
            //     return true;
            // }
            // if (strcmp(var->key, "gambatte_gb_internal_palette") == 0) {
            //     fprintf(stdout, "gambatte_gb_internal_palette: GBC - Grayscale\n");
            //     var->value = "GBC - Grayscale";
            //     return true;
            // }

            if (strcmp(var->key, "gambatte_gbc_color_correction") == 0) {
                fprintf(stdout, "gambatte_gbc_color_correction: disabled\n");
                var->value = "disabled";
                return true;
            }
            if (strcmp(var->key, "gambatte_mix_frames") == 0) {
                fprintf(stdout, "gambatte_mix_frames: disabled\n");
                var->value = "disabled";
                return true;
            }

            // Default fallback
            var->value = NULL;
            return false;
        }
        
        case RETRO_ENVIRONMENT_SET_PIXEL_FORMAT: {
            enum retro_pixel_format *fmt = (enum retro_pixel_format *)data;
            if (*fmt == RETRO_PIXEL_FORMAT_RGB565) {
                return true;
            }
            return false;
        }

        case RETRO_ENVIRONMENT_GET_SYSTEM_DIRECTORY: {
            const char **dir = data;
            static const char *system_dir = "./gambatte";
            *dir = system_dir;
            return true;
        }
        
        case RETRO_ENVIRONMENT_GET_CAN_DUPE: {
            bool *can_dupe = data;
            *can_dupe = true;
            return true;
        }

        default:
            return false;
    }
}

static gpointer emulator_thread_fn(gpointer data) {

    // const int frame_interval_us = 16742; // FRAME_USEC;
    struct sched_param param;
    param.sched_priority = 70;

    if (pthread_setschedparam(pthread_self(), SCHED_RR, &param) != 0) {
        perror("pthread_setschedparam for emulator_thread_fn");
    }

    while (running) {

        int64_t start = g_get_monotonic_time();

        g_mutex_lock(game_loop_mutex);
        if (ready) {
            retro_run(); // will trigger video_refresh via callback
        }
        g_mutex_unlock(game_loop_mutex);

        int64_t elapsed = g_get_monotonic_time() - start;

        if (elapsed < frame_interval_us) {                  
            g_usleep(frame_interval_us - elapsed);
        } else {
            g_print("warning negative elapsed: %f\n", (double) (elapsed) / 1000.0);
        }

        // if ( ((double) (elapsed) / 1000.0) > 4 ){
        //     g_print("retro run slow, elapsed: %f\n", (double) (elapsed) / 1000.0);
        // }

    }
    return NULL;
}

// TODO refactor this 
void sanitize_filename(const char *input, char *output, size_t maxlen);
void sanitize_filename(const char *input, char *output, size_t maxlen);
void on_open(GtkButton *button, gpointer user_data) {
        fprintf(stderr, "on_open\n");

        g_mutex_lock(game_loop_mutex);
        
        ready = FALSE; // use mutexes color?

        char *game_path = simple_file_chooser_list(GTK_WINDOW(window));
        g_print("Selected: %s\n", game_path);
        if (game_path) {
            g_print("game_path: %s\n", game_path);

            if(game.data) {
                retro_unload_game();
                retro_reset();
                retro_deinit();
                audio_backend_deinit(&ab);
            }

            retro_set_environment(environment_cb);
            retro_set_video_refresh(video_refresh);
            retro_set_audio_sample_batch(audio_sample_batch);
            retro_set_input_poll(input_poll);
            retro_set_input_state(input_state);

            fprintf(stdout, "Loaded core symbols\n");

            retro_init();

            g_print("game_path 2: %s\n", game_path);
 

            FILE *game_file = fopen(game_path, "rb");
            if (!game_file) {
                fprintf(stderr, "Failed to open game file\n");
                g_mutex_unlock(game_loop_mutex);
                return;
            }
            fseek(game_file, 0, SEEK_END);
            game.size = ftell(game_file);
            fseek(game_file, 0, SEEK_SET);
            game.data = malloc(game.size);
            fread((void*)game.data, 1, game.size, game_file);
            fclose(game_file);

            if (!retro_load_game(&game)) {
                fprintf(stderr, "Failed to load game\n");
                g_mutex_unlock(game_loop_mutex);
                return;
            }

            struct retro_system_av_info av_info;
            retro_get_system_av_info(&av_info);

            audio_sample_rate = av_info.timing.sample_rate;
            video_fps         = av_info.timing.fps;
            frame_interval_us = (int) (1000000.0 / video_fps);

            ab = audio_backend_init( 32760 );

            g_print("Libretro core reports sample rate: %.2f Hz sample_rate:: %f fusec: %d \n", video_fps, audio_sample_rate, frame_interval_us );

            g_atomic_int_set(&refresh_screen, 10);

            // libretro.cpp:2589
            char raw_name[17];
            strncpy(raw_name, (const char*)game.data + 0x134, sizeof(raw_name) - 1);
            raw_name[sizeof(raw_name) - 1] = '\0';

            sanitize_filename(raw_name, internal_game_name, sizeof(internal_game_name));

            g_print("internal_game_name: %s\n", internal_game_name);

            gtk_widget_show(load_btn);
            gtk_widget_show(save_btn);
                        
            ready = TRUE;
        } else if (game.data) {
            ready = TRUE;
        }
        g_mutex_unlock(game_loop_mutex);
        g_free(game_path);
}

/////
void save_state(const char *filename) {
    size_t size = retro_serialize_size();
    if (size == 0) return;
    void *state = malloc(size);
    if (!state) return;
    if (retro_serialize(state, size)) {
        // char abs_path[PATH_MAX];
        // g_print("retro_serialize: \n");
        // realpath(filename, abs_path);
        // g_print("Saving state to: %s\n", abs_path);        
        FILE *f = fopen(filename, "wb");
        if (f) {
            fwrite(state, 1, size, f);
            fclose(f);
        }
    }
    free(state);
}

void load_state(const char *filename) {
    size_t size = retro_serialize_size();
    if (size == 0) return;
    void *state = malloc(size);
    if (!state) return;
    FILE *f = fopen(filename, "rb");
    if (f) {
        fread(state, 1, size, f);
        fclose(f);
        retro_unserialize(state, size);
    }
    free(state);
}

static void on_option_selected(GtkWidget *button, gpointer user_data) {
    int option = GPOINTER_TO_INT(user_data);
    GtkWidget *dialog = gtk_widget_get_toplevel(button);
    
    // Handle selected option (option 1-5)
    g_print("Selected option: %d\n", option);
    
    // Close dialog
    gtk_dialog_response(GTK_DIALOG(dialog), option);
}

static int load_save_dialog(GtkWindow *parent, StateFileEntry *entries, int action) {
    GtkWidget *dialog = gtk_dialog_new_with_buttons(
       "L:A_D:application_ID:gambatteLoadSaveDialog",
        parent,
        GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
        GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,        
        NULL
    );
    
    gtk_window_set_default_size(GTK_WINDOW(dialog), 300, 400);
    GtkWidget *content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    gtk_container_set_border_width(GTK_CONTAINER(content_area), 15);
    GtkWidget *padding_frame = gtk_alignment_new(0.5, 0.5, 1.0, 1.0);
    gtk_alignment_set_padding(GTK_ALIGNMENT(padding_frame), 15, 15, 20, 20);  // Top, bottom, left, right
    gtk_container_add(GTK_CONTAINER(content_area), padding_frame);
    GtkWidget *vbox = gtk_vbox_new(TRUE, 10);
    gtk_container_add(GTK_CONTAINER(padding_frame), vbox);
    
    for (int i = 0; i < MAX_STATE_FILES; i++) {
        gchar *label;

        if (entries[i].exists) {
            label = g_strdup_printf("slot %d: %s", i + 1, entries[i].modified_time);
        } else {
            label = g_strdup_printf("slot %d: (empty)", i + 1);
        }

        GtkWidget *btn = gtk_button_new_with_label(label);
        
        if (action == STATE_MODE_SAVE || (action == STATE_MODE_LOAD && entries[i].exists) )
            g_signal_connect(btn, "clicked", G_CALLBACK(on_option_selected), GINT_TO_POINTER(i));

        gtk_box_pack_start(GTK_BOX(vbox), btn, FALSE, FALSE, 0);
        g_free(label);
    }
    
    // Show and run dialog
    gtk_widget_show_all(dialog);
    gint res = gtk_dialog_run(GTK_DIALOG(dialog)); 
    gtk_widget_destroy(dialog);
    return res;
}

void sanitize_filename(const char *input, char *output, size_t maxlen) {
    size_t j = 0;
    for (size_t i = 0; input[i] != '\0' && j < maxlen - 1; ++i) {
        char c = input[i];
        if (isalnum((unsigned char)c) || c == '_' || c == '-' || c == '.') {
            output[j++] = c;
        }
    }
    output[j] = '\0';
}

void on_state_mode_click(GtkButton *button, gpointer user_data) {
    
    int action = GPOINTER_TO_INT (user_data);
    
    g_mutex_lock(game_loop_mutex);
    
    // ready = FALSE; // use mutexes color?

    StateFileEntry entries[MAX_STATE_FILES];

    for (int i = 0; i < MAX_STATE_FILES; ++i) {
        snprintf(entries[i].filename, MAX_FILENAME_LEN, "./state/%s.%d", internal_game_name, i + 1);

        struct stat st;
        if (stat(entries[i].filename, &st) == 0) {
            time_t time = st.st_mtime;
            struct tm * stime = localtime(&time);
            strftime(entries[i].modified_time, 2048, "%Y-%m-%d %H:%M", stime);
            entries[i].exists = 1;
        } else {
            entries[i].exists = 0;
        }        

        g_print("file %s %d %s\n", entries[i].filename, entries[i].exists, entries[i].modified_time);
    }

    gint res = load_save_dialog(GTK_WINDOW(window), entries, action);
    
    if (res >= 0 && res < MAX_STATE_FILES) {
        
        if (action == STATE_MODE_LOAD)
            load_state( entries[res].filename );

        if (action == STATE_MODE_SAVE)
            save_state( entries[res].filename );

    }
    g_print("on_load option: %d\n", res);
    
    g_mutex_unlock(game_loop_mutex); // ready = TRUE;
}

void on_refresh(GtkButton *button, gpointer user_data) {
    g_mutex_lock(game_loop_mutex);
    g_mutex_lock(pixbuf_mutex);
    fprintf(stdout, "refresh_screen\n");
    fbink_refresh(fbfd_refresh, drawing_area_abs_y, drawing_area_abs_x, PIXBUF_WIDTH, PIXBUF_HEIGHT, &fbink_cfg_refresh);
    g_mutex_unlock(game_loop_mutex);
    g_mutex_unlock(pixbuf_mutex);
    g_atomic_int_set(&refresh_screen, 30);
}

// GTK button callback to quit
void on_quit(GtkButton *button, gpointer user_data) {
    running = FALSE; // Signal the thread to stop
    if (state->presenter) {
        gray_shm_destroy(state->presenter);
        state->presenter = NULL;
    }    
    gtk_main_quit();
}

void on_draw_mode_toggle(GtkToggleButton *button, gpointer user_data) {
    fprintf(stderr, "on_draw_mode_toggle\n");
    int action = GPOINTER_TO_INT (user_data);
    g_signal_handlers_block_by_func (G_OBJECT(gtk_toggle), G_CALLBACK(on_draw_mode_toggle), GINT_TO_POINTER (DRAW_MODE_GTK));
    g_signal_handlers_block_by_func (G_OBJECT(fbink_toggle), G_CALLBACK(on_draw_mode_toggle), GINT_TO_POINTER (DRAW_MODE_FBINK));
    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(gtk_toggle), action == DRAW_MODE_GTK );
    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON(fbink_toggle), action == DRAW_MODE_FBINK );
    g_signal_handlers_unblock_by_func (G_OBJECT(gtk_toggle), G_CALLBACK(on_draw_mode_toggle), GINT_TO_POINTER (DRAW_MODE_GTK));
    g_signal_handlers_unblock_by_func (G_OBJECT(fbink_toggle), G_CALLBACK(on_draw_mode_toggle), GINT_TO_POINTER (DRAW_MODE_FBINK));

    g_mutex_lock(pixbuf_mutex);    
    draw_mode = action;
    kill_the_ghost = 1;
    g_mutex_unlock(pixbuf_mutex); 

}

void on_toggle_style(GtkToggleButton *toggle, gpointer window) {

    GdkColor white_color, black_color;
    gdk_color_parse("#FFFFFF", &white_color);
    gdk_color_parse("#000000", &black_color);

    style_mode = gtk_toggle_button_get_active(toggle) ? STYLE_MODE_LIGHT : STYLE_MODE_DARK;

    gtk_widget_modify_bg(window, GTK_STATE_NORMAL,                 style_mode == STYLE_MODE_DARK ? &black_color : &white_color);
    gtk_widget_modify_bg(drawing_area, GTK_STATE_NORMAL,           style_mode == STYLE_MODE_DARK ? &black_color : &white_color);
    gtk_widget_modify_bg(drawing_area_container, GTK_STATE_NORMAL, style_mode == STYLE_MODE_DARK ? &white_color : &black_color);

    gtk_widget_queue_draw(GTK_WIDGET(window));
    g_atomic_int_set(&refresh_screen, 30);
}

static void on_area_realize(GtkWidget *widget, MainState *st)
{
    xcb_window_t xid = GDK_WINDOW_XID(widget->window);
    int w = widget->allocation.width, h = widget->allocation.height;
    st->presenter = gray_shm_create(xid, w, h);

    GdkWindow *gdk_win = gtk_widget_get_window(widget);
    int abs_x = 0, abs_y = 0;
    if (gdk_win)
        gdk_window_get_origin(gdk_win, &abs_x, &abs_y);

    g_print("on_area_realize xid: %d w: %d h: %d abs_x: %d abs_y: %d \n", xid, gray_shm_get_width(st->presenter), gray_shm_get_height(st->presenter), abs_x, abs_y);
}

static void on_area_size_allocate(GtkWidget *widget, GtkAllocation *allocation, MainState *st)
{
    if (st->presenter) {
        gray_shm_resize(st->presenter, allocation->width, allocation->height);
    }

    g_print("on_area_size_allocate w: %d h: %d\n", allocation->width, allocation->height);
}

static void init_gtk_and_window() {

    gtk_rc_parse_string(
        "style \"custom-button\" {\n"
        "  bg[NORMAL]      = \"#FFFFFF\"\n"
        "  fg[NORMAL]      = \"#000000\"\n"
        "  bg[ACTIVE]      = \"#000000\"\n"
        "  fg[ACTIVE]      = \"#FFFFFF\"\n"
        "  bg[SELECTED]    = \"#FFFF00\"\n"
        "  fg[SELECTED]    = \"#FF00FF\"\n"
        "  bg[PRELIGHT]    = \"#FFFFFF\"\n"
        "  fg[PRELIGHT]    = \"#000000\"\n"
        "  xthickness = 0\n"
        "  ythickness = 10\n"
        "  font_name = \"Sans Bold 8\"\n"
        "  GtkWidget::focus-line-width = 0\n"
        "  GtkWidget::focus-padding = 0\n"
        "  engine \"pixmap\" {}\n"
        "}\n"
        "style \"white-dialog\" {\n"
        "  bg[NORMAL] = \"#FFFFFF\"\n"
        "  fg[NORMAL] = \"#000000\"\n"
        "  font_name = \"Sans 12\"\n"
        "  xthickness = 20\n"
        "  ythickness = 20\n"        
        "}\n"        
        "widget_class \"*GtkButton\" style \"custom-button\"\n"
        "widget_class \"*GtkToggleButton\" style \"custom-button\"\n"
        "widget_class \"*GtkLabel\" style \"custom-button\"\n"
        "widget_class \"*GtkDialog\" style \"white-dialog\"\n"        
    ); 

    //       
    GtkBuilder *builder = gtk_builder_new();
    GError *error = NULL;

    // Load UI from the xxd-generated header
    if (!gtk_builder_add_from_string(builder, (const gchar *)main_ui_xml, strlen(main_ui_xml), &error)) {
        g_error("Failed to load UI: %s", error->message);
        g_error_free(error);
        return;
    }

    // Connect signals
    gtk_builder_connect_signals(builder, NULL);

    // Get widgets by ID
    window         = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));
    drawing_area   = GTK_WIDGET(gtk_builder_get_object(builder, "drawing_area"));
    joystick_area  = GTK_WIDGET(gtk_builder_get_object(builder, "joystick_area"));
    gtk_toggle     = GTK_WIDGET(gtk_builder_get_object(builder, "gtk_toggle"));
    fbink_toggle   = GTK_WIDGET(gtk_builder_get_object(builder, "fbink_toggle"));

    load_btn       = GTK_WIDGET(gtk_builder_get_object(builder, "load_btn"));
    save_btn       = GTK_WIDGET(gtk_builder_get_object(builder, "save_btn"));

    GtkWidget *center_hbox            = GTK_WIDGET(gtk_builder_get_object(builder, "center_hbox"));
    drawing_area_container = GTK_WIDGET(gtk_builder_get_object(builder, "drawing_area_container"));
    GtkWidget *style_toggle   = GTK_WIDGET(gtk_builder_get_object(builder, "style_toggle"));

    // Set up signals not handled by Glade
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    // g_signal_connect(drawing_area, "expose-event", G_CALLBACK(expose_event), NULL);
    g_signal_connect(drawing_area, "configure-event", G_CALLBACK(on_area_configure_event), NULL);
    g_signal_connect(joystick_area, "expose-event", G_CALLBACK(gb_controls_draw), NULL);
    g_signal_connect(joystick_area, "configure-event", G_CALLBACK(on_area_configure_event), NULL);

    g_signal_connect(gtk_toggle, "toggled", G_CALLBACK(on_draw_mode_toggle), GINT_TO_POINTER(DRAW_MODE_GTK));
    g_signal_connect(fbink_toggle, "toggled", G_CALLBACK(on_draw_mode_toggle), GINT_TO_POINTER(DRAW_MODE_FBINK));
    g_signal_connect(load_btn, "clicked", G_CALLBACK(on_state_mode_click), GINT_TO_POINTER(STATE_MODE_LOAD));
    g_signal_connect(save_btn, "clicked", G_CALLBACK(on_state_mode_click), GINT_TO_POINTER(STATE_MODE_SAVE));

    g_signal_connect(style_toggle, "toggled", G_CALLBACK(on_toggle_style), window);
    g_signal_connect(drawing_area, "realize",       G_CALLBACK(on_area_realize),       &state);
    g_signal_connect(drawing_area, "size-allocate", G_CALLBACK(on_area_size_allocate) ,&state);
    //g_signal_connect(window,       "destroy",       G_CALLBACK(on_area_destroy),       &state);
    gtk_widget_set_name(window,                 "window");
    gtk_widget_set_name(drawing_area,           "drawing_area");
    gtk_widget_set_name(drawing_area_container, "drawing_area_container");
    gtk_widget_set_name(joystick_area,          "joystick_area");

    GdkScreen *screen = gdk_screen_get_default();
    int screen_width  = gdk_screen_get_width(screen);
    int screen_height = gdk_screen_get_height(screen);
    gtk_window_set_default_size(GTK_WINDOW(window), screen_width, screen_height);    
    
    GdkColor white_color, black_color;
    gdk_color_parse("#FFFFFF", &white_color);
    gdk_color_parse("#000000", &black_color);
    gtk_widget_modify_bg(window, GTK_STATE_NORMAL,                 style_mode == STYLE_MODE_DARK ? &black_color : &white_color);
    gtk_widget_modify_bg(drawing_area, GTK_STATE_NORMAL,           style_mode == STYLE_MODE_DARK ? &black_color : &white_color);
    gtk_widget_modify_bg(drawing_area_container, GTK_STATE_NORMAL, style_mode == STYLE_MODE_DARK ? &white_color : &black_color);

    SCALE_FACTOR_A = screen_width < 6 * 160 ? 3 : 6;                     // 160 is the width of the Gameboy screen
    int center_hbox_heigth = SCALE_FACTOR_A * 144 + (2 * SCREEN_BORDER); // 144 is the height of the Gameboy screen
    center_hbox_heigth     = center_hbox_heigth < screen_height / 2 ? screen_height / 2 : center_hbox_heigth;

    gtk_widget_set_size_request(center_hbox, screen_width, center_hbox_heigth);
    gtk_widget_set_size_request(drawing_area, 160 * SCALE_FACTOR_A, 144 * SCALE_FACTOR_A);
    gtk_widget_set_size_request(drawing_area_container, 160 * SCALE_FACTOR_A + SCREEN_BORDER * 2, 144 * SCALE_FACTOR_A + SCREEN_BORDER * 2);

    gtk_widget_set_double_buffered (drawing_area, TRUE);
    
    gtk_widget_set_no_show_all(load_btn, TRUE);
    gtk_widget_set_no_show_all(save_btn, TRUE);

    gtk_widget_show_all(window);

    gtk_widget_hide(load_btn);
    gtk_widget_hide(save_btn);

    g_object_unref(builder);
}

// Main function
int main(int argc, char *argv[]) {

    init_grayscale_lut(contrast, brightness);
    init_bayer16_thresholds();

    fbink_cfg.wfm_mode = WFM_A2;
    fbink_cfg.dithering_mode = HWD_PASSTHROUGH;
    // fbink_cfg.is_verbose = true; 
    fbink_init(fbfd, &fbink_cfg);

    fbink_cfg_refresh.wfm_mode = WFM_AUTO;
    fbink_cfg_refresh.dithering_mode = HWD_PASSTHROUGH;
    fbink_cfg_refresh.is_flashing = true;
    fbink_init(fbfd_refresh, &fbink_cfg_refresh);

    // threading
    g_thread_init(NULL);
    gdk_threads_init();

    // mutexes
    pixbuf_mutex    = g_mutex_new();
    slots_mutex     = g_mutex_new();
    game_loop_mutex = g_mutex_new();

    // queues
    frame_queue     = g_async_queue_new();

    // gtk
    gtk_init(&argc, &argv);

    init_gtk_and_window();

    // Start game loop
    GThread *emulator_thread = g_thread_create(emulator_thread_fn, NULL, FALSE, NULL);
    GThread *touch_thread    = g_thread_create(touch_thread_fn, NULL, FALSE, NULL);    
    GThread *frame_thread    = g_thread_create(frame_thread_loop, NULL, FALSE, NULL);    

    gtk_widget_show_all(window);
    gdk_threads_enter();

    gtk_main();
    gdk_threads_leave();

    audio_backend_deinit(&ab);
    
    // Cleanup
    if (game.data) {
        retro_deinit();
        free((void*)game.data);
    }

    if (pixbuf) g_object_unref(pixbuf);
    if (grayscale_frame_ptr) free(grayscale_frame_ptr);
    g_mutex_free(pixbuf_mutex);
    
    return EXIT_SUCCESS;
}