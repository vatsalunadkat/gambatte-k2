#include <linux/input.h>
#include <fcntl.h>
#include <unistd.h>
#include <glib.h>
#include <gtk/gtk.h>
#include <gdk-pixbuf/gdk-pixbuf.h>
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "libretro.h"
#include "fbink.h"
#include <pthread.h>
// #include <arm_neon.h>
#include "file_picker.h"

static void *core_handle = NULL;

void retro_init(void), retro_deinit(void);
bool retro_load_game(const struct retro_game_info *);
void retro_unload_game(void);
void retro_run(void);
void retro_set_environment(retro_environment_t);
void retro_set_video_refresh(retro_video_refresh_t);
void retro_set_audio_sample_batch(retro_audio_sample_batch_t);
void retro_set_input_poll(retro_input_poll_t);
void retro_set_input_state(retro_input_state_t);
void retro_get_system_av_info(struct retro_system_av_info *);

// GTK widgets
static GtkWidget *window, *border_box, *drawing_area, *joystick_area;
static GtkWidget *gtk_toggle, *fbink_toggle, *options_box;
static int drawing_area_abs_x = 0, drawing_area_abs_y = 0;
static int joystick_area_abs_x = 0, joystick_area_abs_y = 0;
static int frame_width = 0, frame_height = 0;

// Framebuffer/FBInk
int fbfd = FBFD_AUTO, fbfd2 = FBFD_AUTO, fbfd_refresh = FBFD_AUTO;
FBInkConfig fbink_cfg = {0}, fbink_cfg_refresh = {0};

// Mutexes
GMutex *pixbuf_mutex = NULL, *slots_mutex = NULL;

// Buffers
static GdkPixbuf *pixbuf = NULL, *scaled_pixbuf = NULL;

// data arrays
static const uint8_t bayer4[4][4] = {
    {   0, 128,  32, 160 },
    { 192,  64, 224,  96 },
    {  48, 176,  16, 144 },
    { 240, 112, 208,  80 }
};

static uint8_t grayscale_lut[65536] = {0};  // for RGB565 -> RGB888 -> grayscale
static struct retro_game_info game = {0};
// 
typedef struct { uint16_t *data; unsigned width, height; size_t pitch; } FrameJob;
typedef struct { int x, y, w, h, frame_width, frame_height; } DirtyRect;

typedef enum { DRAW_MODE_GTK, DRAW_MODE_FBINK } DrawMode;
static DrawMode draw_mode = DRAW_MODE_GTK;

////// JOYSTICK
typedef struct { float rel_x, rel_y, rel_r; int x, y, r, active; const char *label; } GbButtonRegion;

enum { GB_UP, GB_DOWN, GB_LEFT, GB_RIGHT, GB_A, GB_B, GB_SELECT, GB_START, GB_BUTTON_COUNT };

static GbButtonRegion gb_button_regions[GB_BUTTON_COUNT] = {
//    rel_x  rel_y  rel_r  x   y   r   active label 
    { 0.23,  0.15,  0.08,  0,  0,  0,  0,     "UP"     },
    { 0.23,  0.57,  0.08,  0,  0,  0,  0,     "DOWN"   },
    { 0.11,  0.36,  0.08,  0,  0,  0,  0,     "LEFT"   },
    { 0.35,  0.36,  0.08,  0,  0,  0,  0,     "RIGHT"  },
    { 0.67,  0.24,  0.08,  0,  0,  0,  0,     "A"      },
    { 0.89,  0.43,  0.08,  0,  0,  0,  0,     "B"      },
    { 0.36,  0.82,  0.07,  0,  0,  0,  0,     "SELECT" },
    { 0.69,  0.82,  0.07,  0,  0,  0,  0,     "START"  }
};

#define MAX_TOUCHES 2
typedef struct { int active; int x, y; } TouchSlot;
static TouchSlot slots[MAX_TOUCHES];
///////


typedef struct {
    const char *label;
    int factor_a, factor_b;
    GtkWidget *btn;
} SizeQualityOption;

enum { SQ_A1, SQ_A2, SQ_B1, SQ_B2, SQ_B3, SQ_C1, SQ_D1, SQ_D2, SQ_D3, SQ_COUNT };

static SizeQualityOption size_quality_btns[SQ_COUNT] = {
//  size 1
//  {"--", 1, 1, NULL}, // quality 1: SCALE_FACTOR_A 1 x SCALE_FACTOR_B 1 // (ignore)

//  size 2
//  {"--", 1, 2, NULL}, // quality 1: SCALE_FACTOR_A 1 x SCALE_FACTOR_B 2 // (ignore)
//  {"--", 2, 1, NULL}, // quality 2: SCALE_FACTOR_A 2 x SCALE_FACTOR_B 1 // (ignore)
    
//  size 3
    {"1A", 1, 3, NULL}, // quality 1: SCALE_FACTOR_A 1 x SCALE_FACTOR_B 3
    {"1B", 3, 1, NULL}, // quality 2: SCALE_FACTOR_A 3 x SCALE_FACTOR_B 1
//  size 4
    {"2A", 1, 4, NULL}, // quality 1: SCALE_FACTOR_A 1 x SCALE_FACTOR_B 4
    {"2B", 2, 2, NULL}, // quality 2: SCALE_FACTOR_A 2 x SCALE_FACTOR_B 2
    {"2C", 4, 1, NULL}, // quality 3: SCALE_FACTOR_A 4 x SCALE_FACTOR_B 1
//  size 5
//  {"--", 1, 5, NULL}, // quality 1: SCALE_FACTOR_A 1 x SCALE_FACTOR_B 5 // (ignore)
    {"3A", 5, 1, NULL}, // quality 2: SCALE_FACTOR_A 5 x SCALE_FACTOR_B 1
//  size 6
//  {"--", 1, 6, NULL}, // quality 1: SCALE_FACTOR_A 1 x SCALE_FACTOR_B 6 // (ignore)
    {"4A", 2, 3, NULL}, // quality 2: SCALE_FACTOR_A 2 x SCALE_FACTOR_B 3
    {"4B", 3, 2, NULL}, // quality 3: SCALE_FACTOR_A 3 x SCALE_FACTOR_B 2
    {"4C", 6, 1, NULL}  // quality 4: SCALE_FACTOR_A 6 x SCALE_FACTOR_B 1
};

// Global state
static gboolean running = TRUE;
static gboolean ready = FALSE;
static int TARGET_FPS = 20;

static gchar *core_path = NULL;

static float brightness = 0; // TODO settings on gui
static float contrast = 1.5;

static int SCALE_FACTOR_A = 3;
static int SCALE_FACTOR_B = 1;

static int SCREEN_BORDER = 5; // px

static int kill_the_ghost = 1;

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

static gpointer touch_thread(gpointer data) {

    const char *touch_path = detect_touch_device();
    int fd = open(touch_path, O_RDONLY);
    if (fd < 0) { perror("open"); return NULL; }

    struct input_event ev;
    int current_slot = 0;

    while (1) {
        ssize_t n = read(fd, &ev, sizeof(ev));
        if (n != sizeof(ev)) continue;
        if (ev.type == EV_ABS) {
            switch (ev.code) {
                case ABS_MT_SLOT:
                    current_slot = ev.value;
                    break;
                case ABS_MT_TRACKING_ID:
                    g_mutex_lock(slots_mutex);
                    slots[current_slot].active = (ev.value != -1);
                    g_mutex_unlock(slots_mutex);
                    break;
                case ABS_MT_POSITION_X:
                    g_mutex_lock(slots_mutex);
                    slots[current_slot].x = ev.value;
                    // fprintf(stdout, "Touch slot %d: x=%d\n", current_slot, ev.value);
                    g_mutex_unlock(slots_mutex);
                    break;
                case ABS_MT_POSITION_Y:
                    g_mutex_lock(slots_mutex);
                    slots[current_slot].y = ev.value;
                    // fprintf(stdout, "Touch slot %d: y=%d\n", current_slot, ev.value);
                    g_mutex_unlock(slots_mutex);
                    break;
            }
        }
        if (ev.type == EV_SYN) {
            //
        }
    }
    close(fd);
    return NULL;
}

static void on_drawing_area_size_allocate(GtkWidget *widget, GdkRectangle *allocation, gpointer user_data) {
    GdkWindow *gdk_win = gtk_widget_get_window(widget);
    if (gdk_win) {
        g_mutex_lock(pixbuf_mutex);
        gdk_window_get_origin(gdk_win, &drawing_area_abs_x, &drawing_area_abs_y);
        g_mutex_unlock(pixbuf_mutex);
    }
}

// TODO move to an iddle, bc gets called only once
static void on_joystick_area_size_allocate(GtkWidget *widget, GdkRectangle *allocation, gpointer user_data) {
    
    int w = allocation->width;
    int h = allocation->height;

    fprintf(stdout, "Joystick area size: %dx%d\n", w, h);

    g_mutex_lock(slots_mutex);    
    // scale and position buttons proportionally
    for (int i = 0; i < GB_BUTTON_COUNT; ++i) {
        gb_button_regions[i].x = gb_button_regions[i].rel_x * w;
        gb_button_regions[i].y = gb_button_regions[i].rel_y * h;
        gb_button_regions[i].r = gb_button_regions[i].rel_r * w;
    }
    g_mutex_unlock(slots_mutex);
}

static size_t audio_sample_batch(const int16_t *data, size_t frames) {
    return frames; // bypass audio processing
}

static void refresh_screen(){
    fprintf(stdout, "refresh_screen\n");
    fbink_refresh(fbfd_refresh, 0, 0, 0, 0, &fbink_cfg_refresh);
}

static gboolean expose_event(GtkWidget * widget, GdkEventExpose *event, gpointer data) {
    if (!pixbuf) return FALSE;
    g_mutex_lock(pixbuf_mutex);
    cairo_t *cr = gdk_cairo_create(widget->window);
    gdk_cairo_set_source_pixbuf(cr, pixbuf, SCREEN_BORDER, SCREEN_BORDER);
    cairo_paint(cr);
    cairo_destroy(cr);

    if (kill_the_ghost) {
        refresh_screen();
        kill_the_ghost = 0;
    }
    g_mutex_unlock(pixbuf_mutex);
    return (FALSE);
}

static gboolean gb_controls_draw(GtkWidget * widget, GdkEventExpose *event, gpointer data) {
    // Draw Gameboy background
    fprintf(stdout, "gb_controls_draw\n");

    GtkAllocation alloc;
    gtk_widget_get_allocation(widget, &alloc);
    int width = alloc.width;
    int height = alloc.height;    

    cairo_t *cr = gdk_cairo_create(widget->window);
    cairo_set_source_rgb(cr, 255, 255, 255); // light gray
    cairo_paint(cr);

    // Draw buttons
    for (int i = 0; i < GB_BUTTON_COUNT; ++i) {
        GbButtonRegion *btn = &gb_button_regions[i]; // TODO thread safety.
        // if (gb_buttons[i])  // we could highlight the button if pressed but slows down the refreshing
        cairo_new_path(cr);
        cairo_set_source_rgb(cr, 255, 255, 255);
        cairo_arc(cr, btn->x, btn->y, btn->r, 0, 2*M_PI);
        cairo_fill_preserve(cr);

        cairo_set_source_rgb(cr, 0, 0, 0); // black border
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

static gboolean queue_draw_area_v2(gpointer user_data) {
    DirtyRect *rect = (DirtyRect *)user_data;

    g_mutex_lock(pixbuf_mutex);
    // gtk draw mode
    if (draw_mode == DRAW_MODE_GTK && kill_the_ghost) {
        gtk_widget_queue_draw(drawing_area);
        // reset the flag on expose event
    } else if (draw_mode == DRAW_MODE_GTK) {
        gtk_widget_queue_draw_area(drawing_area, rect->x + SCREEN_BORDER, rect->y + SCREEN_BORDER, rect->w, rect->h);
    // fbink mode
    } else if (draw_mode == DRAW_MODE_FBINK) {
        guchar *pixels = gdk_pixbuf_get_pixels(pixbuf);
        int width  = gdk_pixbuf_get_width(pixbuf); // TODO remove
        int height = gdk_pixbuf_get_height(pixbuf); // TODO remove
        int rowstride = gdk_pixbuf_get_rowstride(pixbuf); // TODO remove
        int ret = fbink_print_raw_data(
            fbfd,
            pixels,
            width,
            height,
            rowstride * height,
            drawing_area_abs_x + SCREEN_BORDER, // x_off
            drawing_area_abs_y + SCREEN_BORDER, // y_off
            &fbink_cfg
        );

        if (ret < 0)
            fprintf(stderr, "fbink_print_raw_data failed: %d\n", ret);

        if (kill_the_ghost) {
            fprintf(stdout, "refresh screen on queue\n");
            fbink_refresh(fbfd_refresh, 0, 0, 0, 0, &fbink_cfg_refresh);
            kill_the_ghost = 0;
        }

        // drawing_area_abs_y + SCREEN_BORDER + rect->y,
        // drawing_area_abs_x + SCREEN_BORDER + rect->x,
        // rect->w,
        // rect->h,
        // TODO refresh only the damaged section (doing it with fbink_print_raw_data behaves strangely / new fbink version fixed that)

    }
    g_mutex_unlock(pixbuf_mutex);
    
    free(rect);
    return FALSE;
}

// move this inside the function
static void ensure_pixbuf(int width, int height) {
    if (pixbuf && (frame_width != width || frame_height != height)) {
        g_object_unref(pixbuf);
        pixbuf = NULL;
    }
    if (!pixbuf) {
        frame_width = width;
        frame_height = height;
        pixbuf = gdk_pixbuf_new(
            GDK_COLORSPACE_RGB, FALSE, 8,
            width, height);
        fprintf(stdout, "ensure_pixbuf: created new pixbuf %dx%d\n", width, height);
        gtk_widget_set_size_request(drawing_area, width + SCREEN_BORDER * 2, height + SCREEN_BORDER * 2); // move this out
        kill_the_ghost = 1; // we are already on pixbuf_mutex lock 
    }
}

static gpointer process_frame_job_drawing_area_version(gpointer user_data) {
    FrameJob *job = user_data;
    
    static int skipped_frame_fps_count;
    static int skipped_frame_mutex_count;
    
    static struct timespec last_frame_time = {0, 0};
    const double max_fps = TARGET_FPS;
    const double min_frame_interval = 1.0 / max_fps;

    struct timespec now_time;
    clock_gettime(CLOCK_MONOTONIC, &now_time);
    double elapsed = (now_time.tv_sec - last_frame_time.tv_sec) +
                    (now_time.tv_nsec - last_frame_time.tv_nsec) / 1e9;

    clock_t t = clock(); 
    // --- FPS debug ---
    static int frame_count = 0;
    static time_t last_time = 0;
    time_t now = time(NULL);

    uint16_t *data = job->data;    // Pointer to RGB565 data
    unsigned width = job->width;   // Width of the frame
    unsigned height = job->height; // Height of the frame
    size_t pitch = job->pitch;     // Pitch of the frame data

    double time_taken;

    // acquire the frame slot or skip frame
    if (!g_mutex_trylock(pixbuf_mutex)) {
        skipped_frame_mutex_count++;
        free(job->data);
        free(job);
        return FALSE;
    }

    const uint16_t *src = data;

    int nchan = 3;

    unsigned first_width = width;
    unsigned first_height = height;    

    unsigned second_width = first_width * SCALE_FACTOR_A;
    unsigned second_height = first_height * SCALE_FACTOR_A;

    unsigned third_width = second_width * SCALE_FACTOR_B;
    unsigned third_height = second_height * SCALE_FACTOR_B;    

    uint16_t dirty_count = 0;
    int min_x = third_width, min_y = third_height, max_x = 0, max_y = 0;

    ensure_pixbuf(third_width, third_height);

    guchar *dst = gdk_pixbuf_get_pixels(pixbuf);

    int dst_rs = third_width * nchan;

    // Convert RGB565 to RGB888 | scale1 apply dithering | and scale2
    for (unsigned y = 0; y < second_height; y++) {
        unsigned src_y = y / SCALE_FACTOR_A;
        for (unsigned x = 0; x < second_width; x++) {
            unsigned src_x = x / SCALE_FACTOR_A;
            uint16_t pixel = src[src_y * (pitch / 2) + src_x];

            unsigned dst_idx = ( (y * SCALE_FACTOR_B) * third_width + (x * SCALE_FACTOR_B) ) * 3;

            uint8_t La = grayscale_lut[pixel];

            uint8_t T = bayer4[y & 3][x & 3];
            char bw = (La > T) ? 255 : 0;

            // checking the first channel is enough since its grayscale
            if ( dst[dst_idx + 0] != bw) { 

                dirty_count++;

                for (int i = 0; i < SCALE_FACTOR_B; i++) {
                    dst[dst_idx + i*3 + 0] = bw;
                    dst[dst_idx + i*3 + 1] = bw;
                    dst[dst_idx + i*3 + 2] = bw;
                }

                if (x * SCALE_FACTOR_B < min_x) min_x = x * SCALE_FACTOR_B;
                if (x * SCALE_FACTOR_B > max_x) max_x = x * SCALE_FACTOR_B + SCALE_FACTOR_B - 1;
                if (y * SCALE_FACTOR_B < min_y) min_y = y * SCALE_FACTOR_B;
                if (y * SCALE_FACTOR_B > max_y) max_y = y * SCALE_FACTOR_B + SCALE_FACTOR_B - 1;

            }

        }
        // Replicate the expanded scanline vertically
        guchar *row_start = dst + (y * SCALE_FACTOR_B) * dst_rs;
        for (int i = 1; i < SCALE_FACTOR_B; i++) {
            memcpy(row_start + i * dst_rs, row_start, dst_rs);
        }
    }

    g_mutex_unlock(pixbuf_mutex);

    t = clock() - t; 
    time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds 
    frame_count++;
    if (now > last_time) { // Print FPS every 5 seconds
        fprintf(stdout,"refresh FPS: %d skipped: %d ( fps: %d / mutex: %d)time_taken: %f dirty_count: %d w:%d h:%d\n", frame_count, skipped_frame_fps_count + skipped_frame_mutex_count, skipped_frame_fps_count, skipped_frame_mutex_count, time_taken, dirty_count, third_width, third_height);
        frame_count = skipped_frame_fps_count = skipped_frame_mutex_count = 0;
        last_time = now;
    }    

    if (dirty_count > 0) {
        DirtyRect *rect = malloc(sizeof(DirtyRect));
        rect->frame_width = third_width;
        rect->frame_height = third_height;
        rect->x = min_x;
        rect->y = min_y;
        rect->w = max_x - min_x + 1;
        rect->h = max_y - min_y + 1;
        // new frame ready
        gdk_threads_add_idle(queue_draw_area_v2, rect);
    } else if (kill_the_ghost) { // TODO impprove this
        DirtyRect *rect = malloc(sizeof(DirtyRect));
        gdk_threads_add_idle(queue_draw_area_v2, rect);
    }

    clock_gettime(CLOCK_MONOTONIC, &last_frame_time);

    free(job->data);
    free(job);
    return NULL;
}

static void video_refresh(const void *data, unsigned width, unsigned height, size_t pitch) {
    if (!data) return;

    // Allocate a buffer for the frame
    size_t frame_size = height * pitch;
    uint16_t *frame_copy = malloc(frame_size);
    if (!frame_copy) return;
    memcpy(frame_copy, data, frame_size);

    FrameJob *job = malloc(sizeof(FrameJob));
    job->data = frame_copy;
    job->width = width;
    job->height = height;
    job->pitch = pitch;

    // schedule frame precessing and exit asap to prevent core slow down
    g_thread_create(process_frame_job_drawing_area_version, job, FALSE, NULL);

}

// input callbacks
static void input_poll(void) {}

static int16_t input_state(unsigned port, unsigned device, unsigned index, unsigned id) {
    if (device == RETRO_DEVICE_JOYPAD && port == 0) {        
        // Clear all buttons
        g_mutex_lock(slots_mutex);
        for (int i = 0; i < GB_BUTTON_COUNT; ++i)
            gb_button_regions[i].active = 0;
        
        // For each active touch, set the corresponding button
        // not the most performant way imho but we dont miss touch events, as the other method, I hope.
        for (int s = 0; s < MAX_TOUCHES; ++s) {
            if (!slots[s].active) {
                continue;
            }
            int rel_x = slots[s].x - joystick_area_abs_x;
            int rel_y = slots[s].y - joystick_area_abs_y;                
            for (int i = 0; i < GB_BUTTON_COUNT; ++i) {
                GbButtonRegion *btn = &gb_button_regions[i];

                int cx = btn->x;
                int cy = btn->y;
                int radius = btn->r;

                int dx = rel_x - cx;
                int dy = rel_y - cy;
                // circle equation
                if (dx * dx + dy * dy <= radius * radius) {
                    btn->active = 1;
                }                    
            }
        }
        
        GbButtonRegion gb_button_regions_copy[GB_BUTTON_COUNT];
        memcpy(gb_button_regions_copy, gb_button_regions, sizeof(gb_button_regions));
        g_mutex_unlock(slots_mutex);

        // WHY THIS DOES NOT WORK?! WHY?
        // int16_t value = 0;
        // switch (id) {
        //     case RETRO_DEVICE_ID_JOYPAD_UP:     value = gb_button_regions[GB_UP].active;
        //     case RETRO_DEVICE_ID_JOYPAD_DOWN:   value = gb_button_regions[GB_DOWN].active;
        //     case RETRO_DEVICE_ID_JOYPAD_LEFT:   value = gb_button_regions[GB_LEFT].active;
        //     case RETRO_DEVICE_ID_JOYPAD_RIGHT:  value = gb_button_regions[GB_RIGHT].active;
        //     case RETRO_DEVICE_ID_JOYPAD_A:      value = gb_button_regions[GB_A].active;
        //     case RETRO_DEVICE_ID_JOYPAD_B:      value = gb_button_regions[GB_B].active;
        //     case RETRO_DEVICE_ID_JOYPAD_SELECT: value = gb_button_regions[GB_SELECT].active;
        //     case RETRO_DEVICE_ID_JOYPAD_START:  value = gb_button_regions[GB_START].active;
        // }
        // return value;

        switch (id) {
            case RETRO_DEVICE_ID_JOYPAD_UP:     return gb_button_regions_copy[GB_UP].active;
            case RETRO_DEVICE_ID_JOYPAD_DOWN:   return gb_button_regions_copy[GB_DOWN].active;
            case RETRO_DEVICE_ID_JOYPAD_LEFT:   return gb_button_regions_copy[GB_LEFT].active;
            case RETRO_DEVICE_ID_JOYPAD_RIGHT:  return gb_button_regions_copy[GB_RIGHT].active;
            case RETRO_DEVICE_ID_JOYPAD_A:      return gb_button_regions_copy[GB_A].active;
            case RETRO_DEVICE_ID_JOYPAD_B:      return gb_button_regions_copy[GB_B].active;
            case RETRO_DEVICE_ID_JOYPAD_SELECT: return gb_button_regions_copy[GB_SELECT].active;
            case RETRO_DEVICE_ID_JOYPAD_START:  return gb_button_regions_copy[GB_START].active;
        }
    }
    return 0;
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

        // case RETRO_ENVIRONMENT_GET_SYSTEM_DIRECTORY: {
        //     const char **dir = data;
        //     static const char *system_dir = "./gambatte";
        //     *dir = system_dir;
        //     return true;
        // }
        
        case RETRO_ENVIRONMENT_GET_CAN_DUPE: {
            bool *can_dupe = data;
            *can_dupe = true;
            return true;
        }

        default:
            return false;
    }
}

// Load libretro core dynamically
static bool init_libretro_core(const char *core_path) {
    /*
    core_handle = dlopen(core_path, RTLD_LAZY);

    if (!core_handle) {
        fprintf(stderr, "Failed to load core: %s\n", dlerror());
        return false;
    }

    // retro_init = retro_init; // = dlsym(core_handle, "retro_init");
    // retro_deinit = retro_deinit; // = dlsym(core_handle, "retro_deinit");
    // retro_load_game = retro_load_game; // = dlsym(core_handle, "retro_load_game");
    // retro_unload_game = retro_unload_game; // = dlsym(core_handle, "retro_unload_game");
    // retro_run = retro_run; // = dlsym(core_handle, "retro_run");
    // retro_set_environment = retro_set_environment; // = dlsym(core_handle, "retro_set_environment");
    // retro_set_video_refresh = retro_set_video_refresh; // = dlsym(core_handle, "retro_set_video_refresh");
    // retro_set_audio_sample_batch = retro_set_audio_sample_batch; // = dlsym(core_handle, "retro_set_audio_sample_batch");
    // retro_set_input_poll = retro_set_input_poll; // = dlsym(core_handle, "retro_set_input_poll");
    // retro_set_input_state = retro_set_input_state; // = dlsym(core_handle, "retro_set_input_state");
    // retro_get_system_av_info = retro_get_system_av_info; // = dlsym(core_handle, "retro_get_system_av_info");

    if (!retro_init || !retro_load_game || !retro_run) {
        fprintf(stderr, "Failed to load core symbols\n");
        return false;
    }
    */
    retro_set_environment(environment_cb);
    retro_set_video_refresh(video_refresh);
    retro_set_audio_sample_batch(audio_sample_batch);
    retro_set_input_poll(input_poll);
    retro_set_input_state(input_state);

    fprintf(stdout, "Loaded core symbols\n");

    retro_init();
    return true;
}

static gpointer game_loop(gpointer data) {

    while (running) {
        if (ready)
            retro_run(); // will trigger video_refresh via callback
        g_usleep(16666); // 60 FPS
    }
    return NULL;
}

// GTK button callback to quit
static void on_quit(GtkWidget *widget, gpointer data) {
    running = FALSE; // Signal the thread to stop
    gtk_main_quit();
}

// TODO refactor this 
static void on_open(GtkWidget *widget, gpointer data) {
        fprintf(stderr, "on_open\n");
        ready = FALSE;

        char *game_path = simple_file_chooser_list(GTK_WINDOW(window));
        g_print("Selected: %s\n", game_path);
        if (game_path) {
            g_print("game_path: %s\n", game_path);

            if(game.data) {
                retro_unload_game();
                retro_deinit();
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
                return EXIT_FAILURE;
            }
            fseek(game_file, 0, SEEK_END);
            game.size = ftell(game_file);
            fseek(game_file, 0, SEEK_SET);
            game.data = malloc(game.size);
            fread((void*)game.data, 1, game.size, game_file);
            fclose(game_file);

            if (!retro_load_game(&game)) {
                fprintf(stderr, "Failed to load game\n");
                return EXIT_FAILURE;
            }
            ready = TRUE;
        } else if (game.data) {
            ready = TRUE;
        }

        g_free(game_path);
}


static void on_draw_mode_toggle(GtkToggleButton *button, gpointer user_data) {
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

static gboolean update_joystick_area_abs_pos(gpointer user_data) {
    GdkWindow *gdk_win;

    gdk_win = gtk_widget_get_window(joystick_area);
    if (gdk_win)
        gdk_window_get_origin(gdk_win, &joystick_area_abs_x, &joystick_area_abs_y);

    gdk_win = gtk_widget_get_window(drawing_area);
    if (gdk_win)
        gdk_window_get_origin(gdk_win, &drawing_area_abs_x, &drawing_area_abs_y);

    fprintf(stdout, "Joystick area abs pos: %d %d\n", joystick_area_abs_x, joystick_area_abs_y);
                
    return FALSE;
}

static void on_size_quality_button_clicked(GtkButton *button, gpointer user_data) {

    SizeQualityOption *selected = (SizeQualityOption *)user_data;

    fprintf(stdout, "on_size_quality_button_clicked: %d %d\n", selected->factor_a, selected->factor_b);

    // deactivate all buttons but selected one
    for (int i = 0; i < SQ_COUNT; ++i) {
        if (size_quality_btns[i].btn) {
            g_signal_handlers_block_by_func(G_OBJECT(size_quality_btns[i].btn), G_CALLBACK(on_size_quality_button_clicked), &size_quality_btns[i]);
            gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(size_quality_btns[i].btn), size_quality_btns[i].btn == selected->btn);
            g_signal_handlers_unblock_by_func(G_OBJECT(size_quality_btns[i].btn), G_CALLBACK(on_size_quality_button_clicked), &size_quality_btns[i]);
        }
    }

    // Set the scale factors
    g_mutex_lock(pixbuf_mutex);    
    SCALE_FACTOR_A = selected->factor_a;
    SCALE_FACTOR_B = selected->factor_b;
    kill_the_ghost = 1;
    g_mutex_unlock(pixbuf_mutex); 

    // gtk_widget_set_sensitive(size_quality_btns[i].btn, TRUE);
    // Optionally, trigger a redraw or reinit if needed
    // For example: kill_the_ghost = 1; or force a frame update
}


static void init_gtk_and_window() {

    const char *window_title = "L:A_N:application_ID:gambatte_PC:N_O:URL_DM:PZ";

    const char *rc_style = 
        "style \"slider-style\"\n"
        "{\n"
        "  GtkRange::slider-width = 40\n"
        "}\n"
        "widget_class \"*GtkHScale\" style \"slider-style\"\n";

    gtk_rc_parse_string(rc_style);

    const char *rc_style2 =
        "style \"drawing-area-border\" {\n"
        "  fg[NORMAL] = \"#000000\"\n"
        "  bg[NORMAL] = \"#FFFFFF\"\n"
        "  engine \"pixmap\" {}\n"
        "}\n"
        "widget \"*.drawing-area\" style \"drawing-area-border\"\n";

    gtk_rc_parse_string(rc_style2);    
    
    const char *rc_button_style =
        "style \"custom-button\" {\n"
        "  bg[NORMAL]      = \"#FFFFFF\"\n" 
        "  fg[NORMAL]      = \"#000000\"\n" 
        // "  base[NORMAL]    = \"#0000FF\"\n" 
        // "  text[NORMAL]    = \"#0000FF\"\n"

        "  bg[ACTIVE]      = \"#000000\"\n" 
        "  fg[ACTIVE]      = \"#FFFFFF\"\n" 
        // "  base[ACTIVE]    = \"#FFFFFF\"\n" 
        // "  text[ACTIVE]    = \"#FFFFFF\"\n"

        "  bg[SELECTED]      = \"#FFFF00\"\n" 
        "  fg[SELECTED]      = \"#FF00FF\"\n" 
        // "  base[SELECTED]    = \"#FFFFFF\"\n" 
        // "  text[SELECTED]    = \"#FFFFFF\"\n"         
        "  bg[PRELIGHT]    = \"#FFFFFF\"\n" 
        "  fg[PRELIGHT]    = \"#000000\"\n"
        "  xthickness = 0\n"                
        "  ythickness = 10\n"
        "  font_name = \"Sans Bold 8\"\n"
        "  GtkWidget::focus-line-width = 0\n"
        "  GtkWidget::focus-padding = 0\n"        
        "  engine \"pixmap\" {}\n"
        "}\n"
        "widget_class \"*GtkButton\" style \"custom-button\"\n"
        "widget_class \"*GtkToggleButton\" style \"custom-button\"\n"
        "widget_class \"*GtkLabel\" style \"custom-button\"\n";
    gtk_rc_parse_string(rc_button_style);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    GdkColor white;
    gdk_color_parse("#FFFFFF", &white);
    gtk_widget_modify_bg(window, GTK_STATE_NORMAL, &white);

    gtk_window_set_title(GTK_WINDOW(window), window_title);
    gtk_window_set_resizable(GTK_WINDOW(window), TRUE);

    GdkScreen *screen = gdk_screen_get_default();
    int screen_width = gdk_screen_get_width(screen);
    int screen_height = gdk_screen_get_height(screen);
    gtk_window_set_default_size(GTK_WINDOW(window), screen_width, screen_height);

    int factor_a = screen_width > 6 * 160 ? 6 : screen_width / 160; // 160 is the width of the Gameboy screen
    int center_hbox_heigth = factor_a * 144 + (2 * SCREEN_BORDER);  // 144 is the height of the Gameboy screen

    // center_hbox_heigth = center_hbox_heigth < screen_height / 2 ? center_hbox_heigth : screen_height / 2;

    fprintf(stdout, "on_window_size_allocate: %dx%d --> %d\n", screen_width, screen_height, screen_width - screen_width % 160 );

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *vbox = gtk_vbox_new(FALSE, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    options_box = gtk_hbox_new(TRUE, 2);

    GtkWidget *open_btn = gtk_button_new_with_label("Open");
    g_signal_connect(open_btn, "clicked", G_CALLBACK(on_open), NULL);
    gtk_box_pack_start(GTK_BOX(options_box), open_btn, TRUE, TRUE, 0);


    for (int i = SQ_COUNT - 1; i >= 0; --i) {
        fprintf(stdout, "SQ_COUNT: %d\n",i);
        if( size_quality_btns[i].factor_a * size_quality_btns[i].factor_b <= factor_a &&
            // chose the second last available (faster)
            size_quality_btns[i].factor_b > 1
        ) {
            fprintf(stdout, "found: %d\n",i);
            SCALE_FACTOR_A = size_quality_btns[i].factor_a;
            SCALE_FACTOR_B = size_quality_btns[i].factor_b;
            break; // skip buttons that are not applicable
        }
    }

    // add buton to change size and quality
    for (int i = 0; i < SQ_COUNT; ++i) {
        if( size_quality_btns[i].factor_a * size_quality_btns[i].factor_b > factor_a ) {
            continue; // skip buttons that are not applicable
        }
        size_quality_btns[i].btn = gtk_toggle_button_new_with_label(size_quality_btns[i].label);
        if (size_quality_btns[i].factor_a == SCALE_FACTOR_A && size_quality_btns[i].factor_b == SCALE_FACTOR_B) {
            gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(size_quality_btns[i].btn), TRUE);
        } else {
            gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(size_quality_btns[i].btn), FALSE);
        }
        g_signal_connect(size_quality_btns[i].btn, "clicked", G_CALLBACK(on_size_quality_button_clicked), &size_quality_btns[i]);
        gtk_box_pack_start(GTK_BOX(options_box), size_quality_btns[i].btn, TRUE, TRUE, 0);
    }

    gtk_toggle   = gtk_toggle_button_new_with_label("GTK");
    fbink_toggle = gtk_toggle_button_new_with_label("FBInk");

    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(gtk_toggle), TRUE);

    g_signal_connect(gtk_toggle, "toggled", G_CALLBACK(on_draw_mode_toggle), GINT_TO_POINTER(DRAW_MODE_GTK));
    g_signal_connect(fbink_toggle, "toggled", G_CALLBACK(on_draw_mode_toggle), GINT_TO_POINTER(DRAW_MODE_FBINK));
    
    gtk_box_pack_start(GTK_BOX(options_box), gtk_toggle, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(options_box), fbink_toggle, TRUE, TRUE, 0);

    GtkWidget *quit_button = gtk_button_new_with_label("Quit");
    g_signal_connect(quit_button, "clicked", G_CALLBACK(on_quit), NULL);

    gtk_box_pack_start(GTK_BOX(options_box), quit_button, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), options_box, FALSE, FALSE, 0);

    GtkWidget *center_hbox = gtk_hbox_new(FALSE, 0);

    gtk_widget_set_size_request(center_hbox, screen_width, center_hbox_heigth); // move this to constants
    fprintf(stdout, "center_hbox: %dx%d\n", screen_width, center_hbox_heigth);
    
    // Add a spacer
    GtkWidget *left_spacer = gtk_label_new(NULL);
    gtk_box_pack_start (GTK_BOX(center_hbox), left_spacer, TRUE, TRUE, 0);

    GtkWidget *center_vbox = gtk_vbox_new(FALSE, 0);

    GtkWidget *top_spacer = gtk_label_new(NULL);
    gtk_box_pack_start (GTK_BOX(center_vbox), top_spacer, TRUE, TRUE, 0);

    // Pack the drawing_area inside the event box
    drawing_area = gtk_drawing_area_new();
    g_signal_connect (drawing_area, "expose-event", G_CALLBACK (expose_event), NULL);
    g_signal_connect (drawing_area, "size-allocate", G_CALLBACK(on_drawing_area_size_allocate), NULL);

    GdkColor drawing_area_border_color;
    gdk_color_parse("#000000", &drawing_area_border_color); // Black border
    gtk_widget_modify_bg(drawing_area, GTK_STATE_NORMAL, &drawing_area_border_color);
    gtk_box_pack_start (GTK_BOX(center_vbox), drawing_area, FALSE, FALSE, 0);

    GtkWidget *bottom_spacer = gtk_label_new(NULL);
    gtk_box_pack_start (GTK_BOX(center_vbox), bottom_spacer, TRUE, TRUE, 0);

    gtk_box_pack_start (GTK_BOX(center_hbox), center_vbox, FALSE, FALSE, 0);

    GtkWidget *right_spacer = gtk_label_new(NULL);
    gtk_box_pack_start(GTK_BOX(center_hbox), right_spacer, TRUE, TRUE, 0);

    gtk_box_pack_start(GTK_BOX(vbox), center_hbox, FALSE, FALSE, 0);

    joystick_area = gtk_drawing_area_new();
    gtk_box_pack_start(GTK_BOX(vbox), joystick_area, TRUE, TRUE, 0);
    g_signal_connect(joystick_area, "expose-event", G_CALLBACK(gb_controls_draw), NULL);
    // TODO should we call this on a iddle function as update_joystick_area_abs_pos?
    g_signal_connect(joystick_area, "size-allocate", G_CALLBACK(on_joystick_area_size_allocate), NULL);
}

// Main function
int main(int argc, char *argv[]) {

    fbink_cfg.wfm_mode = WFM_A2;
    fbink_cfg.dithering_mode = HWD_PASSTHROUGH;
    // fbink_cfg.is_verbose = true; 
    fbink_init(fbfd, &fbink_cfg);

    fbink_cfg_refresh.wfm_mode = WFM_AUTO;
    fbink_cfg_refresh.dithering_mode = HWD_PASSTHROUGH;
    fbink_cfg_refresh.is_flashing = true;
    fbink_init(fbfd_refresh, &fbink_cfg_refresh);

    init_grayscale_lut(contrast, brightness);

    // threading
    g_thread_init(NULL);
    gdk_threads_init();

    // mutexes
    pixbuf_mutex = g_mutex_new();
    slots_mutex = g_mutex_new();

    // gtk
    gtk_init(&argc, &argv);

    /*
    char *game_path = NULL; // argv[2]; // filepicker

    if (argc >= 3) {
        game_path = argv[2];
    } else {
        char game_path_buf[1024] = {0};
        if (!file_picker_select_rom(NULL, game_path_buf, sizeof(game_path_buf), ".")) {
            fprintf(stderr, "No ROM selected.\n");
            return EXIT_FAILURE;
        }
        fprintf(stderr, "ROM selected %s\n", game_path_buf);
        game_path = game_path_buf;
    }
    ////// Load game
    struct retro_game_info game = {0};
    FILE *game_file = fopen(game_path, "rb");
    if (!game_file) {
        fprintf(stderr, "Failed to open game file\n");
        return EXIT_FAILURE;
    }
    fseek(game_file, 0, SEEK_END);
    game.size = ftell(game_file);
    fseek(game_file, 0, SEEK_SET);
    game.data = malloc(game.size);
    fread((void*)game.data, 1, game.size, game_file);
    fclose(game_file);

    if (!retro_load_game(&game)) {
        fprintf(stderr, "Failed to load game\n");
        return EXIT_FAILURE;
    }
    ///////
    */

    init_gtk_and_window();

    // Start game loop
    GThread *emulator_thread = g_thread_create(game_loop, NULL, FALSE, NULL);
    GThread *input_thread = g_thread_create(touch_thread, NULL, FALSE, NULL);    

    gtk_widget_show_all(window);
    gdk_threads_enter();
    
    g_idle_add(update_joystick_area_abs_pos, NULL);
    //g_idle_add(on_open, NULL);

    gtk_main();
    gdk_threads_leave();
    
    // Cleanup
    if (game.data) {
        retro_deinit();
        dlclose(core_handle);
        free((void*)game.data);
    }

    if (pixbuf) g_object_unref(pixbuf);
    g_mutex_free(pixbuf_mutex);
    g_mutex_free(slots_mutex);
    
    return EXIT_SUCCESS;
}