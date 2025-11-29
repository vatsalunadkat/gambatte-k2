#include <glib.h>
#include <glib-object.h>
#include <xcb/xcb.h>


#define TYPE_GRAY_SHM (gray_shm_get_type ())
#define GRAY_SHM(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_GRAY_SHM, GrayShm))
#define GRAY_SHM_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_GRAY_SHM, GrayShmClass))
#define IS_GRAY_SHM(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_GRAY_SHM))
#define IS_GRAY_SHM_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_GRAY_SHM))
#define GRAY_SHM_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_GRAY_SHM, GrayShmClass))

typedef struct _GrayShm GrayShm;
typedef struct _GrayShmClass GrayShmClass;
typedef struct _GrayShmPrivate GrayShmPrivate;

typedef enum  {
	GRAY_SHM_ERROR_ERROR
} GrayShmError;
#define GRAY_SHM_ERROR gray_shm_error_quark ()
struct _GrayShm {
	GObject parent_instance;
	GrayShmPrivate * priv;
};

struct _GrayShmClass {
	GObjectClass parent_class;
};

struct _GrayShmPrivate {
	void* native_handle;
};


static gpointer gray_shm_parent_class = NULL;

GQuark gray_shm_error_quark (void);
GType gray_shm_get_type (void) G_GNUC_CONST;
#define GRAY_SHM_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), TYPE_GRAY_SHM, GrayShmPrivate))
enum  {
	GRAY_SHM_DUMMY_PROPERTY,
	GRAY_SHM_WIDTH,
	GRAY_SHM_HEIGHT
};
void gray_shm_destroy (void* shm);
GrayShm* gray_shm_oop_new (xcb_window_t xid, gint width, gint height);
GrayShm* gray_shm_oop_construct (GType object_type, xcb_window_t xid, gint width, gint height);
void* gray_shm_create (xcb_window_t xid, gint width, gint height);
void gray_shm_oop_resize (GrayShm* self, gint width, gint height);
void gray_shm_resize (void* shm, gint w, gint h);
void gray_shm_oop_commit_rect (GrayShm* self, gint x, gint y, gint width, gint height);
void gray_shm_commit_rect (void* shm, gint x, gint y, gint w, gint h);
guint8* gray_shm_oop_get_buffer (GrayShm* self);
guint8* gray_shm_get_buffer (void* shm);
gint gray_shm_get_width (void* shm);
gint gray_shm_get_height (void* shm);
gint gray_shm_oop_get_width (GrayShm* self);
gint gray_shm_oop_get_height (GrayShm* self);
static void gray_shm_finalize (GObject* obj);
static void _vala_gray_shm_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec);


GQuark gray_shm_error_quark (void) {
	return g_quark_from_static_string ("gray_shm_error-quark");
}


GrayShm* gray_shm_oop_construct (GType object_type, xcb_window_t xid, gint width, gint height) {
	GrayShm * self = NULL;
	xcb_window_t _tmp0_ = 0;
	gint _tmp1_ = 0;
	gint _tmp2_ = 0;
	void* _tmp3_ = NULL;
	void* _tmp4_ = NULL;
	GError * _inner_error_ = NULL;
	self = (GrayShm*) g_object_new (object_type, NULL);
	_tmp0_ = xid;
	_tmp1_ = width;
	_tmp2_ = height;
	_tmp3_ = gray_shm_create (_tmp0_, _tmp1_, _tmp2_);
	self->priv->native_handle = _tmp3_;
	_tmp4_ = self->priv->native_handle;
	if (_tmp4_ == NULL) {
		GError* _tmp5_ = NULL;
		_tmp5_ = g_error_new_literal (GRAY_SHM_ERROR, GRAY_SHM_ERROR_ERROR, "gray_shm_create failed");
		_inner_error_ = _tmp5_;
		g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
		g_clear_error (&_inner_error_);
		return NULL;
	}
	return self;
}


GrayShm* gray_shm_oop_new (xcb_window_t xid, gint width, gint height) {
	return gray_shm_oop_construct (TYPE_GRAY_SHM, xid, width, height);
}


void gray_shm_oop_resize (GrayShm* self, gint width, gint height) {
	void* _tmp0_ = NULL;
	gint _tmp1_ = 0;
	gint _tmp2_ = 0;
	g_return_if_fail (self != NULL);
	_tmp0_ = self->priv->native_handle;
	_tmp1_ = width;
	_tmp2_ = height;
	gray_shm_resize (_tmp0_, _tmp1_, _tmp2_);
}


void gray_shm_oop_commit_rect (GrayShm* self, gint x, gint y, gint width, gint height) {
	void* _tmp0_ = NULL;
	gint _tmp1_ = 0;
	gint _tmp2_ = 0;
	gint _tmp3_ = 0;
	gint _tmp4_ = 0;
	g_return_if_fail (self != NULL);
	_tmp0_ = self->priv->native_handle;
	_tmp1_ = x;
	_tmp2_ = y;
	_tmp3_ = width;
	_tmp4_ = height;
	gray_shm_commit_rect (_tmp0_, _tmp1_, _tmp2_, _tmp3_, _tmp4_);
}


guint8* gray_shm_oop_get_buffer (GrayShm* self) {
	guint8* result = NULL;
	void* _tmp0_ = NULL;
	guint8* _tmp1_ = NULL;
	g_return_val_if_fail (self != NULL, NULL);
	_tmp0_ = self->priv->native_handle;
	_tmp1_ = gray_shm_get_buffer (_tmp0_);
	result = _tmp1_;
	return result;
}


gint gray_shm_oop_get_width (GrayShm* self) {
	gint result;
	void* _tmp0_ = NULL;
	gint _tmp1_ = 0;
	g_return_val_if_fail (self != NULL, 0);
	_tmp0_ = self->priv->native_handle;
	_tmp1_ = gray_shm_get_width (_tmp0_);
	result = _tmp1_;
	return result;
}


gint gray_shm_oop_get_height (GrayShm* self) {
	gint result;
	void* _tmp0_ = NULL;
	gint _tmp1_ = 0;
	g_return_val_if_fail (self != NULL, 0);
	_tmp0_ = self->priv->native_handle;
	_tmp1_ = gray_shm_get_height (_tmp0_);
	result = _tmp1_;
	return result;
}


static void gray_shm_class_init (GrayShmClass * klass) {
	gray_shm_parent_class = g_type_class_peek_parent (klass);
	g_type_class_add_private (klass, sizeof (GrayShmPrivate));
	G_OBJECT_CLASS (klass)->get_property = _vala_gray_shm_get_property;
	G_OBJECT_CLASS (klass)->finalize = gray_shm_finalize;
	g_object_class_install_property (G_OBJECT_CLASS (klass), GRAY_SHM_WIDTH, g_param_spec_int ("width", "width", "width", G_MININT, G_MAXINT, 0, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE));
	g_object_class_install_property (G_OBJECT_CLASS (klass), GRAY_SHM_HEIGHT, g_param_spec_int ("height", "height", "height", G_MININT, G_MAXINT, 0, G_PARAM_STATIC_NAME | G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB | G_PARAM_READABLE));
}


static void gray_shm_instance_init (GrayShm * self) {
	self->priv = GRAY_SHM_GET_PRIVATE (self);
}


static void gray_shm_finalize (GObject* obj) {
	GrayShm * self;
	void* _tmp0_ = NULL;
	self = G_TYPE_CHECK_INSTANCE_CAST (obj, TYPE_GRAY_SHM, GrayShm);
	_tmp0_ = self->priv->native_handle;
	if (_tmp0_ != NULL) {
		void* _tmp1_ = NULL;
		_tmp1_ = self->priv->native_handle;
		gray_shm_destroy (_tmp1_);
		self->priv->native_handle = NULL;
	}
	G_OBJECT_CLASS (gray_shm_parent_class)->finalize (obj);
}


GType gray_shm_get_type (void) {
	static volatile gsize gray_shm_type_id__volatile = 0;
	if (g_once_init_enter (&gray_shm_type_id__volatile)) {
		static const GTypeInfo g_define_type_info = { sizeof (GrayShmClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) gray_shm_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (GrayShm), 0, (GInstanceInitFunc) gray_shm_instance_init, NULL };
		GType gray_shm_type_id;
		gray_shm_type_id = g_type_register_static (G_TYPE_OBJECT, "GrayShm", &g_define_type_info, 0);
		g_once_init_leave (&gray_shm_type_id__volatile, gray_shm_type_id);
	}
	return gray_shm_type_id__volatile;
}


static void _vala_gray_shm_get_property (GObject * object, guint property_id, GValue * value, GParamSpec * pspec) {
	GrayShm * self;
	self = G_TYPE_CHECK_INSTANCE_CAST (object, TYPE_GRAY_SHM, GrayShm);
	switch (property_id) {
		case GRAY_SHM_WIDTH:
		g_value_set_int (value, gray_shm_oop_get_width (self));
		break;
		case GRAY_SHM_HEIGHT:
		g_value_set_int (value, gray_shm_oop_get_height (self));
		break;
		default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
		break;
	}
}



