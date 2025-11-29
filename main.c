#include <glib.h>
#include <glib-object.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include <gee.h>
#include <float.h>
#include <math.h>
#include <gdk/gdk.h>
#include <glib/gstdio.h>
#include <gio/gio.h>
#include <stdio.h>
#include <sched.h>
#include <pthread.h>


#define TYPE_EMULATOR_UI (emulator_ui_get_type ())
#define EMULATOR_UI(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_EMULATOR_UI, EmulatorUI))
#define EMULATOR_UI_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_EMULATOR_UI, EmulatorUIClass))
#define IS_EMULATOR_UI(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_EMULATOR_UI))
#define IS_EMULATOR_UI_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_EMULATOR_UI))
#define EMULATOR_UI_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_EMULATOR_UI, EmulatorUIClass))

typedef struct _EmulatorUI EmulatorUI;
typedef struct _EmulatorUIClass EmulatorUIClass;
typedef struct _EmulatorUIPrivate EmulatorUIPrivate;

#define TYPE_RETRO_CORE (retro_core_get_type ())
#define RETRO_CORE(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_RETRO_CORE, RetroCore))
#define RETRO_CORE_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_RETRO_CORE, RetroCoreClass))
#define IS_RETRO_CORE(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_RETRO_CORE))
#define IS_RETRO_CORE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_RETRO_CORE))
#define RETRO_CORE_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_RETRO_CORE, RetroCoreClass))

typedef struct _RetroCore RetroCore;
typedef struct _RetroCoreClass RetroCoreClass;

#define EMULATOR_UI_TYPE_CORE_SETTINGS (emulator_ui_core_settings_get_type ())

#define GAME_JOYPAD_TYPE_BUTTON (game_joypad_button_get_type ())
typedef struct _GameJoypadButton GameJoypadButton;

#define RETRO_CORE_TYPE_RETRO_VARIABLE (retro_core_retro_variable_get_type ())
typedef struct _RetroCoreRetroVariable RetroCoreRetroVariable;
typedef struct _EmulatorUICoreSettings EmulatorUICoreSettings;

#define TYPE_GAME_SCREEN (game_screen_get_type ())
#define GAME_SCREEN(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_GAME_SCREEN, GameScreen))
#define GAME_SCREEN_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_GAME_SCREEN, GameScreenClass))
#define IS_GAME_SCREEN(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_GAME_SCREEN))
#define IS_GAME_SCREEN_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_GAME_SCREEN))
#define GAME_SCREEN_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_GAME_SCREEN, GameScreenClass))

typedef struct _GameScreen GameScreen;
typedef struct _GameScreenClass GameScreenClass;

#define TYPE_GAME_JOYPAD (game_joypad_get_type ())
#define GAME_JOYPAD(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_GAME_JOYPAD, GameJoypad))
#define GAME_JOYPAD_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_GAME_JOYPAD, GameJoypadClass))
#define IS_GAME_JOYPAD(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_GAME_JOYPAD))
#define IS_GAME_JOYPAD_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_GAME_JOYPAD))
#define GAME_JOYPAD_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_GAME_JOYPAD, GameJoypadClass))

typedef struct _GameJoypad GameJoypad;
typedef struct _GameJoypadClass GameJoypadClass;

#define TYPE_GAME_SPEAKER (game_speaker_get_type ())
#define GAME_SPEAKER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_GAME_SPEAKER, GameSpeaker))
#define GAME_SPEAKER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_GAME_SPEAKER, GameSpeakerClass))
#define IS_GAME_SPEAKER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_GAME_SPEAKER))
#define IS_GAME_SPEAKER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_GAME_SPEAKER))
#define GAME_SPEAKER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_GAME_SPEAKER, GameSpeakerClass))

typedef struct _GameSpeaker GameSpeaker;
typedef struct _GameSpeakerClass GameSpeakerClass;

#define TYPE_LIPSTICK (lipstick_get_type ())
#define LIPSTICK(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_LIPSTICK, Lipstick))
#define LIPSTICK_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_LIPSTICK, LipstickClass))
#define IS_LIPSTICK(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_LIPSTICK))
#define IS_LIPSTICK_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_LIPSTICK))
#define LIPSTICK_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_LIPSTICK, LipstickClass))

typedef struct _Lipstick Lipstick;
typedef struct _LipstickClass LipstickClass;

#define GAME_SCREEN_TYPE_COMMIT_MODE (game_screen_commit_mode_get_type ())
#define _g_object_unref0(var) ((var == NULL) ? NULL : (var = (g_object_unref (var), NULL)))
#define _g_free0(var) (var = (g_free (var), NULL))
#define _g_key_file_free0(var) ((var == NULL) ? NULL : (var = (g_key_file_free (var), NULL)))
typedef struct _Block1Data Block1Data;
typedef struct _Block2Data Block2Data;
#define _g_error_free0(var) ((var == NULL) ? NULL : (var = (g_error_free (var), NULL)))
typedef struct _GameScreenPrivate GameScreenPrivate;
#define _emulator_ui_core_settings_free0(var) ((var == NULL) ? NULL : (var = (emulator_ui_core_settings_free (var), NULL)))
#define _g_regex_unref0(var) ((var == NULL) ? NULL : (var = (g_regex_unref (var), NULL)))

#define TYPE_INK_ROW_HSCALE (ink_row_hscale_get_type ())
#define INK_ROW_HSCALE(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_INK_ROW_HSCALE, InkRowHScale))
#define INK_ROW_HSCALE_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_INK_ROW_HSCALE, InkRowHScaleClass))
#define IS_INK_ROW_HSCALE(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_INK_ROW_HSCALE))
#define IS_INK_ROW_HSCALE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_INK_ROW_HSCALE))
#define INK_ROW_HSCALE_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_INK_ROW_HSCALE, InkRowHScaleClass))

typedef struct _InkRowHScale InkRowHScale;
typedef struct _InkRowHScaleClass InkRowHScaleClass;

#define TYPE_INK_ROW_TOGGLE_BUTTON (ink_row_toggle_button_get_type ())
#define INK_ROW_TOGGLE_BUTTON(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_INK_ROW_TOGGLE_BUTTON, InkRowToggleButton))
#define INK_ROW_TOGGLE_BUTTON_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_INK_ROW_TOGGLE_BUTTON, InkRowToggleButtonClass))
#define IS_INK_ROW_TOGGLE_BUTTON(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_INK_ROW_TOGGLE_BUTTON))
#define IS_INK_ROW_TOGGLE_BUTTON_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_INK_ROW_TOGGLE_BUTTON))
#define INK_ROW_TOGGLE_BUTTON_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_INK_ROW_TOGGLE_BUTTON, InkRowToggleButtonClass))

typedef struct _InkRowToggleButton InkRowToggleButton;
typedef struct _InkRowToggleButtonClass InkRowToggleButtonClass;

#define TYPE_SIMPLE_FILE_PICKER (simple_file_picker_get_type ())
#define SIMPLE_FILE_PICKER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_SIMPLE_FILE_PICKER, SimpleFilePicker))
#define SIMPLE_FILE_PICKER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_SIMPLE_FILE_PICKER, SimpleFilePickerClass))
#define IS_SIMPLE_FILE_PICKER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_SIMPLE_FILE_PICKER))
#define IS_SIMPLE_FILE_PICKER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_SIMPLE_FILE_PICKER))
#define SIMPLE_FILE_PICKER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_SIMPLE_FILE_PICKER, SimpleFilePickerClass))

typedef struct _SimpleFilePicker SimpleFilePicker;
typedef struct _SimpleFilePickerClass SimpleFilePickerClass;
typedef struct _RetroCorePrivate RetroCorePrivate;

#define RETRO_CORE_TYPE_RETRO_GAME_INFO (retro_core_retro_game_info_get_type ())
typedef struct _RetroCoreRetroGameInfo RetroCoreRetroGameInfo;

#define RETRO_CORE_TYPE_RETRO_SYSTEM_AV_INFO (retro_core_retro_system_av_info_get_type ())

#define RETRO_CORE_TYPE_RETRO_GAME_GEOMETRY (retro_core_retro_game_geometry_get_type ())
typedef struct _RetroCoreRetroGameGeometry RetroCoreRetroGameGeometry;

#define RETRO_CORE_TYPE_RETRO_SYSTEM_TIMING (retro_core_retro_system_timing_get_type ())
typedef struct _RetroCoreRetroSystemTiming RetroCoreRetroSystemTiming;
typedef struct _RetroCoreRetroSystemAvInfo RetroCoreRetroSystemAvInfo;
#define _fclose0(var) ((var == NULL) ? NULL : (var = (fclose (var), NULL)))
typedef struct _Block3Data Block3Data;
#define _g_option_context_free0(var) ((var == NULL) ? NULL : (var = (g_option_context_free (var), NULL)))

typedef enum  {
	EMULATOR_UI_ERROR_ERROR
} EmulatorUIError;
#define EMULATOR_UI_ERROR emulator_ui_error_quark ()
struct _EmulatorUI {
	GtkWindow parent_instance;
	EmulatorUIPrivate * priv;
};

struct _EmulatorUIClass {
	GtkWindowClass parent_class;
};

struct _GameJoypadButton {
	gint id;
	gchar* label;
	gint active;
	gint x;
	gint y;
	gint radius;
	gint width;
	gint height;
	gboolean visible;
};

struct _RetroCoreRetroVariable {
	gchar* key;
	gchar* value;
};

struct _EmulatorUICoreSettings {
	gchar* name;
	GameJoypadButton* joypad_buttons;
	gint joypad_buttons_length1;
	gint _joypad_buttons_size_;
	gchar* path;
	RetroCoreRetroVariable* env;
	gint env_length1;
	gint _env_size_;
};

typedef enum  {
	GAME_SCREEN_COMMIT_MODE_SHM,
	GAME_SCREEN_COMMIT_MODE_FBINK
} GameScreenCommitMode;

struct _EmulatorUIPrivate {
	RetroCore* core;
	gchar* game_path;
	EmulatorUICoreSettings core_settings;
	gboolean ready;
	gboolean running;
	GStaticRecMutex __lock_running;
	gboolean paused;
	GStaticRecMutex __lock_paused;
	GameScreen* gamescreen;
	GameJoypad* gamejoypad;
	GameSpeaker* gamespeaker;
	gint core_width;
	gint core_height;
	GThread* core_thread;
	GeeHashMap* cores_map;
	gint frame_interval_us;
	GKeyFile* kf;
	Lipstick* lipstick;
	gchar* _state_dir;
	gchar* _last_dir;
	gint _contrast;
	gint _brightness;
	gint _max_fps;
	GameScreenCommitMode _render_mode;
	gboolean _fullscreen;
	gboolean _audio;
	guint save_settings_timeout_id;
	gboolean autosave;
	gdouble speed_factor;
	gint _frame_count;
	gint _ticker_count;
	gboolean game_memory_loaded;
};

typedef void (*EmulatorUINotifyGroupCallback) (void* user_data);
struct _Block1Data {
	int _ref_count_;
	EmulatorUI* self;
	guint timer_id;
	EmulatorUINotifyGroupCallback callback;
	gpointer callback_target;
};

struct _Block2Data {
	int _ref_count_;
	EmulatorUI* self;
	GtkBuilder* builder;
};

typedef enum  {
	LIPSTICK_ERROR_ERROR
} LipstickError;
#define LIPSTICK_ERROR lipstick_error_quark ()
struct _GameScreen {
	GObject parent_instance;
	GameScreenPrivate * priv;
	gboolean ready;
	GtkDrawingArea* drawing_area;
	gint x;
	gint y;
	gint base_width;
	gint base_height;
	gint scale;
	guint8* grayscale_frame_ptr;
	gboolean _inverted_colors;
};

struct _GameScreenClass {
	GObjectClass parent_class;
};

typedef void (*SettingsBindSaveCallback) (void* user_data);
typedef gboolean (*LipstickEventCallback) (gconstpointer value, void* user_data);
typedef void (*RetroCoreRetroInit) ();
typedef void (*RetroCoreRetroDeinit) ();
typedef guint (*RetroCoreRetroApiVersion) ();
struct _RetroCoreRetroGameInfo {
	gchar* path;
	guint8* data;
	gint data_length1;
	gsize size;
	gchar* meta;
};

typedef gboolean (*RetroCoreRetroLoadGame) (RetroCoreRetroGameInfo* game_info);
typedef void (*RetroCoreRetroUnloadGame) ();
typedef void (*RetroCoreRetroRun) ();
typedef void (*RetroCoreRetroReset) ();
struct _RetroCoreRetroGameGeometry {
	guint base_width;
	guint base_height;
	guint max_width;
	guint max_height;
	gfloat aspect_ratio;
};

struct _RetroCoreRetroSystemTiming {
	gdouble fps;
	gdouble sample_rate;
};

struct _RetroCoreRetroSystemAvInfo {
	RetroCoreRetroGameGeometry geometry;
	RetroCoreRetroSystemTiming timing;
};

typedef void (*RetroCoreRetroGetSystemAvInfo) (RetroCoreRetroSystemAvInfo* info);
typedef void* (*RetroCoreRetroGetMemoryData) (guint id);
typedef gsize (*RetroCoreRetroGetMemorySize) (guint id);
typedef gsize (*RetroCoreRetroSerializeSize) ();
typedef gsize (*RetroCoreRetroSerialize) (void* data, gsize size);
typedef gsize (*RetroCoreRetroUnserialize) (void* data, gsize size);
struct _RetroCore {
	GObject parent_instance;
	RetroCorePrivate * priv;
	gboolean loaded;
	RetroCoreRetroInit retro_init;
	RetroCoreRetroDeinit retro_deinit;
	RetroCoreRetroApiVersion retro_api_version;
	RetroCoreRetroLoadGame retro_load_game;
	RetroCoreRetroUnloadGame retro_unload_game;
	RetroCoreRetroRun retro_run;
	RetroCoreRetroReset retro_reset;
	RetroCoreRetroGetSystemAvInfo retro_get_system_av_info;
	RetroCoreRetroGetMemoryData retro_get_memory_data;
	RetroCoreRetroGetMemorySize retro_get_memory_size;
	RetroCoreRetroSerializeSize retro_serialize_size;
	RetroCoreRetroSerialize retro_serialize;
	RetroCoreRetroUnserialize retro_unserialize;
	gchar* game_checksum;
};

struct _RetroCoreClass {
	GObjectClass parent_class;
};

struct _Block3Data {
	int _ref_count_;
	EmulatorUI* self;
	gdouble scaling;
};

typedef void (*RetroCoreRetroVideoRefreshT) (void* data, guint width, guint height, gsize pitch);
typedef gsize (*RetroCoreRetroAudioSampleBatchT) (void* data, gsize frames);
typedef void (*RetroCoreRetroInputPollT) ();
typedef gint16 (*RetroCoreRetroInputStateT) (guint port, guint device, guint index, guint id);
typedef enum  {
	PLUGIN_ERROR_SYMBOL_NOT_FOUND
} PluginError;
#define PLUGIN_ERROR plugin_error_quark ()

static gpointer emulator_ui_parent_class = NULL;
static EmulatorUI* emulator_ui_self;
static EmulatorUI* emulator_ui_self = NULL;
static gchar* emulator_ui_config_file;
static gchar* emulator_ui_config_file = NULL;
static gchar* emulator_ui_exe_dir;
static gchar* emulator_ui_exe_dir = NULL;

GQuark emulator_ui_error_quark (void);
gchar* realpath (const gchar* path, gchar* resolved_path);
GType emulator_ui_get_type (void) G_GNUC_CONST;
GType retro_core_get_type (void) G_GNUC_CONST;
static GType emulator_ui_core_settings_get_type (void) G_GNUC_CONST G_GNUC_UNUSED;
GType game_joypad_button_get_type (void) G_GNUC_CONST;
GameJoypadButton* game_joypad_button_dup (const GameJoypadButton* self);
void game_joypad_button_free (GameJoypadButton* self);
void game_joypad_button_copy (const GameJoypadButton* self, GameJoypadButton* dest);
void game_joypad_button_destroy (GameJoypadButton* self);
GType retro_core_retro_variable_get_type (void) G_GNUC_CONST;
RetroCoreRetroVariable* retro_core_retro_variable_dup (const RetroCoreRetroVariable* self);
void retro_core_retro_variable_free (RetroCoreRetroVariable* self);
void retro_core_retro_variable_copy (const RetroCoreRetroVariable* self, RetroCoreRetroVariable* dest);
void retro_core_retro_variable_destroy (RetroCoreRetroVariable* self);
static EmulatorUICoreSettings* emulator_ui_core_settings_dup (const EmulatorUICoreSettings* self);
static void emulator_ui_core_settings_free (EmulatorUICoreSettings* self);
static void emulator_ui_core_settings_copy (const EmulatorUICoreSettings* self, EmulatorUICoreSettings* dest);
static void emulator_ui_core_settings_destroy (EmulatorUICoreSettings* self);
GType game_screen_get_type (void) G_GNUC_CONST;
GType game_joypad_get_type (void) G_GNUC_CONST;
GType game_speaker_get_type (void) G_GNUC_CONST;
GType lipstick_get_type (void) G_GNUC_CONST;
GType game_screen_commit_mode_get_type (void) G_GNUC_CONST;
#define EMULATOR_UI_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), TYPE_EMULATOR_UI, EmulatorUIPrivate))
enum  {
	EMULATOR_UI_DUMMY_PROPERTY,
	EMULATOR_UI_DARK_MODE,
	EMULATOR_UI_STATE_DIR,
	EMULATOR_UI_LAST_DIR,
	EMULATOR_UI_CONTRAST,
	EMULATOR_UI_BRIGHTNESS,
	EMULATOR_UI_MAX_FPS,
	EMULATOR_UI_RENDER_MODE,
	EMULATOR_UI_FULLSCREEN,
	EMULATOR_UI_AUDIO,
	EMULATOR_UI_FRAME_COUNT,
	EMULATOR_UI_TICKER_COUNT
};
static void emulator_ui_notify_group (EmulatorUI* self, gchar** prop_list, int prop_list_length1, EmulatorUINotifyGroupCallback callback, void* callback_target);
static Block1Data* block1_data_ref (Block1Data* _data1_);
static void block1_data_unref (void * _userdata_);
static void ____lambda8_ (Block1Data* _data1_, GObject* s, GParamSpec* p);
static gboolean __lambda9_ (Block1Data* _data1_);
static gboolean ___lambda9__gsource_func (gpointer self);
static void _____lambda8__g_object_notify (GObject* _sender, GParamSpec* pspec, gpointer self);
EmulatorUI* emulator_ui_new (GError** error);
EmulatorUI* emulator_ui_construct (GType object_type, GError** error);
static Block2Data* block2_data_ref (Block2Data* _data2_);
static void block2_data_unref (void * _userdata_);
static void __lambda10_ (EmulatorUI* self);
static void _vala_array_add1 (gchar*** array, int* length, int* size, gchar* value);
gboolean emulator_ui_get_fullscreen (EmulatorUI* self);
static void _vala_array_add2 (gchar*** array, int* length, int* size, gchar* value);
static void ___lambda10__emulator_ui_notify_group_callback (gpointer self);
#define main_ui "\n" \
"\n" \
"<interface>\n" \
"    <object class=\"GtkVBox\" id=\"main_vbox\">\n" \
"        <property name=\"name\">main-vbox-dark</property>\n" \
"        <property name=\"border_width\">0</property>\n" \
"        <child>\n" \
"            <object class=\"GtkHButtonBox\" id=\"hbuttonbox1\">\n" \
"                <property name=\"layout_style\">center</property>\n" \
"\n" \
"                <child>\n" \
"                    <object class=\"GtkButton\" id=\"open_button\">\n" \
"                        <property name=\"label\" translatable=\"yes\">" \
"Open Game</property>\n" \
"                    </object>\n" \
"                    <packing>\n" \
"                        <property name=\"expand\">False</property>\n" \
"                        <property name=\"fill\">False</property>\n" \
"                    </packing>\n" \
"                </child>\n" \
"\n" \
"                <!--\n" \
"                <child>\n" \
"                    <object class=\"GtkButton\" id=\"load_button\">\n" \
"                        <property name=\"label\" translatable=\"yes\">" \
"Load</property>\n" \
"                    </object>\n" \
"                    <packing>\n" \
"                        <property name=\"expand\">False</property>\n" \
"                        <property name=\"fill\">False</property>\n" \
"                    </packing>\n" \
"                </child>\n" \
"                \n" \
"                <child>\n" \
"                    <object class=\"GtkButton\" id=\"save_button\">\n" \
"                        <property name=\"label\" translatable=\"yes\">" \
"Save</property>\n" \
"                    </object>\n" \
"                    <packing>\n" \
"                        <property name=\"expand\">False</property>\n" \
"                        <property name=\"fill\">False</property>\n" \
"                    </packing>\n" \
"                </child>\n" \
"                -->\n" \
"\n" \
"                <child>\n" \
"                    <object class=\"GtkToggleButton\" id=\"options_but" \
"ton\">\n" \
"                        <property name=\"label\" translatable=\"yes\">" \
"Options</property>\n" \
"                    </object>\n" \
"                    <packing>\n" \
"                        <property name=\"expand\">False</property>\n" \
"                        <property name=\"fill\">False</property>\n" \
"                    </packing>\n" \
"                </child>\n" \
"\n" \
"                <child>\n" \
"                    <object class=\"GtkToggleButton\" id=\"fullscreen_" \
"toggle\">\n" \
"                        <property name=\"label\" translatable=\"yes\">" \
"Fullscreen</property>\n" \
"                    </object>\n" \
"                    <packing>\n" \
"                        <property name=\"expand\">False</property>\n" \
"                        <property name=\"fill\">False</property>\n" \
"                    </packing>\n" \
"                </child>\n" \
"\n" \
"                <child>\n" \
"                    <object class=\"GtkButton\" id=\"quit_button\">\n" \
"                        <property name=\"label\" translatable=\"yes\">" \
"Quit</property>\n" \
"                    </object>\n" \
"                    <packing>\n" \
"                        <property name=\"expand\">False</property>\n" \
"                        <property name=\"fill\">False</property>\n" \
"                    </packing>\n" \
"                </child>\n" \
"\n" \
"                <child>\n" \
"                    <placeholder />\n" \
"                </child>\n" \
"\n" \
"            </object>\n" \
"            <packing>\n" \
"                <property name=\"expand\">False</property>\n" \
"                <property name=\"fill\">False</property>\n" \
"            </packing>\n" \
"        </child>\n" \
"        <child>\n" \
"            <object class=\"GtkLabel\" id=\"label_spacer_1\">\n" \
"                <property name=\"height_request\">10</property>\n" \
"                <property name=\"label\"></property>\n" \
"            </object>\n" \
"            <packing>\n" \
"                <property name=\"expand\">False</property>\n" \
"                <property name=\"fill\">False</property>\n" \
"            </packing>\n" \
"        </child>\n" \
"        <child>\n" \
"            <object class=\"GtkHBox\" id=\"hbox3\">\n" \
"\n" \
"                <child>\n" \
"                    <object class=\"GtkLabel\" id=\"label1\">\n" \
"                        <property name=\"visible\">True</property>\n" \
"                        <property name=\"can_focus\">False</property>\n" \
"                        <property name=\"label\"></property>\n" \
"                    </object>\n" \
"                    <packing>\n" \
"                        <property name=\"expand\">True</property>\n" \
"                        <property name=\"fill\">True</property>\n" \
"                        <property name=\"position\">0</property>\n" \
"                    </packing>\n" \
"                </child>\n" \
"\n" \
"                <child>\n" \
"                    <object class=\"GtkEventBox\" id=\"drawing_area_co" \
"ntainer\">\n" \
"                        <property name=\"name\">drawing-area-container" \
"</property>\n" \
"                        <child>\n" \
"                            <object class=\"GtkVBox\" id=\"vbox2\">\n" \
"                                <child>\n" \
"                                    <object class=\"GtkLabel\" id=\"to" \
"p_border\">\n" \
"                                        <property name=\"height_reques" \
"t\">5</property>\n" \
"                                    </object>\n" \
"                                    <packing>\n" \
"                                    </packing>\n" \
"                                </child>\n" \
"                                <child>\n" \
"                                    <object class=\"GtkHBox\" id=\"hbo" \
"x4\">\n" \
"                                        <child>\n" \
"                                            <object class=\"GtkLabel\"" \
" id=\"left_border\">\n" \
"                                                <property name=\"width" \
"_request\">5</property>\n" \
"                                            </object>\n" \
"                                            <packing>\n" \
"                                            </packing>\n" \
"                                        </child>\n" \
"                                        <child>\n" \
"                                            <object class=\"GtkDrawing" \
"Area\" id=\"drawing_area\">\n" \
"                                                <property name=\"name\"" \
">drawing-area</property>\n" \
"                                                <property name=\"width" \
"_request\">1</property>\n" \
"                                                <property name=\"heigh" \
"t_request\">1</property>\n" \
"                                            </object>\n" \
"                                            <packing>\n" \
"                                            </packing>\n" \
"                                        </child>\n" \
"                                        <child>\n" \
"                                            <object class=\"GtkLabel\"" \
" id=\"right_border\">\n" \
"                                                <property name=\"width" \
"_request\">5</property>\n" \
"                                            </object>\n" \
"                                            <packing>\n" \
"                                            </packing>\n" \
"                                        </child>\n" \
"                                    </object>\n" \
"                                    <packing>\n" \
"                                    </packing>\n" \
"                                </child>\n" \
"                                <child>\n" \
"                                    <object class=\"GtkLabel\" id=\"bo" \
"ttom_border\">\n" \
"                                        <property name=\"height_reques" \
"t\">5</property>\n" \
"                                    </object>\n" \
"                                    <packing>\n" \
"                                    </packing>\n" \
"                                </child>\n" \
"                            </object>\n" \
"                        </child>\n" \
"                    </object>\n" \
"                    <packing>\n" \
"                        <property name=\"expand\">False</property>\n" \
"                        <property name=\"fill\">False</property>\n" \
"                    </packing>\n" \
"                </child>\n" \
"\n" \
"                <child>\n" \
"                    <object class=\"GtkHBox\" id=\"hbox2\">\n" \
"                        <property name=\"visible\">True</property>\n" \
"                        <property name=\"can_focus\">False</property>\n" \
"\n" \
"                    </object>\n" \
"                    <packing>\n" \
"                        <property name=\"expand\">True</property>\n" \
"                        <property name=\"fill\">False</property>\n" \
"                    </packing>\n" \
"                </child>\n" \
"\n" \
"\n" \
"            </object>\n" \
"            <packing>\n" \
"                <property name=\"expand\">False</property>\n" \
"                <property name=\"fill\">False</property>\n" \
"            </packing>\n" \
"        </child>\n" \
"        <child>\n" \
"            <object class=\"GtkLabel\" id=\"label_spacer_2\">\n" \
"                <property name=\"height_request\">10</property>\n" \
"                <property name=\"label\"></property>\n" \
"            </object>\n" \
"            <packing>\n" \
"                <property name=\"expand\">False</property>\n" \
"                <property name=\"fill\">False</property>\n" \
"            </packing>\n" \
"        </child>\n" \
"\n" \
"\n" \
"        <child>\n" \
"            <object class=\"GtkNotebook\" id=\"notebook\">\n" \
"\n" \
"                <property name=\"visible\">True</property>\n" \
"                <property name=\"can_focus\">False</property>\n" \
"                <property name=\"show_tabs\">False</property>\n" \
"                <property name=\"show_border\">False</property>\n" \
"\n" \
"                <child>\n" \
"                    <object class=\"GtkDrawingArea\" id=\"joystick_are" \
"a\">\n" \
"                        <property name=\"name\">joystick-area</propert" \
"y>\n" \
"                    </object>\n" \
"                </child>\n" \
"\n" \
"                <child type=\"tab\">\n" \
"                    <placeholder />\n" \
"                </child>\n" \
"\n" \
"                <child>\n" \
"                    <object class=\"InkScrolledWindow\" id=\"scrolledw" \
"indow2\">\n" \
"\n" \
"                        <child>\n" \
"                            <object class=\"InkRowHScale\" id=\"contra" \
"st_scale\">\n" \
"                                <property name=\"label\">Contrast</pro" \
"perty>\n" \
"                                <property name=\"description\">Game br" \
"ightness adjustment.</property>\n" \
"                                <property name=\"digits\">0</property>" \
"\n" \
"                            </object>\n" \
"                        </child>\n" \
"\n" \
"                        <child>\n" \
"                            <object class=\"InkRowHScale\" id=\"bright" \
"ness_scale\">\n" \
"                                <property name=\"label\">Brightness</p" \
"roperty>\n" \
"                                <property name=\"description\">Game br" \
"ightness adjustment</property>\n" \
"                                <property name=\"digits\">0</property>" \
"\n" \
"                            </object>\n" \
"                        </child>\n" \
"\n" \
"                        <child>\n" \
"                            <object class=\"InkRowHScale\" id=\"fps_sc" \
"ale\">\n" \
"                                <property name=\"label\">Max FPS</prop" \
"erty>\n" \
"                                <property name=\"description\">Maximum" \
" number of frames sent to the renderer.</property>\n" \
"                                <property name=\"digits\">0</property>" \
"\n" \
"                            </object>\n" \
"                        </child>\n" \
"\n" \
"                        <child>\n" \
"                            <object class=\"InkRowToggleButton\" id=\"" \
"dark_mode_toggle\">\n" \
"                                <property name=\"label\">Dark mode</pr" \
"operty>\n" \
"                                <property name=\"description\"></prope" \
"rty>\n" \
"                            </object>\n" \
"                        </child>\n" \
"\n" \
"                        <child>\n" \
"                            <object class=\"InkRowToggleButton\" id=\"" \
"render_mode_toggle\">\n" \
"                                <property name=\"label\">FBInk mode</p" \
"roperty>\n" \
"                                <property name=\"description\">Fast re" \
"ndering at the cost of reduced image quality.</property>\n" \
"                            </object>\n" \
"                        </child>\n" \
"\n" \
"                        <child>\n" \
"                            <object class=\"InkRowToggleButton\" id=\"" \
"audio_toggle\">\n" \
"                                <property name=\"label\">Audio</proper" \
"ty>\n" \
"                                <property name=\"description\"></prope" \
"rty>\n" \
"                            </object>\n" \
"                        </child>\n" \
"\n" \
"                    </object>\n" \
"                </child>\n" \
"\n" \
"                <child type=\"tab\">\n" \
"                    <placeholder />\n" \
"                </child>\n" \
"\n" \
"            </object>\n" \
"            <packing>\n" \
"            </packing>\n" \
"        </child>\n" \
"\n" \
"    </object>\n" \
"</interface>\n"
GQuark lipstick_error_quark (void);
Lipstick* lipstick_new (const gchar* service, GError** error);
Lipstick* lipstick_construct (GType object_type, const gchar* service, GError** error);
GameJoypad* game_joypad_new (GtkDrawingArea** da);
GameJoypad* game_joypad_construct (GType object_type, GtkDrawingArea** da);
GameScreen* game_screen_new (GtkDrawingArea** da);
GameScreen* game_screen_construct (GType object_type, GtkDrawingArea** da);
static gboolean __lambda11_ (EmulatorUI* self, GdkEventButton* event);
void game_screen_refresh (GameScreen* self);
static gboolean ___lambda11__gtk_widget_button_press_event (GtkWidget* _sender, GdkEventButton* event, gpointer self);
static void _vala_array_add3 (GameJoypadButton** array, int* length, int* size, const GameJoypadButton* value);
static void _vala_array_add4 (RetroCoreRetroVariable** array, int* length, int* size, const RetroCoreRetroVariable* value);
void settings_bind_bind (GType t_type, GBoxedCopyFunc t_dup_func, GDestroyNotify t_destroy_func, GKeyFile* kf, const gchar* section, const gchar* key, GObject* obj, const gchar* prop, SettingsBindSaveCallback save_cb, void* save_cb_target);
static void __lambda13_ (EmulatorUI* self);
static void emulator_ui_save_settings (EmulatorUI* self);
static void ___lambda13__settings_bind_save_callback (gpointer self);
static void __lambda15_ (EmulatorUI* self);
static void ___lambda15__settings_bind_save_callback (gpointer self);
static void __lambda16_ (EmulatorUI* self);
static void ___lambda16__settings_bind_save_callback (gpointer self);
static void __lambda17_ (EmulatorUI* self);
static void ___lambda17__settings_bind_save_callback (gpointer self);
static void __lambda18_ (EmulatorUI* self);
static void ___lambda18__settings_bind_save_callback (gpointer self);
static void __lambda19_ (EmulatorUI* self);
static void ___lambda19__settings_bind_save_callback (gpointer self);
static void __lambda20_ (EmulatorUI* self);
static void ___lambda20__settings_bind_save_callback (gpointer self);
static void __lambda21_ (EmulatorUI* self);
static void ___lambda21__settings_bind_save_callback (gpointer self);
void emulator_ui_set_render_mode (EmulatorUI* self, GameScreenCommitMode value);
GType ink_row_hscale_get_type (void) G_GNUC_CONST;
void ink_row_hscale_set_lower (InkRowHScale* self, gdouble value);
void ink_row_hscale_set_upper (InkRowHScale* self, gdouble value);
GType ink_row_toggle_button_get_type (void) G_GNUC_CONST;
void emulator_ui_set_dark_mode (EmulatorUI* self, gboolean value);
gchar* lipstick_get_string_property (Lipstick* self, const gchar* service, const gchar* property);
void game_screen_set_inverted_colors (GameScreen* self, gboolean value);
void lipstick_subscribe (Lipstick* self, GType g_type, GBoxedCopyFunc g_dup_func, GDestroyNotify g_destroy_func, const gchar* service, const gchar* name, LipstickEventCallback callback, void* callback_target);
static gboolean ____lambda25_ (EmulatorUI* self, const gchar* str);
static gboolean _____lambda25__lipstick_event_callback (gconstpointer value, gpointer self);
static void ___lambda26_ (EmulatorUI* self);
static void emulator_ui_reload_styles (EmulatorUI* self);
static void ____lambda26__g_object_notify (GObject* _sender, GParamSpec* pspec, gpointer self);
static gboolean __lambda27_ (EmulatorUI* self, GBinding* binding, GValue* srcval, GValue* targetval);
static gboolean ___lambda27__gbinding_transform_func (GBinding* binding, GValue* source_value, GValue* target_value, gpointer self);
static gboolean __lambda28_ (EmulatorUI* self, GBinding* binding, GValue* srcval, GValue* targetval);
static gboolean ___lambda28__gbinding_transform_func (GBinding* binding, GValue* source_value, GValue* target_value, gpointer self);
static void __lambda29_ (EmulatorUI* self);
GameScreenCommitMode emulator_ui_get_render_mode (EmulatorUI* self);
static void ___lambda29__g_object_notify (GObject* _sender, GParamSpec* pspec, gpointer self);
static void __lambda30_ (EmulatorUI* self);
gboolean emulator_ui_get_audio (EmulatorUI* self);
void game_speaker_start (GameSpeaker* self);
void game_speaker_stop (GameSpeaker* self);
static void ___lambda30__g_object_notify (GObject* _sender, GParamSpec* pspec, gpointer self);
static void __lambda31_ (EmulatorUI* self, GObject* sender, GParamSpec* property);
static void ___lambda31__g_object_notify (GObject* _sender, GParamSpec* pspec, gpointer self);
static void __lambda32_ (EmulatorUI* self);
static void ___lambda32__g_object_notify (GObject* _sender, GParamSpec* pspec, gpointer self);
static void __lambda33_ (EmulatorUI* self);
void emulator_ui_pause_game (EmulatorUI* self);
static gboolean __lambda34_ (EmulatorUI* self);
void emulator_ui_resume_game (EmulatorUI* self);
static gboolean ___lambda34__gsource_func (gpointer self);
static void ___lambda33__g_object_notify (GObject* _sender, GParamSpec* pspec, gpointer self);
static void __lambda35_ (Block2Data* _data2_);
static void emulator_ui_stop_game (EmulatorUI* self);
GType simple_file_picker_get_type (void) G_GNUC_CONST;
const gchar* emulator_ui_get_last_dir (EmulatorUI* self);
SimpleFilePicker* simple_file_picker_new (GtkWindow* parent, GeeSet* ext, const gchar* start_dir, GError** error);
SimpleFilePicker* simple_file_picker_construct (GType object_type, GtkWindow* parent, GeeSet* ext, const gchar* start_dir, GError** error);
static void __lambda44_ (EmulatorUI* self, SimpleFilePicker* s, const gchar* filename, const gchar* current_dir);
void emulator_ui_set_last_dir (EmulatorUI* self, const gchar* value);
static void emulator_ui_play_game (EmulatorUI* self);
static void emulator_ui_load_game (EmulatorUI* self);
static void ___lambda44__simple_file_picker_file_selected (SimpleFilePicker* _sender, const gchar* path, const gchar* current_dir, gpointer self);
static void ___lambda35__gtk_button_clicked (GtkButton* _sender, gpointer self);
static void __lambda45_ (Block2Data* _data2_, GtkToggleButton* w);
static void ___lambda45__gtk_toggle_button_toggled (GtkToggleButton* _sender, gpointer self);
static void __lambda46_ (EmulatorUI* self, GtkButton* t);
static void ___lambda46__gtk_button_clicked (GtkButton* _sender, gpointer self);
static void __lambda47_ (EmulatorUI* self, gint w, gint h);
static void emulator_ui_resize_drawing_area_and_buffers (EmulatorUI* self);
static void ___lambda47__emulator_ui_emulator_size (EmulatorUI* _sender, gint width, gint height, gpointer self);
static void __lambda48_ (EmulatorUI* self, GdkRectangle* a);
static void ___lambda48__gtk_widget_size_allocate (GtkWidget* _sender, GdkRectangle* allocation, gpointer self);
static void emulator_ui_load_style_rc_file (EmulatorUI* self);
static void emulator_ui_save_memory (EmulatorUI* self);
GType retro_core_retro_game_info_get_type (void) G_GNUC_CONST;
RetroCoreRetroGameInfo* retro_core_retro_game_info_dup (const RetroCoreRetroGameInfo* self);
void retro_core_retro_game_info_free (RetroCoreRetroGameInfo* self);
void retro_core_retro_game_info_copy (const RetroCoreRetroGameInfo* self, RetroCoreRetroGameInfo* dest);
void retro_core_retro_game_info_destroy (RetroCoreRetroGameInfo* self);
GType retro_core_retro_system_av_info_get_type (void) G_GNUC_CONST;
GType retro_core_retro_game_geometry_get_type (void) G_GNUC_CONST;
RetroCoreRetroGameGeometry* retro_core_retro_game_geometry_dup (const RetroCoreRetroGameGeometry* self);
void retro_core_retro_game_geometry_free (RetroCoreRetroGameGeometry* self);
GType retro_core_retro_system_timing_get_type (void) G_GNUC_CONST;
RetroCoreRetroSystemTiming* retro_core_retro_system_timing_dup (const RetroCoreRetroSystemTiming* self);
void retro_core_retro_system_timing_free (RetroCoreRetroSystemTiming* self);
RetroCoreRetroSystemAvInfo* retro_core_retro_system_av_info_dup (const RetroCoreRetroSystemAvInfo* self);
void retro_core_retro_system_av_info_free (RetroCoreRetroSystemAvInfo* self);
static void emulator_ui_load_memory (EmulatorUI* self);
static gboolean __lambda14_ (EmulatorUI* self);
static gboolean ___lambda14__gsource_func (gpointer self);
gint game_screen_get_width (GameScreen* self);
gint game_screen_get_height (GameScreen* self);
void game_screen_resize (GameScreen* self, gint w, gint h, gint s);
static Block3Data* block3_data_ref (Block3Data* _data3_);
static void block3_data_unref (void * _userdata_);
static gboolean __lambda49_ (Block3Data* _data3_, GMatchInfo* mi, GString* _result_);
static gboolean ___lambda49__gregex_eval_callback (GMatchInfo* match_info, GString* _result_, gpointer self);
void* emulator_ui_core_thread_fn (void);
static gpointer _emulator_ui_core_thread_fn_gthread_func (gpointer self);
void game_screen_start (GameScreen* self);
void game_joypad_start (GameJoypad* self);
void game_screen_stop (GameScreen* self);
void game_joypad_stop (GameJoypad* self);
gint emulator_ui_get_ticker_count (EmulatorUI* self);
void emulator_ui_set_ticker_count (EmulatorUI* self, gint value);
void emulator_ui_video_refresh_cb (void* data, guint width, guint height, gsize pitch);
void game_screen_push_frame (GameScreen* self, void* data, guint width, guint height, gsize pitch);
gsize emulator_ui_audio_sample_batch_cb (void* data, gsize frames);
void game_speaker_push_frame (GameSpeaker* self, void* data, gsize frames);
void emulator_ui_input_poll_cb (void);
gint game_joypad_get_button_state (GameJoypad* self, guint id);
gint16 emulator_ui_input_state_cb (guint port, guint device, guint index, guint id);
void retro_core_unload (RetroCore* self);
static void _emulator_ui_video_refresh_cb_retro_core_retro_video_refresh_t (void* data, guint width, guint height, gsize pitch);
static gsize _emulator_ui_audio_sample_batch_cb_retro_core_retro_audio_sample_batch_t (void* data, gsize frames);
static void _emulator_ui_input_poll_cb_retro_core_retro_input_poll_t (void);
static gint16 _emulator_ui_input_state_cb_retro_core_retro_input_state_t (guint port, guint device, guint index, guint id);
GQuark plugin_error_quark (void);
RetroCore* retro_core_new (const gchar* so_path, const gchar* game_rom_path, RetroCoreRetroVariable* game_env_vars, int game_env_vars_length1, RetroCoreRetroVideoRefreshT video_refresh_cb, RetroCoreRetroAudioSampleBatchT audio_sample_batch_cb, RetroCoreRetroInputPollT input_poll_cb, RetroCoreRetroInputStateT input_state_cb, GError** error);
RetroCore* retro_core_construct (GType object_type, const gchar* so_path, const gchar* game_rom_path, RetroCoreRetroVariable* game_env_vars, int game_env_vars_length1, RetroCoreRetroVideoRefreshT video_refresh_cb, RetroCoreRetroAudioSampleBatchT audio_sample_batch_cb, RetroCoreRetroInputPollT input_poll_cb, RetroCoreRetroInputStateT input_state_cb, GError** error);
void game_joypad_set_buttons (GameJoypad* self, GameJoypadButton* _buttons, int _buttons_length1);
GameSpeaker* game_speaker_new (gint rate, gint channels, gint sampleSize);
GameSpeaker* game_speaker_construct (GType object_type, gint rate, gint channels, gint sampleSize);
gint emulator_ui_main (gchar** args, int args_length1);
static void ___lambda50_ (void);
static void ____lambda50__gtk_object_destroy (GtkObject* _sender, gpointer self);
gboolean emulator_ui_get_dark_mode (EmulatorUI* self);
const gchar* emulator_ui_get_state_dir (EmulatorUI* self);
void emulator_ui_set_state_dir (EmulatorUI* self, const gchar* value);
gint emulator_ui_get_contrast (EmulatorUI* self);
void emulator_ui_set_contrast (EmulatorUI* self, gint value);
gint emulator_ui_get_brightness (EmulatorUI* self);
void emulator_ui_set_brightness (EmulatorUI* self, gint value);
gint emulator_ui_get_max_fps (EmulatorUI* self);
void emulator_ui_set_max_fps (EmulatorUI* self, gint value);
void emulator_ui_set_fullscreen (EmulatorUI* self, gboolean value);
void emulator_ui_set_audio (EmulatorUI* self, gboolean value);
gint emulator_ui_get_frame_count (EmulatorUI* self);
void emulator_ui_set_frame_count (EmulatorUI* self, gint value);
static void g_cclosure_user_marshal_VOID__INT_INT (GClosure * closure, GValue * return_value, guint n_param_values, const GValue * param_values, gpointer invocation_hint, gpointer marshal_data);
static void _vala_GameJoypadButton_array_free (GameJoypadButton* array, gint array_length);
static void _vala_RetroCoreRetroVariable_array_free (RetroCoreRetroVariable* array, gint array_length);
static GameJoypadButton* _vala_array_dup1 (GameJoypadButton* self, int length);
static RetroCoreRetroVariable* _vala_array_dup2 (RetroCoreRetroVariable* self, int length);
static void emulator_ui_finalize (GObject* obj);
static void _vala_emulator_ui_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec);
static void _vala_emulator_ui_set_property (GObject * object, guint property_id, const GValue * value, GParamSpec * pspec);
static void _vala_array_destroy (gpointer array, gint array_length, GDestroyNotify destroy_func);
static void _vala_array_free (gpointer array, gint array_length, GDestroyNotify destroy_func);
static gint _vala_array_length (gpointer array);

static const GOptionEntry EMULATOR_UI_options[2] = {{"config", 'c', 0, G_OPTION_ARG_FILENAME, &emulator_ui_config_file, "Config file", "FILE"}, {NULL}};

GQuark emulator_ui_error_quark (void) {
	return g_quark_from_static_string ("emulator_ui_error-quark");
}


static Block1Data* block1_data_ref (Block1Data* _data1_) {
	g_atomic_int_inc (&_data1_->_ref_count_);
	return _data1_;
}


static void block1_data_unref (void * _userdata_) {
	Block1Data* _data1_;
	_data1_ = (Block1Data*) _userdata_;
	if (g_atomic_int_dec_and_test (&_data1_->_ref_count_)) {
		EmulatorUI* self;
		self = _data1_->self;
		_g_object_unref0 (self);
		g_slice_free (Block1Data, _data1_);
	}
}


static gboolean __lambda9_ (Block1Data* _data1_) {
	EmulatorUI* self;
	gboolean result = FALSE;
	EmulatorUINotifyGroupCallback _tmp0_ = NULL;
	void* _tmp0__target = NULL;
	self = _data1_->self;
	_tmp0_ = _data1_->callback;
	_tmp0__target = _data1_->callback_target;
	_tmp0_ (_tmp0__target);
	_data1_->timer_id = (guint) 0;
	result = FALSE;
	return result;
}


static gboolean ___lambda9__gsource_func (gpointer self) {
	gboolean result;
	result = __lambda9_ (self);
	return result;
}


static void ____lambda8_ (Block1Data* _data1_, GObject* s, GParamSpec* p) {
	EmulatorUI* self;
	guint _tmp0_ = 0U;
	guint _tmp2_ = 0U;
	self = _data1_->self;
	g_return_if_fail (s != NULL);
	g_return_if_fail (p != NULL);
	_tmp0_ = _data1_->timer_id;
	if (_tmp0_ != ((guint) 0)) {
		guint _tmp1_ = 0U;
		_tmp1_ = _data1_->timer_id;
		g_source_remove (_tmp1_);
	}
	_tmp2_ = g_timeout_add_full (G_PRIORITY_DEFAULT, (guint) 10, ___lambda9__gsource_func, block1_data_ref (_data1_), block1_data_unref);
	_data1_->timer_id = _tmp2_;
}


static void _____lambda8__g_object_notify (GObject* _sender, GParamSpec* pspec, gpointer self) {
	____lambda8_ (self, _sender, pspec);
}


static void emulator_ui_notify_group (EmulatorUI* self, gchar** prop_list, int prop_list_length1, EmulatorUINotifyGroupCallback callback, void* callback_target) {
	Block1Data* _data1_;
	EmulatorUINotifyGroupCallback _tmp0_ = NULL;
	void* _tmp0__target = NULL;
	gchar** _tmp1_ = NULL;
	gint _tmp1__length1 = 0;
	EmulatorUINotifyGroupCallback _tmp5_ = NULL;
	void* _tmp5__target = NULL;
	g_return_if_fail (self != NULL);
	_data1_ = g_slice_new0 (Block1Data);
	_data1_->_ref_count_ = 1;
	_data1_->self = g_object_ref (self);
	_tmp0_ = callback;
	_tmp0__target = callback_target;
	_data1_->callback = _tmp0_;
	_data1_->callback_target = _tmp0__target;
	_data1_->timer_id = (guint) 0;
	_tmp1_ = prop_list;
	_tmp1__length1 = prop_list_length1;
	{
		gchar** prop_collection = NULL;
		gint prop_collection_length1 = 0;
		gint _prop_collection_size_ = 0;
		gint prop_it = 0;
		prop_collection = _tmp1_;
		prop_collection_length1 = _tmp1__length1;
		for (prop_it = 0; prop_it < _tmp1__length1; prop_it = prop_it + 1) {
			gchar* _tmp2_ = NULL;
			gchar* prop = NULL;
			_tmp2_ = g_strdup (prop_collection[prop_it]);
			prop = _tmp2_;
			{
				const gchar* _tmp3_ = NULL;
				gchar* _tmp4_ = NULL;
				_tmp3_ = prop;
				_tmp4_ = g_strconcat ("notify::", _tmp3_, NULL);
				g_signal_connect_data ((GObject*) self, _tmp4_, (GCallback) _____lambda8__g_object_notify, block1_data_ref (_data1_), (GClosureNotify) block1_data_unref, 0);
				_g_free0 (_tmp4_);
				_g_free0 (prop);
			}
		}
	}
	_tmp5_ = _data1_->callback;
	_tmp5__target = _data1_->callback_target;
	_tmp5_ (_tmp5__target);
	block1_data_unref (_data1_);
	_data1_ = NULL;
}


static Block2Data* block2_data_ref (Block2Data* _data2_) {
	g_atomic_int_inc (&_data2_->_ref_count_);
	return _data2_;
}


static void block2_data_unref (void * _userdata_) {
	Block2Data* _data2_;
	_data2_ = (Block2Data*) _userdata_;
	if (g_atomic_int_dec_and_test (&_data2_->_ref_count_)) {
		EmulatorUI* self;
		self = _data2_->self;
		_g_object_unref0 (_data2_->builder);
		_g_object_unref0 (self);
		g_slice_free (Block2Data, _data2_);
	}
}


static void _vala_array_add1 (gchar*** array, int* length, int* size, gchar* value) {
	if ((*length) == (*size)) {
		*size = (*size) ? (2 * (*size)) : 4;
		*array = g_renew (gchar*, *array, (*size) + 1);
	}
	(*array)[(*length)++] = value;
	(*array)[*length] = NULL;
}


static void _vala_array_add2 (gchar*** array, int* length, int* size, gchar* value) {
	if ((*length) == (*size)) {
		*size = (*size) ? (2 * (*size)) : 4;
		*array = g_renew (gchar*, *array, (*size) + 1);
	}
	(*array)[(*length)++] = value;
	(*array)[*length] = NULL;
}


static void __lambda10_ (EmulatorUI* self) {
	gchar** param = NULL;
	gchar** _tmp0_ = NULL;
	gint param_length1 = 0;
	gint _param_size_ = 0;
	gchar** _tmp1_ = NULL;
	gint _tmp1__length1 = 0;
	gchar* _tmp2_ = NULL;
	gboolean _tmp3_ = FALSE;
	gchar** _tmp6_ = NULL;
	gint _tmp6__length1 = 0;
	gchar* _tmp7_ = NULL;
	gchar* _tmp8_ = NULL;
	_tmp0_ = g_new0 (gchar*, 0 + 1);
	param = _tmp0_;
	param_length1 = 0;
	_param_size_ = param_length1;
	_tmp1_ = param;
	_tmp1__length1 = param_length1;
	_tmp2_ = g_strdup ("L:A_N:application_ID:gambatte_FS:F_O:URL_DM:PZ_O:U");
	_vala_array_add1 (&param, &param_length1, &_param_size_, _tmp2_);
	_tmp3_ = self->priv->_fullscreen;
	if (_tmp3_) {
		gchar** _tmp4_ = NULL;
		gint _tmp4__length1 = 0;
		gchar* _tmp5_ = NULL;
		_tmp4_ = param;
		_tmp4__length1 = param_length1;
		_tmp5_ = g_strdup ("PC:N");
		_vala_array_add2 (&param, &param_length1, &_param_size_, _tmp5_);
	}
	_tmp6_ = param;
	_tmp6__length1 = param_length1;
	_tmp7_ = g_strjoinv ("_", _tmp6_);
	_tmp8_ = _tmp7_;
	gtk_window_set_title ((GtkWindow*) self, _tmp8_);
	_g_free0 (_tmp8_);
	param = (_vala_array_free (param, param_length1, (GDestroyNotify) g_free), NULL);
}


static void ___lambda10__emulator_ui_notify_group_callback (gpointer self) {
	__lambda10_ ((EmulatorUI*) self);
}


static gpointer _g_object_ref0 (gpointer self) {
	return self ? g_object_ref (self) : NULL;
}


static gboolean __lambda11_ (EmulatorUI* self, GdkEventButton* event) {
	gboolean result = FALSE;
	GError * _inner_error_ = NULL;
	g_return_val_if_fail (event != NULL, FALSE);
	{
		EmulatorUI* _tmp0_ = NULL;
		gboolean _tmp1_ = FALSE;
		_tmp0_ = emulator_ui_self;
		_tmp1_ = _tmp0_->priv->running;
		g_static_rec_mutex_lock (&_tmp0_->priv->__lock_running);
		{
			EmulatorUI* _tmp2_ = NULL;
			gboolean _tmp3_ = FALSE;
			_tmp2_ = emulator_ui_self;
			_tmp3_ = _tmp2_->priv->running;
			if (_tmp3_) {
				GameScreen* _tmp4_ = NULL;
				_tmp4_ = self->priv->gamescreen;
				game_screen_refresh (_tmp4_);
			}
		}
		__finally1:
		{
			EmulatorUI* _tmp5_ = NULL;
			gboolean _tmp6_ = FALSE;
			_tmp5_ = emulator_ui_self;
			_tmp6_ = _tmp5_->priv->running;
			g_static_rec_mutex_unlock (&_tmp5_->priv->__lock_running);
		}
		if (G_UNLIKELY (_inner_error_ != NULL)) {
			g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
			g_clear_error (&_inner_error_);
			return FALSE;
		}
	}
	result = FALSE;
	return result;
}


static gboolean ___lambda11__gtk_widget_button_press_event (GtkWidget* _sender, GdkEventButton* event, gpointer self) {
	gboolean result;
	result = __lambda11_ ((EmulatorUI*) self, event);
	return result;
}


static gchar* string_replace (const gchar* self, const gchar* old, const gchar* replacement) {
	gchar* result = NULL;
	GError * _inner_error_ = NULL;
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (old != NULL, NULL);
	g_return_val_if_fail (replacement != NULL, NULL);
	{
		GRegex* regex = NULL;
		const gchar* _tmp0_ = NULL;
		gchar* _tmp1_ = NULL;
		gchar* _tmp2_ = NULL;
		GRegex* _tmp3_ = NULL;
		GRegex* _tmp4_ = NULL;
		gchar* _tmp5_ = NULL;
		GRegex* _tmp6_ = NULL;
		const gchar* _tmp7_ = NULL;
		gchar* _tmp8_ = NULL;
		gchar* _tmp9_ = NULL;
		_tmp0_ = old;
		_tmp1_ = g_regex_escape_string (_tmp0_, -1);
		_tmp2_ = _tmp1_;
		_tmp3_ = g_regex_new (_tmp2_, 0, 0, &_inner_error_);
		_tmp4_ = _tmp3_;
		_g_free0 (_tmp2_);
		regex = _tmp4_;
		if (G_UNLIKELY (_inner_error_ != NULL)) {
			if (_inner_error_->domain == G_REGEX_ERROR) {
				goto __catch2_g_regex_error;
			}
			g_critical ("file %s: line %d: unexpected error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
			g_clear_error (&_inner_error_);
			return NULL;
		}
		_tmp6_ = regex;
		_tmp7_ = replacement;
		_tmp8_ = g_regex_replace_literal (_tmp6_, self, (gssize) -1, 0, _tmp7_, 0, &_inner_error_);
		_tmp5_ = _tmp8_;
		if (G_UNLIKELY (_inner_error_ != NULL)) {
			_g_regex_unref0 (regex);
			if (_inner_error_->domain == G_REGEX_ERROR) {
				goto __catch2_g_regex_error;
			}
			_g_regex_unref0 (regex);
			g_critical ("file %s: line %d: unexpected error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
			g_clear_error (&_inner_error_);
			return NULL;
		}
		_tmp9_ = _tmp5_;
		_tmp5_ = NULL;
		result = _tmp9_;
		_g_free0 (_tmp5_);
		_g_regex_unref0 (regex);
		return result;
	}
	goto __finally2;
	__catch2_g_regex_error:
	{
		GError* e = NULL;
		e = _inner_error_;
		_inner_error_ = NULL;
		g_assert_not_reached ();
		_g_error_free0 (e);
	}
	__finally2:
	if (G_UNLIKELY (_inner_error_ != NULL)) {
		g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
		g_clear_error (&_inner_error_);
		return NULL;
	}
}


static gboolean bool_parse (const gchar* str) {
	gboolean result = FALSE;
	const gchar* _tmp0_ = NULL;
	g_return_val_if_fail (str != NULL, FALSE);
	_tmp0_ = str;
	if (g_strcmp0 (_tmp0_, "true") == 0) {
		result = TRUE;
		return result;
	} else {
		result = FALSE;
		return result;
	}
}


static void _vala_array_add3 (GameJoypadButton** array, int* length, int* size, const GameJoypadButton* value) {
	if ((*length) == (*size)) {
		*size = (*size) ? (2 * (*size)) : 4;
		*array = g_renew (GameJoypadButton, *array, *size);
	}
	(*array)[(*length)++] = *value;
}


static void _vala_array_add4 (RetroCoreRetroVariable** array, int* length, int* size, const RetroCoreRetroVariable* value) {
	if ((*length) == (*size)) {
		*size = (*size) ? (2 * (*size)) : 4;
		*array = g_renew (RetroCoreRetroVariable, *array, *size);
	}
	(*array)[(*length)++] = *value;
}


static void __lambda13_ (EmulatorUI* self) {
	emulator_ui_save_settings (self);
}


static void ___lambda13__settings_bind_save_callback (gpointer self) {
	__lambda13_ ((EmulatorUI*) self);
}


static void __lambda15_ (EmulatorUI* self) {
	emulator_ui_save_settings (self);
}


static void ___lambda15__settings_bind_save_callback (gpointer self) {
	__lambda15_ ((EmulatorUI*) self);
}


static void __lambda16_ (EmulatorUI* self) {
	emulator_ui_save_settings (self);
}


static void ___lambda16__settings_bind_save_callback (gpointer self) {
	__lambda16_ ((EmulatorUI*) self);
}


static void __lambda17_ (EmulatorUI* self) {
	emulator_ui_save_settings (self);
}


static void ___lambda17__settings_bind_save_callback (gpointer self) {
	__lambda17_ ((EmulatorUI*) self);
}


static void __lambda18_ (EmulatorUI* self) {
	emulator_ui_save_settings (self);
}


static void ___lambda18__settings_bind_save_callback (gpointer self) {
	__lambda18_ ((EmulatorUI*) self);
}


static void __lambda19_ (EmulatorUI* self) {
	emulator_ui_save_settings (self);
}


static void ___lambda19__settings_bind_save_callback (gpointer self) {
	__lambda19_ ((EmulatorUI*) self);
}


static void __lambda20_ (EmulatorUI* self) {
	emulator_ui_save_settings (self);
}


static void ___lambda20__settings_bind_save_callback (gpointer self) {
	__lambda20_ ((EmulatorUI*) self);
}


static void __lambda21_ (EmulatorUI* self) {
	emulator_ui_save_settings (self);
}


static void ___lambda21__settings_bind_save_callback (gpointer self) {
	__lambda21_ ((EmulatorUI*) self);
}


static gchar* string_strip (const gchar* self) {
	gchar* result = NULL;
	gchar* _result_ = NULL;
	gchar* _tmp0_ = NULL;
	const gchar* _tmp1_ = NULL;
	g_return_val_if_fail (self != NULL, NULL);
	_tmp0_ = g_strdup (self);
	_result_ = _tmp0_;
	_tmp1_ = _result_;
	g_strstrip (_tmp1_);
	result = _result_;
	return result;
}


static gboolean ____lambda25_ (EmulatorUI* self, const gchar* str) {
	gboolean result = FALSE;
	GameScreen* _tmp0_ = NULL;
	const gchar* _tmp1_ = NULL;
	g_return_val_if_fail (str != NULL, FALSE);
	_tmp0_ = self->priv->gamescreen;
	_tmp1_ = str;
	game_screen_set_inverted_colors (_tmp0_, g_strcmp0 ("Y8INV", _tmp1_) == 0);
	result = TRUE;
	return result;
}


static gboolean _____lambda25__lipstick_event_callback (gconstpointer value, gpointer self) {
	gboolean result;
	result = ____lambda25_ ((EmulatorUI*) self, (const gchar*) value);
	return result;
}


static void ___lambda26_ (EmulatorUI* self) {
	emulator_ui_reload_styles (self);
}


static void ____lambda26__g_object_notify (GObject* _sender, GParamSpec* pspec, gpointer self) {
	___lambda26_ ((EmulatorUI*) self);
}


static gboolean __lambda27_ (EmulatorUI* self, GBinding* binding, GValue* srcval, GValue* targetval) {
	gboolean result = FALSE;
	gint _tmp0_ = 0;
	g_return_val_if_fail (binding != NULL, FALSE);
	g_return_val_if_fail (srcval != NULL, FALSE);
	g_return_val_if_fail (targetval != NULL, FALSE);
	_tmp0_ = g_value_get_enum (srcval);
	g_value_set_boolean (targetval, ((GameScreenCommitMode) _tmp0_) == GAME_SCREEN_COMMIT_MODE_FBINK);
	result = TRUE;
	return result;
}


static gboolean ___lambda27__gbinding_transform_func (GBinding* binding, GValue* source_value, GValue* target_value, gpointer self) {
	gboolean result;
	result = __lambda27_ ((EmulatorUI*) self, binding, source_value, target_value);
	return result;
}


static gboolean __lambda28_ (EmulatorUI* self, GBinding* binding, GValue* srcval, GValue* targetval) {
	gboolean result = FALSE;
	GameScreenCommitMode _tmp0_ = 0;
	gboolean _tmp1_ = FALSE;
	g_return_val_if_fail (binding != NULL, FALSE);
	g_return_val_if_fail (srcval != NULL, FALSE);
	g_return_val_if_fail (targetval != NULL, FALSE);
	_tmp1_ = g_value_get_boolean (srcval);
	if (_tmp1_) {
		_tmp0_ = GAME_SCREEN_COMMIT_MODE_FBINK;
	} else {
		_tmp0_ = GAME_SCREEN_COMMIT_MODE_SHM;
	}
	g_value_set_enum (targetval, (gint) _tmp0_);
	result = TRUE;
	return result;
}


static gboolean ___lambda28__gbinding_transform_func (GBinding* binding, GValue* source_value, GValue* target_value, gpointer self) {
	gboolean result;
	result = __lambda28_ ((EmulatorUI*) self, binding, source_value, target_value);
	return result;
}


static void __lambda29_ (EmulatorUI* self) {
	GameScreenCommitMode _tmp0_ = 0;
	gboolean fbink_enabled = FALSE;
	GameScreenCommitMode _tmp1_ = 0;
	gboolean _tmp2_ = FALSE;
	GKeyFile* _tmp3_ = NULL;
	gboolean _tmp4_ = FALSE;
	GKeyFile* _tmp5_ = NULL;
	GError * _inner_error_ = NULL;
	_tmp0_ = self->priv->_render_mode;
	g_debug ("main.vala:336: render mode chg %d", (gint) _tmp0_);
	_tmp1_ = self->priv->_render_mode;
	fbink_enabled = _tmp1_ == GAME_SCREEN_COMMIT_MODE_FBINK;
	_tmp3_ = self->priv->kf;
	_tmp4_ = g_key_file_get_boolean (_tmp3_, "General", "fbink_mode", &_inner_error_);
	_tmp2_ = _tmp4_;
	if (G_UNLIKELY (_inner_error_ != NULL)) {
		g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
		g_clear_error (&_inner_error_);
		return;
	}
	if (_tmp2_ == fbink_enabled) {
		return;
	}
	_tmp5_ = self->priv->kf;
	g_key_file_set_boolean (_tmp5_, "General", "fbink_mode", fbink_enabled);
	emulator_ui_save_settings (self);
}


static void ___lambda29__g_object_notify (GObject* _sender, GParamSpec* pspec, gpointer self) {
	__lambda29_ ((EmulatorUI*) self);
}


static void __lambda30_ (EmulatorUI* self) {
	GError * _inner_error_ = NULL;
	{
		gboolean _tmp0_ = FALSE;
		_tmp0_ = self->priv->running;
		g_static_rec_mutex_lock (&self->priv->__lock_running);
		{
			gboolean _tmp1_ = FALSE;
			gboolean _tmp3_ = FALSE;
			_tmp1_ = self->priv->running;
			if (!_tmp1_) {
				{
					gboolean _tmp2_ = FALSE;
					_tmp2_ = self->priv->running;
					g_static_rec_mutex_unlock (&self->priv->__lock_running);
				}
				return;
			}
			_tmp3_ = self->priv->_audio;
			if (_tmp3_) {
				GameSpeaker* _tmp4_ = NULL;
				_tmp4_ = self->priv->gamespeaker;
				game_speaker_start (_tmp4_);
			} else {
				GameSpeaker* _tmp5_ = NULL;
				_tmp5_ = self->priv->gamespeaker;
				game_speaker_stop (_tmp5_);
			}
		}
		__finally5:
		{
			gboolean _tmp6_ = FALSE;
			_tmp6_ = self->priv->running;
			g_static_rec_mutex_unlock (&self->priv->__lock_running);
		}
		if (G_UNLIKELY (_inner_error_ != NULL)) {
			g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
			g_clear_error (&_inner_error_);
			return;
		}
	}
}


static void ___lambda30__g_object_notify (GObject* _sender, GParamSpec* pspec, gpointer self) {
	__lambda30_ ((EmulatorUI*) self);
}


static void __lambda31_ (EmulatorUI* self, GObject* sender, GParamSpec* property) {
	GParamSpec* _tmp0_ = NULL;
	const gchar* _tmp1_ = NULL;
	g_return_if_fail (sender != NULL);
	g_return_if_fail (property != NULL);
	_tmp0_ = property;
	_tmp1_ = _tmp0_->name;
	g_debug ("main.vala:365: Property '%s' changed\n", _tmp1_);
}


static void ___lambda31__g_object_notify (GObject* _sender, GParamSpec* pspec, gpointer self) {
	__lambda31_ ((EmulatorUI*) self, _sender, pspec);
}


static void __lambda32_ (EmulatorUI* self) {
	gint _tmp0_ = 0;
	gboolean _tmp1_ = FALSE;
	gboolean _tmp2_ = FALSE;
	g_object_get ((GtkWindow*) self, "is-active", &_tmp1_, NULL);
	_tmp2_ = _tmp1_;
	if (_tmp2_) {
		_tmp0_ = 1;
	} else {
		_tmp0_ = 0;
	}
	g_debug ("main.vala:369: Property 'is-active' %d\n", _tmp0_);
}


static void ___lambda32__g_object_notify (GObject* _sender, GParamSpec* pspec, gpointer self) {
	__lambda32_ ((EmulatorUI*) self);
}


static gboolean __lambda34_ (EmulatorUI* self) {
	gboolean result = FALSE;
	gboolean _tmp0_ = FALSE;
	gboolean _tmp1_ = FALSE;
	g_object_get ((GtkWindow*) self, "has-toplevel-focus", &_tmp0_, NULL);
	_tmp1_ = _tmp0_;
	if (_tmp1_) {
		emulator_ui_resume_game (self);
	}
	result = FALSE;
	return result;
}


static gboolean ___lambda34__gsource_func (gpointer self) {
	gboolean result;
	result = __lambda34_ ((EmulatorUI*) self);
	return result;
}


static void __lambda33_ (EmulatorUI* self) {
	gint _tmp0_ = 0;
	gboolean _tmp1_ = FALSE;
	gboolean _tmp2_ = FALSE;
	gboolean _tmp3_ = FALSE;
	gboolean _tmp4_ = FALSE;
	g_object_get ((GtkWindow*) self, "has-toplevel-focus", &_tmp1_, NULL);
	_tmp2_ = _tmp1_;
	if (_tmp2_) {
		_tmp0_ = 1;
	} else {
		_tmp0_ = 0;
	}
	g_debug ("main.vala:374: Property 'has-toplevel-focus' %d\n", _tmp0_);
	g_object_get ((GtkWindow*) self, "has-toplevel-focus", &_tmp3_, NULL);
	_tmp4_ = _tmp3_;
	if (!_tmp4_) {
		emulator_ui_pause_game (self);
		return;
	}
	g_timeout_add_full (G_PRIORITY_DEFAULT, (guint) 500, ___lambda34__gsource_func, g_object_ref (self), g_object_unref);
}


static void ___lambda33__g_object_notify (GObject* _sender, GParamSpec* pspec, gpointer self) {
	__lambda33_ ((EmulatorUI*) self);
}


static glong string_strnlen (gchar* str, glong maxlen) {
	glong result = 0L;
	gchar* end = NULL;
	gchar* _tmp0_ = NULL;
	glong _tmp1_ = 0L;
	gchar* _tmp2_ = NULL;
	gchar* _tmp3_ = NULL;
	_tmp0_ = str;
	_tmp1_ = maxlen;
	_tmp2_ = memchr (_tmp0_, 0, (gsize) _tmp1_);
	end = _tmp2_;
	_tmp3_ = end;
	if (_tmp3_ == NULL) {
		glong _tmp4_ = 0L;
		_tmp4_ = maxlen;
		result = _tmp4_;
		return result;
	} else {
		gchar* _tmp5_ = NULL;
		gchar* _tmp6_ = NULL;
		_tmp5_ = end;
		_tmp6_ = str;
		result = (glong) (_tmp5_ - _tmp6_);
		return result;
	}
}


static gchar* string_substring (const gchar* self, glong offset, glong len) {
	gchar* result = NULL;
	glong string_length = 0L;
	gboolean _tmp0_ = FALSE;
	glong _tmp1_ = 0L;
	glong _tmp8_ = 0L;
	glong _tmp14_ = 0L;
	glong _tmp17_ = 0L;
	glong _tmp18_ = 0L;
	glong _tmp19_ = 0L;
	glong _tmp20_ = 0L;
	glong _tmp21_ = 0L;
	gchar* _tmp22_ = NULL;
	g_return_val_if_fail (self != NULL, NULL);
	_tmp1_ = offset;
	if (_tmp1_ >= ((glong) 0)) {
		glong _tmp2_ = 0L;
		_tmp2_ = len;
		_tmp0_ = _tmp2_ >= ((glong) 0);
	} else {
		_tmp0_ = FALSE;
	}
	if (_tmp0_) {
		glong _tmp3_ = 0L;
		glong _tmp4_ = 0L;
		glong _tmp5_ = 0L;
		_tmp3_ = offset;
		_tmp4_ = len;
		_tmp5_ = string_strnlen ((gchar*) self, _tmp3_ + _tmp4_);
		string_length = _tmp5_;
	} else {
		gint _tmp6_ = 0;
		gint _tmp7_ = 0;
		_tmp6_ = strlen (self);
		_tmp7_ = _tmp6_;
		string_length = (glong) _tmp7_;
	}
	_tmp8_ = offset;
	if (_tmp8_ < ((glong) 0)) {
		glong _tmp9_ = 0L;
		glong _tmp10_ = 0L;
		glong _tmp11_ = 0L;
		_tmp9_ = string_length;
		_tmp10_ = offset;
		offset = _tmp9_ + _tmp10_;
		_tmp11_ = offset;
		g_return_val_if_fail (_tmp11_ >= ((glong) 0), NULL);
	} else {
		glong _tmp12_ = 0L;
		glong _tmp13_ = 0L;
		_tmp12_ = offset;
		_tmp13_ = string_length;
		g_return_val_if_fail (_tmp12_ <= _tmp13_, NULL);
	}
	_tmp14_ = len;
	if (_tmp14_ < ((glong) 0)) {
		glong _tmp15_ = 0L;
		glong _tmp16_ = 0L;
		_tmp15_ = string_length;
		_tmp16_ = offset;
		len = _tmp15_ - _tmp16_;
	}
	_tmp17_ = offset;
	_tmp18_ = len;
	_tmp19_ = string_length;
	g_return_val_if_fail ((_tmp17_ + _tmp18_) <= _tmp19_, NULL);
	_tmp20_ = offset;
	_tmp21_ = len;
	_tmp22_ = g_strndup (((gchar*) self) + _tmp20_, (gsize) _tmp21_);
	result = _tmp22_;
	return result;
}


static gint string_last_index_of_char (const gchar* self, gunichar c, gint start_index) {
	gint result = 0;
	gchar* _result_ = NULL;
	gint _tmp0_ = 0;
	gunichar _tmp1_ = 0U;
	gchar* _tmp2_ = NULL;
	gchar* _tmp3_ = NULL;
	g_return_val_if_fail (self != NULL, 0);
	_tmp0_ = start_index;
	_tmp1_ = c;
	_tmp2_ = g_utf8_strrchr (((gchar*) self) + _tmp0_, (gssize) -1, _tmp1_);
	_result_ = _tmp2_;
	_tmp3_ = _result_;
	if (_tmp3_ != NULL) {
		gchar* _tmp4_ = NULL;
		_tmp4_ = _result_;
		result = (gint) (_tmp4_ - ((gchar*) self));
		return result;
	} else {
		result = -1;
		return result;
	}
}


static void __lambda44_ (EmulatorUI* self, SimpleFilePicker* s, const gchar* filename, const gchar* current_dir) {
	const gchar* _tmp0_ = NULL;
	gchar* _tmp1_ = NULL;
	gchar* _tmp2_ = NULL;
	const gchar* _tmp3_ = NULL;
	const gchar* _tmp5_ = NULL;
	gchar* _tmp6_ = NULL;
	gchar* _ext = NULL;
	const gchar* _tmp7_ = NULL;
	const gchar* _tmp8_ = NULL;
	gint _tmp9_ = 0;
	gchar* _tmp10_ = NULL;
	GeeHashMap* _tmp11_ = NULL;
	const gchar* _tmp12_ = NULL;
	gpointer _tmp13_ = NULL;
	EmulatorUICoreSettings* _tmp14_ = NULL;
	EmulatorUICoreSettings _tmp15_ = {0};
	const gchar* _tmp16_ = NULL;
	EmulatorUICoreSettings _tmp17_ = {0};
	const gchar* _tmp18_ = NULL;
	g_return_if_fail (s != NULL);
	_tmp0_ = current_dir;
	_tmp1_ = realpath (_tmp0_, NULL);
	_tmp2_ = _tmp1_;
	emulator_ui_set_last_dir (self, _tmp2_);
	_g_free0 (_tmp2_);
	_tmp3_ = filename;
	if (_tmp3_ == NULL) {
		gboolean _tmp4_ = FALSE;
		_tmp4_ = self->priv->ready;
		if (_tmp4_) {
			emulator_ui_play_game (self);
		}
		return;
	}
	_tmp5_ = filename;
	_tmp6_ = realpath (_tmp5_, NULL);
	_g_free0 (self->priv->game_path);
	self->priv->game_path = _tmp6_;
	_tmp7_ = self->priv->game_path;
	_tmp8_ = self->priv->game_path;
	_tmp9_ = string_last_index_of_char (_tmp8_, (gunichar) '.', 0);
	_tmp10_ = string_substring (_tmp7_, (glong) (_tmp9_ + 1), (glong) -1);
	_ext = _tmp10_;
	_tmp11_ = self->priv->cores_map;
	_tmp12_ = _ext;
	_tmp13_ = gee_abstract_map_get ((GeeAbstractMap*) _tmp11_, _tmp12_);
	_tmp14_ = (EmulatorUICoreSettings*) _tmp13_;
	emulator_ui_core_settings_copy (_tmp14_, &_tmp15_);
	emulator_ui_core_settings_destroy (&self->priv->core_settings);
	self->priv->core_settings = _tmp15_;
	_emulator_ui_core_settings_free0 (_tmp14_);
	_tmp16_ = self->priv->game_path;
	_tmp17_ = self->priv->core_settings;
	_tmp18_ = _tmp17_.path;
	g_debug ("main.vala:420: filename: %s | core_settings.path %s\n", _tmp16_, _tmp18_);
	emulator_ui_load_game (self);
	g_debug ("main.vala:426: closing file picker");
	_g_free0 (_ext);
}


static void ___lambda44__simple_file_picker_file_selected (SimpleFilePicker* _sender, const gchar* path, const gchar* current_dir, gpointer self) {
	__lambda44_ ((EmulatorUI*) self, _sender, path, current_dir);
}


static void __lambda35_ (Block2Data* _data2_) {
	EmulatorUI* self;
	GtkBuilder* _tmp0_ = NULL;
	GObject* _tmp1_ = NULL;
	SimpleFilePicker* picker = NULL;
	GeeHashMap* _tmp2_ = NULL;
	GeeSet* _tmp3_ = NULL;
	GeeSet* _tmp4_ = NULL;
	GeeSet* _tmp5_ = NULL;
	const gchar* _tmp6_ = NULL;
	SimpleFilePicker* _tmp7_ = NULL;
	SimpleFilePicker* _tmp8_ = NULL;
	GError * _inner_error_ = NULL;
	self = _data2_->self;
	g_debug ("main.vala:395: opengame");
	_tmp0_ = _data2_->builder;
	_tmp1_ = gtk_builder_get_object (_tmp0_, "notebook");
	gtk_notebook_set_current_page (G_TYPE_CHECK_INSTANCE_TYPE (_tmp1_, GTK_TYPE_NOTEBOOK) ? ((GtkNotebook*) _tmp1_) : NULL, 0);
	emulator_ui_stop_game (self);
	_tmp2_ = self->priv->cores_map;
	_tmp3_ = gee_abstract_map_get_keys ((GeeMap*) _tmp2_);
	_tmp4_ = _tmp3_;
	_tmp5_ = _tmp4_;
	_tmp6_ = self->priv->_last_dir;
	_tmp7_ = simple_file_picker_new ((GtkWindow*) self, _tmp5_, _tmp6_, &_inner_error_);
	g_object_ref_sink (_tmp7_);
	_tmp8_ = _tmp7_;
	_g_object_unref0 (_tmp5_);
	picker = _tmp8_;
	if (G_UNLIKELY (_inner_error_ != NULL)) {
		g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
		g_clear_error (&_inner_error_);
		return;
	}
	g_signal_connect_object (picker, "file-selected", (GCallback) ___lambda44__simple_file_picker_file_selected, self, 0);
	gtk_widget_show_all ((GtkWidget*) picker);
	_g_object_unref0 (picker);
}


static void ___lambda35__gtk_button_clicked (GtkButton* _sender, gpointer self) {
	__lambda35_ (self);
}


static void __lambda45_ (Block2Data* _data2_, GtkToggleButton* w) {
	EmulatorUI* self;
	gint _tmp0_ = 0;
	GtkToggleButton* _tmp1_ = NULL;
	gboolean _tmp2_ = FALSE;
	gboolean _tmp3_ = FALSE;
	GtkBuilder* _tmp4_ = NULL;
	GObject* _tmp5_ = NULL;
	self = _data2_->self;
	g_return_if_fail (w != NULL);
	_tmp1_ = w;
	_tmp2_ = gtk_toggle_button_get_active (_tmp1_);
	_tmp3_ = _tmp2_;
	if (_tmp3_) {
		_tmp0_ = 1;
	} else {
		_tmp0_ = 0;
	}
	_tmp4_ = _data2_->builder;
	_tmp5_ = gtk_builder_get_object (_tmp4_, "notebook");
	gtk_notebook_set_current_page (G_TYPE_CHECK_INSTANCE_TYPE (_tmp5_, GTK_TYPE_NOTEBOOK) ? ((GtkNotebook*) _tmp5_) : NULL, _tmp0_);
}


static void ___lambda45__gtk_toggle_button_toggled (GtkToggleButton* _sender, gpointer self) {
	__lambda45_ (self, _sender);
}


static void __lambda46_ (EmulatorUI* self, GtkButton* t) {
	g_return_if_fail (t != NULL);
	g_debug ("main.vala:473: quit_button pressed!\n");
	emulator_ui_stop_game (self);
	gtk_main_quit ();
}


static void ___lambda46__gtk_button_clicked (GtkButton* _sender, gpointer self) {
	__lambda46_ ((EmulatorUI*) self, _sender);
}


static void __lambda47_ (EmulatorUI* self, gint w, gint h) {
	gint _tmp0_ = 0;
	gint _tmp1_ = 0;
	gint _tmp2_ = 0;
	gint _tmp3_ = 0;
	_tmp0_ = w;
	_tmp1_ = h;
	g_debug ("main.vala:480: emulator_size.connect! %d %d\n", _tmp0_, _tmp1_);
	_tmp2_ = w;
	self->priv->core_width = _tmp2_;
	_tmp3_ = h;
	self->priv->core_height = _tmp3_;
	emulator_ui_resize_drawing_area_and_buffers (self);
}


static void ___lambda47__emulator_ui_emulator_size (EmulatorUI* _sender, gint width, gint height, gpointer self) {
	__lambda47_ ((EmulatorUI*) self, width, height);
}


static void __lambda48_ (EmulatorUI* self, GdkRectangle* a) {
	g_return_if_fail (a != NULL);
	emulator_ui_resize_drawing_area_and_buffers (self);
}


static void ___lambda48__gtk_widget_size_allocate (GtkWidget* _sender, GdkRectangle* allocation, gpointer self) {
	__lambda48_ ((EmulatorUI*) self, allocation);
}


EmulatorUI* emulator_ui_construct (GType object_type, GError** error) {
	EmulatorUI * self = NULL;
	Block2Data* _data2_;
	const gchar* _tmp0_ = NULL;
	gchar* _tmp1_ = NULL;
	gchar* _tmp2_ = NULL;
	gchar** _tmp3_ = NULL;
	gchar** _tmp4_ = NULL;
	gint _tmp4__length1 = 0;
	GtkBuilder* _tmp5_ = NULL;
	GtkBuilder* _tmp6_ = NULL;
	gint _tmp7_ = 0;
	gint _tmp8_ = 0;
	GtkBuilder* _tmp9_ = NULL;
	GtkVBox* main_vbox = NULL;
	GtkBuilder* _tmp10_ = NULL;
	GObject* _tmp11_ = NULL;
	GtkVBox* _tmp12_ = NULL;
	GtkVBox* _tmp13_ = NULL;
	GtkDrawingArea* joypad_area = NULL;
	GtkBuilder* _tmp17_ = NULL;
	GObject* _tmp18_ = NULL;
	GtkDrawingArea* _tmp19_ = NULL;
	GameJoypad* _tmp20_ = NULL;
	GtkDrawingArea* drawing_area = NULL;
	GtkBuilder* _tmp21_ = NULL;
	GObject* _tmp22_ = NULL;
	GtkDrawingArea* _tmp23_ = NULL;
	GameScreen* _tmp24_ = NULL;
	GameScreen* _tmp25_ = NULL;
	GtkDrawingArea* _tmp26_ = NULL;
	GameScreen* _tmp27_ = NULL;
	GtkDrawingArea* _tmp28_ = NULL;
	GKeyFile* _tmp29_ = NULL;
	GKeyFile* _tmp30_ = NULL;
	const gchar* _tmp31_ = NULL;
	GeeHashMap* _tmp32_ = NULL;
	gchar** _tmp33_ = NULL;
	GKeyFile* _tmp34_ = NULL;
	gsize _tmp35_;
	gchar** _tmp36_ = NULL;
	gint _tmp33__length1 = 0;
	gint __tmp33__size_ = 0;
	gchar** _tmp37_ = NULL;
	gint _tmp37__length1 = 0;
	GKeyFile* _tmp139_ = NULL;
	GKeyFile* _tmp140_ = NULL;
	GKeyFile* _tmp141_ = NULL;
	GKeyFile* _tmp142_ = NULL;
	GKeyFile* _tmp143_ = NULL;
	GKeyFile* _tmp144_ = NULL;
	GKeyFile* _tmp145_ = NULL;
	GKeyFile* _tmp146_ = NULL;
	GameScreenCommitMode _tmp147_ = 0;
	gboolean _tmp148_ = FALSE;
	GKeyFile* _tmp149_ = NULL;
	gboolean _tmp150_ = FALSE;
	InkRowHScale* contrast_scale = NULL;
	GtkBuilder* _tmp151_ = NULL;
	GObject* _tmp152_ = NULL;
	InkRowHScale* _tmp153_ = NULL;
	InkRowHScale* brightness_scale = NULL;
	GtkBuilder* _tmp154_ = NULL;
	GObject* _tmp155_ = NULL;
	InkRowHScale* _tmp156_ = NULL;
	InkRowHScale* max_fps_scale = NULL;
	GtkBuilder* _tmp157_ = NULL;
	GObject* _tmp158_ = NULL;
	InkRowHScale* _tmp159_ = NULL;
	InkRowHScale* _tmp160_ = NULL;
	InkRowHScale* _tmp161_ = NULL;
	InkRowHScale* _tmp162_ = NULL;
	GameScreen* _tmp163_ = NULL;
	InkRowHScale* _tmp164_ = NULL;
	InkRowHScale* _tmp165_ = NULL;
	InkRowHScale* _tmp166_ = NULL;
	GameScreen* _tmp167_ = NULL;
	InkRowHScale* _tmp168_ = NULL;
	InkRowHScale* _tmp169_ = NULL;
	InkRowHScale* _tmp170_ = NULL;
	GameScreen* _tmp171_ = NULL;
	InkRowToggleButton* dark_mode_toggle = NULL;
	GtkBuilder* _tmp172_ = NULL;
	GObject* _tmp173_ = NULL;
	InkRowToggleButton* _tmp174_ = NULL;
	gboolean has_feature_nightmode = FALSE;
	gboolean _tmp183_ = FALSE;
	InkRowToggleButton* render_mode_toggle = NULL;
	GtkBuilder* _tmp191_ = NULL;
	GObject* _tmp192_ = NULL;
	InkRowToggleButton* _tmp193_ = NULL;
	InkRowToggleButton* _tmp194_ = NULL;
	GameScreen* _tmp195_ = NULL;
	GtkBuilder* _tmp196_ = NULL;
	GObject* _tmp197_ = NULL;
	GtkBuilder* _tmp198_ = NULL;
	GObject* _tmp199_ = NULL;
	GtkBuilder* _tmp200_ = NULL;
	GObject* _tmp201_ = NULL;
	GtkBuilder* _tmp202_ = NULL;
	GObject* _tmp203_ = NULL;
	GtkBuilder* _tmp204_ = NULL;
	GObject* _tmp205_ = NULL;
	GError * _inner_error_ = NULL;
	_data2_ = g_slice_new0 (Block2Data);
	_data2_->_ref_count_ = 1;
	self = (EmulatorUI*) g_object_new (object_type, NULL);
	_data2_->self = g_object_ref (self);
	_tmp0_ = gtk_window_get_title ((GtkWindow*) self);
	g_debug ("main.vala:119: %s", _tmp0_);
	_tmp1_ = g_strdup ("fullscreen");
	_tmp2_ = g_strdup ("dark-mode");
	_tmp3_ = g_new0 (gchar*, 2 + 1);
	_tmp3_[0] = _tmp1_;
	_tmp3_[1] = _tmp2_;
	_tmp4_ = _tmp3_;
	_tmp4__length1 = 2;
	emulator_ui_notify_group (self, _tmp4_, 2, ___lambda10__emulator_ui_notify_group_callback, self);
	_tmp4_ = (_vala_array_free (_tmp4_, _tmp4__length1, (GDestroyNotify) g_free), NULL);
	gtk_container_set_border_width ((GtkContainer*) self, (guint) 0);
	_tmp5_ = gtk_builder_new ();
	_data2_->builder = _tmp5_;
	_tmp6_ = _data2_->builder;
	_tmp7_ = strlen (main_ui);
	_tmp8_ = _tmp7_;
	gtk_builder_add_from_string (_tmp6_, main_ui, (gsize) _tmp8_, &_inner_error_);
	if (G_UNLIKELY (_inner_error_ != NULL)) {
		g_propagate_error (error, _inner_error_);
		block2_data_unref (_data2_);
		_data2_ = NULL;
		_g_object_unref0 (self);
		return NULL;
	}
	_tmp9_ = _data2_->builder;
	gtk_builder_connect_signals (_tmp9_, self);
	_tmp10_ = _data2_->builder;
	_tmp11_ = gtk_builder_get_object (_tmp10_, "main_vbox");
	_tmp12_ = _g_object_ref0 (G_TYPE_CHECK_INSTANCE_TYPE (_tmp11_, GTK_TYPE_VBOX) ? ((GtkVBox*) _tmp11_) : NULL);
	main_vbox = _tmp12_;
	_tmp13_ = main_vbox;
	gtk_container_add ((GtkContainer*) self, (GtkWidget*) _tmp13_);
	{
		Lipstick* _tmp14_ = NULL;
		Lipstick* _tmp15_ = NULL;
		Lipstick* _tmp16_ = NULL;
		_tmp15_ = lipstick_new ("", &_inner_error_);
		_tmp14_ = _tmp15_;
		if (G_UNLIKELY (_inner_error_ != NULL)) {
			goto __catch0_g_error;
		}
		_tmp16_ = _tmp14_;
		_tmp14_ = NULL;
		_g_object_unref0 (self->priv->lipstick);
		self->priv->lipstick = _tmp16_;
		_g_object_unref0 (_tmp14_);
	}
	goto __finally0;
	__catch0_g_error:
	{
		GError* e = NULL;
		e = _inner_error_;
		_inner_error_ = NULL;
		g_warning ("main.vala:153: lipstick error\n");
		_g_error_free0 (e);
	}
	__finally0:
	if (G_UNLIKELY (_inner_error_ != NULL)) {
		g_propagate_error (error, _inner_error_);
		_g_object_unref0 (main_vbox);
		block2_data_unref (_data2_);
		_data2_ = NULL;
		_g_object_unref0 (self);
		return NULL;
	}
	_tmp17_ = _data2_->builder;
	_tmp18_ = gtk_builder_get_object (_tmp17_, "joystick_area");
	_tmp19_ = _g_object_ref0 (G_TYPE_CHECK_INSTANCE_TYPE (_tmp18_, GTK_TYPE_DRAWING_AREA) ? ((GtkDrawingArea*) _tmp18_) : NULL);
	joypad_area = _tmp19_;
	_tmp20_ = game_joypad_new (&joypad_area);
	_g_object_unref0 (self->priv->gamejoypad);
	self->priv->gamejoypad = _tmp20_;
	_tmp21_ = _data2_->builder;
	_tmp22_ = gtk_builder_get_object (_tmp21_, "drawing_area");
	_tmp23_ = _g_object_ref0 (G_TYPE_CHECK_INSTANCE_TYPE (_tmp22_, GTK_TYPE_DRAWING_AREA) ? ((GtkDrawingArea*) _tmp22_) : NULL);
	drawing_area = _tmp23_;
	_tmp24_ = game_screen_new (&drawing_area);
	_g_object_unref0 (self->priv->gamescreen);
	self->priv->gamescreen = _tmp24_;
	_tmp25_ = self->priv->gamescreen;
	_tmp26_ = _tmp25_->drawing_area;
	gtk_widget_add_events ((GtkWidget*) _tmp26_, (gint) GDK_BUTTON_PRESS_MASK);
	_tmp27_ = self->priv->gamescreen;
	_tmp28_ = _tmp27_->drawing_area;
	g_signal_connect_object ((GtkWidget*) _tmp28_, "button-press-event", (GCallback) ___lambda11__gtk_widget_button_press_event, self, 0);
	_tmp29_ = g_key_file_new ();
	_g_key_file_free0 (self->priv->kf);
	self->priv->kf = _tmp29_;
	_tmp30_ = self->priv->kf;
	_tmp31_ = emulator_ui_config_file;
	g_key_file_load_from_file (_tmp30_, _tmp31_, G_KEY_FILE_KEEP_COMMENTS, &_inner_error_);
	if (G_UNLIKELY (_inner_error_ != NULL)) {
		g_propagate_error (error, _inner_error_);
		_g_object_unref0 (drawing_area);
		_g_object_unref0 (joypad_area);
		_g_object_unref0 (main_vbox);
		block2_data_unref (_data2_);
		_data2_ = NULL;
		_g_object_unref0 (self);
		return NULL;
	}
	_tmp32_ = gee_hash_map_new (G_TYPE_STRING, (GBoxedCopyFunc) g_strdup, g_free, EMULATOR_UI_TYPE_CORE_SETTINGS, (GBoxedCopyFunc) emulator_ui_core_settings_dup, emulator_ui_core_settings_free, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
	_g_object_unref0 (self->priv->cores_map);
	self->priv->cores_map = _tmp32_;
	_tmp34_ = self->priv->kf;
	_tmp36_ = g_key_file_get_keys (_tmp34_, "Cores", &_tmp35_, &_inner_error_);
	_tmp33_ = _tmp36_;
	_tmp33__length1 = _tmp35_;
	__tmp33__size_ = _tmp33__length1;
	if (G_UNLIKELY (_inner_error_ != NULL)) {
		g_propagate_error (error, _inner_error_);
		_g_object_unref0 (drawing_area);
		_g_object_unref0 (joypad_area);
		_g_object_unref0 (main_vbox);
		block2_data_unref (_data2_);
		_data2_ = NULL;
		_g_object_unref0 (self);
		return NULL;
	}
	_tmp37_ = _tmp33_;
	_tmp37__length1 = _tmp33__length1;
	_tmp33_ = NULL;
	_tmp33__length1 = 0;
	{
		gchar** k_collection = NULL;
		gint k_collection_length1 = 0;
		gint _k_collection_size_ = 0;
		gint k_it = 0;
		k_collection = _tmp37_;
		k_collection_length1 = _tmp37__length1;
		for (k_it = 0; k_it < _tmp37__length1; k_it = k_it + 1) {
			gchar* _tmp38_ = NULL;
			gchar* k = NULL;
			_tmp38_ = g_strdup (k_collection[k_it]);
			k = _tmp38_;
			{
				gchar** k_parts = NULL;
				const gchar* _tmp39_ = NULL;
				gchar** _tmp40_ = NULL;
				gchar** _tmp41_ = NULL;
				gint k_parts_length1 = 0;
				gint _k_parts_size_ = 0;
				gchar* ext = NULL;
				gchar** _tmp42_ = NULL;
				gint _tmp42__length1 = 0;
				const gchar* _tmp43_ = NULL;
				gchar* _tmp44_ = NULL;
				gchar* prop1 = NULL;
				gchar** _tmp45_ = NULL;
				gint _tmp45__length1 = 0;
				const gchar* _tmp46_ = NULL;
				gchar* _tmp47_ = NULL;
				gchar* prop2 = NULL;
				gchar** _tmp48_ = NULL;
				gint _tmp48__length1 = 0;
				const gchar* _tmp49_ = NULL;
				gchar* _tmp50_ = NULL;
				gchar* value = NULL;
				GKeyFile* _tmp51_ = NULL;
				const gchar* _tmp52_ = NULL;
				gchar* _tmp53_ = NULL;
				EmulatorUICoreSettings _core = {0};
				GeeHashMap* _tmp54_ = NULL;
				const gchar* _tmp55_ = NULL;
				gboolean _tmp56_ = FALSE;
				const gchar* _tmp62_ = NULL;
				const gchar* _tmp63_ = NULL;
				GQuark _tmp65_ = 0U;
				static GQuark _tmp64_label0 = 0;
				static GQuark _tmp64_label1 = 0;
				static GQuark _tmp64_label2 = 0;
				static GQuark _tmp64_label3 = 0;
				GeeHashMap* _tmp136_ = NULL;
				const gchar* _tmp137_ = NULL;
				EmulatorUICoreSettings _tmp138_ = {0};
				_tmp39_ = k;
				_tmp41_ = _tmp40_ = g_strsplit (_tmp39_, ".", 0);
				k_parts = _tmp41_;
				k_parts_length1 = _vala_array_length (_tmp40_);
				_k_parts_size_ = k_parts_length1;
				_tmp42_ = k_parts;
				_tmp42__length1 = k_parts_length1;
				_tmp43_ = _tmp42_[0];
				_tmp44_ = g_strdup (_tmp43_);
				ext = _tmp44_;
				_tmp45_ = k_parts;
				_tmp45__length1 = k_parts_length1;
				_tmp46_ = _tmp45_[1];
				_tmp47_ = g_strdup (_tmp46_);
				prop1 = _tmp47_;
				_tmp48_ = k_parts;
				_tmp48__length1 = k_parts_length1;
				_tmp49_ = _tmp48_[2];
				_tmp50_ = g_strdup (_tmp49_);
				prop2 = _tmp50_;
				_tmp51_ = self->priv->kf;
				_tmp52_ = k;
				_tmp53_ = g_key_file_get_string (_tmp51_, "Cores", _tmp52_, &_inner_error_);
				value = _tmp53_;
				if (G_UNLIKELY (_inner_error_ != NULL)) {
					g_propagate_error (error, _inner_error_);
					_g_free0 (prop2);
					_g_free0 (prop1);
					_g_free0 (ext);
					k_parts = (_vala_array_free (k_parts, k_parts_length1, (GDestroyNotify) g_free), NULL);
					_g_free0 (k);
					k_collection = (_vala_array_free (k_collection, k_collection_length1, (GDestroyNotify) g_free), NULL);
					_tmp33_ = (_vala_array_free (_tmp33_, _tmp33__length1, (GDestroyNotify) g_free), NULL);
					_g_object_unref0 (drawing_area);
					_g_object_unref0 (joypad_area);
					_g_object_unref0 (main_vbox);
					block2_data_unref (_data2_);
					_data2_ = NULL;
					_g_object_unref0 (self);
					return NULL;
				}
				_tmp54_ = self->priv->cores_map;
				_tmp55_ = ext;
				_tmp56_ = gee_abstract_map_has_key ((GeeAbstractMap*) _tmp54_, _tmp55_);
				if (_tmp56_) {
					GeeHashMap* _tmp57_ = NULL;
					const gchar* _tmp58_ = NULL;
					gpointer _tmp59_ = NULL;
					EmulatorUICoreSettings* _tmp60_ = NULL;
					EmulatorUICoreSettings _tmp61_ = {0};
					_tmp57_ = self->priv->cores_map;
					_tmp58_ = ext;
					_tmp59_ = gee_abstract_map_get ((GeeAbstractMap*) _tmp57_, _tmp58_);
					_tmp60_ = (EmulatorUICoreSettings*) _tmp59_;
					emulator_ui_core_settings_copy (_tmp60_, &_tmp61_);
					emulator_ui_core_settings_destroy (&_core);
					_core = _tmp61_;
					_emulator_ui_core_settings_free0 (_tmp60_);
				} else {
					emulator_ui_core_settings_destroy (&_core);
					memset (&_core, 0, sizeof (EmulatorUICoreSettings));
				}
				_tmp62_ = prop1;
				_tmp63_ = _tmp62_;
				_tmp65_ = (NULL == _tmp63_) ? 0 : g_quark_from_string (_tmp63_);
				if (_tmp65_ == ((0 != _tmp64_label0) ? _tmp64_label0 : (_tmp64_label0 = g_quark_from_static_string ("name")))) {
					switch (0) {
						default:
						{
							const gchar* _tmp66_ = NULL;
							gchar* _tmp67_ = NULL;
							_tmp66_ = value;
							_tmp67_ = g_strdup (_tmp66_);
							_g_free0 (_core.name);
							_core.name = _tmp67_;
							break;
						}
					}
				} else if (_tmp65_ == ((0 != _tmp64_label1) ? _tmp64_label1 : (_tmp64_label1 = g_quark_from_static_string ("path")))) {
					switch (0) {
						default:
						{
							const gchar* _tmp68_ = NULL;
							gboolean _tmp69_ = FALSE;
							gchar* core_path = NULL;
							const gchar* _tmp70_ = NULL;
							gchar* _tmp71_ = NULL;
							const gchar* _tmp72_ = NULL;
							gboolean _tmp73_ = FALSE;
							const gchar* _tmp81_ = NULL;
							gboolean _tmp82_ = FALSE;
							const gchar* _tmp85_ = NULL;
							gchar* _tmp86_ = NULL;
							_tmp69_ = g_file_test ("/lib/ld-linux-armhf.so.3", G_FILE_TEST_EXISTS);
							if (_tmp69_) {
								_tmp68_ = "armhf";
							} else {
								_tmp68_ = "armel";
							}
							_tmp70_ = value;
							_tmp71_ = string_replace (_tmp70_, "<arch>", _tmp68_);
							core_path = _tmp71_;
							_tmp72_ = core_path;
							_tmp73_ = g_path_is_absolute (_tmp72_);
							if (!_tmp73_) {
								const gchar* _tmp74_ = NULL;
								gchar* _tmp75_ = NULL;
								gchar* _tmp76_ = NULL;
								const gchar* _tmp77_ = NULL;
								gchar* _tmp78_ = NULL;
								gchar* _tmp79_ = NULL;
								gchar* _tmp80_ = NULL;
								_tmp74_ = emulator_ui_config_file;
								_tmp75_ = g_path_get_dirname (_tmp74_);
								_tmp76_ = _tmp75_;
								_tmp77_ = core_path;
								_tmp78_ = g_build_filename (_tmp76_, _tmp77_, NULL);
								_tmp79_ = _tmp78_;
								_tmp80_ = realpath (_tmp79_, NULL);
								_g_free0 (core_path);
								core_path = _tmp80_;
								_g_free0 (_tmp79_);
								_g_free0 (_tmp76_);
							}
							_tmp81_ = core_path;
							_tmp82_ = g_file_test (_tmp81_, G_FILE_TEST_EXISTS);
							if (!_tmp82_) {
								const gchar* _tmp83_ = NULL;
								GError* _tmp84_ = NULL;
								_tmp83_ = core_path;
								_tmp84_ = g_error_new (EMULATOR_UI_ERROR, EMULATOR_UI_ERROR_ERROR, "core file %s doesn't exist", _tmp83_);
								_inner_error_ = _tmp84_;
								g_propagate_error (error, _inner_error_);
								_g_free0 (core_path);
								emulator_ui_core_settings_destroy (&_core);
								_g_free0 (value);
								_g_free0 (prop2);
								_g_free0 (prop1);
								_g_free0 (ext);
								k_parts = (_vala_array_free (k_parts, k_parts_length1, (GDestroyNotify) g_free), NULL);
								_g_free0 (k);
								k_collection = (_vala_array_free (k_collection, k_collection_length1, (GDestroyNotify) g_free), NULL);
								_tmp33_ = (_vala_array_free (_tmp33_, _tmp33__length1, (GDestroyNotify) g_free), NULL);
								_g_object_unref0 (drawing_area);
								_g_object_unref0 (joypad_area);
								_g_object_unref0 (main_vbox);
								block2_data_unref (_data2_);
								_data2_ = NULL;
								_g_object_unref0 (self);
								return NULL;
							}
							_tmp85_ = core_path;
							_tmp86_ = g_strdup (_tmp85_);
							_g_free0 (_core.path);
							_core.path = _tmp86_;
							_g_free0 (core_path);
							break;
						}
					}
				} else if (_tmp65_ == ((0 != _tmp64_label2) ? _tmp64_label2 : (_tmp64_label2 = g_quark_from_static_string ("joypad")))) {
					switch (0) {
						default:
						{
							gchar* joypad_group = NULL;
							const gchar* _tmp87_ = NULL;
							gchar* _tmp88_ = NULL;
							gchar** _tmp89_ = NULL;
							GKeyFile* _tmp90_ = NULL;
							const gchar* _tmp91_ = NULL;
							gsize _tmp92_;
							gchar** _tmp93_ = NULL;
							gint _tmp89__length1 = 0;
							gint __tmp89__size_ = 0;
							gchar** _tmp94_ = NULL;
							gint _tmp94__length1 = 0;
							_tmp87_ = value;
							_tmp88_ = g_strconcat ("Joypad.", _tmp87_, NULL);
							joypad_group = _tmp88_;
							_tmp90_ = self->priv->kf;
							_tmp91_ = joypad_group;
							_tmp93_ = g_key_file_get_keys (_tmp90_, _tmp91_, &_tmp92_, &_inner_error_);
							_tmp89_ = _tmp93_;
							_tmp89__length1 = _tmp92_;
							__tmp89__size_ = _tmp89__length1;
							if (G_UNLIKELY (_inner_error_ != NULL)) {
								g_propagate_error (error, _inner_error_);
								_g_free0 (joypad_group);
								emulator_ui_core_settings_destroy (&_core);
								_g_free0 (value);
								_g_free0 (prop2);
								_g_free0 (prop1);
								_g_free0 (ext);
								k_parts = (_vala_array_free (k_parts, k_parts_length1, (GDestroyNotify) g_free), NULL);
								_g_free0 (k);
								k_collection = (_vala_array_free (k_collection, k_collection_length1, (GDestroyNotify) g_free), NULL);
								_tmp33_ = (_vala_array_free (_tmp33_, _tmp33__length1, (GDestroyNotify) g_free), NULL);
								_g_object_unref0 (drawing_area);
								_g_object_unref0 (joypad_area);
								_g_object_unref0 (main_vbox);
								block2_data_unref (_data2_);
								_data2_ = NULL;
								_g_object_unref0 (self);
								return NULL;
							}
							_tmp94_ = _tmp89_;
							_tmp94__length1 = _tmp89__length1;
							_tmp89_ = NULL;
							_tmp89__length1 = 0;
							{
								gchar** btn_collection = NULL;
								gint btn_collection_length1 = 0;
								gint _btn_collection_size_ = 0;
								gint btn_it = 0;
								btn_collection = _tmp94_;
								btn_collection_length1 = _tmp94__length1;
								for (btn_it = 0; btn_it < _tmp94__length1; btn_it = btn_it + 1) {
									gchar* _tmp95_ = NULL;
									gchar* btn = NULL;
									_tmp95_ = g_strdup (btn_collection[btn_it]);
									btn = _tmp95_;
									{
										gchar** btn_data = NULL;
										GKeyFile* _tmp96_ = NULL;
										const gchar* _tmp97_ = NULL;
										const gchar* _tmp98_ = NULL;
										gsize _tmp99_;
										gchar** _tmp100_ = NULL;
										gint btn_data_length1 = 0;
										gint _btn_data_size_ = 0;
										const gchar* _tmp101_ = NULL;
										gchar** _tmp102_ = NULL;
										gint _tmp102__length1 = 0;
										const gchar* _tmp103_ = NULL;
										gboolean _tmp104_ = FALSE;
										GameJoypadButton* _tmp106_ = NULL;
										gint _tmp106__length1 = 0;
										gchar** _tmp107_ = NULL;
										gint _tmp107__length1 = 0;
										const gchar* _tmp108_ = NULL;
										gint _tmp109_ = 0;
										gchar* _tmp110_ = NULL;
										gchar** _tmp111_ = NULL;
										gint _tmp111__length1 = 0;
										const gchar* _tmp112_ = NULL;
										gint _tmp113_ = 0;
										gchar** _tmp114_ = NULL;
										gint _tmp114__length1 = 0;
										const gchar* _tmp115_ = NULL;
										gint _tmp116_ = 0;
										gchar** _tmp117_ = NULL;
										gint _tmp117__length1 = 0;
										const gchar* _tmp118_ = NULL;
										gint _tmp119_ = 0;
										gchar** _tmp120_ = NULL;
										gint _tmp120__length1 = 0;
										const gchar* _tmp121_ = NULL;
										gint _tmp122_ = 0;
										gchar** _tmp123_ = NULL;
										gint _tmp123__length1 = 0;
										const gchar* _tmp124_ = NULL;
										gint _tmp125_ = 0;
										gchar** _tmp126_ = NULL;
										gint _tmp126__length1 = 0;
										const gchar* _tmp127_ = NULL;
										gboolean _tmp128_ = FALSE;
										GameJoypadButton _tmp129_ = {0};
										_tmp96_ = self->priv->kf;
										_tmp97_ = joypad_group;
										_tmp98_ = btn;
										_tmp100_ = g_key_file_get_string_list (_tmp96_, _tmp97_, _tmp98_, &_tmp99_, &_inner_error_);
										btn_data = _tmp100_;
										btn_data_length1 = _tmp99_;
										_btn_data_size_ = btn_data_length1;
										if (G_UNLIKELY (_inner_error_ != NULL)) {
											g_propagate_error (error, _inner_error_);
											_g_free0 (btn);
											btn_collection = (_vala_array_free (btn_collection, btn_collection_length1, (GDestroyNotify) g_free), NULL);
											_tmp89_ = (_vala_array_free (_tmp89_, _tmp89__length1, (GDestroyNotify) g_free), NULL);
											_g_free0 (joypad_group);
											emulator_ui_core_settings_destroy (&_core);
											_g_free0 (value);
											_g_free0 (prop2);
											_g_free0 (prop1);
											_g_free0 (ext);
											k_parts = (_vala_array_free (k_parts, k_parts_length1, (GDestroyNotify) g_free), NULL);
											_g_free0 (k);
											k_collection = (_vala_array_free (k_collection, k_collection_length1, (GDestroyNotify) g_free), NULL);
											_tmp33_ = (_vala_array_free (_tmp33_, _tmp33__length1, (GDestroyNotify) g_free), NULL);
											_g_object_unref0 (drawing_area);
											_g_object_unref0 (joypad_area);
											_g_object_unref0 (main_vbox);
											block2_data_unref (_data2_);
											_data2_ = NULL;
											_g_object_unref0 (self);
											return NULL;
										}
										_tmp102_ = btn_data;
										_tmp102__length1 = btn_data_length1;
										_tmp103_ = _tmp102_[1];
										_tmp104_ = bool_parse (_tmp103_);
										if (_tmp104_) {
											const gchar* _tmp105_ = NULL;
											_tmp105_ = btn;
											_tmp101_ = _tmp105_;
										} else {
											_tmp101_ = "";
										}
										_tmp106_ = _core.joypad_buttons;
										_tmp106__length1 = _core.joypad_buttons_length1;
										_tmp107_ = btn_data;
										_tmp107__length1 = btn_data_length1;
										_tmp108_ = _tmp107_[0];
										_tmp109_ = atoi (_tmp108_);
										_tmp110_ = g_strdup (_tmp101_);
										_tmp111_ = btn_data;
										_tmp111__length1 = btn_data_length1;
										_tmp112_ = _tmp111_[2];
										_tmp113_ = atoi (_tmp112_);
										_tmp114_ = btn_data;
										_tmp114__length1 = btn_data_length1;
										_tmp115_ = _tmp114_[3];
										_tmp116_ = atoi (_tmp115_);
										_tmp117_ = btn_data;
										_tmp117__length1 = btn_data_length1;
										_tmp118_ = _tmp117_[4];
										_tmp119_ = atoi (_tmp118_);
										_tmp120_ = btn_data;
										_tmp120__length1 = btn_data_length1;
										_tmp121_ = _tmp120_[5];
										_tmp122_ = atoi (_tmp121_);
										_tmp123_ = btn_data;
										_tmp123__length1 = btn_data_length1;
										_tmp124_ = _tmp123_[6];
										_tmp125_ = atoi (_tmp124_);
										_tmp126_ = btn_data;
										_tmp126__length1 = btn_data_length1;
										_tmp127_ = _tmp126_[7];
										_tmp128_ = bool_parse (_tmp127_);
										memset (&_tmp129_, 0, sizeof (GameJoypadButton));
										_tmp129_.id = _tmp109_;
										_g_free0 (_tmp129_.label);
										_tmp129_.label = _tmp110_;
										_tmp129_.x = _tmp113_;
										_tmp129_.y = _tmp116_;
										_tmp129_.radius = _tmp119_;
										_tmp129_.width = _tmp122_;
										_tmp129_.height = _tmp125_;
										_tmp129_.visible = _tmp128_;
										_vala_array_add3 (&_core.joypad_buttons, &_core.joypad_buttons_length1, &_core._joypad_buttons_size_, &_tmp129_);
										btn_data = (_vala_array_free (btn_data, btn_data_length1, (GDestroyNotify) g_free), NULL);
										_g_free0 (btn);
									}
								}
								btn_collection = (_vala_array_free (btn_collection, btn_collection_length1, (GDestroyNotify) g_free), NULL);
							}
							_tmp89_ = (_vala_array_free (_tmp89_, _tmp89__length1, (GDestroyNotify) g_free), NULL);
							_g_free0 (joypad_group);
							break;
						}
					}
				} else if (_tmp65_ == ((0 != _tmp64_label3) ? _tmp64_label3 : (_tmp64_label3 = g_quark_from_static_string ("env")))) {
					switch (0) {
						default:
						{
							RetroCoreRetroVariable* _tmp130_ = NULL;
							gint _tmp130__length1 = 0;
							const gchar* _tmp131_ = NULL;
							gchar* _tmp132_ = NULL;
							const gchar* _tmp133_ = NULL;
							gchar* _tmp134_ = NULL;
							RetroCoreRetroVariable _tmp135_ = {0};
							_tmp130_ = _core.env;
							_tmp130__length1 = _core.env_length1;
							_tmp131_ = prop2;
							_tmp132_ = g_strdup (_tmp131_);
							_tmp133_ = value;
							_tmp134_ = g_strdup (_tmp133_);
							memset (&_tmp135_, 0, sizeof (RetroCoreRetroVariable));
							_g_free0 (_tmp135_.key);
							_tmp135_.key = _tmp132_;
							_g_free0 (_tmp135_.value);
							_tmp135_.value = _tmp134_;
							_vala_array_add4 (&_core.env, &_core.env_length1, &_core._env_size_, &_tmp135_);
							break;
						}
					}
				}
				_tmp136_ = self->priv->cores_map;
				_tmp137_ = ext;
				_tmp138_ = _core;
				gee_abstract_map_set ((GeeAbstractMap*) _tmp136_, _tmp137_, &_tmp138_);
				emulator_ui_core_settings_destroy (&_core);
				_g_free0 (value);
				_g_free0 (prop2);
				_g_free0 (prop1);
				_g_free0 (ext);
				k_parts = (_vala_array_free (k_parts, k_parts_length1, (GDestroyNotify) g_free), NULL);
				_g_free0 (k);
			}
		}
		k_collection = (_vala_array_free (k_collection, k_collection_length1, (GDestroyNotify) g_free), NULL);
	}
	_tmp139_ = self->priv->kf;
	settings_bind_bind (G_TYPE_STRING, (GBoxedCopyFunc) g_strdup, g_free, _tmp139_, "General", "state_dir", (GObject*) self, "state-dir", ___lambda13__settings_bind_save_callback, self);
	_tmp140_ = self->priv->kf;
	settings_bind_bind (G_TYPE_STRING, (GBoxedCopyFunc) g_strdup, g_free, _tmp140_, "General", "last_dir", (GObject*) self, "last-dir", ___lambda15__settings_bind_save_callback, self);
	_tmp141_ = self->priv->kf;
	settings_bind_bind (G_TYPE_INT, NULL, NULL, _tmp141_, "General", "brightness", (GObject*) self, "brightness", ___lambda16__settings_bind_save_callback, self);
	_tmp142_ = self->priv->kf;
	settings_bind_bind (G_TYPE_INT, NULL, NULL, _tmp142_, "General", "contrast", (GObject*) self, "contrast", ___lambda17__settings_bind_save_callback, self);
	_tmp143_ = self->priv->kf;
	settings_bind_bind (G_TYPE_INT, NULL, NULL, _tmp143_, "General", "max_fps", (GObject*) self, "max-fps", ___lambda18__settings_bind_save_callback, self);
	_tmp144_ = self->priv->kf;
	settings_bind_bind (G_TYPE_BOOLEAN, NULL, NULL, _tmp144_, "General", "dark_mode", (GObject*) self, "dark-mode", ___lambda19__settings_bind_save_callback, self);
	_tmp145_ = self->priv->kf;
	settings_bind_bind (G_TYPE_BOOLEAN, NULL, NULL, _tmp145_, "General", "fullscreen", (GObject*) self, "fullscreen", ___lambda20__settings_bind_save_callback, self);
	_tmp146_ = self->priv->kf;
	settings_bind_bind (G_TYPE_BOOLEAN, NULL, NULL, _tmp146_, "General", "audio", (GObject*) self, "audio", ___lambda21__settings_bind_save_callback, self);
	_tmp149_ = self->priv->kf;
	_tmp150_ = g_key_file_get_boolean (_tmp149_, "General", "fbink_mode", &_inner_error_);
	_tmp148_ = _tmp150_;
	if (G_UNLIKELY (_inner_error_ != NULL)) {
		g_propagate_error (error, _inner_error_);
		_tmp33_ = (_vala_array_free (_tmp33_, _tmp33__length1, (GDestroyNotify) g_free), NULL);
		_g_object_unref0 (drawing_area);
		_g_object_unref0 (joypad_area);
		_g_object_unref0 (main_vbox);
		block2_data_unref (_data2_);
		_data2_ = NULL;
		_g_object_unref0 (self);
		return NULL;
	}
	if (_tmp148_) {
		_tmp147_ = GAME_SCREEN_COMMIT_MODE_FBINK;
	} else {
		_tmp147_ = GAME_SCREEN_COMMIT_MODE_SHM;
	}
	emulator_ui_set_render_mode (self, _tmp147_);
	_tmp151_ = _data2_->builder;
	_tmp152_ = gtk_builder_get_object (_tmp151_, "contrast_scale");
	_tmp153_ = _g_object_ref0 (G_TYPE_CHECK_INSTANCE_TYPE (_tmp152_, TYPE_INK_ROW_HSCALE) ? ((InkRowHScale*) _tmp152_) : NULL);
	contrast_scale = _tmp153_;
	_tmp154_ = _data2_->builder;
	_tmp155_ = gtk_builder_get_object (_tmp154_, "brightness_scale");
	_tmp156_ = _g_object_ref0 (G_TYPE_CHECK_INSTANCE_TYPE (_tmp155_, TYPE_INK_ROW_HSCALE) ? ((InkRowHScale*) _tmp155_) : NULL);
	brightness_scale = _tmp156_;
	_tmp157_ = _data2_->builder;
	_tmp158_ = gtk_builder_get_object (_tmp157_, "fps_scale");
	_tmp159_ = _g_object_ref0 (G_TYPE_CHECK_INSTANCE_TYPE (_tmp158_, TYPE_INK_ROW_HSCALE) ? ((InkRowHScale*) _tmp158_) : NULL);
	max_fps_scale = _tmp159_;
	_tmp160_ = contrast_scale;
	ink_row_hscale_set_lower (_tmp160_, (gdouble) 0);
	_tmp161_ = contrast_scale;
	ink_row_hscale_set_upper (_tmp161_, (gdouble) 100);
	_tmp162_ = contrast_scale;
	g_object_bind_property_with_closures ((GObject*) self, "contrast", (GObject*) _tmp162_, "value", G_BINDING_BIDIRECTIONAL | G_BINDING_SYNC_CREATE, (GClosure*) ((NULL == NULL) ? NULL : g_cclosure_new ((GCallback) NULL, NULL, NULL)), (GClosure*) ((NULL == NULL) ? NULL : g_cclosure_new ((GCallback) NULL, NULL, NULL)));
	_tmp163_ = self->priv->gamescreen;
	g_object_bind_property_with_closures ((GObject*) self, "contrast", (GObject*) _tmp163_, "contrast", G_BINDING_DEFAULT | G_BINDING_SYNC_CREATE, (GClosure*) ((NULL == NULL) ? NULL : g_cclosure_new ((GCallback) NULL, NULL, NULL)), (GClosure*) ((NULL == NULL) ? NULL : g_cclosure_new ((GCallback) NULL, NULL, NULL)));
	_tmp164_ = brightness_scale;
	ink_row_hscale_set_lower (_tmp164_, (gdouble) 0);
	_tmp165_ = brightness_scale;
	ink_row_hscale_set_upper (_tmp165_, (gdouble) 100);
	_tmp166_ = brightness_scale;
	g_object_bind_property_with_closures ((GObject*) self, "brightness", (GObject*) _tmp166_, "value", G_BINDING_BIDIRECTIONAL | G_BINDING_SYNC_CREATE, (GClosure*) ((NULL == NULL) ? NULL : g_cclosure_new ((GCallback) NULL, NULL, NULL)), (GClosure*) ((NULL == NULL) ? NULL : g_cclosure_new ((GCallback) NULL, NULL, NULL)));
	_tmp167_ = self->priv->gamescreen;
	g_object_bind_property_with_closures ((GObject*) self, "brightness", (GObject*) _tmp167_, "brightness", G_BINDING_DEFAULT | G_BINDING_SYNC_CREATE, (GClosure*) ((NULL == NULL) ? NULL : g_cclosure_new ((GCallback) NULL, NULL, NULL)), (GClosure*) ((NULL == NULL) ? NULL : g_cclosure_new ((GCallback) NULL, NULL, NULL)));
	_tmp168_ = max_fps_scale;
	ink_row_hscale_set_lower (_tmp168_, (gdouble) 1);
	_tmp169_ = max_fps_scale;
	ink_row_hscale_set_upper (_tmp169_, (gdouble) 60);
	_tmp170_ = max_fps_scale;
	g_object_bind_property_with_closures ((GObject*) self, "max-fps", (GObject*) _tmp170_, "value", G_BINDING_BIDIRECTIONAL | G_BINDING_SYNC_CREATE, (GClosure*) ((NULL == NULL) ? NULL : g_cclosure_new ((GCallback) NULL, NULL, NULL)), (GClosure*) ((NULL == NULL) ? NULL : g_cclosure_new ((GCallback) NULL, NULL, NULL)));
	_tmp171_ = self->priv->gamescreen;
	g_object_bind_property_with_closures ((GObject*) self, "max-fps", (GObject*) _tmp171_, "max-fps", G_BINDING_DEFAULT | G_BINDING_SYNC_CREATE, (GClosure*) ((NULL == NULL) ? NULL : g_cclosure_new ((GCallback) NULL, NULL, NULL)), (GClosure*) ((NULL == NULL) ? NULL : g_cclosure_new ((GCallback) NULL, NULL, NULL)));
	_tmp172_ = _data2_->builder;
	_tmp173_ = gtk_builder_get_object (_tmp172_, "dark_mode_toggle");
	_tmp174_ = _g_object_ref0 (G_TYPE_CHECK_INSTANCE_TYPE (_tmp173_, TYPE_INK_ROW_TOGGLE_BUTTON) ? ((InkRowToggleButton*) _tmp173_) : NULL);
	dark_mode_toggle = _tmp174_;
	has_feature_nightmode = FALSE;
	{
		gchar* _std_output = NULL;
		gchar* _tmp175_ = NULL;
		gboolean _tmp176_ = FALSE;
		gboolean _tmp177_ = FALSE;
		gchar* _tmp178_ = NULL;
		gboolean _tmp179_ = FALSE;
		_tmp175_ = g_strdup ("");
		_std_output = _tmp175_;
		_tmp179_ = g_spawn_command_line_sync ("devcap-get-feature -s nightmode available", &_tmp178_, NULL, NULL, &_inner_error_);
		_g_free0 (_std_output);
		_std_output = _tmp178_;
		_tmp177_ = _tmp179_;
		if (G_UNLIKELY (_inner_error_ != NULL)) {
			_g_free0 (_std_output);
			goto __catch3_g_error;
		}
		if (_tmp177_) {
			const gchar* _tmp180_ = NULL;
			gchar* _tmp181_ = NULL;
			gchar* _tmp182_ = NULL;
			_tmp180_ = _std_output;
			_tmp181_ = string_strip (_tmp180_);
			_tmp182_ = _tmp181_;
			_tmp176_ = g_strcmp0 (_tmp182_, "true") == 0;
			_g_free0 (_tmp182_);
		} else {
			_tmp176_ = FALSE;
		}
		has_feature_nightmode = _tmp176_;
		_g_free0 (_std_output);
	}
	goto __finally3;
	__catch3_g_error:
	{
		GError* e = NULL;
		e = _inner_error_;
		_inner_error_ = NULL;
		g_warning ("main.vala:285: devcap command error\n");
		_g_error_free0 (e);
	}
	__finally3:
	if (G_UNLIKELY (_inner_error_ != NULL)) {
		g_propagate_error (error, _inner_error_);
		_g_object_unref0 (dark_mode_toggle);
		_g_object_unref0 (max_fps_scale);
		_g_object_unref0 (brightness_scale);
		_g_object_unref0 (contrast_scale);
		_tmp33_ = (_vala_array_free (_tmp33_, _tmp33__length1, (GDestroyNotify) g_free), NULL);
		_g_object_unref0 (drawing_area);
		_g_object_unref0 (joypad_area);
		_g_object_unref0 (main_vbox);
		block2_data_unref (_data2_);
		_data2_ = NULL;
		_g_object_unref0 (self);
		return NULL;
	}
	_tmp183_ = has_feature_nightmode;
	if (_tmp183_) {
		InkRowToggleButton* _tmp184_ = NULL;
		emulator_ui_set_dark_mode (self, FALSE);
		_tmp184_ = dark_mode_toggle;
		gtk_widget_set_no_show_all ((GtkWidget*) _tmp184_, TRUE);
		{
			GameScreen* _tmp185_ = NULL;
			Lipstick* _tmp186_ = NULL;
			gchar* _tmp187_ = NULL;
			gchar* _tmp188_ = NULL;
			Lipstick* _tmp189_ = NULL;
			_tmp185_ = self->priv->gamescreen;
			_tmp186_ = self->priv->lipstick;
			_tmp187_ = lipstick_get_string_property (_tmp186_, "com.lab126.winmgr", "epdcMode");
			_tmp188_ = _tmp187_;
			game_screen_set_inverted_colors (_tmp185_, g_strcmp0 ("Y8INV", _tmp188_) == 0);
			_g_free0 (_tmp188_);
			_tmp189_ = self->priv->lipstick;
			lipstick_subscribe (_tmp189_, G_TYPE_STRING, (GBoxedCopyFunc) g_strdup, g_free, "com.lab126.winmgr", "nightModeStateChanged", _____lambda25__lipstick_event_callback, self);
		}
		goto __finally4;
		__catch4_g_error:
		{
			GError* e = NULL;
			e = _inner_error_;
			_inner_error_ = NULL;
			g_warning ("main.vala:306: lipstick error\n");
			_g_error_free0 (e);
		}
		__finally4:
		if (G_UNLIKELY (_inner_error_ != NULL)) {
			g_propagate_error (error, _inner_error_);
			_g_object_unref0 (dark_mode_toggle);
			_g_object_unref0 (max_fps_scale);
			_g_object_unref0 (brightness_scale);
			_g_object_unref0 (contrast_scale);
			_tmp33_ = (_vala_array_free (_tmp33_, _tmp33__length1, (GDestroyNotify) g_free), NULL);
			_g_object_unref0 (drawing_area);
			_g_object_unref0 (joypad_area);
			_g_object_unref0 (main_vbox);
			block2_data_unref (_data2_);
			_data2_ = NULL;
			_g_object_unref0 (self);
			return NULL;
		}
	} else {
		InkRowToggleButton* _tmp190_ = NULL;
		_tmp190_ = dark_mode_toggle;
		g_object_bind_property_with_closures ((GObject*) self, "dark-mode", (GObject*) _tmp190_, "active", G_BINDING_BIDIRECTIONAL | G_BINDING_SYNC_CREATE, (GClosure*) ((NULL == NULL) ? NULL : g_cclosure_new ((GCallback) NULL, NULL, NULL)), (GClosure*) ((NULL == NULL) ? NULL : g_cclosure_new ((GCallback) NULL, NULL, NULL)));
		g_signal_connect_object ((GObject*) self, "notify::dark-mode", (GCallback) ____lambda26__g_object_notify, self, 0);
	}
	_tmp191_ = _data2_->builder;
	_tmp192_ = gtk_builder_get_object (_tmp191_, "render_mode_toggle");
	_tmp193_ = _g_object_ref0 (G_TYPE_CHECK_INSTANCE_TYPE (_tmp192_, TYPE_INK_ROW_TOGGLE_BUTTON) ? ((InkRowToggleButton*) _tmp192_) : NULL);
	render_mode_toggle = _tmp193_;
	_tmp194_ = render_mode_toggle;
	g_object_bind_property_with_closures ((GObject*) self, "render-mode", (GObject*) _tmp194_, "active", G_BINDING_BIDIRECTIONAL | G_BINDING_SYNC_CREATE, (GClosure*) ((___lambda27__gbinding_transform_func == NULL) ? NULL : g_cclosure_new ((GCallback) ___lambda27__gbinding_transform_func, g_object_ref (self), g_object_unref)), (GClosure*) ((___lambda28__gbinding_transform_func == NULL) ? NULL : g_cclosure_new ((GCallback) ___lambda28__gbinding_transform_func, g_object_ref (self), g_object_unref)));
	_tmp195_ = self->priv->gamescreen;
	g_object_bind_property_with_closures ((GObject*) self, "render-mode", (GObject*) _tmp195_, "mode", G_BINDING_DEFAULT | G_BINDING_SYNC_CREATE, (GClosure*) ((NULL == NULL) ? NULL : g_cclosure_new ((GCallback) NULL, NULL, NULL)), (GClosure*) ((NULL == NULL) ? NULL : g_cclosure_new ((GCallback) NULL, NULL, NULL)));
	g_signal_connect_object ((GObject*) self, "notify::render-mode", (GCallback) ___lambda29__g_object_notify, self, 0);
	_tmp196_ = _data2_->builder;
	_tmp197_ = gtk_builder_get_object (_tmp196_, "audio_toggle");
	g_object_bind_property_with_closures ((GObject*) self, "audio", (GObject*) (G_TYPE_CHECK_INSTANCE_TYPE (_tmp197_, TYPE_INK_ROW_TOGGLE_BUTTON) ? ((InkRowToggleButton*) _tmp197_) : NULL), "active", G_BINDING_BIDIRECTIONAL | G_BINDING_SYNC_CREATE, (GClosure*) ((NULL == NULL) ? NULL : g_cclosure_new ((GCallback) NULL, NULL, NULL)), (GClosure*) ((NULL == NULL) ? NULL : g_cclosure_new ((GCallback) NULL, NULL, NULL)));
	g_signal_connect_object ((GObject*) self, "notify::audio", (GCallback) ___lambda30__g_object_notify, self, 0);
	g_signal_connect_object ((GObject*) self, "notify", (GCallback) ___lambda31__g_object_notify, self, 0);
	g_signal_connect_object ((GObject*) self, "notify::is-active", (GCallback) ___lambda32__g_object_notify, self, 0);
	g_signal_connect_object ((GObject*) self, "notify::has-toplevel-focus", (GCallback) ___lambda33__g_object_notify, self, 0);
	_tmp198_ = _data2_->builder;
	_tmp199_ = gtk_builder_get_object (_tmp198_, "open_button");
	g_signal_connect_data (G_TYPE_CHECK_INSTANCE_TYPE (_tmp199_, GTK_TYPE_BUTTON) ? ((GtkButton*) _tmp199_) : NULL, "clicked", (GCallback) ___lambda35__gtk_button_clicked, block2_data_ref (_data2_), (GClosureNotify) block2_data_unref, 0);
	_tmp200_ = _data2_->builder;
	_tmp201_ = gtk_builder_get_object (_tmp200_, "options_button");
	g_signal_connect_data (G_TYPE_CHECK_INSTANCE_TYPE (_tmp201_, GTK_TYPE_TOGGLE_BUTTON) ? ((GtkToggleButton*) _tmp201_) : NULL, "toggled", (GCallback) ___lambda45__gtk_toggle_button_toggled, block2_data_ref (_data2_), (GClosureNotify) block2_data_unref, 0);
	_tmp202_ = _data2_->builder;
	_tmp203_ = gtk_builder_get_object (_tmp202_, "fullscreen_toggle");
	g_object_bind_property_with_closures ((GObject*) self, "fullscreen", (GObject*) (G_TYPE_CHECK_INSTANCE_TYPE (_tmp203_, GTK_TYPE_TOGGLE_BUTTON) ? ((GtkToggleButton*) _tmp203_) : NULL), "active", G_BINDING_BIDIRECTIONAL | G_BINDING_SYNC_CREATE, (GClosure*) ((NULL == NULL) ? NULL : g_cclosure_new ((GCallback) NULL, NULL, NULL)), (GClosure*) ((NULL == NULL) ? NULL : g_cclosure_new ((GCallback) NULL, NULL, NULL)));
	_tmp204_ = _data2_->builder;
	_tmp205_ = gtk_builder_get_object (_tmp204_, "quit_button");
	g_signal_connect_object (G_TYPE_CHECK_INSTANCE_TYPE (_tmp205_, GTK_TYPE_BUTTON) ? ((GtkButton*) _tmp205_) : NULL, "clicked", (GCallback) ___lambda46__gtk_button_clicked, self, 0);
	g_signal_connect_object (self, "emulator-size", (GCallback) ___lambda47__emulator_ui_emulator_size, self, 0);
	g_signal_connect_object ((GtkWidget*) self, "size-allocate", (GCallback) ___lambda48__gtk_widget_size_allocate, self, 0);
	emulator_ui_load_style_rc_file (self);
	gtk_widget_show_all ((GtkWidget*) self);
	_g_object_unref0 (render_mode_toggle);
	_g_object_unref0 (dark_mode_toggle);
	_g_object_unref0 (max_fps_scale);
	_g_object_unref0 (brightness_scale);
	_g_object_unref0 (contrast_scale);
	_tmp33_ = (_vala_array_free (_tmp33_, _tmp33__length1, (GDestroyNotify) g_free), NULL);
	_g_object_unref0 (drawing_area);
	_g_object_unref0 (joypad_area);
	_g_object_unref0 (main_vbox);
	block2_data_unref (_data2_);
	_data2_ = NULL;
	return self;
}


EmulatorUI* emulator_ui_new (GError** error) {
	return emulator_ui_construct (TYPE_EMULATOR_UI, error);
}


static void emulator_ui_save_memory (EmulatorUI* self) {
	GError * _inner_error_ = NULL;
	g_return_if_fail (self != NULL);
	{
		gboolean _tmp0_ = FALSE;
		_tmp0_ = self->priv->running;
		g_static_rec_mutex_lock (&self->priv->__lock_running);
		{
			gchar* game_path_wo_ext = NULL;
			const gchar* _tmp1_ = NULL;
			const gchar* _tmp2_ = NULL;
			gint _tmp3_ = 0;
			gchar* _tmp4_ = NULL;
			gsize ram_size = 0UL;
			RetroCore* _tmp5_ = NULL;
			RetroCoreRetroGetMemorySize _tmp6_ = NULL;
			gsize _tmp7_ = 0UL;
			gsize rtc_size = 0UL;
			RetroCore* _tmp8_ = NULL;
			RetroCoreRetroGetMemorySize _tmp9_ = NULL;
			gsize _tmp10_ = 0UL;
			gsize state_size = 0UL;
			RetroCore* _tmp11_ = NULL;
			RetroCoreRetroSerializeSize _tmp12_ = NULL;
			gsize _tmp13_ = 0UL;
			GFile* ram_file = NULL;
			const gchar* _tmp14_ = NULL;
			gchar* _tmp15_ = NULL;
			gchar* _tmp16_ = NULL;
			GFile* _tmp17_ = NULL;
			GFile* _tmp18_ = NULL;
			GFile* rtc_file = NULL;
			const gchar* _tmp19_ = NULL;
			gchar* _tmp20_ = NULL;
			gchar* _tmp21_ = NULL;
			GFile* _tmp22_ = NULL;
			GFile* _tmp23_ = NULL;
			GFile* state_file = NULL;
			const gchar* _tmp24_ = NULL;
			gchar* _tmp25_ = NULL;
			gchar* _tmp26_ = NULL;
			GFile* _tmp27_ = NULL;
			GFile* _tmp28_ = NULL;
			gsize _tmp29_ = 0UL;
			gsize _tmp30_ = 0UL;
			gsize _tmp31_ = 0UL;
			const gchar* _tmp32_ = NULL;
			gsize _tmp33_ = 0UL;
			_tmp1_ = self->priv->game_path;
			_tmp2_ = self->priv->game_path;
			_tmp3_ = string_last_index_of_char (_tmp2_, (gunichar) '.', 0);
			_tmp4_ = string_substring (_tmp1_, (glong) 0, (glong) _tmp3_);
			game_path_wo_ext = _tmp4_;
			_tmp5_ = self->priv->core;
			_tmp6_ = _tmp5_->retro_get_memory_size;
			_tmp7_ = _tmp6_ ((guint) 0);
			ram_size = _tmp7_;
			_tmp8_ = self->priv->core;
			_tmp9_ = _tmp8_->retro_get_memory_size;
			_tmp10_ = _tmp9_ ((guint) 1);
			rtc_size = _tmp10_;
			_tmp11_ = self->priv->core;
			_tmp12_ = _tmp11_->retro_serialize_size;
			_tmp13_ = _tmp12_ ();
			state_size = _tmp13_;
			_tmp14_ = game_path_wo_ext;
			_tmp15_ = g_strconcat (_tmp14_, ".sav", NULL);
			_tmp16_ = _tmp15_;
			_tmp17_ = g_file_new_for_path (_tmp16_);
			_tmp18_ = _tmp17_;
			_g_free0 (_tmp16_);
			ram_file = _tmp18_;
			_tmp19_ = game_path_wo_ext;
			_tmp20_ = g_strconcat (_tmp19_, ".rtc", NULL);
			_tmp21_ = _tmp20_;
			_tmp22_ = g_file_new_for_path (_tmp21_);
			_tmp23_ = _tmp22_;
			_g_free0 (_tmp21_);
			rtc_file = _tmp23_;
			_tmp24_ = game_path_wo_ext;
			_tmp25_ = g_strconcat (_tmp24_, ".state", NULL);
			_tmp26_ = _tmp25_;
			_tmp27_ = g_file_new_for_path (_tmp26_);
			_tmp28_ = _tmp27_;
			_g_free0 (_tmp26_);
			state_file = _tmp28_;
			_tmp29_ = ram_size;
			_tmp30_ = rtc_size;
			_tmp31_ = state_size;
			_tmp32_ = game_path_wo_ext;
			g_debug ("main.vala:571: SAVE: ram_size %d rtc_size %d state_size %d path %s\n", (gint) _tmp29_, (gint) _tmp30_, (gint) _tmp31_, _tmp32_);
			_tmp33_ = ram_size;
			if (_tmp33_ > ((gsize) 0)) {
				guint8* ram_content = NULL;
				gsize _tmp34_ = 0UL;
				guint8* _tmp35_ = NULL;
				gint ram_content_length1 = 0;
				gint _ram_content_size_ = 0;
				guint8* ram_ptr = NULL;
				RetroCore* _tmp36_ = NULL;
				RetroCoreRetroGetMemoryData _tmp37_ = NULL;
				void* _tmp38_ = NULL;
				guint8* _tmp39_ = NULL;
				gint _tmp39__length1 = 0;
				guint8* _tmp40_ = NULL;
				gsize _tmp41_ = 0UL;
				GFile* _tmp42_ = NULL;
				guint8* _tmp43_ = NULL;
				gint _tmp43__length1 = 0;
				gsize _tmp44_ = 0UL;
				_tmp34_ = ram_size;
				_tmp35_ = g_new0 (guint8, _tmp34_);
				ram_content = _tmp35_;
				ram_content_length1 = _tmp34_;
				_ram_content_size_ = ram_content_length1;
				_tmp36_ = self->priv->core;
				_tmp37_ = _tmp36_->retro_get_memory_data;
				_tmp38_ = _tmp37_ ((guint) 0);
				ram_ptr = (guint8*) _tmp38_;
				_tmp39_ = ram_content;
				_tmp39__length1 = ram_content_length1;
				_tmp40_ = ram_ptr;
				_tmp41_ = ram_size;
				memcpy (_tmp39_, _tmp40_, _tmp41_);
				_tmp42_ = ram_file;
				_tmp43_ = ram_content;
				_tmp43__length1 = ram_content_length1;
				g_file_replace_contents (_tmp42_, _tmp43_, (gsize) _tmp43__length1, NULL, TRUE, G_FILE_CREATE_NONE, NULL, NULL, &_inner_error_);
				if (G_UNLIKELY (_inner_error_ != NULL)) {
					ram_content = (g_free (ram_content), NULL);
					_g_object_unref0 (state_file);
					_g_object_unref0 (rtc_file);
					_g_object_unref0 (ram_file);
					_g_free0 (game_path_wo_ext);
					goto __finally6;
				}
				_tmp44_ = rtc_size;
				if (_tmp44_ > ((gsize) 0)) {
					guint8* rtc_content = NULL;
					gsize _tmp45_ = 0UL;
					guint8* _tmp46_ = NULL;
					gint rtc_content_length1 = 0;
					gint _rtc_content_size_ = 0;
					guint8* rtc_ptr = NULL;
					RetroCore* _tmp47_ = NULL;
					RetroCoreRetroGetMemoryData _tmp48_ = NULL;
					void* _tmp49_ = NULL;
					guint8* _tmp50_ = NULL;
					gint _tmp50__length1 = 0;
					guint8* _tmp51_ = NULL;
					gsize _tmp52_ = 0UL;
					GFile* _tmp53_ = NULL;
					guint8* _tmp54_ = NULL;
					gint _tmp54__length1 = 0;
					_tmp45_ = rtc_size;
					_tmp46_ = g_new0 (guint8, _tmp45_);
					rtc_content = _tmp46_;
					rtc_content_length1 = _tmp45_;
					_rtc_content_size_ = rtc_content_length1;
					_tmp47_ = self->priv->core;
					_tmp48_ = _tmp47_->retro_get_memory_data;
					_tmp49_ = _tmp48_ ((guint) 1);
					rtc_ptr = (guint8*) _tmp49_;
					_tmp50_ = rtc_content;
					_tmp50__length1 = rtc_content_length1;
					_tmp51_ = rtc_ptr;
					_tmp52_ = rtc_size;
					memcpy (_tmp50_, _tmp51_, _tmp52_);
					_tmp53_ = rtc_file;
					_tmp54_ = rtc_content;
					_tmp54__length1 = rtc_content_length1;
					g_file_replace_contents (_tmp53_, _tmp54_, (gsize) _tmp54__length1, NULL, TRUE, G_FILE_CREATE_NONE, NULL, NULL, &_inner_error_);
					if (G_UNLIKELY (_inner_error_ != NULL)) {
						rtc_content = (g_free (rtc_content), NULL);
						ram_content = (g_free (ram_content), NULL);
						_g_object_unref0 (state_file);
						_g_object_unref0 (rtc_file);
						_g_object_unref0 (ram_file);
						_g_free0 (game_path_wo_ext);
						goto __finally6;
					}
					rtc_content = (g_free (rtc_content), NULL);
				}
				ram_content = (g_free (ram_content), NULL);
			} else {
				guint8* state_content = NULL;
				gsize _tmp55_ = 0UL;
				guint8* _tmp56_ = NULL;
				gint state_content_length1 = 0;
				gint _state_content_size_ = 0;
				RetroCore* _tmp57_ = NULL;
				RetroCoreRetroSerialize _tmp58_ = NULL;
				guint8* _tmp59_ = NULL;
				gint _tmp59__length1 = 0;
				gsize _tmp60_ = 0UL;
				GFile* _tmp61_ = NULL;
				guint8* _tmp62_ = NULL;
				gint _tmp62__length1 = 0;
				_tmp55_ = state_size;
				_tmp56_ = g_new0 (guint8, _tmp55_);
				state_content = _tmp56_;
				state_content_length1 = _tmp55_;
				_state_content_size_ = state_content_length1;
				_tmp57_ = self->priv->core;
				_tmp58_ = _tmp57_->retro_serialize;
				_tmp59_ = state_content;
				_tmp59__length1 = state_content_length1;
				_tmp60_ = state_size;
				_tmp58_ (_tmp59_, _tmp60_);
				_tmp61_ = state_file;
				_tmp62_ = state_content;
				_tmp62__length1 = state_content_length1;
				g_file_replace_contents (_tmp61_, _tmp62_, (gsize) _tmp62__length1, NULL, TRUE, G_FILE_CREATE_NONE, NULL, NULL, &_inner_error_);
				if (G_UNLIKELY (_inner_error_ != NULL)) {
					state_content = (g_free (state_content), NULL);
					_g_object_unref0 (state_file);
					_g_object_unref0 (rtc_file);
					_g_object_unref0 (ram_file);
					_g_free0 (game_path_wo_ext);
					goto __finally6;
				}
				state_content = (g_free (state_content), NULL);
			}
			_g_object_unref0 (state_file);
			_g_object_unref0 (rtc_file);
			_g_object_unref0 (ram_file);
			_g_free0 (game_path_wo_ext);
		}
		__finally6:
		{
			gboolean _tmp63_ = FALSE;
			_tmp63_ = self->priv->running;
			g_static_rec_mutex_unlock (&self->priv->__lock_running);
		}
		if (G_UNLIKELY (_inner_error_ != NULL)) {
			g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
			g_clear_error (&_inner_error_);
			return;
		}
	}
}


static void emulator_ui_load_memory (EmulatorUI* self) {
	GError * _inner_error_ = NULL;
	g_return_if_fail (self != NULL);
	{
		gboolean _tmp0_ = FALSE;
		_tmp0_ = self->priv->running;
		g_static_rec_mutex_lock (&self->priv->__lock_running);
		{
			gchar* game_path_wo_ext = NULL;
			const gchar* _tmp1_ = NULL;
			const gchar* _tmp2_ = NULL;
			gint _tmp3_ = 0;
			gchar* _tmp4_ = NULL;
			gsize ram_size = 0UL;
			RetroCore* _tmp5_ = NULL;
			RetroCoreRetroGetMemorySize _tmp6_ = NULL;
			gsize _tmp7_ = 0UL;
			gsize rtc_size = 0UL;
			RetroCore* _tmp8_ = NULL;
			RetroCoreRetroGetMemorySize _tmp9_ = NULL;
			gsize _tmp10_ = 0UL;
			gsize state_size = 0UL;
			RetroCore* _tmp11_ = NULL;
			RetroCoreRetroSerializeSize _tmp12_ = NULL;
			gsize _tmp13_ = 0UL;
			GFile* ram_file = NULL;
			const gchar* _tmp14_ = NULL;
			gchar* _tmp15_ = NULL;
			gchar* _tmp16_ = NULL;
			GFile* _tmp17_ = NULL;
			GFile* _tmp18_ = NULL;
			GFile* rtc_file = NULL;
			const gchar* _tmp19_ = NULL;
			gchar* _tmp20_ = NULL;
			gchar* _tmp21_ = NULL;
			GFile* _tmp22_ = NULL;
			GFile* _tmp23_ = NULL;
			GFile* state_file = NULL;
			const gchar* _tmp24_ = NULL;
			gchar* _tmp25_ = NULL;
			gchar* _tmp26_ = NULL;
			GFile* _tmp27_ = NULL;
			GFile* _tmp28_ = NULL;
			gsize _tmp29_ = 0UL;
			gsize _tmp30_ = 0UL;
			gsize _tmp31_ = 0UL;
			const gchar* _tmp32_ = NULL;
			gboolean _tmp33_ = FALSE;
			gsize _tmp34_ = 0UL;
			_tmp1_ = self->priv->game_path;
			_tmp2_ = self->priv->game_path;
			_tmp3_ = string_last_index_of_char (_tmp2_, (gunichar) '.', 0);
			_tmp4_ = string_substring (_tmp1_, (glong) 0, (glong) _tmp3_);
			game_path_wo_ext = _tmp4_;
			_tmp5_ = self->priv->core;
			_tmp6_ = _tmp5_->retro_get_memory_size;
			_tmp7_ = _tmp6_ ((guint) 0);
			ram_size = _tmp7_;
			_tmp8_ = self->priv->core;
			_tmp9_ = _tmp8_->retro_get_memory_size;
			_tmp10_ = _tmp9_ ((guint) 1);
			rtc_size = _tmp10_;
			_tmp11_ = self->priv->core;
			_tmp12_ = _tmp11_->retro_serialize_size;
			_tmp13_ = _tmp12_ ();
			state_size = _tmp13_;
			_tmp14_ = game_path_wo_ext;
			_tmp15_ = g_strconcat (_tmp14_, ".sav", NULL);
			_tmp16_ = _tmp15_;
			_tmp17_ = g_file_new_for_path (_tmp16_);
			_tmp18_ = _tmp17_;
			_g_free0 (_tmp16_);
			ram_file = _tmp18_;
			_tmp19_ = game_path_wo_ext;
			_tmp20_ = g_strconcat (_tmp19_, ".rtc", NULL);
			_tmp21_ = _tmp20_;
			_tmp22_ = g_file_new_for_path (_tmp21_);
			_tmp23_ = _tmp22_;
			_g_free0 (_tmp21_);
			rtc_file = _tmp23_;
			_tmp24_ = game_path_wo_ext;
			_tmp25_ = g_strconcat (_tmp24_, ".state", NULL);
			_tmp26_ = _tmp25_;
			_tmp27_ = g_file_new_for_path (_tmp26_);
			_tmp28_ = _tmp27_;
			_g_free0 (_tmp26_);
			state_file = _tmp28_;
			_tmp29_ = ram_size;
			_tmp30_ = rtc_size;
			_tmp31_ = state_size;
			_tmp32_ = game_path_wo_ext;
			g_debug ("main.vala:608: LOAD: ram_size %d rtc_size %d state_size %d path %s\n", (gint) _tmp29_, (gint) _tmp30_, (gint) _tmp31_, _tmp32_);
			_tmp34_ = ram_size;
			if (_tmp34_ > ((gsize) 0)) {
				GFile* _tmp35_ = NULL;
				gboolean _tmp36_ = FALSE;
				_tmp35_ = ram_file;
				_tmp36_ = g_file_query_exists (_tmp35_, NULL);
				_tmp33_ = _tmp36_;
			} else {
				_tmp33_ = FALSE;
			}
			if (_tmp33_) {
				guint8* ram_content = NULL;
				gint ram_content_length1 = 0;
				gint _ram_content_size_ = 0;
				GFile* _tmp37_ = NULL;
				guint8* _tmp38_ = NULL;
				gsize _tmp39_;
				guint8* _tmp40_ = NULL;
				gint _tmp40__length1 = 0;
				guint8* ram_ptr = NULL;
				RetroCore* _tmp41_ = NULL;
				RetroCoreRetroGetMemoryData _tmp42_ = NULL;
				void* _tmp43_ = NULL;
				guint8* _tmp44_ = NULL;
				gint _tmp44__length1 = 0;
				gsize _tmp45_ = 0UL;
				_tmp37_ = ram_file;
				g_file_load_contents (_tmp37_, NULL, &_tmp38_, &_tmp39_, NULL, &_inner_error_);
				ram_content = (g_free (ram_content), NULL);
				ram_content = _tmp38_;
				ram_content_length1 = _tmp39_;
				_ram_content_size_ = ram_content_length1;
				if (G_UNLIKELY (_inner_error_ != NULL)) {
					ram_content = (g_free (ram_content), NULL);
					_g_object_unref0 (state_file);
					_g_object_unref0 (rtc_file);
					_g_object_unref0 (ram_file);
					_g_free0 (game_path_wo_ext);
					goto __finally7;
				}
				_tmp40_ = ram_content;
				_tmp40__length1 = ram_content_length1;
				g_debug ("main.vala:616: ram_content lenght %d\n", _tmp40__length1);
				_tmp41_ = self->priv->core;
				_tmp42_ = _tmp41_->retro_get_memory_data;
				_tmp43_ = _tmp42_ ((guint) 0);
				ram_ptr = (guint8*) _tmp43_;
				_tmp44_ = ram_content;
				_tmp44__length1 = ram_content_length1;
				_tmp45_ = ram_size;
				if (((gsize) _tmp44__length1) <= _tmp45_) {
					guint8* _tmp46_ = NULL;
					guint8* _tmp47_ = NULL;
					gint _tmp47__length1 = 0;
					gsize _tmp48_ = 0UL;
					gboolean _tmp49_ = FALSE;
					gsize _tmp50_ = 0UL;
					g_debug ("main.vala:622: restoring ram_content\n");
					_tmp46_ = ram_ptr;
					_tmp47_ = ram_content;
					_tmp47__length1 = ram_content_length1;
					_tmp48_ = ram_size;
					memcpy (_tmp46_, _tmp47_, _tmp48_);
					_tmp50_ = rtc_size;
					if (_tmp50_ > ((gsize) 0)) {
						GFile* _tmp51_ = NULL;
						gboolean _tmp52_ = FALSE;
						_tmp51_ = rtc_file;
						_tmp52_ = g_file_query_exists (_tmp51_, NULL);
						_tmp49_ = _tmp52_;
					} else {
						_tmp49_ = FALSE;
					}
					if (_tmp49_) {
						guint8* rtc_content = NULL;
						gint rtc_content_length1 = 0;
						gint _rtc_content_size_ = 0;
						GFile* _tmp53_ = NULL;
						guint8* _tmp54_ = NULL;
						gsize _tmp55_;
						guint8* _tmp56_ = NULL;
						gint _tmp56__length1 = 0;
						guint8* rtc_ptr = NULL;
						RetroCore* _tmp57_ = NULL;
						RetroCoreRetroGetMemoryData _tmp58_ = NULL;
						void* _tmp59_ = NULL;
						guint8* _tmp60_ = NULL;
						gint _tmp60__length1 = 0;
						gsize _tmp61_ = 0UL;
						_tmp53_ = rtc_file;
						g_file_load_contents (_tmp53_, NULL, &_tmp54_, &_tmp55_, NULL, &_inner_error_);
						rtc_content = (g_free (rtc_content), NULL);
						rtc_content = _tmp54_;
						rtc_content_length1 = _tmp55_;
						_rtc_content_size_ = rtc_content_length1;
						if (G_UNLIKELY (_inner_error_ != NULL)) {
							rtc_content = (g_free (rtc_content), NULL);
							ram_content = (g_free (ram_content), NULL);
							_g_object_unref0 (state_file);
							_g_object_unref0 (rtc_file);
							_g_object_unref0 (ram_file);
							_g_free0 (game_path_wo_ext);
							goto __finally7;
						}
						_tmp56_ = rtc_content;
						_tmp56__length1 = rtc_content_length1;
						g_debug ("main.vala:632: rtc_content lenght %d\n", _tmp56__length1);
						_tmp57_ = self->priv->core;
						_tmp58_ = _tmp57_->retro_get_memory_data;
						_tmp59_ = _tmp58_ ((guint) 1);
						rtc_ptr = (guint8*) _tmp59_;
						_tmp60_ = rtc_content;
						_tmp60__length1 = rtc_content_length1;
						_tmp61_ = rtc_size;
						if (((gsize) _tmp60__length1) <= _tmp61_) {
							guint8* _tmp62_ = NULL;
							guint8* _tmp63_ = NULL;
							gint _tmp63__length1 = 0;
							gsize _tmp64_ = 0UL;
							_tmp62_ = rtc_ptr;
							_tmp63_ = rtc_content;
							_tmp63__length1 = rtc_content_length1;
							_tmp64_ = rtc_size;
							memcpy (_tmp62_, _tmp63_, _tmp64_);
						}
						rtc_content = (g_free (rtc_content), NULL);
					}
				}
				ram_content = (g_free (ram_content), NULL);
			} else {
				gboolean _tmp65_ = FALSE;
				gsize _tmp66_ = 0UL;
				_tmp66_ = state_size;
				if (_tmp66_ > ((gsize) 0)) {
					GFile* _tmp67_ = NULL;
					gboolean _tmp68_ = FALSE;
					_tmp67_ = state_file;
					_tmp68_ = g_file_query_exists (_tmp67_, NULL);
					_tmp65_ = _tmp68_;
				} else {
					_tmp65_ = FALSE;
				}
				if (_tmp65_) {
					guint8* state_content = NULL;
					gint state_content_length1 = 0;
					gint _state_content_size_ = 0;
					GFile* _tmp69_ = NULL;
					guint8* _tmp70_ = NULL;
					gsize _tmp71_;
					guint8* _tmp72_ = NULL;
					gint _tmp72__length1 = 0;
					guint8* _tmp73_ = NULL;
					gint _tmp73__length1 = 0;
					gsize _tmp74_ = 0UL;
					_tmp69_ = state_file;
					g_file_load_contents (_tmp69_, NULL, &_tmp70_, &_tmp71_, NULL, &_inner_error_);
					state_content = (g_free (state_content), NULL);
					state_content = _tmp70_;
					state_content_length1 = _tmp71_;
					_state_content_size_ = state_content_length1;
					if (G_UNLIKELY (_inner_error_ != NULL)) {
						state_content = (g_free (state_content), NULL);
						_g_object_unref0 (state_file);
						_g_object_unref0 (rtc_file);
						_g_object_unref0 (ram_file);
						_g_free0 (game_path_wo_ext);
						goto __finally7;
					}
					_tmp72_ = state_content;
					_tmp72__length1 = state_content_length1;
					g_debug ("main.vala:650: state_content lenght %d\n", _tmp72__length1);
					_tmp73_ = state_content;
					_tmp73__length1 = state_content_length1;
					_tmp74_ = state_size;
					if (((gsize) _tmp73__length1) == _tmp74_) {
						RetroCore* _tmp75_ = NULL;
						RetroCoreRetroUnserialize _tmp76_ = NULL;
						guint8* _tmp77_ = NULL;
						gint _tmp77__length1 = 0;
						gsize _tmp78_ = 0UL;
						_tmp75_ = self->priv->core;
						_tmp76_ = _tmp75_->retro_unserialize;
						_tmp77_ = state_content;
						_tmp77__length1 = state_content_length1;
						_tmp78_ = state_size;
						_tmp76_ (_tmp77_, _tmp78_);
					}
					state_content = (g_free (state_content), NULL);
				}
			}
			_g_object_unref0 (state_file);
			_g_object_unref0 (rtc_file);
			_g_object_unref0 (ram_file);
			_g_free0 (game_path_wo_ext);
		}
		__finally7:
		{
			gboolean _tmp79_ = FALSE;
			_tmp79_ = self->priv->running;
			g_static_rec_mutex_unlock (&self->priv->__lock_running);
		}
		if (G_UNLIKELY (_inner_error_ != NULL)) {
			g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
			g_clear_error (&_inner_error_);
			return;
		}
	}
}


static gboolean __lambda14_ (EmulatorUI* self) {
	gboolean result = FALSE;
	gchar* data = NULL;
	GKeyFile* _tmp0_ = NULL;
	gchar* _tmp1_ = NULL;
	FILE* fs = NULL;
	const gchar* _tmp2_ = NULL;
	FILE* _tmp3_ = NULL;
	g_debug ("main.vala:672: save_settings");
	_tmp0_ = self->priv->kf;
	_tmp1_ = g_key_file_to_data (_tmp0_, NULL, NULL);
	data = _tmp1_;
	_tmp2_ = emulator_ui_config_file;
	_tmp3_ = fopen (_tmp2_, "w");
	fs = _tmp3_;
	fputs (data, fs);
	self->priv->save_settings_timeout_id = (guint) 0;
	result = FALSE;
	_fclose0 (fs);
	_g_free0 (data);
	return result;
}


static gboolean ___lambda14__gsource_func (gpointer self) {
	gboolean result;
	result = __lambda14_ ((EmulatorUI*) self);
	return result;
}


static void emulator_ui_save_settings (EmulatorUI* self) {
	guint _tmp0_ = 0U;
	guint _tmp2_ = 0U;
	g_return_if_fail (self != NULL);
	_tmp0_ = self->priv->save_settings_timeout_id;
	if (_tmp0_ != ((guint) 0)) {
		guint _tmp1_ = 0U;
		_tmp1_ = self->priv->save_settings_timeout_id;
		g_source_remove (_tmp1_);
	}
	_tmp2_ = g_timeout_add_full (G_PRIORITY_DEFAULT, (guint) 1000, ___lambda14__gsource_func, g_object_ref (self), g_object_unref);
	self->priv->save_settings_timeout_id = _tmp2_;
}


static void emulator_ui_resize_drawing_area_and_buffers (EmulatorUI* self) {
	gint scale = 0;
	GtkAllocation _tmp0_ = {0};
	gint _tmp1_ = 0;
	guint _tmp2_ = 0U;
	guint _tmp3_ = 0U;
	gint _tmp4_ = 0;
	gint _tmp5_ = 0;
	gint width = 0;
	gint _tmp6_ = 0;
	gint _tmp7_ = 0;
	gint height = 0;
	gint _tmp8_ = 0;
	gint _tmp9_ = 0;
	gboolean _tmp10_ = FALSE;
	GameScreen* _tmp11_ = NULL;
	gint _tmp12_ = 0;
	gint _tmp13_ = 0;
	gint _tmp14_ = 0;
	g_return_if_fail (self != NULL);
	_tmp0_ = ((GtkWidget*) self)->allocation;
	_tmp1_ = _tmp0_.width;
	_tmp2_ = gtk_container_get_border_width ((GtkContainer*) self);
	_tmp3_ = _tmp2_;
	_tmp4_ = MIN (_tmp1_ - (((gint) _tmp3_) * 2), 1000);
	_tmp5_ = self->priv->core_width;
	scale = (_tmp4_ - 40) / _tmp5_;
	_tmp6_ = scale;
	_tmp7_ = self->priv->core_width;
	width = _tmp6_ * _tmp7_;
	_tmp8_ = scale;
	_tmp9_ = self->priv->core_height;
	height = _tmp8_ * _tmp9_;
	_tmp11_ = self->priv->gamescreen;
	_tmp12_ = game_screen_get_width (_tmp11_);
	_tmp13_ = _tmp12_;
	_tmp14_ = width;
	if (_tmp13_ != _tmp14_) {
		_tmp10_ = TRUE;
	} else {
		GameScreen* _tmp15_ = NULL;
		gint _tmp16_ = 0;
		gint _tmp17_ = 0;
		gint _tmp18_ = 0;
		_tmp15_ = self->priv->gamescreen;
		_tmp16_ = game_screen_get_height (_tmp15_);
		_tmp17_ = _tmp16_;
		_tmp18_ = height;
		_tmp10_ = _tmp17_ != _tmp18_;
	}
	if (_tmp10_) {
		GameScreen* _tmp19_ = NULL;
		gint _tmp20_ = 0;
		gint _tmp21_ = 0;
		gint _tmp22_ = 0;
		_tmp19_ = self->priv->gamescreen;
		_tmp20_ = self->priv->core_width;
		_tmp21_ = self->priv->core_height;
		_tmp22_ = scale;
		game_screen_resize (_tmp19_, _tmp20_, _tmp21_, _tmp22_);
	}
}


static Block3Data* block3_data_ref (Block3Data* _data3_) {
	g_atomic_int_inc (&_data3_->_ref_count_);
	return _data3_;
}


static void block3_data_unref (void * _userdata_) {
	Block3Data* _data3_;
	_data3_ = (Block3Data*) _userdata_;
	if (g_atomic_int_dec_and_test (&_data3_->_ref_count_)) {
		EmulatorUI* self;
		self = _data3_->self;
		_g_object_unref0 (self);
		g_slice_free (Block3Data, _data3_);
	}
}


static gboolean __lambda49_ (Block3Data* _data3_, GMatchInfo* mi, GString* _result_) {
	EmulatorUI* self;
	gboolean result = FALSE;
	gchar* s = NULL;
	GMatchInfo* _tmp0_ = NULL;
	gchar* _tmp1_ = NULL;
	gint n = 0;
	gint _tmp2_ = 0;
	GString* _tmp3_ = NULL;
	gdouble _tmp4_ = 0.0;
	gchar* _tmp5_ = NULL;
	gchar* _tmp6_ = NULL;
	gdouble _tmp7_ = 0.0;
	gdouble _tmp8_ = 0.0;
	gchar* _tmp9_ = NULL;
	gchar* _tmp10_ = NULL;
	self = _data3_->self;
	g_return_val_if_fail (mi != NULL, FALSE);
	g_return_val_if_fail (_result_ != NULL, FALSE);
	_tmp0_ = mi;
	_tmp1_ = g_match_info_fetch (_tmp0_, 1);
	s = _tmp1_;
	_tmp2_ = atoi (s);
	n = _tmp2_;
	_tmp3_ = _result_;
	_tmp4_ = _data3_->scaling;
	_tmp5_ = g_strdup_printf ("%i", (gint) (n * _tmp4_));
	_tmp6_ = _tmp5_;
	g_string_append (_tmp3_, _tmp6_);
	_g_free0 (_tmp6_);
	_tmp7_ = _data3_->scaling;
	_tmp8_ = _data3_->scaling;
	_tmp9_ = g_strdup_printf ("%i", (gint) (n * _tmp8_));
	_tmp10_ = _tmp9_;
	g_debug ("main.vala:768: scaling %f %s to %s", _tmp7_, s, _tmp10_);
	_g_free0 (_tmp10_);
	result = FALSE;
	_g_free0 (s);
	return result;
}


static gboolean ___lambda49__gregex_eval_callback (GMatchInfo* match_info, GString* _result_, gpointer self) {
	gboolean result;
	result = __lambda49_ (self, match_info, _result_);
	return result;
}


static void emulator_ui_load_style_rc_file (EmulatorUI* self) {
	Block3Data* _data3_;
	gchar* contents = NULL;
	gchar* _tmp0_ = NULL;
	GdkScreen* _tmp1_ = NULL;
	gint _tmp2_ = 0;
	GRegex* regex = NULL;
	GRegex* _tmp3_ = NULL;
	gchar* style_rc_file_content = NULL;
	GRegex* _tmp4_ = NULL;
	const gchar* _tmp5_ = NULL;
	const gchar* _tmp6_ = NULL;
	gint _tmp7_ = 0;
	gint _tmp8_ = 0;
	gchar* _tmp9_ = NULL;
	const gchar* _tmp10_ = NULL;
	GError * _inner_error_ = NULL;
	g_return_if_fail (self != NULL);
	_data3_ = g_slice_new0 (Block3Data);
	_data3_->_ref_count_ = 1;
	_data3_->self = g_object_ref (self);
	_tmp0_ = g_strdup ("\n" \
"            style \"app-font\" {\n" \
"                font_name = \"Amazon Ember Regular 10\"\n" \
"            }\n" \
"            widget_class \"*\" style \"app-font\"\n" \
"\n" \
"            style \"primary\" {\n" \
"                bg[NORMAL]   = \"#000000\" # normal background (0)\n" \
"                fg[NORMAL]   = \"#FFFFFF\" # normal text (0) \n" \
"                bg[ACTIVE]   = \"#FFFFFF\" # pressed (active toggle?) " \
"background (1)\n" \
"                fg[ACTIVE]   = \"#000000\" # pressed (active toggle?) " \
"text (1)\n" \
"                bg[SELECTED] = \"#000000\" # ?\n" \
"                fg[SELECTED] = \"#FFFFFF\" # ?      \n" \
"                bg[PRELIGHT] = \"#000000\" # hover background (2)\n" \
"                fg[PRELIGHT] = \"#FFFFFF\" # hover text (2)\n" \
"            }\n" \
"            style \"secondary\" {\n" \
"                bg[NORMAL]   = \"#FFFFFF\" # normal background\n" \
"                fg[NORMAL]   = \"#000000\" # normal text  \n" \
"                bg[ACTIVE]   = \"#000000\" # pressed (active?) backgro" \
"und \n" \
"                fg[ACTIVE]   = \"#FFFFFF\" # pressed (active?) text \n" \
"                bg[SELECTED] = \"#FFFFFF\" # ?\n" \
"                fg[SELECTED] = \"#000000\" # ?      \n" \
"                bg[PRELIGHT] = \"#FFFFFF\" # hover background\n" \
"                fg[PRELIGHT] = \"#000000\" # hover text\n" \
"            }\n" \
"            widget \"*app-dark*\" style \"primary\"\n" \
"            widget \"*app-dark*.drawing-area-container\" style \"secon" \
"dary\"\n" \
"            widget \"*app-light*\" style \"secondary\"\n" \
"            widget \"*app-light*.drawing-area-container\" style \"prim" \
"ary\"\n" \
"\n" \
"            style \"button\" {\n" \
"                xthickness = 0\n" \
"                ythickness = 0\n" \
"                GtkWidget::focus-line-width = 0\n" \
"                GtkWidget::focus-padding = 0    \n" \
"            }\n" \
"            widget_class \"*GtkButton\" style \"button\"\n" \
"            widget_class \"*GtkToggleButton\" style \"button\"\n" \
"            widget_class \"*GtkRadioButton\" style \"button\"\n" \
"            widget_class \"*InkRadioButton\" style \"button\"\n" \
"            widget_class \"*InkToggleButton\" style \"button\"\n" \
"\n" \
"            style \"slider\"\n" \
"            {\n" \
"                font_name = \"Amazon Ember Regular 8\"\n" \
"                GtkRange::trough-border = 0\n" \
"                GtkRange::slider-width = @35\n" \
"                GtkScale::slider-length = @35    \n" \
"            }\n" \
"            widget_class \"*InkHScale\" style \"slider\"\n" \
"            widget_class \"*GtkHScale\" style \"slider\"\n" \
"        ");
	contents = _tmp0_;
	_tmp1_ = gtk_window_get_screen ((GtkWindow*) self);
	_tmp2_ = gdk_screen_get_width (_tmp1_);
	_data3_->scaling = _tmp2_ / 600.0;
	_tmp3_ = g_regex_new ("@(\\d+)", 0, 0, &_inner_error_);
	regex = _tmp3_;
	if (G_UNLIKELY (_inner_error_ != NULL)) {
		_g_free0 (contents);
		block3_data_unref (_data3_);
		_data3_ = NULL;
		g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
		g_clear_error (&_inner_error_);
		return;
	}
	_tmp4_ = regex;
	_tmp5_ = contents;
	_tmp6_ = contents;
	_tmp7_ = strlen (_tmp6_);
	_tmp8_ = _tmp7_;
	_tmp9_ = g_regex_replace_eval (_tmp4_, (const gchar*) _tmp5_, (gssize) _tmp8_, 0, 0, ___lambda49__gregex_eval_callback, _data3_, &_inner_error_);
	style_rc_file_content = _tmp9_;
	if (G_UNLIKELY (_inner_error_ != NULL)) {
		_g_regex_unref0 (regex);
		_g_free0 (contents);
		block3_data_unref (_data3_);
		_data3_ = NULL;
		g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
		g_clear_error (&_inner_error_);
		return;
	}
	_tmp10_ = style_rc_file_content;
	gtk_rc_parse_string (_tmp10_);
	_g_free0 (style_rc_file_content);
	_g_regex_unref0 (regex);
	_g_free0 (contents);
	block3_data_unref (_data3_);
	_data3_ = NULL;
}


static void emulator_ui_reload_styles (EmulatorUI* self) {
	g_return_if_fail (self != NULL);
	gtk_widget_reset_rc_styles ((GtkWidget*) self);
}


static gpointer _emulator_ui_core_thread_fn_gthread_func (gpointer self) {
	gpointer result;
	result = emulator_ui_core_thread_fn ();
	return result;
}


static void emulator_ui_play_game (EmulatorUI* self) {
	GThread* _tmp7_ = NULL;
	GThread* _tmp8_ = NULL;
	GameScreen* _tmp9_ = NULL;
	GameJoypad* _tmp10_ = NULL;
	gboolean _tmp11_ = FALSE;
	GError * _inner_error_ = NULL;
	g_return_if_fail (self != NULL);
	g_debug ("main.vala:786: play_game");
	{
		gboolean _tmp0_ = FALSE;
		_tmp0_ = self->priv->running;
		g_static_rec_mutex_lock (&self->priv->__lock_running);
		{
			gboolean _tmp1_ = FALSE;
			_tmp1_ = self->priv->running;
			if (_tmp1_) {
				{
					gboolean _tmp2_ = FALSE;
					_tmp2_ = self->priv->running;
					g_static_rec_mutex_unlock (&self->priv->__lock_running);
				}
				return;
			}
			self->priv->running = TRUE;
			{
				gboolean _tmp3_ = FALSE;
				_tmp3_ = self->priv->paused;
				g_static_rec_mutex_lock (&self->priv->__lock_paused);
				{
					self->priv->paused = FALSE;
				}
				__finally9:
				{
					gboolean _tmp4_ = FALSE;
					_tmp4_ = self->priv->paused;
					g_static_rec_mutex_unlock (&self->priv->__lock_paused);
				}
				if (G_UNLIKELY (_inner_error_ != NULL)) {
					{
						gboolean _tmp5_ = FALSE;
						_tmp5_ = self->priv->running;
						g_static_rec_mutex_unlock (&self->priv->__lock_running);
					}
					g_critical ("file %s: line %d: unexpected error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
					g_clear_error (&_inner_error_);
					return;
				}
			}
		}
		__finally8:
		{
			gboolean _tmp6_ = FALSE;
			_tmp6_ = self->priv->running;
			g_static_rec_mutex_unlock (&self->priv->__lock_running);
		}
		if (G_UNLIKELY (_inner_error_ != NULL)) {
			g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
			g_clear_error (&_inner_error_);
			return;
		}
	}
	g_debug ("main.vala:798: game about to start");
	_tmp8_ = g_thread_create (_emulator_ui_core_thread_fn_gthread_func, NULL, TRUE, &_inner_error_);
	_tmp7_ = _tmp8_;
	if (G_UNLIKELY (_inner_error_ != NULL)) {
		g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
		g_clear_error (&_inner_error_);
		return;
	}
	self->priv->core_thread = _tmp7_;
	_tmp9_ = self->priv->gamescreen;
	game_screen_start (_tmp9_);
	_tmp10_ = self->priv->gamejoypad;
	game_joypad_start (_tmp10_);
	_tmp11_ = self->priv->_audio;
	if (_tmp11_) {
		GameSpeaker* _tmp12_ = NULL;
		_tmp12_ = self->priv->gamespeaker;
		game_speaker_start (_tmp12_);
	}
	g_debug ("main.vala:803: game started");
}


void emulator_ui_resume_game (EmulatorUI* self) {
	GThread* _tmp10_ = NULL;
	GThread* _tmp11_ = NULL;
	GameScreen* _tmp12_ = NULL;
	GameScreen* _tmp13_ = NULL;
	GtkDrawingArea* _tmp14_ = NULL;
	GameJoypad* _tmp15_ = NULL;
	gboolean _tmp16_ = FALSE;
	GError * _inner_error_ = NULL;
	g_return_if_fail (self != NULL);
	g_debug ("main.vala:807: resume_game");
	{
		gboolean _tmp0_ = FALSE;
		_tmp0_ = self->priv->running;
		g_static_rec_mutex_lock (&self->priv->__lock_running);
		{
			gboolean _tmp1_ = FALSE;
			_tmp1_ = self->priv->running;
			if (!_tmp1_) {
				{
					gboolean _tmp2_ = FALSE;
					_tmp2_ = self->priv->running;
					g_static_rec_mutex_unlock (&self->priv->__lock_running);
				}
				return;
			}
			{
				gboolean _tmp3_ = FALSE;
				_tmp3_ = self->priv->paused;
				g_static_rec_mutex_lock (&self->priv->__lock_paused);
				{
					gboolean _tmp4_ = FALSE;
					_tmp4_ = self->priv->paused;
					if (!_tmp4_) {
						{
							gboolean _tmp5_ = FALSE;
							_tmp5_ = self->priv->paused;
							g_static_rec_mutex_unlock (&self->priv->__lock_paused);
						}
						{
							gboolean _tmp6_ = FALSE;
							_tmp6_ = self->priv->running;
							g_static_rec_mutex_unlock (&self->priv->__lock_running);
						}
						return;
					}
					self->priv->paused = FALSE;
				}
				__finally11:
				{
					gboolean _tmp7_ = FALSE;
					_tmp7_ = self->priv->paused;
					g_static_rec_mutex_unlock (&self->priv->__lock_paused);
				}
				if (G_UNLIKELY (_inner_error_ != NULL)) {
					{
						gboolean _tmp8_ = FALSE;
						_tmp8_ = self->priv->running;
						g_static_rec_mutex_unlock (&self->priv->__lock_running);
					}
					g_critical ("file %s: line %d: unexpected error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
					g_clear_error (&_inner_error_);
					return;
				}
			}
		}
		__finally10:
		{
			gboolean _tmp9_ = FALSE;
			_tmp9_ = self->priv->running;
			g_static_rec_mutex_unlock (&self->priv->__lock_running);
		}
		if (G_UNLIKELY (_inner_error_ != NULL)) {
			g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
			g_clear_error (&_inner_error_);
			return;
		}
	}
	g_debug ("main.vala:819: game about to resume");
	_tmp11_ = g_thread_create (_emulator_ui_core_thread_fn_gthread_func, NULL, TRUE, &_inner_error_);
	_tmp10_ = _tmp11_;
	if (G_UNLIKELY (_inner_error_ != NULL)) {
		g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
		g_clear_error (&_inner_error_);
		return;
	}
	self->priv->core_thread = _tmp10_;
	_tmp12_ = self->priv->gamescreen;
	game_screen_start (_tmp12_);
	_tmp13_ = self->priv->gamescreen;
	_tmp14_ = _tmp13_->drawing_area;
	gtk_widget_queue_draw ((GtkWidget*) _tmp14_);
	_tmp15_ = self->priv->gamejoypad;
	game_joypad_start (_tmp15_);
	_tmp16_ = self->priv->_audio;
	if (_tmp16_) {
		GameSpeaker* _tmp17_ = NULL;
		_tmp17_ = self->priv->gamespeaker;
		game_speaker_start (_tmp17_);
	}
	g_debug ("main.vala:827: game resumed");
}


static void emulator_ui_stop_game (EmulatorUI* self) {
	GThread* _tmp13_ = NULL;
	GameScreen* _tmp14_ = NULL;
	GameJoypad* _tmp15_ = NULL;
	GameSpeaker* _tmp16_ = NULL;
	GError * _inner_error_ = NULL;
	g_return_if_fail (self != NULL);
	g_debug ("main.vala:832: stop_game");
	{
		gboolean _tmp0_ = FALSE;
		_tmp0_ = self->priv->running;
		g_static_rec_mutex_lock (&self->priv->__lock_running);
		{
			gboolean _tmp1_ = FALSE;
			gboolean _tmp3_ = FALSE;
			gboolean _tmp4_ = FALSE;
			_tmp1_ = self->priv->running;
			if (!_tmp1_) {
				{
					gboolean _tmp2_ = FALSE;
					_tmp2_ = self->priv->running;
					g_static_rec_mutex_unlock (&self->priv->__lock_running);
				}
				return;
			}
			_tmp4_ = self->priv->autosave;
			if (_tmp4_) {
				gboolean _tmp5_ = FALSE;
				_tmp5_ = self->priv->game_memory_loaded;
				_tmp3_ = _tmp5_;
			} else {
				_tmp3_ = FALSE;
			}
			if (_tmp3_) {
				g_debug ("main.vala:839: auto saving...");
				emulator_ui_save_memory (self);
			}
			self->priv->running = FALSE;
			{
				gboolean _tmp6_ = FALSE;
				_tmp6_ = self->priv->paused;
				g_static_rec_mutex_lock (&self->priv->__lock_paused);
				{
					gboolean _tmp7_ = FALSE;
					_tmp7_ = self->priv->paused;
					if (_tmp7_) {
						self->priv->paused = FALSE;
						{
							gboolean _tmp8_ = FALSE;
							_tmp8_ = self->priv->paused;
							g_static_rec_mutex_unlock (&self->priv->__lock_paused);
						}
						{
							gboolean _tmp9_ = FALSE;
							_tmp9_ = self->priv->running;
							g_static_rec_mutex_unlock (&self->priv->__lock_running);
						}
						return;
					}
				}
				__finally13:
				{
					gboolean _tmp10_ = FALSE;
					_tmp10_ = self->priv->paused;
					g_static_rec_mutex_unlock (&self->priv->__lock_paused);
				}
				if (G_UNLIKELY (_inner_error_ != NULL)) {
					{
						gboolean _tmp11_ = FALSE;
						_tmp11_ = self->priv->running;
						g_static_rec_mutex_unlock (&self->priv->__lock_running);
					}
					g_critical ("file %s: line %d: unexpected error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
					g_clear_error (&_inner_error_);
					return;
				}
			}
		}
		__finally12:
		{
			gboolean _tmp12_ = FALSE;
			_tmp12_ = self->priv->running;
			g_static_rec_mutex_unlock (&self->priv->__lock_running);
		}
		if (G_UNLIKELY (_inner_error_ != NULL)) {
			g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
			g_clear_error (&_inner_error_);
			return;
		}
	}
	g_debug ("main.vala:854: game about to stop");
	_tmp13_ = self->priv->core_thread;
	g_thread_join (_tmp13_);
	_tmp14_ = self->priv->gamescreen;
	game_screen_stop (_tmp14_);
	_tmp15_ = self->priv->gamejoypad;
	game_joypad_stop (_tmp15_);
	_tmp16_ = self->priv->gamespeaker;
	game_speaker_stop (_tmp16_);
	g_debug ("main.vala:859: game stopped!\n");
}


void emulator_ui_pause_game (EmulatorUI* self) {
	GThread* _tmp13_ = NULL;
	GameScreen* _tmp14_ = NULL;
	GameJoypad* _tmp15_ = NULL;
	GameSpeaker* _tmp16_ = NULL;
	GError * _inner_error_ = NULL;
	g_return_if_fail (self != NULL);
	g_debug ("main.vala:863: pause_game");
	{
		gboolean _tmp0_ = FALSE;
		_tmp0_ = self->priv->running;
		g_static_rec_mutex_lock (&self->priv->__lock_running);
		{
			gboolean _tmp1_ = FALSE;
			gboolean _tmp3_ = FALSE;
			gboolean _tmp4_ = FALSE;
			_tmp1_ = self->priv->running;
			if (!_tmp1_) {
				{
					gboolean _tmp2_ = FALSE;
					_tmp2_ = self->priv->running;
					g_static_rec_mutex_unlock (&self->priv->__lock_running);
				}
				return;
			}
			_tmp4_ = self->priv->autosave;
			if (_tmp4_) {
				gboolean _tmp5_ = FALSE;
				_tmp5_ = self->priv->game_memory_loaded;
				_tmp3_ = _tmp5_;
			} else {
				_tmp3_ = FALSE;
			}
			if (_tmp3_) {
				g_debug ("main.vala:871: auto saving...");
				emulator_ui_save_memory (self);
			}
			{
				gboolean _tmp6_ = FALSE;
				_tmp6_ = self->priv->paused;
				g_static_rec_mutex_lock (&self->priv->__lock_paused);
				{
					gboolean _tmp7_ = FALSE;
					_tmp7_ = self->priv->paused;
					if (_tmp7_) {
						{
							gboolean _tmp8_ = FALSE;
							_tmp8_ = self->priv->paused;
							g_static_rec_mutex_unlock (&self->priv->__lock_paused);
						}
						{
							gboolean _tmp9_ = FALSE;
							_tmp9_ = self->priv->running;
							g_static_rec_mutex_unlock (&self->priv->__lock_running);
						}
						return;
					}
					self->priv->paused = TRUE;
				}
				__finally15:
				{
					gboolean _tmp10_ = FALSE;
					_tmp10_ = self->priv->paused;
					g_static_rec_mutex_unlock (&self->priv->__lock_paused);
				}
				if (G_UNLIKELY (_inner_error_ != NULL)) {
					{
						gboolean _tmp11_ = FALSE;
						_tmp11_ = self->priv->running;
						g_static_rec_mutex_unlock (&self->priv->__lock_running);
					}
					g_critical ("file %s: line %d: unexpected error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
					g_clear_error (&_inner_error_);
					return;
				}
			}
		}
		__finally14:
		{
			gboolean _tmp12_ = FALSE;
			_tmp12_ = self->priv->running;
			g_static_rec_mutex_unlock (&self->priv->__lock_running);
		}
		if (G_UNLIKELY (_inner_error_ != NULL)) {
			g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
			g_clear_error (&_inner_error_);
			return;
		}
	}
	g_debug ("main.vala:882: game about to pause");
	_tmp13_ = self->priv->core_thread;
	g_thread_join (_tmp13_);
	_tmp14_ = self->priv->gamescreen;
	game_screen_stop (_tmp14_);
	_tmp15_ = self->priv->gamejoypad;
	game_joypad_stop (_tmp15_);
	_tmp16_ = self->priv->gamespeaker;
	game_speaker_stop (_tmp16_);
	g_debug ("main.vala:887: game paused");
}


void* emulator_ui_core_thread_fn (void) {
	void* result = NULL;
	struct sched_param param = {0};
	struct sched_param _tmp0_ = {0};
	gulong _tmp1_ = 0UL;
	gint _tmp2_ = 0;
	gint64 t1 = 0LL;
	gint64 _tmp4_ = 0LL;
	gint64 t2 = 0LL;
	gint64 elapsed = 0LL;
	gint64 autosave_time = 0LL;
	gint64 _tmp5_ = 0LL;
	gint64 _frame_interval_us = 0LL;
	GError * _inner_error_ = NULL;
	g_debug ("main.vala:892: [main.core_thread_fn] ENTER\n");
	param = _tmp0_;
	param.sched_priority = 70;
	_tmp1_ = pthread_self ();
	_tmp2_ = pthread_setschedparam (_tmp1_, (gint) SCHED_RR, &param);
	if (_tmp2_ != 0) {
		FILE* _tmp3_ = NULL;
		_tmp3_ = stderr;
		fprintf (_tmp3_, "pthread_setschedparam failed\n");
	}
	_tmp4_ = g_get_monotonic_time ();
	t1 = _tmp4_;
	t2 = (gint64) 0;
	elapsed = (gint64) 0;
	_tmp5_ = t1;
	autosave_time = _tmp5_;
	_frame_interval_us = (gint64) 0;
	while (TRUE) {
		EmulatorUI* _tmp6_ = NULL;
		gint _tmp7_ = 0;
		EmulatorUI* _tmp8_ = NULL;
		gdouble _tmp9_ = 0.0;
		gint64 _tmp10_ = 0LL;
		gint64 _tmp11_ = 0LL;
		gint64 _tmp12_ = 0LL;
		gint64 _tmp13_ = 0LL;
		gint64 _tmp14_ = 0LL;
		gint64 _tmp15_ = 0LL;
		gint64 _tmp19_ = 0LL;
		gint64 _tmp20_ = 0LL;
		gint64 _tmp21_ = 0LL;
		gint64 _tmp22_ = 0LL;
		gint64 _tmp23_ = 0LL;
		gint64 _tmp24_ = 0LL;
		gint64 _tmp25_ = 0LL;
		gint64 _tmp26_ = 0LL;
		_tmp6_ = emulator_ui_self;
		_tmp7_ = _tmp6_->priv->frame_interval_us;
		_tmp8_ = emulator_ui_self;
		_tmp9_ = _tmp8_->priv->speed_factor;
		_frame_interval_us = (gint64) (_tmp7_ / _tmp9_);
		_tmp10_ = g_get_monotonic_time ();
		t2 = _tmp10_;
		_tmp11_ = elapsed;
		_tmp12_ = t2;
		_tmp13_ = t1;
		elapsed = _tmp11_ + (_tmp12_ - _tmp13_);
		_tmp14_ = elapsed;
		_tmp15_ = _frame_interval_us;
		if (_tmp14_ < _tmp15_) {
			gint64 _tmp16_ = 0LL;
			gint64 _tmp17_ = 0LL;
			_tmp16_ = _frame_interval_us;
			_tmp17_ = elapsed;
			g_usleep ((gulong) (_tmp16_ - _tmp17_));
		} else {
			gint64 _tmp18_ = 0LL;
			_tmp18_ = elapsed;
			g_debug ("main.vala:913: [core_thread_fn] warning negative drift, elapsed: %f\n", ((gdouble) _tmp18_) / 1000.0);
		}
		_tmp19_ = g_get_monotonic_time ();
		t1 = _tmp19_;
		_tmp20_ = t1;
		_tmp21_ = t2;
		_tmp22_ = _frame_interval_us;
		_tmp23_ = elapsed;
		elapsed = (_tmp20_ - _tmp21_) - (_tmp22_ - _tmp23_);
		_tmp24_ = elapsed;
		_tmp25_ = llabs (_tmp24_);
		_tmp26_ = _frame_interval_us;
		if (_tmp25_ > (_tmp26_ * 2)) {
			gint64 _tmp27_ = 0LL;
			_tmp27_ = elapsed;
			g_debug ("main.vala:921: [core_thread_fn] warning ignored drift correction: %f\n", ((gdouble) _tmp27_) / 1000.0);
			elapsed = (gint64) 0;
		}
		{
			EmulatorUI* _tmp28_ = NULL;
			gboolean _tmp29_ = FALSE;
			_tmp28_ = emulator_ui_self;
			_tmp29_ = _tmp28_->priv->running;
			g_static_rec_mutex_lock (&_tmp28_->priv->__lock_running);
			{
				EmulatorUI* _tmp30_ = NULL;
				gboolean _tmp31_ = FALSE;
				EmulatorUI* _tmp46_ = NULL;
				RetroCore* _tmp47_ = NULL;
				RetroCoreRetroRun _tmp48_ = NULL;
				EmulatorUI* _tmp49_ = NULL;
				gint _tmp50_ = 0;
				gint _tmp51_ = 0;
				EmulatorUI* _tmp52_ = NULL;
				gboolean _tmp53_ = FALSE;
				_tmp30_ = emulator_ui_self;
				_tmp31_ = _tmp30_->priv->running;
				if (!_tmp31_) {
					{
						EmulatorUI* _tmp32_ = NULL;
						gboolean _tmp33_ = FALSE;
						_tmp32_ = emulator_ui_self;
						_tmp33_ = _tmp32_->priv->running;
						g_static_rec_mutex_unlock (&_tmp32_->priv->__lock_running);
					}
					break;
				}
				{
					EmulatorUI* _tmp34_ = NULL;
					gboolean _tmp35_ = FALSE;
					_tmp34_ = emulator_ui_self;
					_tmp35_ = _tmp34_->priv->paused;
					g_static_rec_mutex_lock (&_tmp34_->priv->__lock_paused);
					{
						EmulatorUI* _tmp36_ = NULL;
						gboolean _tmp37_ = FALSE;
						_tmp36_ = emulator_ui_self;
						_tmp37_ = _tmp36_->priv->paused;
						if (_tmp37_) {
							{
								EmulatorUI* _tmp38_ = NULL;
								gboolean _tmp39_ = FALSE;
								_tmp38_ = emulator_ui_self;
								_tmp39_ = _tmp38_->priv->paused;
								g_static_rec_mutex_unlock (&_tmp38_->priv->__lock_paused);
							}
							{
								EmulatorUI* _tmp40_ = NULL;
								gboolean _tmp41_ = FALSE;
								_tmp40_ = emulator_ui_self;
								_tmp41_ = _tmp40_->priv->running;
								g_static_rec_mutex_unlock (&_tmp40_->priv->__lock_running);
							}
							break;
						}
					}
					__finally17:
					{
						EmulatorUI* _tmp42_ = NULL;
						gboolean _tmp43_ = FALSE;
						_tmp42_ = emulator_ui_self;
						_tmp43_ = _tmp42_->priv->paused;
						g_static_rec_mutex_unlock (&_tmp42_->priv->__lock_paused);
					}
					if (G_UNLIKELY (_inner_error_ != NULL)) {
						{
							EmulatorUI* _tmp44_ = NULL;
							gboolean _tmp45_ = FALSE;
							_tmp44_ = emulator_ui_self;
							_tmp45_ = _tmp44_->priv->running;
							g_static_rec_mutex_unlock (&_tmp44_->priv->__lock_running);
						}
						g_critical ("file %s: line %d: unexpected error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
						g_clear_error (&_inner_error_);
						return NULL;
					}
				}
				_tmp46_ = emulator_ui_self;
				_tmp47_ = _tmp46_->priv->core;
				_tmp48_ = _tmp47_->retro_run;
				_tmp48_ ();
				_tmp49_ = emulator_ui_self;
				_tmp50_ = emulator_ui_get_ticker_count (_tmp49_);
				_tmp51_ = _tmp50_;
				emulator_ui_set_ticker_count (_tmp49_, _tmp51_ + 1);
				_tmp52_ = emulator_ui_self;
				_tmp53_ = _tmp52_->priv->autosave;
				if (_tmp53_) {
					EmulatorUI* _tmp54_ = NULL;
					gboolean _tmp55_ = FALSE;
					_tmp54_ = emulator_ui_self;
					_tmp55_ = _tmp54_->priv->game_memory_loaded;
					if (!_tmp55_) {
						EmulatorUI* _tmp56_ = NULL;
						EmulatorUI* _tmp57_ = NULL;
						_tmp56_ = emulator_ui_self;
						emulator_ui_load_memory (_tmp56_);
						_tmp57_ = emulator_ui_self;
						_tmp57_->priv->game_memory_loaded = TRUE;
					} else {
						gint64 _tmp58_ = 0LL;
						gint64 _tmp59_ = 0LL;
						_tmp58_ = t1;
						_tmp59_ = autosave_time;
						if (((_tmp58_ - _tmp59_) / 1000.0) > ((gdouble) 30000)) {
							EmulatorUI* _tmp60_ = NULL;
							gint64 _tmp61_ = 0LL;
							g_debug ("main.vala:942: auto saving...");
							_tmp60_ = emulator_ui_self;
							emulator_ui_save_memory (_tmp60_);
							_tmp61_ = t1;
							autosave_time = _tmp61_;
						}
					}
				}
			}
			__finally16:
			{
				EmulatorUI* _tmp62_ = NULL;
				gboolean _tmp63_ = FALSE;
				_tmp62_ = emulator_ui_self;
				_tmp63_ = _tmp62_->priv->running;
				g_static_rec_mutex_unlock (&_tmp62_->priv->__lock_running);
			}
			if (G_UNLIKELY (_inner_error_ != NULL)) {
				g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
				g_clear_error (&_inner_error_);
				return NULL;
			}
		}
	}
	g_debug ("main.vala:954: [main.core_thread_fn] LEAVE\n");
	result = NULL;
	return result;
}


void emulator_ui_video_refresh_cb (void* data, guint width, guint height, gsize pitch) {
	void* _tmp0_ = NULL;
	EmulatorUI* _tmp1_ = NULL;
	GameScreen* _tmp2_ = NULL;
	void* _tmp3_ = NULL;
	guint _tmp4_ = 0U;
	guint _tmp5_ = 0U;
	gsize _tmp6_ = 0UL;
	_tmp0_ = data;
	if (_tmp0_ == NULL) {
		return;
	}
	_tmp1_ = emulator_ui_self;
	_tmp2_ = _tmp1_->priv->gamescreen;
	_tmp3_ = data;
	_tmp4_ = width;
	_tmp5_ = height;
	_tmp6_ = pitch;
	game_screen_push_frame (_tmp2_, _tmp3_, _tmp4_, _tmp5_, _tmp6_);
}


gsize emulator_ui_audio_sample_batch_cb (void* data, gsize frames) {
	gsize result = 0UL;
	void* _tmp0_ = NULL;
	gsize _tmp5_ = 0UL;
	_tmp0_ = data;
	if (_tmp0_ != NULL) {
		EmulatorUI* _tmp1_ = NULL;
		GameSpeaker* _tmp2_ = NULL;
		void* _tmp3_ = NULL;
		gsize _tmp4_ = 0UL;
		_tmp1_ = emulator_ui_self;
		_tmp2_ = _tmp1_->priv->gamespeaker;
		_tmp3_ = data;
		_tmp4_ = frames;
		game_speaker_push_frame (_tmp2_, _tmp3_, _tmp4_);
	}
	_tmp5_ = frames;
	result = _tmp5_;
	return result;
}


void emulator_ui_input_poll_cb (void) {
	gint _tmp0_ = 0;
	EmulatorUI* _tmp1_ = NULL;
	GameJoypad* _tmp2_ = NULL;
	gint _tmp3_ = 0;
	EmulatorUI* _tmp4_ = NULL;
	_tmp1_ = emulator_ui_self;
	_tmp2_ = _tmp1_->priv->gamejoypad;
	_tmp3_ = game_joypad_get_button_state (_tmp2_, (guint) 99);
	if (_tmp3_ == 1) {
		_tmp0_ = 2;
	} else {
		_tmp0_ = 1;
	}
	_tmp4_ = emulator_ui_self;
	_tmp4_->priv->speed_factor = (gdouble) _tmp0_;
}


gint16 emulator_ui_input_state_cb (guint port, guint device, guint index, guint id) {
	gint16 result = 0;
	gboolean _tmp0_ = FALSE;
	guint _tmp1_ = 0U;
	_tmp1_ = device;
	if (_tmp1_ == ((guint) 1)) {
		guint _tmp2_ = 0U;
		_tmp2_ = port;
		_tmp0_ = _tmp2_ == ((guint) 0);
	} else {
		_tmp0_ = FALSE;
	}
	if (_tmp0_) {
		EmulatorUI* _tmp3_ = NULL;
		GameJoypad* _tmp4_ = NULL;
		guint _tmp5_ = 0U;
		gint _tmp6_ = 0;
		_tmp3_ = emulator_ui_self;
		_tmp4_ = _tmp3_->priv->gamejoypad;
		_tmp5_ = id;
		_tmp6_ = game_joypad_get_button_state (_tmp4_, _tmp5_);
		result = (gint16) _tmp6_;
		return result;
	}
	result = (gint16) 0;
	return result;
}


static void _emulator_ui_video_refresh_cb_retro_core_retro_video_refresh_t (void* data, guint width, guint height, gsize pitch) {
	emulator_ui_video_refresh_cb (data, width, height, pitch);
}


static gsize _emulator_ui_audio_sample_batch_cb_retro_core_retro_audio_sample_batch_t (void* data, gsize frames) {
	gsize result;
	result = emulator_ui_audio_sample_batch_cb (data, frames);
	return result;
}


static void _emulator_ui_input_poll_cb_retro_core_retro_input_poll_t (void) {
	emulator_ui_input_poll_cb ();
}


static gint16 _emulator_ui_input_state_cb_retro_core_retro_input_state_t (guint port, guint device, guint index, guint id) {
	gint16 result;
	result = emulator_ui_input_state_cb (port, device, index, id);
	return result;
}


static void emulator_ui_load_game (EmulatorUI* self) {
	GError * _inner_error_ = NULL;
	g_return_if_fail (self != NULL);
	{
		RetroCore* _tmp0_ = NULL;
		RetroCore* _tmp2_ = NULL;
		EmulatorUICoreSettings _tmp3_ = {0};
		const gchar* _tmp4_ = NULL;
		const gchar* _tmp5_ = NULL;
		EmulatorUICoreSettings _tmp6_ = {0};
		RetroCoreRetroVariable* _tmp7_ = NULL;
		gint _tmp7__length1 = 0;
		RetroCore* _tmp8_ = NULL;
		RetroCore* _tmp9_ = NULL;
		RetroCoreRetroSystemAvInfo av_info = {0};
		RetroCore* _tmp10_ = NULL;
		RetroCoreRetroGetSystemAvInfo _tmp11_ = NULL;
		RetroCoreRetroSystemAvInfo _tmp12_ = {0};
		RetroCore* _tmp13_ = NULL;
		RetroCoreRetroApiVersion _tmp14_ = NULL;
		guint _tmp15_ = 0U;
		RetroCoreRetroSystemAvInfo _tmp16_ = {0};
		RetroCoreRetroSystemTiming _tmp17_ = {0};
		gdouble _tmp18_ = 0.0;
		RetroCoreRetroSystemAvInfo _tmp19_ = {0};
		RetroCoreRetroSystemTiming _tmp20_ = {0};
		gdouble _tmp21_ = 0.0;
		RetroCoreRetroSystemAvInfo _tmp22_ = {0};
		RetroCoreRetroGameGeometry _tmp23_ = {0};
		guint _tmp24_ = 0U;
		RetroCoreRetroSystemAvInfo _tmp25_ = {0};
		RetroCoreRetroGameGeometry _tmp26_ = {0};
		guint _tmp27_ = 0U;
		RetroCoreRetroSystemAvInfo _tmp28_ = {0};
		RetroCoreRetroGameGeometry _tmp29_ = {0};
		guint _tmp30_ = 0U;
		RetroCoreRetroSystemAvInfo _tmp31_ = {0};
		RetroCoreRetroGameGeometry _tmp32_ = {0};
		guint _tmp33_ = 0U;
		RetroCoreRetroSystemAvInfo _tmp34_ = {0};
		RetroCoreRetroGameGeometry _tmp35_ = {0};
		gfloat _tmp36_ = 0.0F;
		RetroCoreRetroSystemAvInfo _tmp37_ = {0};
		RetroCoreRetroGameGeometry _tmp38_ = {0};
		guint _tmp39_ = 0U;
		RetroCoreRetroSystemAvInfo _tmp40_ = {0};
		RetroCoreRetroGameGeometry _tmp41_ = {0};
		guint _tmp42_ = 0U;
		RetroCoreRetroSystemAvInfo _tmp43_ = {0};
		RetroCoreRetroSystemTiming _tmp44_ = {0};
		gdouble _tmp45_ = 0.0;
		GameJoypad* _tmp46_ = NULL;
		EmulatorUICoreSettings _tmp47_ = {0};
		GameJoypadButton* _tmp48_ = NULL;
		gint _tmp48__length1 = 0;
		gint64 start = 0LL;
		gint64 _tmp49_ = 0LL;
		RetroCoreRetroSystemAvInfo _tmp50_ = {0};
		RetroCoreRetroSystemTiming _tmp51_ = {0};
		gdouble _tmp52_ = 0.0;
		GameSpeaker* _tmp53_ = NULL;
		gint64 elapsed = 0LL;
		gint64 _tmp54_ = 0LL;
		self->priv->game_memory_loaded = FALSE;
		_tmp0_ = self->priv->core;
		if (_tmp0_ != NULL) {
			RetroCore* _tmp1_ = NULL;
			_tmp1_ = self->priv->core;
			retro_core_unload (_tmp1_);
			emulator_ui_stop_game (self);
		}
		_tmp3_ = self->priv->core_settings;
		_tmp4_ = _tmp3_.path;
		_tmp5_ = self->priv->game_path;
		_tmp6_ = self->priv->core_settings;
		_tmp7_ = _tmp6_.env;
		_tmp7__length1 = _tmp6_.env_length1;
		_tmp8_ = retro_core_new (_tmp4_, _tmp5_, _tmp7_, _tmp7__length1, _emulator_ui_video_refresh_cb_retro_core_retro_video_refresh_t, _emulator_ui_audio_sample_batch_cb_retro_core_retro_audio_sample_batch_t, _emulator_ui_input_poll_cb_retro_core_retro_input_poll_t, _emulator_ui_input_state_cb_retro_core_retro_input_state_t, &_inner_error_);
		_tmp2_ = _tmp8_;
		if (G_UNLIKELY (_inner_error_ != NULL)) {
			goto __catch18_g_error;
		}
		_tmp9_ = _tmp2_;
		_tmp2_ = NULL;
		_g_object_unref0 (self->priv->core);
		self->priv->core = _tmp9_;
		_tmp10_ = self->priv->core;
		_tmp11_ = _tmp10_->retro_get_system_av_info;
		_tmp11_ (&_tmp12_);
		av_info = _tmp12_;
		_tmp13_ = self->priv->core;
		_tmp14_ = _tmp13_->retro_api_version;
		_tmp15_ = _tmp14_ ();
		g_debug ("main.vala:1028: retro_api_version: %d\n", (gint) _tmp15_);
		_tmp16_ = av_info;
		_tmp17_ = _tmp16_.timing;
		_tmp18_ = _tmp17_.fps;
		g_debug ("main.vala:1029: av_info.timing.fps: %f\n", _tmp18_);
		_tmp19_ = av_info;
		_tmp20_ = _tmp19_.timing;
		_tmp21_ = _tmp20_.sample_rate;
		g_debug ("main.vala:1030: av_info.timing.sample_rate: %f\n", _tmp21_);
		_tmp22_ = av_info;
		_tmp23_ = _tmp22_.geometry;
		_tmp24_ = _tmp23_.base_width;
		g_debug ("main.vala:1031: av_info.geometry.base_width: %d\n", (gint) _tmp24_);
		_tmp25_ = av_info;
		_tmp26_ = _tmp25_.geometry;
		_tmp27_ = _tmp26_.base_height;
		g_debug ("main.vala:1032: av_info.geometry.base_height: %d\n", (gint) _tmp27_);
		_tmp28_ = av_info;
		_tmp29_ = _tmp28_.geometry;
		_tmp30_ = _tmp29_.max_width;
		g_debug ("main.vala:1033: av_info.geometry.max_width: %d\n", (gint) _tmp30_);
		_tmp31_ = av_info;
		_tmp32_ = _tmp31_.geometry;
		_tmp33_ = _tmp32_.max_height;
		g_debug ("main.vala:1034: av_info.geometry.max_height: %d\n", (gint) _tmp33_);
		_tmp34_ = av_info;
		_tmp35_ = _tmp34_.geometry;
		_tmp36_ = _tmp35_.aspect_ratio;
		g_debug ("main.vala:1035: av_info.geometry.aspect_ratio: %f\n", (gdouble) _tmp36_);
		_tmp37_ = av_info;
		_tmp38_ = _tmp37_.geometry;
		_tmp39_ = _tmp38_.base_width;
		self->priv->core_width = (gint) _tmp39_;
		_tmp40_ = av_info;
		_tmp41_ = _tmp40_.geometry;
		_tmp42_ = _tmp41_.base_height;
		self->priv->core_height = (gint) _tmp42_;
		_tmp43_ = av_info;
		_tmp44_ = _tmp43_.timing;
		_tmp45_ = _tmp44_.fps;
		self->priv->frame_interval_us = (gint) (1000000.0 / _tmp45_);
		emulator_ui_resize_drawing_area_and_buffers (self);
		_tmp46_ = self->priv->gamejoypad;
		_tmp47_ = self->priv->core_settings;
		_tmp48_ = _tmp47_.joypad_buttons;
		_tmp48__length1 = _tmp47_.joypad_buttons_length1;
		game_joypad_set_buttons (_tmp46_, _tmp48_, _tmp48__length1);
		_tmp49_ = g_get_monotonic_time ();
		start = _tmp49_;
		_tmp50_ = av_info;
		_tmp51_ = _tmp50_.timing;
		_tmp52_ = _tmp51_.sample_rate;
		_tmp53_ = game_speaker_new ((gint) (_tmp52_ - 8), 2, 16);
		_g_object_unref0 (self->priv->gamespeaker);
		self->priv->gamespeaker = _tmp53_;
		_tmp54_ = g_get_monotonic_time ();
		elapsed = _tmp54_ - start;
		g_debug ("main.vala:1052: [gamespeaker elapsed: %f\n", ((gdouble) elapsed) / 1000.0);
		emulator_ui_play_game (self);
		self->priv->ready = TRUE;
		_g_object_unref0 (_tmp2_);
	}
	goto __finally18;
	__catch18_g_error:
	{
		GError* e = NULL;
		FILE* _tmp55_ = NULL;
		const gchar* _tmp56_ = NULL;
		e = _inner_error_;
		_inner_error_ = NULL;
		_tmp55_ = stderr;
		_tmp56_ = e->message;
		fprintf (_tmp55_, "load_game failed: %s\n", _tmp56_);
		exit (1);
		_g_error_free0 (e);
	}
	__finally18:
	if (G_UNLIKELY (_inner_error_ != NULL)) {
		g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
		g_clear_error (&_inner_error_);
		return;
	}
}


static void ___lambda50_ (void) {
	gtk_main_quit ();
}


static void ____lambda50__gtk_object_destroy (GtkObject* _sender, gpointer self) {
	___lambda50_ ();
}


gint emulator_ui_main (gchar** args, int args_length1) {
	gint result = 0;
	gchar* exe_path = NULL;
	const gchar* _tmp8_ = NULL;
	gchar* _tmp9_ = NULL;
	GOptionContext* opt_context = NULL;
	GOptionContext* _tmp10_ = NULL;
	GOptionContext* _tmp11_ = NULL;
	GOptionContext* _tmp12_ = NULL;
	GError * _inner_error_ = NULL;
	exe_path = NULL;
	{
		gchar* _tmp0_ = NULL;
		gchar* _tmp1_ = NULL;
		gchar* _tmp2_ = NULL;
		_tmp1_ = g_file_read_link ("/proc/self/exe", &_inner_error_);
		_tmp0_ = _tmp1_;
		if (G_UNLIKELY (_inner_error_ != NULL)) {
			goto __catch19_g_error;
		}
		_tmp2_ = _tmp0_;
		_tmp0_ = NULL;
		_g_free0 (exe_path);
		exe_path = _tmp2_;
		_g_free0 (_tmp0_);
	}
	goto __finally19;
	__catch19_g_error:
	{
		GError* e = NULL;
		GError* _tmp3_ = NULL;
		const gchar* _tmp4_ = NULL;
		gchar** _tmp5_ = NULL;
		gint _tmp5__length1 = 0;
		const gchar* _tmp6_ = NULL;
		gchar* _tmp7_ = NULL;
		e = _inner_error_;
		_inner_error_ = NULL;
		_tmp3_ = e;
		_tmp4_ = _tmp3_->message;
		g_warning ("main.vala:1102: Failed to find executable path: %s\n", _tmp4_);
		_tmp5_ = args;
		_tmp5__length1 = args_length1;
		_tmp6_ = _tmp5_[0];
		_tmp7_ = g_strdup (_tmp6_);
		_g_free0 (exe_path);
		exe_path = _tmp7_;
		_g_error_free0 (e);
	}
	__finally19:
	if (G_UNLIKELY (_inner_error_ != NULL)) {
		_g_free0 (exe_path);
		g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
		g_clear_error (&_inner_error_);
		return 0;
	}
	_tmp8_ = exe_path;
	_tmp9_ = g_path_get_dirname (_tmp8_);
	_g_free0 (emulator_ui_exe_dir);
	emulator_ui_exe_dir = _tmp9_;
	_tmp10_ = g_option_context_new ("- OptionContext example");
	opt_context = _tmp10_;
	_tmp11_ = opt_context;
	g_option_context_set_help_enabled (_tmp11_, TRUE);
	_tmp12_ = opt_context;
	g_option_context_add_main_entries (_tmp12_, EMULATOR_UI_options, NULL);
	{
		GOptionContext* _tmp13_ = NULL;
		_tmp13_ = opt_context;
		g_option_context_parse (_tmp13_, &args_length1, &args, &_inner_error_);
		if (G_UNLIKELY (_inner_error_ != NULL)) {
			if (_inner_error_->domain == G_OPTION_ERROR) {
				goto __catch20_g_option_error;
			}
			_g_option_context_free0 (opt_context);
			_g_free0 (exe_path);
			g_critical ("file %s: line %d: unexpected error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
			g_clear_error (&_inner_error_);
			return 0;
		}
	}
	goto __finally20;
	__catch20_g_option_error:
	{
		GError* e = NULL;
		GError* _tmp14_ = NULL;
		const gchar* _tmp15_ = NULL;
		gchar** _tmp16_ = NULL;
		gint _tmp16__length1 = 0;
		const gchar* _tmp17_ = NULL;
		e = _inner_error_;
		_inner_error_ = NULL;
		_tmp14_ = e;
		_tmp15_ = _tmp14_->message;
		g_printerr ("error: %s\n", _tmp15_);
		_tmp16_ = args;
		_tmp16__length1 = args_length1;
		_tmp17_ = _tmp16_[0];
		g_printerr ("Run '%s --help' to see a full list of available command line options.\n", _tmp17_);
		result = 1;
		_g_error_free0 (e);
		_g_option_context_free0 (opt_context);
		_g_free0 (exe_path);
		return result;
	}
	__finally20:
	if (G_UNLIKELY (_inner_error_ != NULL)) {
		_g_option_context_free0 (opt_context);
		_g_free0 (exe_path);
		g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
		g_clear_error (&_inner_error_);
		return 0;
	}
	{
		const gchar* _tmp18_ = NULL;
		gboolean _tmp28_ = FALSE;
		const gchar* _tmp29_ = NULL;
		EmulatorUI* _tmp33_ = NULL;
		EmulatorUI* _tmp34_ = NULL;
		EmulatorUI* _tmp35_ = NULL;
		EmulatorUI* _tmp36_ = NULL;
		_tmp18_ = emulator_ui_config_file;
		if (_tmp18_ == NULL) {
			const gchar* _tmp19_ = NULL;
			gchar* _tmp20_ = NULL;
			_tmp19_ = emulator_ui_exe_dir;
			_tmp20_ = g_build_filename (_tmp19_, "config.ini", NULL);
			_g_free0 (emulator_ui_config_file);
			emulator_ui_config_file = _tmp20_;
		} else {
			const gchar* _tmp21_ = NULL;
			gboolean _tmp22_ = FALSE;
			_tmp21_ = emulator_ui_config_file;
			_tmp22_ = g_path_is_absolute (_tmp21_);
			if (!_tmp22_) {
				const gchar* _tmp23_ = NULL;
				const gchar* _tmp24_ = NULL;
				gchar* _tmp25_ = NULL;
				gchar* _tmp26_ = NULL;
				gchar* _tmp27_ = NULL;
				_tmp23_ = emulator_ui_exe_dir;
				_tmp24_ = emulator_ui_config_file;
				_tmp25_ = g_build_filename (_tmp23_, _tmp24_, NULL);
				_tmp26_ = _tmp25_;
				_tmp27_ = realpath (_tmp26_, NULL);
				_g_free0 (emulator_ui_config_file);
				emulator_ui_config_file = _tmp27_;
				_g_free0 (_tmp26_);
			}
		}
		_tmp29_ = emulator_ui_config_file;
		if (_tmp29_ == NULL) {
			_tmp28_ = TRUE;
		} else {
			const gchar* _tmp30_ = NULL;
			gboolean _tmp31_ = FALSE;
			_tmp30_ = emulator_ui_config_file;
			_tmp31_ = g_file_test (_tmp30_, G_FILE_TEST_EXISTS);
			_tmp28_ = !_tmp31_;
		}
		if (_tmp28_) {
			GError* _tmp32_ = NULL;
			_tmp32_ = g_error_new_literal (EMULATOR_UI_ERROR, EMULATOR_UI_ERROR_ERROR, "config file doesn't exist");
			_inner_error_ = _tmp32_;
			goto __catch21_g_error;
		}
		gtk_init (&args_length1, &args);
		_tmp34_ = emulator_ui_new (&_inner_error_);
		g_object_ref_sink (_tmp34_);
		_tmp33_ = _tmp34_;
		if (G_UNLIKELY (_inner_error_ != NULL)) {
			goto __catch21_g_error;
		}
		_tmp35_ = _tmp33_;
		_tmp33_ = NULL;
		g_object_ref_sink (_tmp35_);
		_g_object_unref0 (emulator_ui_self);
		emulator_ui_self = _tmp35_;
		_tmp36_ = emulator_ui_self;
		g_signal_connect ((GtkObject*) _tmp36_, "destroy", (GCallback) ____lambda50__gtk_object_destroy, NULL);
		_g_object_unref0 (_tmp33_);
	}
	goto __finally21;
	__catch21_g_error:
	{
		GError* e = NULL;
		GError* _tmp37_ = NULL;
		const gchar* _tmp38_ = NULL;
		GtkMessageDialog* dialog = NULL;
		GError* _tmp39_ = NULL;
		const gchar* _tmp40_ = NULL;
		GtkMessageDialog* _tmp41_ = NULL;
		GtkMessageDialog* _tmp42_ = NULL;
		GtkMessageDialog* _tmp43_ = NULL;
		GtkMessageDialog* _tmp44_ = NULL;
		e = _inner_error_;
		_inner_error_ = NULL;
		_tmp37_ = e;
		_tmp38_ = _tmp37_->message;
		g_warning ("main.vala:1139: [error]: %s", _tmp38_);
		_tmp39_ = e;
		_tmp40_ = _tmp39_->message;
		_tmp41_ = (GtkMessageDialog*) gtk_message_dialog_new (NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE, "[error]: %s", _tmp40_);
		g_object_ref_sink (_tmp41_);
		dialog = _tmp41_;
		_tmp42_ = dialog;
		gtk_window_set_title ((GtkWindow*) _tmp42_, "L:A_N:application_ID:gambatte_PC:N");
		_tmp43_ = dialog;
		gtk_dialog_run ((GtkDialog*) _tmp43_);
		_tmp44_ = dialog;
		gtk_object_destroy ((GtkObject*) _tmp44_);
		result = 1;
		_g_object_unref0 (dialog);
		_g_error_free0 (e);
		_g_option_context_free0 (opt_context);
		_g_free0 (exe_path);
		return result;
	}
	__finally21:
	if (G_UNLIKELY (_inner_error_ != NULL)) {
		_g_option_context_free0 (opt_context);
		_g_free0 (exe_path);
		g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
		g_clear_error (&_inner_error_);
		return 0;
	}
	gtk_main ();
	result = 0;
	_g_option_context_free0 (opt_context);
	_g_free0 (exe_path);
	return result;
}


int main (int argc, char ** argv) {
#if !GLIB_CHECK_VERSION (2,32,0)
	g_thread_init (NULL);
#endif
#if !GLIB_CHECK_VERSION (2,35,0)
	g_type_init ();
#endif
	return emulator_ui_main (argv, argc);
}


gboolean emulator_ui_get_dark_mode (EmulatorUI* self) {
	gboolean result;
	const gchar* _tmp0_ = NULL;
	const gchar* _tmp1_ = NULL;
	g_return_val_if_fail (self != NULL, FALSE);
	_tmp0_ = gtk_widget_get_name ((GtkWidget*) self);
	_tmp1_ = _tmp0_;
	result = g_strcmp0 (_tmp1_, "app-dark") == 0;
	return result;
}


void emulator_ui_set_dark_mode (EmulatorUI* self, gboolean value) {
	const gchar* _tmp0_ = NULL;
	gboolean _tmp1_ = FALSE;
	g_return_if_fail (self != NULL);
	_tmp1_ = value;
	if (_tmp1_) {
		_tmp0_ = "app-dark";
	} else {
		_tmp0_ = "app-light";
	}
	gtk_widget_set_name ((GtkWidget*) self, _tmp0_);
	g_object_notify ((GObject *) self, "dark-mode");
}


const gchar* emulator_ui_get_state_dir (EmulatorUI* self) {
	const gchar* result;
	const gchar* _tmp0_ = NULL;
	g_return_val_if_fail (self != NULL, NULL);
	_tmp0_ = self->priv->_state_dir;
	result = _tmp0_;
	return result;
}


void emulator_ui_set_state_dir (EmulatorUI* self, const gchar* value) {
	const gchar* _tmp0_ = NULL;
	gchar* _tmp1_ = NULL;
	g_return_if_fail (self != NULL);
	_tmp0_ = value;
	_tmp1_ = g_strdup (_tmp0_);
	_g_free0 (self->priv->_state_dir);
	self->priv->_state_dir = _tmp1_;
	g_object_notify ((GObject *) self, "state-dir");
}


const gchar* emulator_ui_get_last_dir (EmulatorUI* self) {
	const gchar* result;
	const gchar* _tmp0_ = NULL;
	g_return_val_if_fail (self != NULL, NULL);
	_tmp0_ = self->priv->_last_dir;
	result = _tmp0_;
	return result;
}


void emulator_ui_set_last_dir (EmulatorUI* self, const gchar* value) {
	const gchar* _tmp0_ = NULL;
	gchar* _tmp1_ = NULL;
	g_return_if_fail (self != NULL);
	_tmp0_ = value;
	_tmp1_ = g_strdup (_tmp0_);
	_g_free0 (self->priv->_last_dir);
	self->priv->_last_dir = _tmp1_;
	g_object_notify ((GObject *) self, "last-dir");
}


gint emulator_ui_get_contrast (EmulatorUI* self) {
	gint result;
	gint _tmp0_ = 0;
	g_return_val_if_fail (self != NULL, 0);
	_tmp0_ = self->priv->_contrast;
	result = _tmp0_;
	return result;
}


void emulator_ui_set_contrast (EmulatorUI* self, gint value) {
	gint _tmp0_ = 0;
	g_return_if_fail (self != NULL);
	_tmp0_ = value;
	self->priv->_contrast = _tmp0_;
	g_object_notify ((GObject *) self, "contrast");
}


gint emulator_ui_get_brightness (EmulatorUI* self) {
	gint result;
	gint _tmp0_ = 0;
	g_return_val_if_fail (self != NULL, 0);
	_tmp0_ = self->priv->_brightness;
	result = _tmp0_;
	return result;
}


void emulator_ui_set_brightness (EmulatorUI* self, gint value) {
	gint _tmp0_ = 0;
	g_return_if_fail (self != NULL);
	_tmp0_ = value;
	self->priv->_brightness = _tmp0_;
	g_object_notify ((GObject *) self, "brightness");
}


gint emulator_ui_get_max_fps (EmulatorUI* self) {
	gint result;
	gint _tmp0_ = 0;
	g_return_val_if_fail (self != NULL, 0);
	_tmp0_ = self->priv->_max_fps;
	result = _tmp0_;
	return result;
}


void emulator_ui_set_max_fps (EmulatorUI* self, gint value) {
	gint _tmp0_ = 0;
	g_return_if_fail (self != NULL);
	_tmp0_ = value;
	self->priv->_max_fps = _tmp0_;
	g_object_notify ((GObject *) self, "max-fps");
}


GameScreenCommitMode emulator_ui_get_render_mode (EmulatorUI* self) {
	GameScreenCommitMode result;
	GameScreenCommitMode _tmp0_ = 0;
	g_return_val_if_fail (self != NULL, 0);
	_tmp0_ = self->priv->_render_mode;
	result = _tmp0_;
	return result;
}


void emulator_ui_set_render_mode (EmulatorUI* self, GameScreenCommitMode value) {
	GameScreenCommitMode _tmp0_ = 0;
	g_return_if_fail (self != NULL);
	_tmp0_ = value;
	self->priv->_render_mode = _tmp0_;
	g_object_notify ((GObject *) self, "render-mode");
}


gboolean emulator_ui_get_fullscreen (EmulatorUI* self) {
	gboolean result;
	gboolean _tmp0_ = FALSE;
	g_return_val_if_fail (self != NULL, FALSE);
	_tmp0_ = self->priv->_fullscreen;
	result = _tmp0_;
	return result;
}


void emulator_ui_set_fullscreen (EmulatorUI* self, gboolean value) {
	gboolean _tmp0_ = FALSE;
	g_return_if_fail (self != NULL);
	_tmp0_ = value;
	self->priv->_fullscreen = _tmp0_;
	g_object_notify ((GObject *) self, "fullscreen");
}


gboolean emulator_ui_get_audio (EmulatorUI* self) {
	gboolean result;
	gboolean _tmp0_ = FALSE;
	g_return_val_if_fail (self != NULL, FALSE);
	_tmp0_ = self->priv->_audio;
	result = _tmp0_;
	return result;
}


void emulator_ui_set_audio (EmulatorUI* self, gboolean value) {
	gboolean _tmp0_ = FALSE;
	g_return_if_fail (self != NULL);
	_tmp0_ = value;
	self->priv->_audio = _tmp0_;
	g_object_notify ((GObject *) self, "audio");
}


gint emulator_ui_get_frame_count (EmulatorUI* self) {
	gint result;
	gint _tmp0_ = 0;
	g_return_val_if_fail (self != NULL, 0);
	_tmp0_ = g_atomic_int_get ((volatile gint *) (&self->priv->_frame_count));
	result = _tmp0_;
	return result;
}


void emulator_ui_set_frame_count (EmulatorUI* self, gint value) {
	gint _tmp0_ = 0;
	g_return_if_fail (self != NULL);
	_tmp0_ = value;
	g_atomic_int_set ((volatile gint *) (&self->priv->_frame_count), _tmp0_);
}


gint emulator_ui_get_ticker_count (EmulatorUI* self) {
	gint result;
	gint _tmp0_ = 0;
	g_return_val_if_fail (self != NULL, 0);
	_tmp0_ = g_atomic_int_get ((volatile gint *) (&self->priv->_ticker_count));
	result = _tmp0_;
	return result;
}


void emulator_ui_set_ticker_count (EmulatorUI* self, gint value) {
	gint _tmp0_ = 0;
	g_return_if_fail (self != NULL);
	_tmp0_ = value;
	g_atomic_int_set ((volatile gint *) (&self->priv->_ticker_count), _tmp0_);
}


static void g_cclosure_user_marshal_VOID__INT_INT (GClosure * closure, GValue * return_value, guint n_param_values, const GValue * param_values, gpointer invocation_hint, gpointer marshal_data) {
	typedef void (*GMarshalFunc_VOID__INT_INT) (gpointer data1, gint arg_1, gint arg_2, gpointer data2);
	register GMarshalFunc_VOID__INT_INT callback;
	register GCClosure * cc;
	register gpointer data1;
	register gpointer data2;
	cc = (GCClosure *) closure;
	g_return_if_fail (n_param_values == 3);
	if (G_CCLOSURE_SWAP_DATA (closure)) {
		data1 = closure->data;
		data2 = param_values->data[0].v_pointer;
	} else {
		data1 = param_values->data[0].v_pointer;
		data2 = closure->data;
	}
	callback = (GMarshalFunc_VOID__INT_INT) (marshal_data ? marshal_data : cc->callback);
	callback (data1, g_value_get_int (param_values + 1), g_value_get_int (param_values + 2), data2);
}


static void _vala_GameJoypadButton_array_free (GameJoypadButton* array, gint array_length) {
	if (array != NULL) {
		int i;
		for (i = 0; i < array_length; i = i + 1) {
			game_joypad_button_destroy (&array[i]);
		}
	}
	g_free (array);
}


static void _vala_RetroCoreRetroVariable_array_free (RetroCoreRetroVariable* array, gint array_length) {
	if (array != NULL) {
		int i;
		for (i = 0; i < array_length; i = i + 1) {
			retro_core_retro_variable_destroy (&array[i]);
		}
	}
	g_free (array);
}


static GameJoypadButton* _vala_array_dup1 (GameJoypadButton* self, int length) {
	GameJoypadButton* result;
	int i;
	result = g_new0 (GameJoypadButton, length);
	for (i = 0; i < length; i++) {
		GameJoypadButton _tmp0_ = {0};
		game_joypad_button_copy (&self[i], &_tmp0_);
		result[i] = _tmp0_;
	}
	return result;
}


static RetroCoreRetroVariable* _vala_array_dup2 (RetroCoreRetroVariable* self, int length) {
	RetroCoreRetroVariable* result;
	int i;
	result = g_new0 (RetroCoreRetroVariable, length);
	for (i = 0; i < length; i++) {
		RetroCoreRetroVariable _tmp0_ = {0};
		retro_core_retro_variable_copy (&self[i], &_tmp0_);
		result[i] = _tmp0_;
	}
	return result;
}


static void emulator_ui_core_settings_copy (const EmulatorUICoreSettings* self, EmulatorUICoreSettings* dest) {
	const gchar* _tmp0_ = NULL;
	gchar* _tmp1_ = NULL;
	GameJoypadButton* _tmp2_ = NULL;
	gint _tmp2__length1 = 0;
	GameJoypadButton* _tmp3_ = NULL;
	gint _tmp3__length1 = 0;
	const gchar* _tmp4_ = NULL;
	gchar* _tmp5_ = NULL;
	RetroCoreRetroVariable* _tmp6_ = NULL;
	gint _tmp6__length1 = 0;
	RetroCoreRetroVariable* _tmp7_ = NULL;
	gint _tmp7__length1 = 0;
	_tmp0_ = (*self).name;
	_tmp1_ = g_strdup (_tmp0_);
	_g_free0 ((*dest).name);
	(*dest).name = _tmp1_;
	_tmp2_ = (*self).joypad_buttons;
	_tmp2__length1 = (*self).joypad_buttons_length1;
	_tmp3_ = (_tmp2_ != NULL) ? _vala_array_dup1 (_tmp2_, _tmp2__length1) : ((gpointer) _tmp2_);
	_tmp3__length1 = _tmp2__length1;
	(*dest).joypad_buttons = (_vala_GameJoypadButton_array_free ((*dest).joypad_buttons, (*dest).joypad_buttons_length1), NULL);
	(*dest).joypad_buttons = _tmp3_;
	(*dest).joypad_buttons_length1 = _tmp3__length1;
	(*dest)._joypad_buttons_size_ = (*dest).joypad_buttons_length1;
	_tmp4_ = (*self).path;
	_tmp5_ = g_strdup (_tmp4_);
	_g_free0 ((*dest).path);
	(*dest).path = _tmp5_;
	_tmp6_ = (*self).env;
	_tmp6__length1 = (*self).env_length1;
	_tmp7_ = (_tmp6_ != NULL) ? _vala_array_dup2 (_tmp6_, _tmp6__length1) : ((gpointer) _tmp6_);
	_tmp7__length1 = _tmp6__length1;
	(*dest).env = (_vala_RetroCoreRetroVariable_array_free ((*dest).env, (*dest).env_length1), NULL);
	(*dest).env = _tmp7_;
	(*dest).env_length1 = _tmp7__length1;
	(*dest)._env_size_ = (*dest).env_length1;
}


static void emulator_ui_core_settings_destroy (EmulatorUICoreSettings* self) {
	_g_free0 ((*self).name);
	(*self).joypad_buttons = (_vala_GameJoypadButton_array_free ((*self).joypad_buttons, (*self).joypad_buttons_length1), NULL);
	_g_free0 ((*self).path);
	(*self).env = (_vala_RetroCoreRetroVariable_array_free ((*self).env, (*self).env_length1), NULL);
}


static EmulatorUICoreSettings* emulator_ui_core_settings_dup (const EmulatorUICoreSettings* self) {
	EmulatorUICoreSettings* dup;
	dup = g_new0 (EmulatorUICoreSettings, 1);
	emulator_ui_core_settings_copy (self, dup);
	return dup;
}


static void emulator_ui_core_settings_free (EmulatorUICoreSettings* self) {
	emulator_ui_core_settings_destroy (self);
	g_free (self);
}


static GType emulator_ui_core_settings_get_type (void) {
	static volatile gsize emulator_ui_core_settings_type_id__volatile = 0;
	if (g_once_init_enter (&emulator_ui_core_settings_type_id__volatile)) {
		GType emulator_ui_core_settings_type_id;
		emulator_ui_core_settings_type_id = g_boxed_type_register_static ("EmulatorUICoreSettings", (GBoxedCopyFunc) emulator_ui_core_settings_dup, (GBoxedFreeFunc) emulator_ui_core_settings_free);
		g_once_init_leave (&emulator_ui_core_settings_type_id__volatile, emulator_ui_core_settings_type_id);
	}
	return emulator_ui_core_settings_type_id__volatile;
}


static void emulator_ui_class_init (EmulatorUIClass * klass) {
	emulator_ui_parent_class = g_type_class_peek_parent (klass);
	g_type_class_add_private (klass, sizeof (EmulatorUIPrivate));
	G_OBJECT_CLASS (klass)->get_property = _vala_emulator_ui_get_property;
	G_OBJECT_CLASS (klass)->set_property = _vala_emulator_ui_set_property;
	G_OBJECT_CLASS (klass)->finalize = emulator_ui_finalize;
	g_object_class_install_property (G_OBJECT_CLASS (klass), EMULATOR_UI_DARK_MODE, g_param_spec_boolean ("dark-mode", "dark-mode", "dark-mode", FALSE, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
	g_object_class_install_property (G_OBJECT_CLASS (klass), EMULATOR_UI_STATE_DIR, g_param_spec_string ("state-dir", "state-dir", "state-dir", NULL, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
	g_object_class_install_property (G_OBJECT_CLASS (klass), EMULATOR_UI_LAST_DIR, g_param_spec_string ("last-dir", "last-dir", "last-dir", NULL, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
	g_object_class_install_property (G_OBJECT_CLASS (klass), EMULATOR_UI_CONTRAST, g_param_spec_int ("contrast", "contrast", "contrast", G_MININT, G_MAXINT, 0, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
	g_object_class_install_property (G_OBJECT_CLASS (klass), EMULATOR_UI_BRIGHTNESS, g_param_spec_int ("brightness", "brightness", "brightness", G_MININT, G_MAXINT, 0, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
	g_object_class_install_property (G_OBJECT_CLASS (klass), EMULATOR_UI_MAX_FPS, g_param_spec_int ("max-fps", "max-fps", "max-fps", G_MININT, G_MAXINT, 30, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
	g_object_class_install_property (G_OBJECT_CLASS (klass), EMULATOR_UI_RENDER_MODE, g_param_spec_enum ("render-mode", "render-mode", "render-mode", GAME_SCREEN_TYPE_COMMIT_MODE, GAME_SCREEN_COMMIT_MODE_SHM, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
	g_object_class_install_property (G_OBJECT_CLASS (klass), EMULATOR_UI_FULLSCREEN, g_param_spec_boolean ("fullscreen", "fullscreen", "fullscreen", TRUE, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
	g_object_class_install_property (G_OBJECT_CLASS (klass), EMULATOR_UI_AUDIO, g_param_spec_boolean ("audio", "audio", "audio", TRUE, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
	g_object_class_install_property (G_OBJECT_CLASS (klass), EMULATOR_UI_FRAME_COUNT, g_param_spec_int ("frame-count", "frame-count", "frame-count", G_MININT, G_MAXINT, 0, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
	g_object_class_install_property (G_OBJECT_CLASS (klass), EMULATOR_UI_TICKER_COUNT, g_param_spec_int ("ticker-count", "ticker-count", "ticker-count", G_MININT, G_MAXINT, 0, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE | G_PARAM_WRITABLE));
	g_signal_new ("emulator_size", TYPE_EMULATOR_UI, G_SIGNAL_RUN_LAST, 0, NULL, NULL, g_cclosure_user_marshal_VOID__INT_INT, G_TYPE_NONE, 2, G_TYPE_INT, G_TYPE_INT);
	g_signal_new ("open_game", TYPE_EMULATOR_UI, G_SIGNAL_RUN_LAST, 0, NULL, NULL, g_cclosure_marshal_VOID__VOID, G_TYPE_NONE, 0);
}


static void emulator_ui_instance_init (EmulatorUI * self) {
	gchar* _tmp0_ = NULL;
	gchar* _tmp1_ = NULL;
	gchar* _tmp2_ = NULL;
	self->priv = EMULATOR_UI_GET_PRIVATE (self);
	self->priv->core = NULL;
	_tmp0_ = g_strdup ("");
	self->priv->game_path = _tmp0_;
	self->priv->ready = FALSE;
	g_static_rec_mutex_init (&self->priv->__lock_running);
	self->priv->running = FALSE;
	g_static_rec_mutex_init (&self->priv->__lock_paused);
	self->priv->paused = FALSE;
	self->priv->core_width = 160;
	self->priv->core_height = 144;
	self->priv->frame_interval_us = 16742;
	_tmp1_ = g_strdup ("");
	self->priv->_state_dir = _tmp1_;
	_tmp2_ = g_strdup ("");
	self->priv->_last_dir = _tmp2_;
	self->priv->_contrast = 0;
	self->priv->_brightness = 0;
	self->priv->_max_fps = 30;
	self->priv->_render_mode = GAME_SCREEN_COMMIT_MODE_SHM;
	self->priv->_fullscreen = TRUE;
	self->priv->_audio = TRUE;
	self->priv->save_settings_timeout_id = (guint) 0;
	self->priv->autosave = TRUE;
	self->priv->speed_factor = (gdouble) 1;
	self->priv->_frame_count = 0;
	self->priv->_ticker_count = 0;
	self->priv->game_memory_loaded = FALSE;
}


static void emulator_ui_finalize (GObject* obj) {
	EmulatorUI * self;
	self = G_TYPE_CHECK_INSTANCE_CAST (obj, TYPE_EMULATOR_UI, EmulatorUI);
	_g_object_unref0 (self->priv->core);
	_g_free0 (self->priv->game_path);
	emulator_ui_core_settings_destroy (&self->priv->core_settings);
	g_static_rec_mutex_free (&self->priv->__lock_running);
	g_static_rec_mutex_free (&self->priv->__lock_paused);
	_g_object_unref0 (self->priv->gamescreen);
	_g_object_unref0 (self->priv->gamejoypad);
	_g_object_unref0 (self->priv->gamespeaker);
	_g_object_unref0 (self->priv->cores_map);
	_g_key_file_free0 (self->priv->kf);
	_g_object_unref0 (self->priv->lipstick);
	_g_free0 (self->priv->_state_dir);
	_g_free0 (self->priv->_last_dir);
	G_OBJECT_CLASS (emulator_ui_parent_class)->finalize (obj);
}


GType emulator_ui_get_type (void) {
	static volatile gsize emulator_ui_type_id__volatile = 0;
	if (g_once_init_enter (&emulator_ui_type_id__volatile)) {
		static const GTypeInfo g_define_type_info = { sizeof (EmulatorUIClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) emulator_ui_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (EmulatorUI), 0, (GInstanceInitFunc) emulator_ui_instance_init, NULL };
		GType emulator_ui_type_id;
		emulator_ui_type_id = g_type_register_static (GTK_TYPE_WINDOW, "EmulatorUI", &g_define_type_info, 0);
		g_once_init_leave (&emulator_ui_type_id__volatile, emulator_ui_type_id);
	}
	return emulator_ui_type_id__volatile;
}


static void _vala_emulator_ui_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec) {
	EmulatorUI * self;
	self = G_TYPE_CHECK_INSTANCE_CAST (object, TYPE_EMULATOR_UI, EmulatorUI);
	switch (property_id) {
		case EMULATOR_UI_DARK_MODE:
		g_value_set_boolean (value, emulator_ui_get_dark_mode (self));
		break;
		case EMULATOR_UI_STATE_DIR:
		g_value_set_string (value, emulator_ui_get_state_dir (self));
		break;
		case EMULATOR_UI_LAST_DIR:
		g_value_set_string (value, emulator_ui_get_last_dir (self));
		break;
		case EMULATOR_UI_CONTRAST:
		g_value_set_int (value, emulator_ui_get_contrast (self));
		break;
		case EMULATOR_UI_BRIGHTNESS:
		g_value_set_int (value, emulator_ui_get_brightness (self));
		break;
		case EMULATOR_UI_MAX_FPS:
		g_value_set_int (value, emulator_ui_get_max_fps (self));
		break;
		case EMULATOR_UI_RENDER_MODE:
		g_value_set_enum (value, emulator_ui_get_render_mode (self));
		break;
		case EMULATOR_UI_FULLSCREEN:
		g_value_set_boolean (value, emulator_ui_get_fullscreen (self));
		break;
		case EMULATOR_UI_AUDIO:
		g_value_set_boolean (value, emulator_ui_get_audio (self));
		break;
		case EMULATOR_UI_FRAME_COUNT:
		g_value_set_int (value, emulator_ui_get_frame_count (self));
		break;
		case EMULATOR_UI_TICKER_COUNT:
		g_value_set_int (value, emulator_ui_get_ticker_count (self));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}


static void _vala_emulator_ui_set_property (GObject * object, guint property_id, const GValue * value, GParamSpec * pspec) {
	EmulatorUI * self;
	self = G_TYPE_CHECK_INSTANCE_CAST (object, TYPE_EMULATOR_UI, EmulatorUI);
	switch (property_id) {
		case EMULATOR_UI_DARK_MODE:
		emulator_ui_set_dark_mode (self, g_value_get_boolean (value));
		break;
		case EMULATOR_UI_STATE_DIR:
		emulator_ui_set_state_dir (self, g_value_get_string (value));
		break;
		case EMULATOR_UI_LAST_DIR:
		emulator_ui_set_last_dir (self, g_value_get_string (value));
		break;
		case EMULATOR_UI_CONTRAST:
		emulator_ui_set_contrast (self, g_value_get_int (value));
		break;
		case EMULATOR_UI_BRIGHTNESS:
		emulator_ui_set_brightness (self, g_value_get_int (value));
		break;
		case EMULATOR_UI_MAX_FPS:
		emulator_ui_set_max_fps (self, g_value_get_int (value));
		break;
		case EMULATOR_UI_RENDER_MODE:
		emulator_ui_set_render_mode (self, g_value_get_enum (value));
		break;
		case EMULATOR_UI_FULLSCREEN:
		emulator_ui_set_fullscreen (self, g_value_get_boolean (value));
		break;
		case EMULATOR_UI_AUDIO:
		emulator_ui_set_audio (self, g_value_get_boolean (value));
		break;
		case EMULATOR_UI_FRAME_COUNT:
		emulator_ui_set_frame_count (self, g_value_get_int (value));
		break;
		case EMULATOR_UI_TICKER_COUNT:
		emulator_ui_set_ticker_count (self, g_value_get_int (value));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}


static void _vala_array_destroy (gpointer array, gint array_length, GDestroyNotify destroy_func) {
	if ((array != NULL) && (destroy_func != NULL)) {
		int i;
		for (i = 0; i < array_length; i = i + 1) {
			if (((gpointer*) array)[i] != NULL) {
				destroy_func (((gpointer*) array)[i]);
			}
		}
	}
}


static void _vala_array_free (gpointer array, gint array_length, GDestroyNotify destroy_func) {
	_vala_array_destroy (array, array_length, destroy_func);
	g_free (array);
}


static gint _vala_array_length (gpointer array) {
	int length;
	length = 0;
	if (array) {
		while (((gpointer*) array)[length]) {
			length++;
		}
	}
	return length;
}



