#include <glib.h>
#include <glib-object.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <math.h>
#include <gmodule.h>
#include <stdio.h>
#include <gio/gio.h>


#define TYPE_RETRO_CORE (retro_core_get_type ())
#define RETRO_CORE(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_RETRO_CORE, RetroCore))
#define RETRO_CORE_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_RETRO_CORE, RetroCoreClass))
#define IS_RETRO_CORE(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_RETRO_CORE))
#define IS_RETRO_CORE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_RETRO_CORE))
#define RETRO_CORE_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_RETRO_CORE, RetroCoreClass))

typedef struct _RetroCore RetroCore;
typedef struct _RetroCoreClass RetroCoreClass;
typedef struct _RetroCorePrivate RetroCorePrivate;

#define RETRO_CORE_TYPE_RETRO_GAME_INFO (retro_core_retro_game_info_get_type ())
typedef struct _RetroCoreRetroGameInfo RetroCoreRetroGameInfo;

#define RETRO_CORE_TYPE_RETRO_SYSTEM_AV_INFO (retro_core_retro_system_av_info_get_type ())

#define RETRO_CORE_TYPE_RETRO_GAME_GEOMETRY (retro_core_retro_game_geometry_get_type ())
typedef struct _RetroCoreRetroGameGeometry RetroCoreRetroGameGeometry;

#define RETRO_CORE_TYPE_RETRO_SYSTEM_TIMING (retro_core_retro_system_timing_get_type ())
typedef struct _RetroCoreRetroSystemTiming RetroCoreRetroSystemTiming;
typedef struct _RetroCoreRetroSystemAvInfo RetroCoreRetroSystemAvInfo;

#define RETRO_CORE_TYPE_RETRO_PIXEL_FORMAT (retro_core_retro_pixel_format_get_type ())

#define RETRO_CORE_TYPE_RETRO_ENVIRONMENT_SET (retro_core_retro_environment_set_get_type ())

#define RETRO_CORE_TYPE_RETRO_ENVIRONMENT_GET (retro_core_retro_environment_get_get_type ())
#define _g_module_close0(var) ((var == NULL) ? NULL : (var = (g_module_close (var), NULL)))

#define RETRO_CORE_TYPE_RETRO_VARIABLE (retro_core_retro_variable_get_type ())
typedef struct _RetroCoreRetroVariable RetroCoreRetroVariable;
#define _g_free0(var) (var = (g_free (var), NULL))
#define _g_object_unref0(var) ((var == NULL) ? NULL : (var = (g_object_unref (var), NULL)))
#define _g_error_free0(var) ((var == NULL) ? NULL : (var = (g_error_free (var), NULL)))

typedef enum  {
	PLUGIN_ERROR_SYMBOL_NOT_FOUND
} PluginError;
#define PLUGIN_ERROR plugin_error_quark ()
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

struct _RetroCorePrivate {
	GModule* module;
};

typedef enum  {
	RETRO_CORE_RETRO_PIXEL_FORMAT__0RGB1555 = 0,
	RETRO_CORE_RETRO_PIXEL_FORMAT_XRGB8888 = 1,
	RETRO_CORE_RETRO_PIXEL_FORMAT_RGB565 = 2
} RetroCoreRetroPixelFormat;

typedef enum  {
	RETRO_CORE_RETRO_ENVIRONMENT_SET_PIXEL_FORMAT = 10
} RetroCoreRetroEnvironmentSet;

typedef enum  {
	RETRO_CORE_RETRO_ENVIRONMENT_GET_VARIABLE = 15,
	RETRO_CORE_RETRO_ENVIRONMENT_GET_SYSTEM_DIRECTORY = 9,
	RETRO_CORE_RETRO_ENVIRONMENT_GET_SAVE_DIRECTORY = 31,
	RETRO_CORE_RETRO_ENVIRONMENT_GET_CAN_DUPE = 3
} RetroCoreRetroEnvironmentGet;

struct _RetroCoreRetroVariable {
	gchar* key;
	gchar* value;
};

typedef void (*RetroCoreRetroVideoRefreshT) (void* data, guint width, guint height, gsize pitch);
typedef gsize (*RetroCoreRetroAudioSampleBatchT) (void* data, gsize frames);
typedef void (*RetroCoreRetroInputPollT) ();
typedef gint16 (*RetroCoreRetroInputStateT) (guint port, guint device, guint index, guint id);
typedef gboolean (*RetroCoreRetroEnvironmentT) (guint cmd, void* data);
typedef void (*RetroCoreRetroSetEnvironment) (RetroCoreRetroEnvironmentT cb);
typedef void (*RetroCoreRetroSetVideoRefresh) (RetroCoreRetroVideoRefreshT cb);
typedef void (*RetroCoreRetroSetAudioSampleBatch) (RetroCoreRetroAudioSampleBatchT cb);
typedef void (*RetroCoreRetroSetInputPoll) (RetroCoreRetroInputPollT cb);
typedef void (*RetroCoreRetroSetInputState) (RetroCoreRetroInputStateT cb);

static gpointer retro_core_parent_class = NULL;
static RetroCoreRetroVariable* retro_core_environment_vars;
static gint retro_core_environment_vars_length1;
static RetroCoreRetroVariable* retro_core_environment_vars = NULL;
static gint retro_core_environment_vars_length1 = 0;
static gint _retro_core_environment_vars_size_ = 0;

GQuark plugin_error_quark (void);
GType retro_core_get_type (void) G_GNUC_CONST;
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
#define RETRO_CORE_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), TYPE_RETRO_CORE, RetroCorePrivate))
enum  {
	RETRO_CORE_DUMMY_PROPERTY
};
void retro_core_unload (RetroCore* self);
GType retro_core_retro_pixel_format_get_type (void) G_GNUC_CONST;
GType retro_core_retro_environment_set_get_type (void) G_GNUC_CONST;
GType retro_core_retro_environment_get_get_type (void) G_GNUC_CONST;
GType retro_core_retro_variable_get_type (void) G_GNUC_CONST;
RetroCoreRetroVariable* retro_core_retro_variable_dup (const RetroCoreRetroVariable* self);
void retro_core_retro_variable_free (RetroCoreRetroVariable* self);
void retro_core_retro_variable_copy (const RetroCoreRetroVariable* self, RetroCoreRetroVariable* dest);
void retro_core_retro_variable_destroy (RetroCoreRetroVariable* self);
RetroCore* retro_core_new (const gchar* so_path, const gchar* game_rom_path, RetroCoreRetroVariable* game_env_vars, int game_env_vars_length1, RetroCoreRetroVideoRefreshT video_refresh_cb, RetroCoreRetroAudioSampleBatchT audio_sample_batch_cb, RetroCoreRetroInputPollT input_poll_cb, RetroCoreRetroInputStateT input_state_cb, GError** error);
RetroCore* retro_core_construct (GType object_type, const gchar* so_path, const gchar* game_rom_path, RetroCoreRetroVariable* game_env_vars, int game_env_vars_length1, RetroCoreRetroVideoRefreshT video_refresh_cb, RetroCoreRetroAudioSampleBatchT audio_sample_batch_cb, RetroCoreRetroInputPollT input_poll_cb, RetroCoreRetroInputStateT input_state_cb, GError** error);
static void* retro_core_load_symbol (RetroCore* self, const gchar* name, GError** error);
static RetroCoreRetroVariable* _vala_array_dup3 (RetroCoreRetroVariable* self, int length);
static void _vala_RetroCoreRetroVariable_array_free (RetroCoreRetroVariable* array, gint array_length);
static gboolean retro_core_environment_cb (guint cmd, void* data);
static gboolean _retro_core_environment_cb_retro_core_retro_environment_t (guint cmd, void* data);
static void retro_core_load_game (RetroCore* self, const gchar* game_rom_path, RetroCoreRetroGameInfo* game);
static guint8* _vala_array_dup4 (guint8* self, int length);
static guint8* _vala_array_dup5 (guint8* self, int length);
static void retro_core_finalize (GObject* obj);


GQuark plugin_error_quark (void) {
	return g_quark_from_static_string ("plugin_error-quark");
}


GType retro_core_retro_pixel_format_get_type (void) {
	static volatile gsize retro_core_retro_pixel_format_type_id__volatile = 0;
	if (g_once_init_enter (&retro_core_retro_pixel_format_type_id__volatile)) {
		static const GEnumValue values[] = {{RETRO_CORE_RETRO_PIXEL_FORMAT__0RGB1555, "RETRO_CORE_RETRO_PIXEL_FORMAT__0RGB1555", "-0rgb1555"}, {RETRO_CORE_RETRO_PIXEL_FORMAT_XRGB8888, "RETRO_CORE_RETRO_PIXEL_FORMAT_XRGB8888", "xrgb8888"}, {RETRO_CORE_RETRO_PIXEL_FORMAT_RGB565, "RETRO_CORE_RETRO_PIXEL_FORMAT_RGB565", "rgb565"}, {0, NULL, NULL}};
		GType retro_core_retro_pixel_format_type_id;
		retro_core_retro_pixel_format_type_id = g_enum_register_static ("RetroCoreRetroPixelFormat", values);
		g_once_init_leave (&retro_core_retro_pixel_format_type_id__volatile, retro_core_retro_pixel_format_type_id);
	}
	return retro_core_retro_pixel_format_type_id__volatile;
}


GType retro_core_retro_environment_set_get_type (void) {
	static volatile gsize retro_core_retro_environment_set_type_id__volatile = 0;
	if (g_once_init_enter (&retro_core_retro_environment_set_type_id__volatile)) {
		static const GEnumValue values[] = {{RETRO_CORE_RETRO_ENVIRONMENT_SET_PIXEL_FORMAT, "RETRO_CORE_RETRO_ENVIRONMENT_SET_PIXEL_FORMAT", "pixel-format"}, {0, NULL, NULL}};
		GType retro_core_retro_environment_set_type_id;
		retro_core_retro_environment_set_type_id = g_enum_register_static ("RetroCoreRetroEnvironmentSet", values);
		g_once_init_leave (&retro_core_retro_environment_set_type_id__volatile, retro_core_retro_environment_set_type_id);
	}
	return retro_core_retro_environment_set_type_id__volatile;
}


GType retro_core_retro_environment_get_get_type (void) {
	static volatile gsize retro_core_retro_environment_get_type_id__volatile = 0;
	if (g_once_init_enter (&retro_core_retro_environment_get_type_id__volatile)) {
		static const GEnumValue values[] = {{RETRO_CORE_RETRO_ENVIRONMENT_GET_VARIABLE, "RETRO_CORE_RETRO_ENVIRONMENT_GET_VARIABLE", "variable"}, {RETRO_CORE_RETRO_ENVIRONMENT_GET_SYSTEM_DIRECTORY, "RETRO_CORE_RETRO_ENVIRONMENT_GET_SYSTEM_DIRECTORY", "system-directory"}, {RETRO_CORE_RETRO_ENVIRONMENT_GET_SAVE_DIRECTORY, "RETRO_CORE_RETRO_ENVIRONMENT_GET_SAVE_DIRECTORY", "save-directory"}, {RETRO_CORE_RETRO_ENVIRONMENT_GET_CAN_DUPE, "RETRO_CORE_RETRO_ENVIRONMENT_GET_CAN_DUPE", "can-dupe"}, {0, NULL, NULL}};
		GType retro_core_retro_environment_get_type_id;
		retro_core_retro_environment_get_type_id = g_enum_register_static ("RetroCoreRetroEnvironmentGet", values);
		g_once_init_leave (&retro_core_retro_environment_get_type_id__volatile, retro_core_retro_environment_get_type_id);
	}
	return retro_core_retro_environment_get_type_id__volatile;
}


static RetroCoreRetroVariable* _vala_array_dup3 (RetroCoreRetroVariable* self, int length) {
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


static void _vala_RetroCoreRetroVariable_array_free (RetroCoreRetroVariable* array, gint array_length) {
	if (array != NULL) {
		int i;
		for (i = 0; i < array_length; i = i + 1) {
			retro_core_retro_variable_destroy (&array[i]);
		}
	}
	g_free (array);
}


static gboolean _retro_core_environment_cb_retro_core_retro_environment_t (guint cmd, void* data) {
	gboolean result;
	result = retro_core_environment_cb (cmd, data);
	return result;
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


RetroCore* retro_core_construct (GType object_type, const gchar* so_path, const gchar* game_rom_path, RetroCoreRetroVariable* game_env_vars, int game_env_vars_length1, RetroCoreRetroVideoRefreshT video_refresh_cb, RetroCoreRetroAudioSampleBatchT audio_sample_batch_cb, RetroCoreRetroInputPollT input_poll_cb, RetroCoreRetroInputStateT input_state_cb, GError** error) {
	RetroCore * self = NULL;
	const gchar* _tmp0_ = NULL;
	GModule* _tmp1_ = NULL;
	GModule* _tmp2_ = NULL;
	void* _tmp6_ = NULL;
	void* _tmp7_ = NULL;
	void* _tmp8_ = NULL;
	void* _tmp9_ = NULL;
	void* _tmp10_ = NULL;
	void* _tmp11_ = NULL;
	void* _tmp12_ = NULL;
	void* _tmp13_ = NULL;
	void* _tmp14_ = NULL;
	void* _tmp15_ = NULL;
	void* _tmp16_ = NULL;
	void* _tmp17_ = NULL;
	void* _tmp18_ = NULL;
	void* _tmp19_ = NULL;
	void* _tmp20_ = NULL;
	void* _tmp21_ = NULL;
	RetroCoreRetroSetEnvironment retro_set_environment = NULL;
	void* _tmp22_ = NULL;
	void* _tmp23_ = NULL;
	RetroCoreRetroSetVideoRefresh retro_set_video_refresh = NULL;
	void* _tmp24_ = NULL;
	void* _tmp25_ = NULL;
	RetroCoreRetroSetAudioSampleBatch retro_set_audio_sample_batch = NULL;
	void* _tmp26_ = NULL;
	void* _tmp27_ = NULL;
	RetroCoreRetroSetInputPoll retro_set_input_poll = NULL;
	void* _tmp28_ = NULL;
	void* _tmp29_ = NULL;
	RetroCoreRetroSetInputState retro_set_input_state = NULL;
	void* _tmp30_ = NULL;
	void* _tmp31_ = NULL;
	void* _tmp32_ = NULL;
	void* _tmp33_ = NULL;
	void* _tmp34_ = NULL;
	void* _tmp35_ = NULL;
	void* _tmp36_ = NULL;
	void* _tmp37_ = NULL;
	void* _tmp38_ = NULL;
	void* _tmp39_ = NULL;
	void* _tmp40_ = NULL;
	void* _tmp41_ = NULL;
	RetroCoreRetroVariable* _tmp42_ = NULL;
	gint _tmp42__length1 = 0;
	RetroCoreRetroVariable* _tmp43_ = NULL;
	gint _tmp43__length1 = 0;
	RetroCoreRetroSetEnvironment _tmp44_ = NULL;
	RetroCoreRetroSetVideoRefresh _tmp45_ = NULL;
	RetroCoreRetroVideoRefreshT _tmp46_ = NULL;
	RetroCoreRetroSetAudioSampleBatch _tmp47_ = NULL;
	RetroCoreRetroAudioSampleBatchT _tmp48_ = NULL;
	RetroCoreRetroSetInputPoll _tmp49_ = NULL;
	RetroCoreRetroInputPollT _tmp50_ = NULL;
	RetroCoreRetroSetInputState _tmp51_ = NULL;
	RetroCoreRetroInputStateT _tmp52_ = NULL;
	RetroCoreRetroInit _tmp53_ = NULL;
	RetroCoreRetroGameInfo game_info = {0};
	RetroCoreRetroGameInfo _tmp54_ = {0};
	const gchar* _tmp55_ = NULL;
	RetroCoreRetroLoadGame _tmp56_ = NULL;
	gboolean _tmp57_ = FALSE;
	RetroCoreRetroGameInfo _tmp59_ = {0};
	guint8* _tmp60_ = NULL;
	gint _tmp60__length1 = 0;
	gchar* _tmp61_ = NULL;
	FILE* _tmp62_ = NULL;
	const gchar* _tmp63_ = NULL;
	gchar* _tmp64_ = NULL;
	gchar* _tmp65_ = NULL;
	GError * _inner_error_ = NULL;
	g_return_val_if_fail (so_path != NULL, NULL);
	g_return_val_if_fail (game_rom_path != NULL, NULL);
	self = (RetroCore*) g_object_new (object_type, NULL);
	_tmp0_ = so_path;
	_tmp1_ = g_module_open (_tmp0_, G_MODULE_BIND_LAZY);
	_g_module_close0 (self->priv->module);
	self->priv->module = _tmp1_;
	_tmp2_ = self->priv->module;
	if (_tmp2_ == NULL) {
		const gchar* _tmp3_ = NULL;
		const gchar* _tmp4_ = NULL;
		GError* _tmp5_ = NULL;
		_tmp3_ = so_path;
		_tmp4_ = g_module_error ();
		_tmp5_ = g_error_new (PLUGIN_ERROR, PLUGIN_ERROR_SYMBOL_NOT_FOUND, "Failed to open %s: %s", _tmp3_, _tmp4_);
		_inner_error_ = _tmp5_;
		if (_inner_error_->domain == PLUGIN_ERROR) {
			g_propagate_error (error, _inner_error_);
			_g_object_unref0 (self);
			return NULL;
		} else {
			g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
			g_clear_error (&_inner_error_);
			return NULL;
		}
	}
	_tmp7_ = retro_core_load_symbol (self, "retro_init", &_inner_error_);
	_tmp6_ = _tmp7_;
	if (G_UNLIKELY (_inner_error_ != NULL)) {
		if (_inner_error_->domain == PLUGIN_ERROR) {
			g_propagate_error (error, _inner_error_);
			_g_object_unref0 (self);
			return NULL;
		} else {
			g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
			g_clear_error (&_inner_error_);
			return NULL;
		}
	}
	self->retro_init = (RetroCoreRetroInit) _tmp6_;
	_tmp9_ = retro_core_load_symbol (self, "retro_deinit", &_inner_error_);
	_tmp8_ = _tmp9_;
	if (G_UNLIKELY (_inner_error_ != NULL)) {
		if (_inner_error_->domain == PLUGIN_ERROR) {
			g_propagate_error (error, _inner_error_);
			_g_object_unref0 (self);
			return NULL;
		} else {
			g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
			g_clear_error (&_inner_error_);
			return NULL;
		}
	}
	self->retro_deinit = (RetroCoreRetroDeinit) _tmp8_;
	_tmp11_ = retro_core_load_symbol (self, "retro_api_version", &_inner_error_);
	_tmp10_ = _tmp11_;
	if (G_UNLIKELY (_inner_error_ != NULL)) {
		if (_inner_error_->domain == PLUGIN_ERROR) {
			g_propagate_error (error, _inner_error_);
			_g_object_unref0 (self);
			return NULL;
		} else {
			g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
			g_clear_error (&_inner_error_);
			return NULL;
		}
	}
	self->retro_api_version = (RetroCoreRetroApiVersion) _tmp10_;
	_tmp13_ = retro_core_load_symbol (self, "retro_load_game", &_inner_error_);
	_tmp12_ = _tmp13_;
	if (G_UNLIKELY (_inner_error_ != NULL)) {
		if (_inner_error_->domain == PLUGIN_ERROR) {
			g_propagate_error (error, _inner_error_);
			_g_object_unref0 (self);
			return NULL;
		} else {
			g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
			g_clear_error (&_inner_error_);
			return NULL;
		}
	}
	self->retro_load_game = (RetroCoreRetroLoadGame) _tmp12_;
	_tmp15_ = retro_core_load_symbol (self, "retro_unload_game", &_inner_error_);
	_tmp14_ = _tmp15_;
	if (G_UNLIKELY (_inner_error_ != NULL)) {
		if (_inner_error_->domain == PLUGIN_ERROR) {
			g_propagate_error (error, _inner_error_);
			_g_object_unref0 (self);
			return NULL;
		} else {
			g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
			g_clear_error (&_inner_error_);
			return NULL;
		}
	}
	self->retro_unload_game = (RetroCoreRetroUnloadGame) _tmp14_;
	_tmp17_ = retro_core_load_symbol (self, "retro_run", &_inner_error_);
	_tmp16_ = _tmp17_;
	if (G_UNLIKELY (_inner_error_ != NULL)) {
		if (_inner_error_->domain == PLUGIN_ERROR) {
			g_propagate_error (error, _inner_error_);
			_g_object_unref0 (self);
			return NULL;
		} else {
			g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
			g_clear_error (&_inner_error_);
			return NULL;
		}
	}
	self->retro_run = (RetroCoreRetroRun) _tmp16_;
	_tmp19_ = retro_core_load_symbol (self, "retro_reset", &_inner_error_);
	_tmp18_ = _tmp19_;
	if (G_UNLIKELY (_inner_error_ != NULL)) {
		if (_inner_error_->domain == PLUGIN_ERROR) {
			g_propagate_error (error, _inner_error_);
			_g_object_unref0 (self);
			return NULL;
		} else {
			g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
			g_clear_error (&_inner_error_);
			return NULL;
		}
	}
	self->retro_reset = (RetroCoreRetroReset) _tmp18_;
	_tmp21_ = retro_core_load_symbol (self, "retro_set_environment", &_inner_error_);
	_tmp20_ = _tmp21_;
	if (G_UNLIKELY (_inner_error_ != NULL)) {
		if (_inner_error_->domain == PLUGIN_ERROR) {
			g_propagate_error (error, _inner_error_);
			_g_object_unref0 (self);
			return NULL;
		} else {
			g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
			g_clear_error (&_inner_error_);
			return NULL;
		}
	}
	retro_set_environment = (RetroCoreRetroSetEnvironment) _tmp20_;
	_tmp23_ = retro_core_load_symbol (self, "retro_set_video_refresh", &_inner_error_);
	_tmp22_ = _tmp23_;
	if (G_UNLIKELY (_inner_error_ != NULL)) {
		if (_inner_error_->domain == PLUGIN_ERROR) {
			g_propagate_error (error, _inner_error_);
			_g_object_unref0 (self);
			return NULL;
		} else {
			g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
			g_clear_error (&_inner_error_);
			return NULL;
		}
	}
	retro_set_video_refresh = (RetroCoreRetroSetVideoRefresh) _tmp22_;
	_tmp25_ = retro_core_load_symbol (self, "retro_set_audio_sample_batch", &_inner_error_);
	_tmp24_ = _tmp25_;
	if (G_UNLIKELY (_inner_error_ != NULL)) {
		if (_inner_error_->domain == PLUGIN_ERROR) {
			g_propagate_error (error, _inner_error_);
			_g_object_unref0 (self);
			return NULL;
		} else {
			g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
			g_clear_error (&_inner_error_);
			return NULL;
		}
	}
	retro_set_audio_sample_batch = (RetroCoreRetroSetAudioSampleBatch) _tmp24_;
	_tmp27_ = retro_core_load_symbol (self, "retro_set_input_poll", &_inner_error_);
	_tmp26_ = _tmp27_;
	if (G_UNLIKELY (_inner_error_ != NULL)) {
		if (_inner_error_->domain == PLUGIN_ERROR) {
			g_propagate_error (error, _inner_error_);
			_g_object_unref0 (self);
			return NULL;
		} else {
			g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
			g_clear_error (&_inner_error_);
			return NULL;
		}
	}
	retro_set_input_poll = (RetroCoreRetroSetInputPoll) _tmp26_;
	_tmp29_ = retro_core_load_symbol (self, "retro_set_input_state", &_inner_error_);
	_tmp28_ = _tmp29_;
	if (G_UNLIKELY (_inner_error_ != NULL)) {
		if (_inner_error_->domain == PLUGIN_ERROR) {
			g_propagate_error (error, _inner_error_);
			_g_object_unref0 (self);
			return NULL;
		} else {
			g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
			g_clear_error (&_inner_error_);
			return NULL;
		}
	}
	retro_set_input_state = (RetroCoreRetroSetInputState) _tmp28_;
	_tmp31_ = retro_core_load_symbol (self, "retro_get_system_av_info", &_inner_error_);
	_tmp30_ = _tmp31_;
	if (G_UNLIKELY (_inner_error_ != NULL)) {
		if (_inner_error_->domain == PLUGIN_ERROR) {
			g_propagate_error (error, _inner_error_);
			_g_object_unref0 (self);
			return NULL;
		} else {
			g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
			g_clear_error (&_inner_error_);
			return NULL;
		}
	}
	self->retro_get_system_av_info = (RetroCoreRetroGetSystemAvInfo) _tmp30_;
	_tmp33_ = retro_core_load_symbol (self, "retro_get_memory_data", &_inner_error_);
	_tmp32_ = _tmp33_;
	if (G_UNLIKELY (_inner_error_ != NULL)) {
		if (_inner_error_->domain == PLUGIN_ERROR) {
			g_propagate_error (error, _inner_error_);
			_g_object_unref0 (self);
			return NULL;
		} else {
			g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
			g_clear_error (&_inner_error_);
			return NULL;
		}
	}
	self->retro_get_memory_data = (RetroCoreRetroGetMemoryData) _tmp32_;
	_tmp35_ = retro_core_load_symbol (self, "retro_get_memory_size", &_inner_error_);
	_tmp34_ = _tmp35_;
	if (G_UNLIKELY (_inner_error_ != NULL)) {
		if (_inner_error_->domain == PLUGIN_ERROR) {
			g_propagate_error (error, _inner_error_);
			_g_object_unref0 (self);
			return NULL;
		} else {
			g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
			g_clear_error (&_inner_error_);
			return NULL;
		}
	}
	self->retro_get_memory_size = (RetroCoreRetroGetMemorySize) _tmp34_;
	_tmp37_ = retro_core_load_symbol (self, "retro_serialize_size", &_inner_error_);
	_tmp36_ = _tmp37_;
	if (G_UNLIKELY (_inner_error_ != NULL)) {
		if (_inner_error_->domain == PLUGIN_ERROR) {
			g_propagate_error (error, _inner_error_);
			_g_object_unref0 (self);
			return NULL;
		} else {
			g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
			g_clear_error (&_inner_error_);
			return NULL;
		}
	}
	self->retro_serialize_size = (RetroCoreRetroSerializeSize) _tmp36_;
	_tmp39_ = retro_core_load_symbol (self, "retro_serialize", &_inner_error_);
	_tmp38_ = _tmp39_;
	if (G_UNLIKELY (_inner_error_ != NULL)) {
		if (_inner_error_->domain == PLUGIN_ERROR) {
			g_propagate_error (error, _inner_error_);
			_g_object_unref0 (self);
			return NULL;
		} else {
			g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
			g_clear_error (&_inner_error_);
			return NULL;
		}
	}
	self->retro_serialize = (RetroCoreRetroSerialize) _tmp38_;
	_tmp41_ = retro_core_load_symbol (self, "retro_unserialize", &_inner_error_);
	_tmp40_ = _tmp41_;
	if (G_UNLIKELY (_inner_error_ != NULL)) {
		if (_inner_error_->domain == PLUGIN_ERROR) {
			g_propagate_error (error, _inner_error_);
			_g_object_unref0 (self);
			return NULL;
		} else {
			g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
			g_clear_error (&_inner_error_);
			return NULL;
		}
	}
	self->retro_unserialize = (RetroCoreRetroUnserialize) _tmp40_;
	_tmp42_ = game_env_vars;
	_tmp42__length1 = game_env_vars_length1;
	_tmp43_ = (_tmp42_ != NULL) ? _vala_array_dup3 (_tmp42_, _tmp42__length1) : ((gpointer) _tmp42_);
	_tmp43__length1 = _tmp42__length1;
	retro_core_environment_vars = (_vala_RetroCoreRetroVariable_array_free (retro_core_environment_vars, retro_core_environment_vars_length1), NULL);
	retro_core_environment_vars = _tmp43_;
	retro_core_environment_vars_length1 = _tmp43__length1;
	_retro_core_environment_vars_size_ = retro_core_environment_vars_length1;
	_tmp44_ = retro_set_environment;
	_tmp44_ (_retro_core_environment_cb_retro_core_retro_environment_t);
	_tmp45_ = retro_set_video_refresh;
	_tmp46_ = video_refresh_cb;
	_tmp45_ (_tmp46_);
	_tmp47_ = retro_set_audio_sample_batch;
	_tmp48_ = audio_sample_batch_cb;
	_tmp47_ (_tmp48_);
	_tmp49_ = retro_set_input_poll;
	_tmp50_ = input_poll_cb;
	_tmp49_ (_tmp50_);
	_tmp51_ = retro_set_input_state;
	_tmp52_ = input_state_cb;
	_tmp51_ (_tmp52_);
	_tmp53_ = self->retro_init;
	_tmp53_ ();
	game_info = _tmp54_;
	_tmp55_ = game_rom_path;
	retro_core_load_game (self, _tmp55_, &game_info);
	_tmp56_ = self->retro_load_game;
	_tmp57_ = _tmp56_ (&game_info);
	if (!_tmp57_) {
		FILE* _tmp58_ = NULL;
		_tmp58_ = stderr;
		fprintf (_tmp58_, "Failed to load game\n");
		retro_core_retro_game_info_destroy (&game_info);
		return self;
	}
	_tmp59_ = game_info;
	_tmp60_ = _tmp59_.data;
	_tmp60__length1 = _tmp59_.data_length1;
	_tmp61_ = g_compute_checksum_for_data (G_CHECKSUM_MD5, _tmp60_, _tmp60__length1);
	_g_free0 (self->game_checksum);
	self->game_checksum = _tmp61_;
	_tmp62_ = stdout;
	_tmp63_ = self->game_checksum;
	_tmp64_ = string_substring (_tmp63_, (glong) 0, (glong) 10);
	_tmp65_ = _tmp64_;
	fprintf (_tmp62_, "Checksum %s\n", _tmp65_);
	_g_free0 (_tmp65_);
	self->loaded = TRUE;
	retro_core_retro_game_info_destroy (&game_info);
	return self;
}


RetroCore* retro_core_new (const gchar* so_path, const gchar* game_rom_path, RetroCoreRetroVariable* game_env_vars, int game_env_vars_length1, RetroCoreRetroVideoRefreshT video_refresh_cb, RetroCoreRetroAudioSampleBatchT audio_sample_batch_cb, RetroCoreRetroInputPollT input_poll_cb, RetroCoreRetroInputStateT input_state_cb, GError** error) {
	return retro_core_construct (TYPE_RETRO_CORE, so_path, game_rom_path, game_env_vars, game_env_vars_length1, video_refresh_cb, audio_sample_batch_cb, input_poll_cb, input_state_cb, error);
}


static void* retro_core_load_symbol (RetroCore* self, const gchar* name, GError** error) {
	void* result = NULL;
	void* sym = NULL;
	gboolean _tmp0_ = FALSE;
	GModule* _tmp1_ = NULL;
	const gchar* _tmp2_ = NULL;
	void* _tmp3_ = NULL;
	gboolean _tmp4_ = FALSE;
	void* _tmp8_ = NULL;
	GError * _inner_error_ = NULL;
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (name != NULL, NULL);
	sym = NULL;
	_tmp1_ = self->priv->module;
	_tmp2_ = name;
	_tmp4_ = g_module_symbol (_tmp1_, _tmp2_, &_tmp3_);
	sym = _tmp3_;
	if (!_tmp4_) {
		_tmp0_ = TRUE;
	} else {
		void* _tmp5_ = NULL;
		_tmp5_ = sym;
		_tmp0_ = _tmp5_ == NULL;
	}
	if (_tmp0_) {
		const gchar* _tmp6_ = NULL;
		GError* _tmp7_ = NULL;
		_tmp6_ = name;
		_tmp7_ = g_error_new (PLUGIN_ERROR, PLUGIN_ERROR_SYMBOL_NOT_FOUND, "Symbol %s not found", _tmp6_);
		_inner_error_ = _tmp7_;
		if (_inner_error_->domain == PLUGIN_ERROR) {
			g_propagate_error (error, _inner_error_);
			return NULL;
		} else {
			g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
			g_clear_error (&_inner_error_);
			return NULL;
		}
	}
	_tmp8_ = sym;
	result = _tmp8_;
	return result;
}


static guint8* _vala_array_dup4 (guint8* self, int length) {
	return g_memdup (self, length * sizeof (guint8));
}


static void retro_core_load_game (RetroCore* self, const gchar* game_rom_path, RetroCoreRetroGameInfo* game) {
	guint8* contents = NULL;
	gint contents_length1 = 0;
	gint _contents_size_ = 0;
	gchar* checksum = NULL;
	guint8* _tmp8_ = NULL;
	gint _tmp8__length1 = 0;
	gchar* _tmp9_ = NULL;
	FILE* _tmp10_ = NULL;
	const gchar* _tmp11_ = NULL;
	guint8* _tmp12_ = NULL;
	gint _tmp12__length1 = 0;
	guint8* _tmp13_ = NULL;
	gint _tmp13__length1 = 0;
	guint8* _tmp14_ = NULL;
	gint _tmp14__length1 = 0;
	GError * _inner_error_ = NULL;
	g_return_if_fail (self != NULL);
	g_return_if_fail (game_rom_path != NULL);
	g_return_if_fail (game != NULL);
	{
		GFile* file = NULL;
		const gchar* _tmp0_ = NULL;
		GFile* _tmp1_ = NULL;
		GFile* _tmp2_ = NULL;
		guint8* _tmp3_ = NULL;
		gsize _tmp4_;
		_tmp0_ = game_rom_path;
		_tmp1_ = g_file_new_for_path (_tmp0_);
		file = _tmp1_;
		_tmp2_ = file;
		g_file_load_contents (_tmp2_, NULL, &_tmp3_, &_tmp4_, NULL, &_inner_error_);
		contents = (g_free (contents), NULL);
		contents = _tmp3_;
		contents_length1 = _tmp4_;
		_contents_size_ = contents_length1;
		if (G_UNLIKELY (_inner_error_ != NULL)) {
			_g_object_unref0 (file);
			goto __catch22_g_error;
		}
		_g_object_unref0 (file);
	}
	goto __finally22;
	__catch22_g_error:
	{
		GError* e = NULL;
		FILE* _tmp5_ = NULL;
		GError* _tmp6_ = NULL;
		const gchar* _tmp7_ = NULL;
		e = _inner_error_;
		_inner_error_ = NULL;
		_tmp5_ = stderr;
		_tmp6_ = e;
		_tmp7_ = _tmp6_->message;
		fprintf (_tmp5_, "Failed to open game file: %s\n", _tmp7_);
		_g_error_free0 (e);
		contents = (g_free (contents), NULL);
		return;
	}
	__finally22:
	if (G_UNLIKELY (_inner_error_ != NULL)) {
		contents = (g_free (contents), NULL);
		g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
		g_clear_error (&_inner_error_);
		return;
	}
	_tmp8_ = contents;
	_tmp8__length1 = contents_length1;
	_tmp9_ = g_compute_checksum_for_data (G_CHECKSUM_MD5, _tmp8_, _tmp8__length1);
	checksum = _tmp9_;
	_tmp10_ = stdout;
	_tmp11_ = checksum;
	fprintf (_tmp10_, "B Checksum %s\n", _tmp11_);
	_tmp12_ = contents;
	_tmp12__length1 = contents_length1;
	_tmp13_ = (_tmp12_ != NULL) ? _vala_array_dup4 (_tmp12_, _tmp12__length1) : ((gpointer) _tmp12_);
	_tmp13__length1 = _tmp12__length1;
	(*game).data = (g_free ((*game).data), NULL);
	(*game).data = _tmp13_;
	(*game).data_length1 = _tmp13__length1;
	_tmp14_ = contents;
	_tmp14__length1 = contents_length1;
	(*game).size = (gsize) _tmp14__length1;
	_g_free0 (checksum);
	contents = (g_free (contents), NULL);
}


static gboolean retro_core_environment_cb (guint cmd, void* data) {
	gboolean result = FALSE;
	guint _tmp0_ = 0U;
	_tmp0_ = cmd;
	switch (_tmp0_) {
		case RETRO_CORE_RETRO_ENVIRONMENT_GET_VARIABLE:
		{
			{
				RetroCoreRetroVariable* retrovar = NULL;
				void* _tmp1_ = NULL;
				RetroCoreRetroVariable* _tmp2_ = NULL;
				gint _tmp2__length1 = 0;
				FILE* _tmp16_ = NULL;
				RetroCoreRetroVariable* _tmp17_ = NULL;
				const gchar* _tmp18_ = NULL;
				_tmp1_ = data;
				retrovar = (RetroCoreRetroVariable*) _tmp1_;
				_tmp2_ = retro_core_environment_vars;
				_tmp2__length1 = retro_core_environment_vars_length1;
				{
					RetroCoreRetroVariable* game_env_var_collection = NULL;
					gint game_env_var_collection_length1 = 0;
					gint _game_env_var_collection_size_ = 0;
					gint game_env_var_it = 0;
					game_env_var_collection = _tmp2_;
					game_env_var_collection_length1 = _tmp2__length1;
					for (game_env_var_it = 0; game_env_var_it < _tmp2__length1; game_env_var_it = game_env_var_it + 1) {
						RetroCoreRetroVariable _tmp3_ = {0};
						RetroCoreRetroVariable game_env_var = {0};
						retro_core_retro_variable_copy (&game_env_var_collection[game_env_var_it], &_tmp3_);
						game_env_var = _tmp3_;
						{
							RetroCoreRetroVariable* _tmp4_ = NULL;
							const gchar* _tmp5_ = NULL;
							RetroCoreRetroVariable _tmp6_ = {0};
							const gchar* _tmp7_ = NULL;
							RetroCoreRetroVariable _tmp8_ = {0};
							const gchar* _tmp9_ = NULL;
							gchar* _tmp10_ = NULL;
							FILE* _tmp11_ = NULL;
							RetroCoreRetroVariable* _tmp12_ = NULL;
							const gchar* _tmp13_ = NULL;
							RetroCoreRetroVariable _tmp14_ = {0};
							const gchar* _tmp15_ = NULL;
							_tmp4_ = retrovar;
							_tmp5_ = (*_tmp4_).key;
							_tmp6_ = game_env_var;
							_tmp7_ = _tmp6_.key;
							if (g_strcmp0 (_tmp5_, _tmp7_) != 0) {
								retro_core_retro_variable_destroy (&game_env_var);
								continue;
							}
							_tmp8_ = game_env_var;
							_tmp9_ = _tmp8_.value;
							_tmp10_ = g_strdup (_tmp9_);
							_g_free0 ((*retrovar).value);
							(*retrovar).value = _tmp10_;
							_tmp11_ = stdout;
							_tmp12_ = retrovar;
							_tmp13_ = (*_tmp12_).key;
							_tmp14_ = game_env_var;
							_tmp15_ = _tmp14_.value;
							fprintf (_tmp11_, "RetroEnvironmentGet.VARIABLE SET: '%s' TO '%s'\n", _tmp13_, _tmp15_);
							result = TRUE;
							retro_core_retro_variable_destroy (&game_env_var);
							return result;
						}
					}
				}
				_tmp16_ = stdout;
				_tmp17_ = retrovar;
				_tmp18_ = (*_tmp17_).key;
				fprintf (_tmp16_, "RetroEnvironmentGet.VARIABLE IGNORED: '%s'\n", _tmp18_);
				_g_free0 ((*retrovar).value);
				(*retrovar).value = NULL;
				result = FALSE;
				return result;
			}
		}
		case RETRO_CORE_RETRO_ENVIRONMENT_SET_PIXEL_FORMAT:
		{
			{
				RetroCoreRetroPixelFormat* fmt = NULL;
				void* _tmp19_ = NULL;
				RetroCoreRetroPixelFormat* _tmp20_ = NULL;
				_tmp19_ = data;
				fmt = (RetroCoreRetroPixelFormat*) _tmp19_;
				_tmp20_ = fmt;
				if ((*_tmp20_) == RETRO_CORE_RETRO_PIXEL_FORMAT_RGB565) {
					FILE* _tmp21_ = NULL;
					_tmp21_ = stdout;
					fprintf (_tmp21_, "RetroPixelFormat: RGB565\n");
					result = TRUE;
					return result;
				}
				result = FALSE;
				return result;
			}
		}
		case RETRO_CORE_RETRO_ENVIRONMENT_GET_SYSTEM_DIRECTORY:
		{
			{
				const gchar** dir = NULL;
				void* _tmp22_ = NULL;
				const gchar** _tmp23_ = NULL;
				const gchar* _tmp24_ = NULL;
				_tmp22_ = data;
				dir = (const gchar**) _tmp22_;
				_tmp23_ = dir;
				*_tmp23_ = "./.gambatte";
				_tmp24_ = *_tmp23_;
				result = TRUE;
				return result;
			}
		}
		case RETRO_CORE_RETRO_ENVIRONMENT_GET_SAVE_DIRECTORY:
		{
			{
				const gchar** dir = NULL;
				void* _tmp25_ = NULL;
				const gchar** _tmp26_ = NULL;
				const gchar* _tmp27_ = NULL;
				_tmp25_ = data;
				dir = (const gchar**) _tmp25_;
				_tmp26_ = dir;
				*_tmp26_ = "./.gambatte";
				_tmp27_ = *_tmp26_;
				result = TRUE;
				return result;
			}
		}
		case RETRO_CORE_RETRO_ENVIRONMENT_GET_CAN_DUPE:
		{
			{
				gboolean* can_dupe = NULL;
				void* _tmp28_ = NULL;
				gboolean* _tmp29_ = NULL;
				gboolean _tmp30_ = FALSE;
				_tmp28_ = data;
				can_dupe = (gboolean*) _tmp28_;
				_tmp29_ = can_dupe;
				*_tmp29_ = TRUE;
				_tmp30_ = *_tmp29_;
				result = TRUE;
				return result;
			}
		}
		default:
		{
			result = FALSE;
			return result;
		}
	}
}


void retro_core_unload (RetroCore* self) {
	FILE* _tmp0_ = NULL;
	gboolean _tmp1_ = FALSE;
	gboolean _tmp2_ = FALSE;
	RetroCoreRetroUnloadGame _tmp4_ = NULL;
	RetroCoreRetroDeinit _tmp5_ = NULL;
	FILE* _tmp6_ = NULL;
	g_return_if_fail (self != NULL);
	_tmp0_ = stdout;
	fprintf (_tmp0_, "unload\n");
	_tmp2_ = self->loaded;
	if (!_tmp2_) {
		_tmp1_ = TRUE;
	} else {
		GModule* _tmp3_ = NULL;
		_tmp3_ = self->priv->module;
		_tmp1_ = _tmp3_ == NULL;
	}
	if (_tmp1_) {
		return;
	}
	_tmp4_ = self->retro_unload_game;
	_tmp4_ ();
	_tmp5_ = self->retro_deinit;
	_tmp5_ ();
	_g_module_close0 (self->priv->module);
	self->priv->module = NULL;
	self->loaded = FALSE;
	_tmp6_ = stdout;
	fprintf (_tmp6_, "unload end\n");
}


RetroCoreRetroGameGeometry* retro_core_retro_game_geometry_dup (const RetroCoreRetroGameGeometry* self) {
	RetroCoreRetroGameGeometry* dup;
	dup = g_new0 (RetroCoreRetroGameGeometry, 1);
	memcpy (dup, self, sizeof (RetroCoreRetroGameGeometry));
	return dup;
}


void retro_core_retro_game_geometry_free (RetroCoreRetroGameGeometry* self) {
	g_free (self);
}


GType retro_core_retro_game_geometry_get_type (void) {
	static volatile gsize retro_core_retro_game_geometry_type_id__volatile = 0;
	if (g_once_init_enter (&retro_core_retro_game_geometry_type_id__volatile)) {
		GType retro_core_retro_game_geometry_type_id;
		retro_core_retro_game_geometry_type_id = g_boxed_type_register_static ("RetroCoreRetroGameGeometry", (GBoxedCopyFunc) retro_core_retro_game_geometry_dup, (GBoxedFreeFunc) retro_core_retro_game_geometry_free);
		g_once_init_leave (&retro_core_retro_game_geometry_type_id__volatile, retro_core_retro_game_geometry_type_id);
	}
	return retro_core_retro_game_geometry_type_id__volatile;
}


RetroCoreRetroSystemTiming* retro_core_retro_system_timing_dup (const RetroCoreRetroSystemTiming* self) {
	RetroCoreRetroSystemTiming* dup;
	dup = g_new0 (RetroCoreRetroSystemTiming, 1);
	memcpy (dup, self, sizeof (RetroCoreRetroSystemTiming));
	return dup;
}


void retro_core_retro_system_timing_free (RetroCoreRetroSystemTiming* self) {
	g_free (self);
}


GType retro_core_retro_system_timing_get_type (void) {
	static volatile gsize retro_core_retro_system_timing_type_id__volatile = 0;
	if (g_once_init_enter (&retro_core_retro_system_timing_type_id__volatile)) {
		GType retro_core_retro_system_timing_type_id;
		retro_core_retro_system_timing_type_id = g_boxed_type_register_static ("RetroCoreRetroSystemTiming", (GBoxedCopyFunc) retro_core_retro_system_timing_dup, (GBoxedFreeFunc) retro_core_retro_system_timing_free);
		g_once_init_leave (&retro_core_retro_system_timing_type_id__volatile, retro_core_retro_system_timing_type_id);
	}
	return retro_core_retro_system_timing_type_id__volatile;
}


RetroCoreRetroSystemAvInfo* retro_core_retro_system_av_info_dup (const RetroCoreRetroSystemAvInfo* self) {
	RetroCoreRetroSystemAvInfo* dup;
	dup = g_new0 (RetroCoreRetroSystemAvInfo, 1);
	memcpy (dup, self, sizeof (RetroCoreRetroSystemAvInfo));
	return dup;
}


void retro_core_retro_system_av_info_free (RetroCoreRetroSystemAvInfo* self) {
	g_free (self);
}


GType retro_core_retro_system_av_info_get_type (void) {
	static volatile gsize retro_core_retro_system_av_info_type_id__volatile = 0;
	if (g_once_init_enter (&retro_core_retro_system_av_info_type_id__volatile)) {
		GType retro_core_retro_system_av_info_type_id;
		retro_core_retro_system_av_info_type_id = g_boxed_type_register_static ("RetroCoreRetroSystemAvInfo", (GBoxedCopyFunc) retro_core_retro_system_av_info_dup, (GBoxedFreeFunc) retro_core_retro_system_av_info_free);
		g_once_init_leave (&retro_core_retro_system_av_info_type_id__volatile, retro_core_retro_system_av_info_type_id);
	}
	return retro_core_retro_system_av_info_type_id__volatile;
}


static guint8* _vala_array_dup5 (guint8* self, int length) {
	return g_memdup (self, length * sizeof (guint8));
}


void retro_core_retro_game_info_copy (const RetroCoreRetroGameInfo* self, RetroCoreRetroGameInfo* dest) {
	const gchar* _tmp0_ = NULL;
	gchar* _tmp1_ = NULL;
	guint8* _tmp2_ = NULL;
	gint _tmp2__length1 = 0;
	guint8* _tmp3_ = NULL;
	gint _tmp3__length1 = 0;
	gsize _tmp4_ = 0UL;
	const gchar* _tmp5_ = NULL;
	gchar* _tmp6_ = NULL;
	_tmp0_ = (*self).path;
	_tmp1_ = g_strdup (_tmp0_);
	_g_free0 ((*dest).path);
	(*dest).path = _tmp1_;
	_tmp2_ = (*self).data;
	_tmp2__length1 = (*self).data_length1;
	_tmp3_ = (_tmp2_ != NULL) ? _vala_array_dup5 (_tmp2_, _tmp2__length1) : ((gpointer) _tmp2_);
	_tmp3__length1 = _tmp2__length1;
	(*dest).data = (g_free ((*dest).data), NULL);
	(*dest).data = _tmp3_;
	(*dest).data_length1 = _tmp3__length1;
	_tmp4_ = (*self).size;
	(*dest).size = _tmp4_;
	_tmp5_ = (*self).meta;
	_tmp6_ = g_strdup (_tmp5_);
	_g_free0 ((*dest).meta);
	(*dest).meta = _tmp6_;
}


void retro_core_retro_game_info_destroy (RetroCoreRetroGameInfo* self) {
	_g_free0 ((*self).path);
	(*self).data = (g_free ((*self).data), NULL);
	_g_free0 ((*self).meta);
}


RetroCoreRetroGameInfo* retro_core_retro_game_info_dup (const RetroCoreRetroGameInfo* self) {
	RetroCoreRetroGameInfo* dup;
	dup = g_new0 (RetroCoreRetroGameInfo, 1);
	retro_core_retro_game_info_copy (self, dup);
	return dup;
}


void retro_core_retro_game_info_free (RetroCoreRetroGameInfo* self) {
	retro_core_retro_game_info_destroy (self);
	g_free (self);
}


GType retro_core_retro_game_info_get_type (void) {
	static volatile gsize retro_core_retro_game_info_type_id__volatile = 0;
	if (g_once_init_enter (&retro_core_retro_game_info_type_id__volatile)) {
		GType retro_core_retro_game_info_type_id;
		retro_core_retro_game_info_type_id = g_boxed_type_register_static ("RetroCoreRetroGameInfo", (GBoxedCopyFunc) retro_core_retro_game_info_dup, (GBoxedFreeFunc) retro_core_retro_game_info_free);
		g_once_init_leave (&retro_core_retro_game_info_type_id__volatile, retro_core_retro_game_info_type_id);
	}
	return retro_core_retro_game_info_type_id__volatile;
}


void retro_core_retro_variable_copy (const RetroCoreRetroVariable* self, RetroCoreRetroVariable* dest) {
	const gchar* _tmp0_ = NULL;
	gchar* _tmp1_ = NULL;
	const gchar* _tmp2_ = NULL;
	gchar* _tmp3_ = NULL;
	_tmp0_ = (*self).key;
	_tmp1_ = g_strdup (_tmp0_);
	_g_free0 ((*dest).key);
	(*dest).key = _tmp1_;
	_tmp2_ = (*self).value;
	_tmp3_ = g_strdup (_tmp2_);
	_g_free0 ((*dest).value);
	(*dest).value = _tmp3_;
}


void retro_core_retro_variable_destroy (RetroCoreRetroVariable* self) {
	_g_free0 ((*self).key);
	_g_free0 ((*self).value);
}


RetroCoreRetroVariable* retro_core_retro_variable_dup (const RetroCoreRetroVariable* self) {
	RetroCoreRetroVariable* dup;
	dup = g_new0 (RetroCoreRetroVariable, 1);
	retro_core_retro_variable_copy (self, dup);
	return dup;
}


void retro_core_retro_variable_free (RetroCoreRetroVariable* self) {
	retro_core_retro_variable_destroy (self);
	g_free (self);
}


GType retro_core_retro_variable_get_type (void) {
	static volatile gsize retro_core_retro_variable_type_id__volatile = 0;
	if (g_once_init_enter (&retro_core_retro_variable_type_id__volatile)) {
		GType retro_core_retro_variable_type_id;
		retro_core_retro_variable_type_id = g_boxed_type_register_static ("RetroCoreRetroVariable", (GBoxedCopyFunc) retro_core_retro_variable_dup, (GBoxedFreeFunc) retro_core_retro_variable_free);
		g_once_init_leave (&retro_core_retro_variable_type_id__volatile, retro_core_retro_variable_type_id);
	}
	return retro_core_retro_variable_type_id__volatile;
}


static void retro_core_class_init (RetroCoreClass * klass) {
	retro_core_parent_class = g_type_class_peek_parent (klass);
	g_type_class_add_private (klass, sizeof (RetroCorePrivate));
	G_OBJECT_CLASS (klass)->finalize = retro_core_finalize;
}


static void retro_core_instance_init (RetroCore * self) {
	self->priv = RETRO_CORE_GET_PRIVATE (self);
	self->priv->module = NULL;
	self->loaded = FALSE;
}


static void retro_core_finalize (GObject* obj) {
	RetroCore * self;
	FILE* _tmp0_ = NULL;
	self = G_TYPE_CHECK_INSTANCE_CAST (obj, TYPE_RETRO_CORE, RetroCore);
	_tmp0_ = stdout;
	fprintf (_tmp0_, "unload RetroCore\n");
	retro_core_unload (self);
	_g_module_close0 (self->priv->module);
	_g_free0 (self->game_checksum);
	G_OBJECT_CLASS (retro_core_parent_class)->finalize (obj);
}


GType retro_core_get_type (void) {
	static volatile gsize retro_core_type_id__volatile = 0;
	if (g_once_init_enter (&retro_core_type_id__volatile)) {
		static const GTypeInfo g_define_type_info = { sizeof (RetroCoreClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) retro_core_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (RetroCore), 0, (GInstanceInitFunc) retro_core_instance_init, NULL };
		GType retro_core_type_id;
		retro_core_type_id = g_type_register_static (G_TYPE_OBJECT, "RetroCore", &g_define_type_info, 0);
		g_once_init_leave (&retro_core_type_id__volatile, retro_core_type_id);
	}
	return retro_core_type_id__volatile;
}



