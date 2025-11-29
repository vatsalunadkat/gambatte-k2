#include <glib.h>
#include <glib-object.h>
#include <string.h>


#define TYPE_FB_INK (fb_ink_get_type ())
#define FB_INK(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_FB_INK, FBInk))
#define FB_INK_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_FB_INK, FBInkClass))
#define IS_FB_INK(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_FB_INK))
#define IS_FB_INK_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_FB_INK))
#define FB_INK_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_FB_INK, FBInkClass))

typedef struct _FBInk FBInk;
typedef struct _FBInkClass FBInkClass;
typedef struct _FBInkPrivate FBInkPrivate;

#define FB_INK_TYPE_CONFIG (fb_ink_config_get_type ())
typedef struct _FBInkConfig FBInkConfig;

#define FB_INK_TYPE_FBFD (fb_ink_fbfd_get_type ())

#define FB_INK_TYPE_WFM_MODE_INDEX_E (fb_ink_wfm_mode_index_e_get_type ())

#define FB_INK_TYPE_HW_DITHER_INDEX_E (fb_ink_hw_dither_index_e_get_type ())

#define FB_INK_TYPE_INPUT_DEVICE_TYPE_E (fb_ink_input_device_type_e_get_type ())

#define FB_INK_TYPE_INPUT_DEVICE (fb_ink_input_device_get_type ())
typedef struct _FBInkInputDevice FBInkInputDevice;
#define _g_free0(var) (var = (g_free (var), NULL))

typedef enum  {
	FB_INK_ERROR_ERROR
} FBInkError;
#define FB_INK_ERROR fb_ink_error_quark ()
struct _FBInk {
	GObject parent_instance;
	FBInkPrivate * priv;
};

struct _FBInkClass {
	GObjectClass parent_class;
};

struct _FBInkConfig {
	gshort row;
	gshort col;
	guint8 fontmult;
	guint8 fontname;
	guint8 is_inverted;
	guint8 is_flashing;
	guint8 is_cleared;
	guint8 is_centered;
	gshort hoffset;
	gshort voffset;
	guint8 is_halfway;
	guint8 is_padded;
	guint8 is_rpadded;
	guint8 fg_color;
	guint8 bg_color;
	guint8 is_overlay;
	guint8 is_bgless;
	guint8 is_fgless;
	guint8 no_viewport;
	guint8 is_verbose;
	guint8 is_quiet;
	guint8 ignore_alpha;
	guint8 halign;
	guint8 valign;
	gshort scaled_width;
	gshort scaled_height;
	guint8 wfm_mode;
	guint8 dithering_mode;
	guint8 sw_dithering;
	guint8 cfa_mode;
	guint8 is_nightmode;
	guint8 no_refresh;
	guint8 no_merge;
	guint8 is_animated;
	guint8 saturation_boost;
	guint8 to_syslog;
};

struct _FBInkPrivate {
	gint fbfd;
	FBInkConfig cfg;
};

typedef enum  {
	FB_INK_FBFD_AUTO = -1
} FBInkFBFD;

typedef enum  {
	FB_INK_WFM_MODE_INDEX_E_AUTO = 0,
	FB_INK_WFM_MODE_INDEX_E_DU,
	FB_INK_WFM_MODE_INDEX_E_GC16,
	FB_INK_WFM_MODE_INDEX_E_GC4,
	FB_INK_WFM_MODE_INDEX_E_A2,
	FB_INK_WFM_MODE_INDEX_E_GL16,
	FB_INK_WFM_MODE_INDEX_E_REAGL,
	FB_INK_WFM_MODE_INDEX_E_REAGLD,
	FB_INK_WFM_MODE_INDEX_E_GC16_FAST,
	FB_INK_WFM_MODE_INDEX_E_GL16_FAST,
	FB_INK_WFM_MODE_INDEX_E_DU4,
	FB_INK_WFM_MODE_INDEX_E_GL4,
	FB_INK_WFM_MODE_INDEX_E_GL16_INV,
	FB_INK_WFM_MODE_INDEX_E_GCK16,
	FB_INK_WFM_MODE_INDEX_E_GLKW16,
	FB_INK_WFM_MODE_INDEX_E_INIT,
	FB_INK_WFM_MODE_INDEX_E_UNKNOWN,
	FB_INK_WFM_MODE_INDEX_E_INIT2,
	FB_INK_WFM_MODE_INDEX_E_A2IN,
	FB_INK_WFM_MODE_INDEX_E_A2OUT,
	FB_INK_WFM_MODE_INDEX_E_GC16HQ,
	FB_INK_WFM_MODE_INDEX_E_GS16,
	FB_INK_WFM_MODE_INDEX_E_GU16,
	FB_INK_WFM_MODE_INDEX_E_GLK16,
	FB_INK_WFM_MODE_INDEX_E_CLEAR,
	FB_INK_WFM_MODE_INDEX_E_GC4L,
	FB_INK_WFM_MODE_INDEX_E_GCC16,
	FB_INK_WFM_MODE_INDEX_E_GLRC16,
	FB_INK_WFM_MODE_INDEX_E_GC16_PARTIAL,
	FB_INK_WFM_MODE_INDEX_E_GCK16_PARTIAL,
	FB_INK_WFM_MODE_INDEX_E_DUNM,
	FB_INK_WFM_MODE_INDEX_E_P2SW,
	FB_INK_WFM_MODE_INDEX_E_GCCK16,
	FB_INK_WFM_MODE_INDEX_E_GLRCK16,
	FB_INK_WFM_MODE_INDEX_E_MAX = 255
} FBInkWFM_MODE_INDEX_E;

typedef enum  {
	FB_INK_HW_DITHER_INDEX_E_PASSTHROUGH = 0,
	FB_INK_HW_DITHER_INDEX_E_FLOYD_STEINBERG,
	FB_INK_HW_DITHER_INDEX_E_ATKINSON,
	FB_INK_HW_DITHER_INDEX_E_ORDERED,
	FB_INK_HW_DITHER_INDEX_E_QUANT_ONLY,
	FB_INK_HW_DITHER_INDEX_E_LEGACY = 255
} FBInkHW_DITHER_INDEX_E;

typedef enum  {
	FB_INK_INPUT_DEVICE_TYPE_E_UNKNOWN = 0,
	FB_INK_INPUT_DEVICE_TYPE_E_POINTINGSTICK = 1 << 0,
	FB_INK_INPUT_DEVICE_TYPE_E_MOUSE = 1 << 1,
	FB_INK_INPUT_DEVICE_TYPE_E_TOUCHPAD = 1 << 2,
	FB_INK_INPUT_DEVICE_TYPE_E_TOUCHSCREEN = 1 << 3,
	FB_INK_INPUT_DEVICE_TYPE_E_JOYSTICK = 1 << 4,
	FB_INK_INPUT_DEVICE_TYPE_E_TABLET = 1 << 5,
	FB_INK_INPUT_DEVICE_TYPE_E_KEY = 1 << 6,
	FB_INK_INPUT_DEVICE_TYPE_E_KEYBOARD = 1 << 7,
	FB_INK_INPUT_DEVICE_TYPE_E_ACCELEROMETER = 1 << 8,
	FB_INK_INPUT_DEVICE_TYPE_E_POWER_BUTTON = 1 << 16,
	FB_INK_INPUT_DEVICE_TYPE_E_SLEEP_COVER = 1 << 17,
	FB_INK_INPUT_DEVICE_TYPE_E_PAGINATION_BUTTONS = 1 << 18,
	FB_INK_INPUT_DEVICE_TYPE_E_HOME_BUTTON = 1 << 19,
	FB_INK_INPUT_DEVICE_TYPE_E_LIGHT_BUTTON = 1 << 20,
	FB_INK_INPUT_DEVICE_TYPE_E_MENU_BUTTON = 1 << 21,
	FB_INK_INPUT_DEVICE_TYPE_E_DPAD = 1 << 22,
	FB_INK_INPUT_DEVICE_TYPE_E_ROTATION_EVENT = 1 << 23,
	FB_INK_INPUT_DEVICE_TYPE_E_SCALED_TABLET = 1 << 24,
	FB_INK_INPUT_DEVICE_TYPE_E_VOLUME_BUTTONS = 1 << 25
} FBInkINPUT_DEVICE_TYPE_E;

struct _FBInkInputDevice {
	guint32 type;
	gint fd;
	guint8 matched;
	gchar name[256];
	gchar path[4096];
};


static gpointer fb_ink_parent_class = NULL;

GQuark fb_ink_error_quark (void);
GType fb_ink_get_type (void) G_GNUC_CONST;
GType fb_ink_config_get_type (void) G_GNUC_CONST;
FBInkConfig* fb_ink_config_dup (const FBInkConfig* self);
void fb_ink_config_free (FBInkConfig* self);
#define FB_INK_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), TYPE_FB_INK, FBInkPrivate))
enum  {
	FB_INK_DUMMY_PROPERTY
};
gint fbink_close (gint fbfd);
GType fb_ink_fbfd_get_type (void) G_GNUC_CONST;
GType fb_ink_wfm_mode_index_e_get_type (void) G_GNUC_CONST;
GType fb_ink_hw_dither_index_e_get_type (void) G_GNUC_CONST;
GType fb_ink_input_device_type_e_get_type (void) G_GNUC_CONST;
gint fbink_open (void);
gint fbink_init (gint fbfd, FBInkConfig* fbink_cfg);
gint fbink_print_raw_data (gint fbfd, guint8* data, gint w, gint h, gsize len, gint x_off, gint y_off, FBInkConfig* fbink_cfg);
gint fbink_refresh (gint fbfd, guint32 region_top, guint32 region_left, guint32 region_width, guint32 region_height, FBInkConfig* fbink_cfg);
GType fb_ink_input_device_get_type (void) G_GNUC_CONST;
FBInkInputDevice* fb_ink_input_device_dup (const FBInkInputDevice* self);
void fb_ink_input_device_free (FBInkInputDevice* self);
FBInkInputDevice* fbink_input_scan (guint32 match_types, guint32 exclude_types, guint32 settings, size_t* result_length1);
FBInk* fb_ink_new (FBInkConfig* fbink_cfg, GError** error);
FBInk* fb_ink_construct (GType object_type, FBInkConfig* fbink_cfg, GError** error);
gint fb_ink_refresh (FBInk* self, guint x, guint y, guint w, guint h);
gint fb_ink_print_raw_data (FBInk* self, guint8* data, gint w, gint h, gsize len, gint x_off, gint y_off);
gchar* fb_ink_detect_touch_device (void);
static void fb_ink_finalize (GObject* obj);


GQuark fb_ink_error_quark (void) {
	return g_quark_from_static_string ("fb_ink_error-quark");
}


GType fb_ink_fbfd_get_type (void) {
	static volatile gsize fb_ink_fbfd_type_id__volatile = 0;
	if (g_once_init_enter (&fb_ink_fbfd_type_id__volatile)) {
		static const GEnumValue values[] = {{FB_INK_FBFD_AUTO, "FB_INK_FBFD_AUTO", "auto"}, {0, NULL, NULL}};
		GType fb_ink_fbfd_type_id;
		fb_ink_fbfd_type_id = g_enum_register_static ("FBInkFBFD", values);
		g_once_init_leave (&fb_ink_fbfd_type_id__volatile, fb_ink_fbfd_type_id);
	}
	return fb_ink_fbfd_type_id__volatile;
}


GType fb_ink_wfm_mode_index_e_get_type (void) {
	static volatile gsize fb_ink_wfm_mode_index_e_type_id__volatile = 0;
	if (g_once_init_enter (&fb_ink_wfm_mode_index_e_type_id__volatile)) {
		static const GEnumValue values[] = {{FB_INK_WFM_MODE_INDEX_E_AUTO, "FB_INK_WFM_MODE_INDEX_E_AUTO", "auto"}, {FB_INK_WFM_MODE_INDEX_E_DU, "FB_INK_WFM_MODE_INDEX_E_DU", "du"}, {FB_INK_WFM_MODE_INDEX_E_GC16, "FB_INK_WFM_MODE_INDEX_E_GC16", "gc16"}, {FB_INK_WFM_MODE_INDEX_E_GC4, "FB_INK_WFM_MODE_INDEX_E_GC4", "gc4"}, {FB_INK_WFM_MODE_INDEX_E_A2, "FB_INK_WFM_MODE_INDEX_E_A2", "a2"}, {FB_INK_WFM_MODE_INDEX_E_GL16, "FB_INK_WFM_MODE_INDEX_E_GL16", "gl16"}, {FB_INK_WFM_MODE_INDEX_E_REAGL, "FB_INK_WFM_MODE_INDEX_E_REAGL", "reagl"}, {FB_INK_WFM_MODE_INDEX_E_REAGLD, "FB_INK_WFM_MODE_INDEX_E_REAGLD", "reagld"}, {FB_INK_WFM_MODE_INDEX_E_GC16_FAST, "FB_INK_WFM_MODE_INDEX_E_GC16_FAST", "gc16-fast"}, {FB_INK_WFM_MODE_INDEX_E_GL16_FAST, "FB_INK_WFM_MODE_INDEX_E_GL16_FAST", "gl16-fast"}, {FB_INK_WFM_MODE_INDEX_E_DU4, "FB_INK_WFM_MODE_INDEX_E_DU4", "du4"}, {FB_INK_WFM_MODE_INDEX_E_GL4, "FB_INK_WFM_MODE_INDEX_E_GL4", "gl4"}, {FB_INK_WFM_MODE_INDEX_E_GL16_INV, "FB_INK_WFM_MODE_INDEX_E_GL16_INV", "gl16-inv"}, {FB_INK_WFM_MODE_INDEX_E_GCK16, "FB_INK_WFM_MODE_INDEX_E_GCK16", "gck16"}, {FB_INK_WFM_MODE_INDEX_E_GLKW16, "FB_INK_WFM_MODE_INDEX_E_GLKW16", "glkw16"}, {FB_INK_WFM_MODE_INDEX_E_INIT, "FB_INK_WFM_MODE_INDEX_E_INIT", "init"}, {FB_INK_WFM_MODE_INDEX_E_UNKNOWN, "FB_INK_WFM_MODE_INDEX_E_UNKNOWN", "unknown"}, {FB_INK_WFM_MODE_INDEX_E_INIT2, "FB_INK_WFM_MODE_INDEX_E_INIT2", "init2"}, {FB_INK_WFM_MODE_INDEX_E_A2IN, "FB_INK_WFM_MODE_INDEX_E_A2IN", "a2in"}, {FB_INK_WFM_MODE_INDEX_E_A2OUT, "FB_INK_WFM_MODE_INDEX_E_A2OUT", "a2out"}, {FB_INK_WFM_MODE_INDEX_E_GC16HQ, "FB_INK_WFM_MODE_INDEX_E_GC16HQ", "gc16hq"}, {FB_INK_WFM_MODE_INDEX_E_GS16, "FB_INK_WFM_MODE_INDEX_E_GS16", "gs16"}, {FB_INK_WFM_MODE_INDEX_E_GU16, "FB_INK_WFM_MODE_INDEX_E_GU16", "gu16"}, {FB_INK_WFM_MODE_INDEX_E_GLK16, "FB_INK_WFM_MODE_INDEX_E_GLK16", "glk16"}, {FB_INK_WFM_MODE_INDEX_E_CLEAR, "FB_INK_WFM_MODE_INDEX_E_CLEAR", "clear"}, {FB_INK_WFM_MODE_INDEX_E_GC4L, "FB_INK_WFM_MODE_INDEX_E_GC4L", "gc4l"}, {FB_INK_WFM_MODE_INDEX_E_GCC16, "FB_INK_WFM_MODE_INDEX_E_GCC16", "gcc16"}, {FB_INK_WFM_MODE_INDEX_E_GLRC16, "FB_INK_WFM_MODE_INDEX_E_GLRC16", "glrc16"}, {FB_INK_WFM_MODE_INDEX_E_GC16_PARTIAL, "FB_INK_WFM_MODE_INDEX_E_GC16_PARTIAL", "gc16-partial"}, {FB_INK_WFM_MODE_INDEX_E_GCK16_PARTIAL, "FB_INK_WFM_MODE_INDEX_E_GCK16_PARTIAL", "gck16-partial"}, {FB_INK_WFM_MODE_INDEX_E_DUNM, "FB_INK_WFM_MODE_INDEX_E_DUNM", "dunm"}, {FB_INK_WFM_MODE_INDEX_E_P2SW, "FB_INK_WFM_MODE_INDEX_E_P2SW", "p2sw"}, {FB_INK_WFM_MODE_INDEX_E_GCCK16, "FB_INK_WFM_MODE_INDEX_E_GCCK16", "gcck16"}, {FB_INK_WFM_MODE_INDEX_E_GLRCK16, "FB_INK_WFM_MODE_INDEX_E_GLRCK16", "glrck16"}, {FB_INK_WFM_MODE_INDEX_E_MAX, "FB_INK_WFM_MODE_INDEX_E_MAX", "max"}, {0, NULL, NULL}};
		GType fb_ink_wfm_mode_index_e_type_id;
		fb_ink_wfm_mode_index_e_type_id = g_enum_register_static ("FBInkWFM_MODE_INDEX_E", values);
		g_once_init_leave (&fb_ink_wfm_mode_index_e_type_id__volatile, fb_ink_wfm_mode_index_e_type_id);
	}
	return fb_ink_wfm_mode_index_e_type_id__volatile;
}


GType fb_ink_hw_dither_index_e_get_type (void) {
	static volatile gsize fb_ink_hw_dither_index_e_type_id__volatile = 0;
	if (g_once_init_enter (&fb_ink_hw_dither_index_e_type_id__volatile)) {
		static const GEnumValue values[] = {{FB_INK_HW_DITHER_INDEX_E_PASSTHROUGH, "FB_INK_HW_DITHER_INDEX_E_PASSTHROUGH", "passthrough"}, {FB_INK_HW_DITHER_INDEX_E_FLOYD_STEINBERG, "FB_INK_HW_DITHER_INDEX_E_FLOYD_STEINBERG", "floyd-steinberg"}, {FB_INK_HW_DITHER_INDEX_E_ATKINSON, "FB_INK_HW_DITHER_INDEX_E_ATKINSON", "atkinson"}, {FB_INK_HW_DITHER_INDEX_E_ORDERED, "FB_INK_HW_DITHER_INDEX_E_ORDERED", "ordered"}, {FB_INK_HW_DITHER_INDEX_E_QUANT_ONLY, "FB_INK_HW_DITHER_INDEX_E_QUANT_ONLY", "quant-only"}, {FB_INK_HW_DITHER_INDEX_E_LEGACY, "FB_INK_HW_DITHER_INDEX_E_LEGACY", "legacy"}, {0, NULL, NULL}};
		GType fb_ink_hw_dither_index_e_type_id;
		fb_ink_hw_dither_index_e_type_id = g_enum_register_static ("FBInkHW_DITHER_INDEX_E", values);
		g_once_init_leave (&fb_ink_hw_dither_index_e_type_id__volatile, fb_ink_hw_dither_index_e_type_id);
	}
	return fb_ink_hw_dither_index_e_type_id__volatile;
}


GType fb_ink_input_device_type_e_get_type (void) {
	static volatile gsize fb_ink_input_device_type_e_type_id__volatile = 0;
	if (g_once_init_enter (&fb_ink_input_device_type_e_type_id__volatile)) {
		static const GFlagsValue values[] = {{FB_INK_INPUT_DEVICE_TYPE_E_UNKNOWN, "FB_INK_INPUT_DEVICE_TYPE_E_UNKNOWN", "unknown"}, {FB_INK_INPUT_DEVICE_TYPE_E_POINTINGSTICK, "FB_INK_INPUT_DEVICE_TYPE_E_POINTINGSTICK", "pointingstick"}, {FB_INK_INPUT_DEVICE_TYPE_E_MOUSE, "FB_INK_INPUT_DEVICE_TYPE_E_MOUSE", "mouse"}, {FB_INK_INPUT_DEVICE_TYPE_E_TOUCHPAD, "FB_INK_INPUT_DEVICE_TYPE_E_TOUCHPAD", "touchpad"}, {FB_INK_INPUT_DEVICE_TYPE_E_TOUCHSCREEN, "FB_INK_INPUT_DEVICE_TYPE_E_TOUCHSCREEN", "touchscreen"}, {FB_INK_INPUT_DEVICE_TYPE_E_JOYSTICK, "FB_INK_INPUT_DEVICE_TYPE_E_JOYSTICK", "joystick"}, {FB_INK_INPUT_DEVICE_TYPE_E_TABLET, "FB_INK_INPUT_DEVICE_TYPE_E_TABLET", "tablet"}, {FB_INK_INPUT_DEVICE_TYPE_E_KEY, "FB_INK_INPUT_DEVICE_TYPE_E_KEY", "key"}, {FB_INK_INPUT_DEVICE_TYPE_E_KEYBOARD, "FB_INK_INPUT_DEVICE_TYPE_E_KEYBOARD", "keyboard"}, {FB_INK_INPUT_DEVICE_TYPE_E_ACCELEROMETER, "FB_INK_INPUT_DEVICE_TYPE_E_ACCELEROMETER", "accelerometer"}, {FB_INK_INPUT_DEVICE_TYPE_E_POWER_BUTTON, "FB_INK_INPUT_DEVICE_TYPE_E_POWER_BUTTON", "power-button"}, {FB_INK_INPUT_DEVICE_TYPE_E_SLEEP_COVER, "FB_INK_INPUT_DEVICE_TYPE_E_SLEEP_COVER", "sleep-cover"}, {FB_INK_INPUT_DEVICE_TYPE_E_PAGINATION_BUTTONS, "FB_INK_INPUT_DEVICE_TYPE_E_PAGINATION_BUTTONS", "pagination-buttons"}, {FB_INK_INPUT_DEVICE_TYPE_E_HOME_BUTTON, "FB_INK_INPUT_DEVICE_TYPE_E_HOME_BUTTON", "home-button"}, {FB_INK_INPUT_DEVICE_TYPE_E_LIGHT_BUTTON, "FB_INK_INPUT_DEVICE_TYPE_E_LIGHT_BUTTON", "light-button"}, {FB_INK_INPUT_DEVICE_TYPE_E_MENU_BUTTON, "FB_INK_INPUT_DEVICE_TYPE_E_MENU_BUTTON", "menu-button"}, {FB_INK_INPUT_DEVICE_TYPE_E_DPAD, "FB_INK_INPUT_DEVICE_TYPE_E_DPAD", "dpad"}, {FB_INK_INPUT_DEVICE_TYPE_E_ROTATION_EVENT, "FB_INK_INPUT_DEVICE_TYPE_E_ROTATION_EVENT", "rotation-event"}, {FB_INK_INPUT_DEVICE_TYPE_E_SCALED_TABLET, "FB_INK_INPUT_DEVICE_TYPE_E_SCALED_TABLET", "scaled-tablet"}, {FB_INK_INPUT_DEVICE_TYPE_E_VOLUME_BUTTONS, "FB_INK_INPUT_DEVICE_TYPE_E_VOLUME_BUTTONS", "volume-buttons"}, {0, NULL, NULL}};
		GType fb_ink_input_device_type_e_type_id;
		fb_ink_input_device_type_e_type_id = g_flags_register_static ("FBInkINPUT_DEVICE_TYPE_E", values);
		g_once_init_leave (&fb_ink_input_device_type_e_type_id__volatile, fb_ink_input_device_type_e_type_id);
	}
	return fb_ink_input_device_type_e_type_id__volatile;
}


FBInk* fb_ink_construct (GType object_type, FBInkConfig* fbink_cfg, GError** error) {
	FBInk * self = NULL;
	FBInkConfig _tmp0_ = {0};
	gint _tmp1_ = 0;
	gint _tmp2_ = 0;
	gint _tmp3_ = 0;
	g_return_val_if_fail (fbink_cfg != NULL, NULL);
	self = (FBInk*) g_object_new (object_type, NULL);
	_tmp0_ = *fbink_cfg;
	self->priv->cfg = _tmp0_;
	_tmp1_ = fbink_open ();
	self->priv->fbfd = _tmp1_;
	_tmp2_ = self->priv->fbfd;
	_tmp3_ = fbink_init (_tmp2_, &self->priv->cfg);
	if (_tmp3_ != 0) {
	}
	return self;
}


FBInk* fb_ink_new (FBInkConfig* fbink_cfg, GError** error) {
	return fb_ink_construct (TYPE_FB_INK, fbink_cfg, error);
}


gint fb_ink_refresh (FBInk* self, guint x, guint y, guint w, guint h) {
	gint result = 0;
	gint _tmp0_ = 0;
	guint _tmp1_ = 0U;
	guint _tmp2_ = 0U;
	guint _tmp3_ = 0U;
	guint _tmp4_ = 0U;
	gint _tmp5_ = 0;
	g_return_val_if_fail (self != NULL, 0);
	_tmp0_ = self->priv->fbfd;
	_tmp1_ = y;
	_tmp2_ = x;
	_tmp3_ = w;
	_tmp4_ = h;
	_tmp5_ = fbink_refresh (_tmp0_, (guint32) _tmp1_, (guint32) _tmp2_, (guint32) _tmp3_, (guint32) _tmp4_, &self->priv->cfg);
	result = _tmp5_;
	return result;
}


gint fb_ink_print_raw_data (FBInk* self, guint8* data, gint w, gint h, gsize len, gint x_off, gint y_off) {
	gint result = 0;
	gint _tmp0_ = 0;
	guint8* _tmp1_ = NULL;
	gint _tmp2_ = 0;
	gint _tmp3_ = 0;
	gsize _tmp4_ = 0UL;
	gint _tmp5_ = 0;
	gint _tmp6_ = 0;
	gint _tmp7_ = 0;
	g_return_val_if_fail (self != NULL, 0);
	_tmp0_ = self->priv->fbfd;
	_tmp1_ = data;
	_tmp2_ = w;
	_tmp3_ = h;
	_tmp4_ = len;
	_tmp5_ = x_off;
	_tmp6_ = y_off;
	_tmp7_ = fbink_print_raw_data (_tmp0_, _tmp1_, _tmp2_, _tmp3_, _tmp4_, _tmp5_, _tmp6_, &self->priv->cfg);
	result = _tmp7_;
	return result;
}


gchar* fb_ink_detect_touch_device (void) {
	gchar* result = NULL;
	gchar* detected_touch_path = NULL;
	gchar* _tmp0_ = NULL;
	guint32 match_mask = 0U;
	FBInkInputDevice* devices = NULL;
	guint32 _tmp1_ = 0U;
	size_t _tmp2_;
	FBInkInputDevice* _tmp3_ = NULL;
	gint devices_length1 = 0;
	gint _devices_size_ = 0;
	FBInkInputDevice* _tmp4_ = NULL;
	gint _tmp4__length1 = 0;
	_tmp0_ = g_strdup ("/dev/input/event1");
	detected_touch_path = _tmp0_;
	match_mask = (guint32) (FB_INK_INPUT_DEVICE_TYPE_E_TOUCHSCREEN | FB_INK_INPUT_DEVICE_TYPE_E_SCALED_TABLET);
	_tmp1_ = match_mask;
	_tmp3_ = fbink_input_scan (_tmp1_, (guint32) 0, (guint32) 0, &_tmp2_);
	devices = _tmp3_;
	devices_length1 = _tmp2_;
	_devices_size_ = devices_length1;
	_tmp4_ = devices;
	_tmp4__length1 = devices_length1;
	{
		FBInkInputDevice* device_collection = NULL;
		gint device_collection_length1 = 0;
		gint _device_collection_size_ = 0;
		gint device_it = 0;
		device_collection = _tmp4_;
		device_collection_length1 = _tmp4__length1;
		for (device_it = 0; device_it < _tmp4__length1; device_it = device_it + 1) {
			FBInkInputDevice device = {0};
			device = device_collection[device_it];
			{
				FBInkInputDevice _tmp5_ = {0};
				guint8 _tmp6_ = 0U;
				_tmp5_ = device;
				_tmp6_ = _tmp5_.matched;
				if (((gint) _tmp6_) == 1) {
					FBInkInputDevice _tmp7_ = {0};
					gchar* _tmp8_ = NULL;
					_tmp7_ = device;
					_tmp8_ = g_strdup ((const gchar*) _tmp7_.path);
					_g_free0 (detected_touch_path);
					detected_touch_path = _tmp8_;
					break;
				}
			}
		}
	}
	result = detected_touch_path;
	devices = (g_free (devices), NULL);
	return result;
}


FBInkConfig* fb_ink_config_dup (const FBInkConfig* self) {
	FBInkConfig* dup;
	dup = g_new0 (FBInkConfig, 1);
	memcpy (dup, self, sizeof (FBInkConfig));
	return dup;
}


void fb_ink_config_free (FBInkConfig* self) {
	g_free (self);
}


GType fb_ink_config_get_type (void) {
	static volatile gsize fb_ink_config_type_id__volatile = 0;
	if (g_once_init_enter (&fb_ink_config_type_id__volatile)) {
		GType fb_ink_config_type_id;
		fb_ink_config_type_id = g_boxed_type_register_static ("FBInkConfig", (GBoxedCopyFunc) fb_ink_config_dup, (GBoxedFreeFunc) fb_ink_config_free);
		g_once_init_leave (&fb_ink_config_type_id__volatile, fb_ink_config_type_id);
	}
	return fb_ink_config_type_id__volatile;
}


FBInkInputDevice* fb_ink_input_device_dup (const FBInkInputDevice* self) {
	FBInkInputDevice* dup;
	dup = g_new0 (FBInkInputDevice, 1);
	memcpy (dup, self, sizeof (FBInkInputDevice));
	return dup;
}


void fb_ink_input_device_free (FBInkInputDevice* self) {
	g_free (self);
}


GType fb_ink_input_device_get_type (void) {
	static volatile gsize fb_ink_input_device_type_id__volatile = 0;
	if (g_once_init_enter (&fb_ink_input_device_type_id__volatile)) {
		GType fb_ink_input_device_type_id;
		fb_ink_input_device_type_id = g_boxed_type_register_static ("FBInkInputDevice", (GBoxedCopyFunc) fb_ink_input_device_dup, (GBoxedFreeFunc) fb_ink_input_device_free);
		g_once_init_leave (&fb_ink_input_device_type_id__volatile, fb_ink_input_device_type_id);
	}
	return fb_ink_input_device_type_id__volatile;
}


static void fb_ink_class_init (FBInkClass * klass) {
	fb_ink_parent_class = g_type_class_peek_parent (klass);
	g_type_class_add_private (klass, sizeof (FBInkPrivate));
	G_OBJECT_CLASS (klass)->finalize = fb_ink_finalize;
}


static void fb_ink_instance_init (FBInk * self) {
	self->priv = FB_INK_GET_PRIVATE (self);
}


static void fb_ink_finalize (GObject* obj) {
	FBInk * self;
	gint _tmp0_ = 0;
	self = G_TYPE_CHECK_INSTANCE_CAST (obj, TYPE_FB_INK, FBInk);
	_tmp0_ = self->priv->fbfd;
	fbink_close (_tmp0_);
	G_OBJECT_CLASS (fb_ink_parent_class)->finalize (obj);
}


GType fb_ink_get_type (void) {
	static volatile gsize fb_ink_type_id__volatile = 0;
	if (g_once_init_enter (&fb_ink_type_id__volatile)) {
		static const GTypeInfo g_define_type_info = { sizeof (FBInkClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) fb_ink_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (FBInk), 0, (GInstanceInitFunc) fb_ink_instance_init, NULL };
		GType fb_ink_type_id;
		fb_ink_type_id = g_type_register_static (G_TYPE_OBJECT, "FBInk", &g_define_type_info, 0);
		g_once_init_leave (&fb_ink_type_id__volatile, fb_ink_type_id);
	}
	return fb_ink_type_id__volatile;
}



