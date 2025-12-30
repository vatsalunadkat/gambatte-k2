#include <glib.h>
#include <glib-object.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include <gdk/gdk.h>
#include <float.h>
#include <math.h>
#include <cairo.h>
#include <sched.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/types.h>
#include <poll.h>
#include <linux/input.h>
#include <unistd.h>


#define TYPE_GAME_JOYPAD (game_joypad_get_type ())
#define GAME_JOYPAD(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_GAME_JOYPAD, GameJoypad))
#define GAME_JOYPAD_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_GAME_JOYPAD, GameJoypadClass))
#define IS_GAME_JOYPAD(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_GAME_JOYPAD))
#define IS_GAME_JOYPAD_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_GAME_JOYPAD))
#define GAME_JOYPAD_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_GAME_JOYPAD, GameJoypadClass))

typedef struct _GameJoypad GameJoypad;
typedef struct _GameJoypadClass GameJoypadClass;
typedef struct _GameJoypadPrivate GameJoypadPrivate;

#define GAME_JOYPAD_TYPE_RUN_STATE (game_joypad_run_state_get_type ())

#define GAME_JOYPAD_TYPE_BUTTON (game_joypad_button_get_type ())
typedef struct _GameJoypadButton GameJoypadButton;
#define _g_object_unref0(var) ((var == NULL) ? NULL : (var = (g_object_unref (var), NULL)))
#define _g_free0(var) (var = (g_free (var), NULL))
#define _cairo_destroy0(var) ((var == NULL) ? NULL : (var = (cairo_destroy (var), NULL)))

#define GAME_JOYPAD_TYPE_TOUCH_SLOT (game_joypad_touch_slot_get_type ())
typedef struct _GameJoypadTouchSlot GameJoypadTouchSlot;

struct _GameJoypad {
	GObject parent_instance;
	GameJoypadPrivate * priv;
	GtkDrawingArea* drawing_area;
	gint x;
	gint y;
	gint width;
	gint height;
};

struct _GameJoypadClass {
	GObjectClass parent_class;
};

typedef enum  {
	GAME_JOYPAD_RUN_STATE_STOPPED,
	GAME_JOYPAD_RUN_STATE_PAUSED,
	GAME_JOYPAD_RUN_STATE_RUNNING
} GameJoypadRunState;

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

struct _GameJoypadPrivate {
	GameJoypadRunState state;
	GStaticRecMutex __lock_state;
	GameJoypadButton* buttons;
	gint buttons_length1;
	gint _buttons_size_;
	GThread* thread;
	gchar* touch_device;
	guint queue_draw_event_source_id;
	GStaticRecMutex __lock_queue_draw_event_source_id;
};

struct _GameJoypadTouchSlot {
	gboolean active;
	gint x;
	gint y;
};


static gpointer game_joypad_parent_class = NULL;
static GameJoypad* game_joypad_self;
static GameJoypad* game_joypad_self = NULL;

GType game_joypad_get_type (void) G_GNUC_CONST;
static GType game_joypad_run_state_get_type (void) G_GNUC_CONST G_GNUC_UNUSED;
GType game_joypad_button_get_type (void) G_GNUC_CONST;
GameJoypadButton* game_joypad_button_dup (const GameJoypadButton* self);
void game_joypad_button_free (GameJoypadButton* self);
void game_joypad_button_copy (const GameJoypadButton* self, GameJoypadButton* dest);
void game_joypad_button_destroy (GameJoypadButton* self);
#define GAME_JOYPAD_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), TYPE_GAME_JOYPAD, GameJoypadPrivate))
enum  {
	GAME_JOYPAD_DUMMY_PROPERTY
};
static void _vala_GameJoypadButton_array_free (GameJoypadButton* array, gint array_length);
GameJoypad* game_joypad_new (GtkDrawingArea** da);
GameJoypad* game_joypad_construct (GType object_type, GtkDrawingArea** da);
static gboolean game_joypad_expose_event (GameJoypad* self, GtkWidget* w, GdkEventExpose* ee);
static gboolean _game_joypad_expose_event_gtk_widget_expose_event (GtkWidget* _sender, GdkEventExpose* event, gpointer self);
static void __lambda4_ (GameJoypad* self, GdkRectangle* a);
static void ___lambda4__gtk_widget_size_allocate (GtkWidget* _sender, GdkRectangle* allocation, gpointer self);
static void __lambda5_ (GameJoypad* self, GtkWidget* a);
void game_joypad_pause (GameJoypad* self);
static void ___lambda5__gtk_widget_unmap (GtkWidget* _sender, gpointer self);
static void __lambda6_ (GameJoypad* self, GtkWidget* a);
void game_joypad_resume (GameJoypad* self);
static void ___lambda6__gtk_widget_map (GtkWidget* _sender, gpointer self);
gchar* fb_ink_detect_touch_device (void);
void game_joypad_set_buttons (GameJoypad* self, GameJoypadButton* _buttons, int _buttons_length1);
static GameJoypadButton* _vala_array_dup7 (GameJoypadButton* self, int length);
gint game_joypad_get_button_state (GameJoypad* self, guint id);
void game_joypad_start (GameJoypad* self);
void* game_joypad_thread_fn (void);
static gpointer _game_joypad_thread_fn_gthread_func (gpointer self);
void game_joypad_stop (GameJoypad* self);
static GType game_joypad_touch_slot_get_type (void) G_GNUC_CONST G_GNUC_UNUSED;
static GameJoypadTouchSlot* game_joypad_touch_slot_dup (const GameJoypadTouchSlot* self);
static void game_joypad_touch_slot_free (GameJoypadTouchSlot* self);
static void game_joypad_trigger_queue_draw (GameJoypad* self);
static gboolean _____lambda7_ (GameJoypad* self);
static gboolean ______lambda7__gsource_func (gpointer self);
static void game_joypad_finalize (GObject* obj);


static GType game_joypad_run_state_get_type (void) {
	static volatile gsize game_joypad_run_state_type_id__volatile = 0;
	if (g_once_init_enter (&game_joypad_run_state_type_id__volatile)) {
		static const GEnumValue values[] = {{GAME_JOYPAD_RUN_STATE_STOPPED, "GAME_JOYPAD_RUN_STATE_STOPPED", "stopped"}, {GAME_JOYPAD_RUN_STATE_PAUSED, "GAME_JOYPAD_RUN_STATE_PAUSED", "paused"}, {GAME_JOYPAD_RUN_STATE_RUNNING, "GAME_JOYPAD_RUN_STATE_RUNNING", "running"}, {0, NULL, NULL}};
		GType game_joypad_run_state_type_id;
		game_joypad_run_state_type_id = g_enum_register_static ("GameJoypadRunState", values);
		g_once_init_leave (&game_joypad_run_state_type_id__volatile, game_joypad_run_state_type_id);
	}
	return game_joypad_run_state_type_id__volatile;
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


static gpointer _g_object_ref0 (gpointer self) {
	return self ? g_object_ref (self) : NULL;
}


static gboolean _game_joypad_expose_event_gtk_widget_expose_event (GtkWidget* _sender, GdkEventExpose* event, gpointer self) {
	gboolean result;
	result = game_joypad_expose_event ((GameJoypad*) self, _sender, event);
	return result;
}


static void __lambda4_ (GameJoypad* self, GdkRectangle* a) {
	GtkDrawingArea* _tmp0_ = NULL;
	GdkWindow* _tmp1_ = NULL;
	GdkRectangle _tmp2_ = {0};
	gint _tmp3_ = 0;
	GdkRectangle _tmp4_ = {0};
	gint _tmp5_ = 0;
	gint _x = 0;
	gint _y = 0;
	GtkDrawingArea* _tmp6_ = NULL;
	GdkWindow* _tmp7_ = NULL;
	gint _tmp8_ = 0;
	gint _tmp9_ = 0;
	gint _tmp10_ = 0;
	gint _tmp11_ = 0;
	g_return_if_fail (a != NULL);
	_tmp0_ = self->drawing_area;
	_tmp1_ = ((GtkWidget*) _tmp0_)->window;
	if (_tmp1_ == NULL) {
		return;
	}
	_tmp2_ = *a;
	_tmp3_ = _tmp2_.width;
	g_atomic_int_set ((volatile gint *) (&self->width), _tmp3_);
	_tmp4_ = *a;
	_tmp5_ = _tmp4_.height;
	g_atomic_int_set ((volatile gint *) (&self->height), _tmp5_);
	_tmp6_ = self->drawing_area;
	_tmp7_ = ((GtkWidget*) _tmp6_)->window;
	gdk_window_get_origin (_tmp7_, &_tmp8_, &_tmp9_);
	_x = _tmp8_;
	_y = _tmp9_;
	_tmp10_ = _x;
	g_atomic_int_set ((volatile gint *) (&self->x), _tmp10_);
	_tmp11_ = _y;
	g_atomic_int_set ((volatile gint *) (&self->y), _tmp11_);
}


static void ___lambda4__gtk_widget_size_allocate (GtkWidget* _sender, GdkRectangle* allocation, gpointer self) {
	__lambda4_ ((GameJoypad*) self, allocation);
}


static void __lambda5_ (GameJoypad* self, GtkWidget* a) {
	g_return_if_fail (a != NULL);
	game_joypad_pause (self);
}


static void ___lambda5__gtk_widget_unmap (GtkWidget* _sender, gpointer self) {
	__lambda5_ ((GameJoypad*) self, _sender);
}


static void __lambda6_ (GameJoypad* self, GtkWidget* a) {
	g_return_if_fail (a != NULL);
	game_joypad_resume (self);
}


static void ___lambda6__gtk_widget_map (GtkWidget* _sender, gpointer self) {
	__lambda6_ ((GameJoypad*) self, _sender);
}


GameJoypad* game_joypad_construct (GType object_type, GtkDrawingArea** da) {
	GameJoypad * self = NULL;
	GameJoypad* _tmp0_ = NULL;
	GtkDrawingArea* _tmp1_ = NULL;
	GtkDrawingArea* _tmp2_ = NULL;
	GtkDrawingArea* _tmp3_ = NULL;
	GtkDrawingArea* _tmp4_ = NULL;
	GtkDrawingArea* _tmp5_ = NULL;
	GtkDrawingArea* _tmp6_ = NULL;
	gchar* _tmp7_ = NULL;
	g_return_val_if_fail (*da != NULL, NULL);
	self = (GameJoypad*) g_object_new (object_type, NULL);
	_tmp0_ = _g_object_ref0 (self);
	_g_object_unref0 (game_joypad_self);
	game_joypad_self = _tmp0_;
	_tmp1_ = *da;
	_tmp2_ = _g_object_ref0 (_tmp1_);
	_g_object_unref0 (self->drawing_area);
	self->drawing_area = _tmp2_;
	_tmp3_ = self->drawing_area;
	g_signal_connect_object ((GtkWidget*) _tmp3_, "expose-event", (GCallback) _game_joypad_expose_event_gtk_widget_expose_event, self, 0);
	_tmp4_ = self->drawing_area;
	g_signal_connect_object ((GtkWidget*) _tmp4_, "size-allocate", (GCallback) ___lambda4__gtk_widget_size_allocate, self, 0);
	_tmp5_ = self->drawing_area;
	g_signal_connect_object ((GtkWidget*) _tmp5_, "unmap", (GCallback) ___lambda5__gtk_widget_unmap, self, 0);
	_tmp6_ = self->drawing_area;
	g_signal_connect_object ((GtkWidget*) _tmp6_, "map", (GCallback) ___lambda6__gtk_widget_map, self, 0);
	_tmp7_ = fb_ink_detect_touch_device ();
	_g_free0 (self->priv->touch_device);
	self->priv->touch_device = _tmp7_;
	return self;
}


GameJoypad* game_joypad_new (GtkDrawingArea** da) {
	return game_joypad_construct (TYPE_GAME_JOYPAD, da);
}


static gboolean game_joypad_expose_event (GameJoypad* self, GtkWidget* w, GdkEventExpose* ee) {
	gboolean result = FALSE;
	GtkAllocation alloc = {0};
	GtkWidget* _tmp0_ = NULL;
	GtkAllocation _tmp1_ = {0};
	gint width = 0;
	GtkAllocation _tmp2_ = {0};
	gint _tmp3_ = 0;
	gint height = 0;
	GtkAllocation _tmp4_ = {0};
	gint _tmp5_ = 0;
	GtkStyle* style = NULL;
	GtkWidget* _tmp6_ = NULL;
	GtkStyle* _tmp7_ = NULL;
	GtkStyle* _tmp8_ = NULL;
	GdkColor fg = {0};
	GtkStyle* _tmp9_ = NULL;
	GdkColor* _tmp10_ = NULL;
	gint _tmp10__length1 = 0;
	GdkColor _tmp11_ = {0};
	gdouble fg_r = 0.0;
	GdkColor _tmp12_ = {0};
	guint16 _tmp13_ = 0U;
	gdouble fg_g = 0.0;
	GdkColor _tmp14_ = {0};
	guint16 _tmp15_ = 0U;
	gdouble fg_b = 0.0;
	GdkColor _tmp16_ = {0};
	guint16 _tmp17_ = 0U;
	cairo_t* cr = NULL;
	GtkWidget* _tmp18_ = NULL;
	GdkWindow* _tmp19_ = NULL;
	cairo_t* _tmp20_ = NULL;
	g_return_val_if_fail (self != NULL, FALSE);
	g_return_val_if_fail (w != NULL, FALSE);
	g_return_val_if_fail (ee != NULL, FALSE);
	_tmp0_ = w;
	_tmp1_ = _tmp0_->allocation;
	alloc = _tmp1_;
	_tmp2_ = alloc;
	_tmp3_ = _tmp2_.width;
	width = _tmp3_;
	_tmp4_ = alloc;
	_tmp5_ = _tmp4_.height;
	height = _tmp5_;
	_tmp6_ = w;
	_tmp7_ = gtk_widget_get_style (_tmp6_);
	_tmp8_ = _g_object_ref0 (_tmp7_);
	style = _tmp8_;
	_tmp9_ = style;
	_tmp10_ = _tmp9_->fg;
	_tmp10__length1 = -1;
	_tmp11_ = _tmp10_[GTK_STATE_NORMAL];
	fg = _tmp11_;
	_tmp12_ = fg;
	_tmp13_ = _tmp12_.red;
	fg_r = _tmp13_ / 65535.0;
	_tmp14_ = fg;
	_tmp15_ = _tmp14_.green;
	fg_g = _tmp15_ / 65535.0;
	_tmp16_ = fg;
	_tmp17_ = _tmp16_.blue;
	fg_b = _tmp17_ / 65535.0;
	_tmp18_ = w;
	_tmp19_ = _tmp18_->window;
	_tmp20_ = gdk_cairo_create ((GdkDrawable*) _tmp19_);
	cr = _tmp20_;
	{
		gint idx = 0;
		idx = 0;
		{
			gboolean _tmp21_ = FALSE;
			_tmp21_ = TRUE;
			while (TRUE) {
				gint _tmp23_ = 0;
				GameJoypadButton* _tmp24_ = NULL;
				gint _tmp24__length1 = 0;
				gboolean btn_active = FALSE;
				GameJoypadButton* _tmp25_ = NULL;
				gint _tmp25__length1 = 0;
				gint _tmp26_ = 0;
				gint _tmp27_ = 0;
				gboolean _tmp28_ = FALSE;
				GameJoypadButton* _tmp29_ = NULL;
				gint _tmp29__length1 = 0;
				gint _tmp30_ = 0;
				GameJoypadButton _tmp31_ = {0};
				gboolean _tmp32_ = FALSE;
				gdouble btn_x = 0.0;
				GameJoypadButton* _tmp34_ = NULL;
				gint _tmp34__length1 = 0;
				gint _tmp35_ = 0;
				GameJoypadButton _tmp36_ = {0};
				gint _tmp37_ = 0;
				gint _tmp38_ = 0;
				gdouble btn_y = 0.0;
				GameJoypadButton* _tmp39_ = NULL;
				gint _tmp39__length1 = 0;
				gint _tmp40_ = 0;
				GameJoypadButton _tmp41_ = {0};
				gint _tmp42_ = 0;
				gint _tmp43_ = 0;
				gdouble btn_r = 0.0;
				GameJoypadButton* _tmp44_ = NULL;
				gint _tmp44__length1 = 0;
				gint _tmp45_ = 0;
				GameJoypadButton _tmp46_ = {0};
				gint _tmp47_ = 0;
				gint _tmp48_ = 0;
				gdouble btn_w = 0.0;
				GameJoypadButton* _tmp49_ = NULL;
				gint _tmp49__length1 = 0;
				gint _tmp50_ = 0;
				GameJoypadButton _tmp51_ = {0};
				gint _tmp52_ = 0;
				gint _tmp53_ = 0;
				gdouble btn_h = 0.0;
				GameJoypadButton* _tmp54_ = NULL;
				gint _tmp54__length1 = 0;
				gint _tmp55_ = 0;
				GameJoypadButton _tmp56_ = {0};
				gint _tmp57_ = 0;
				gint _tmp58_ = 0;
				cairo_t* _tmp59_ = NULL;
				cairo_t* _tmp60_ = NULL;
				gdouble _tmp61_ = 0.0;
				gdouble _tmp62_ = 0.0;
				gdouble _tmp63_ = 0.0;
				GameJoypadButton* _tmp64_ = NULL;
				gint _tmp64__length1 = 0;
				gint _tmp65_ = 0;
				GameJoypadButton _tmp66_ = {0};
				gint _tmp67_ = 0;
				cairo_t* _tmp79_ = NULL;
				gboolean _tmp80_ = FALSE;
				cairo_t* _tmp83_ = NULL;
				cairo_t* _tmp84_ = NULL;
				gint _tmp85_ = 0;
				gchar* label = NULL;
				GameJoypadButton* _tmp86_ = NULL;
				gint _tmp86__length1 = 0;
				gint _tmp87_ = 0;
				GameJoypadButton _tmp88_ = {0};
				const gchar* _tmp89_ = NULL;
				gchar* _tmp90_ = NULL;
				cairo_text_extents_t te = {0};
				cairo_t* _tmp91_ = NULL;
				const gchar* _tmp92_ = NULL;
				cairo_text_extents_t _tmp93_ = {0};
				cairo_t* _tmp94_ = NULL;
				gdouble _tmp95_ = 0.0;
				cairo_text_extents_t _tmp96_ = {0};
				gdouble _tmp97_ = 0.0;
				cairo_text_extents_t _tmp98_ = {0};
				gdouble _tmp99_ = 0.0;
				gdouble _tmp100_ = 0.0;
				cairo_text_extents_t _tmp101_ = {0};
				gdouble _tmp102_ = 0.0;
				cairo_t* _tmp103_ = NULL;
				const gchar* _tmp104_ = NULL;
				if (!_tmp21_) {
					gint _tmp22_ = 0;
					_tmp22_ = idx;
					idx = _tmp22_ + 1;
				}
				_tmp21_ = FALSE;
				_tmp23_ = idx;
				_tmp24_ = self->priv->buttons;
				_tmp24__length1 = self->priv->buttons_length1;
				if (!(_tmp23_ < _tmp24__length1)) {
					break;
				}
				_tmp25_ = self->priv->buttons;
				_tmp25__length1 = self->priv->buttons_length1;
				_tmp26_ = idx;
				_tmp27_ = g_atomic_int_get ((volatile gint *) (&_tmp25_[_tmp26_].active));
				btn_active = _tmp27_ == 1;
				_tmp29_ = self->priv->buttons;
				_tmp29__length1 = self->priv->buttons_length1;
				_tmp30_ = idx;
				_tmp31_ = _tmp29_[_tmp30_];
				_tmp32_ = _tmp31_.visible;
				if (!_tmp32_) {
					gboolean _tmp33_ = FALSE;
					_tmp33_ = btn_active;
					_tmp28_ = !_tmp33_;
				} else {
					_tmp28_ = FALSE;
				}
				if (_tmp28_) {
					continue;
				}
				_tmp34_ = self->priv->buttons;
				_tmp34__length1 = self->priv->buttons_length1;
				_tmp35_ = idx;
				_tmp36_ = _tmp34_[_tmp35_];
				_tmp37_ = _tmp36_.x;
				_tmp38_ = width;
				btn_x = (_tmp37_ * _tmp38_) / 100.0;
				_tmp39_ = self->priv->buttons;
				_tmp39__length1 = self->priv->buttons_length1;
				_tmp40_ = idx;
				_tmp41_ = _tmp39_[_tmp40_];
				_tmp42_ = _tmp41_.y;
				_tmp43_ = height;
				btn_y = (_tmp42_ * _tmp43_) / 100.0;
				_tmp44_ = self->priv->buttons;
				_tmp44__length1 = self->priv->buttons_length1;
				_tmp45_ = idx;
				_tmp46_ = _tmp44_[_tmp45_];
				_tmp47_ = _tmp46_.radius;
				_tmp48_ = width;
				btn_r = (_tmp47_ * _tmp48_) / 100.0;
				_tmp49_ = self->priv->buttons;
				_tmp49__length1 = self->priv->buttons_length1;
				_tmp50_ = idx;
				_tmp51_ = _tmp49_[_tmp50_];
				_tmp52_ = _tmp51_.width;
				_tmp53_ = width;
				btn_w = (_tmp52_ * _tmp53_) / 100.0;
				_tmp54_ = self->priv->buttons;
				_tmp54__length1 = self->priv->buttons_length1;
				_tmp55_ = idx;
				_tmp56_ = _tmp54_[_tmp55_];
				_tmp57_ = _tmp56_.height;
				_tmp58_ = width;
				btn_h = (_tmp57_ * _tmp58_) / 100.0;
				_tmp59_ = cr;
				cairo_new_path (_tmp59_);
				_tmp60_ = cr;
				_tmp61_ = fg_r;
				_tmp62_ = fg_g;
				_tmp63_ = fg_b;
				cairo_set_source_rgb (_tmp60_, _tmp61_, _tmp62_, _tmp63_);
				_tmp64_ = self->priv->buttons;
				_tmp64__length1 = self->priv->buttons_length1;
				_tmp65_ = idx;
				_tmp66_ = _tmp64_[_tmp65_];
				_tmp67_ = _tmp66_.radius;
				if (_tmp67_ > 0) {
					cairo_t* _tmp68_ = NULL;
					gdouble _tmp69_ = 0.0;
					gdouble _tmp70_ = 0.0;
					gdouble _tmp71_ = 0.0;
					_tmp68_ = cr;
					_tmp69_ = btn_x;
					_tmp70_ = btn_y;
					_tmp71_ = btn_r;
					cairo_arc (_tmp68_, _tmp69_, _tmp70_, _tmp71_, (gdouble) 0, 2 * G_PI);
				} else {
					cairo_t* _tmp72_ = NULL;
					gdouble _tmp73_ = 0.0;
					gdouble _tmp74_ = 0.0;
					gdouble _tmp75_ = 0.0;
					gdouble _tmp76_ = 0.0;
					gdouble _tmp77_ = 0.0;
					gdouble _tmp78_ = 0.0;
					_tmp72_ = cr;
					_tmp73_ = btn_x;
					_tmp74_ = btn_w;
					_tmp75_ = btn_y;
					_tmp76_ = btn_h;
					_tmp77_ = btn_w;
					_tmp78_ = btn_h;
					cairo_rectangle (_tmp72_, _tmp73_ - (_tmp74_ / 2.0), _tmp75_ - (_tmp76_ / 2.0), _tmp77_, _tmp78_);
				}
				_tmp79_ = cr;
				cairo_set_line_width (_tmp79_, 5.0);
				_tmp80_ = btn_active;
				if (_tmp80_) {
					cairo_t* _tmp81_ = NULL;
					_tmp81_ = cr;
					cairo_fill (_tmp81_);
				} else {
					cairo_t* _tmp82_ = NULL;
					_tmp82_ = cr;
					cairo_stroke (_tmp82_);
				}
				_tmp83_ = cr;
				cairo_select_font_face (_tmp83_, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
				_tmp84_ = cr;
				_tmp85_ = width;
				cairo_set_font_size (_tmp84_, _tmp85_ * 0.03);
				_tmp86_ = self->priv->buttons;
				_tmp86__length1 = self->priv->buttons_length1;
				_tmp87_ = idx;
				_tmp88_ = _tmp86_[_tmp87_];
				_tmp89_ = _tmp88_.label;
				_tmp90_ = g_strdup (_tmp89_);
				label = _tmp90_;
				_tmp91_ = cr;
				_tmp92_ = label;
				cairo_text_extents (_tmp91_, _tmp92_, &_tmp93_);
				te = _tmp93_;
				_tmp94_ = cr;
				_tmp95_ = btn_x;
				_tmp96_ = te;
				_tmp97_ = _tmp96_.width;
				_tmp98_ = te;
				_tmp99_ = _tmp98_.x_bearing;
				_tmp100_ = btn_y;
				_tmp101_ = te;
				_tmp102_ = _tmp101_.height;
				cairo_move_to (_tmp94_, (_tmp95_ - (_tmp97_ / 2.0)) - _tmp99_, _tmp100_ + (_tmp102_ / 2.0));
				_tmp103_ = cr;
				_tmp104_ = label;
				cairo_show_text (_tmp103_, _tmp104_);
				_g_free0 (label);
			}
		}
	}
	result = FALSE;
	_cairo_destroy0 (cr);
	_g_object_unref0 (style);
	return result;
}


static GameJoypadButton* _vala_array_dup7 (GameJoypadButton* self, int length) {
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


void game_joypad_set_buttons (GameJoypad* self, GameJoypadButton* _buttons, int _buttons_length1) {
	GameJoypadButton* _tmp0_ = NULL;
	gint _tmp0__length1 = 0;
	GameJoypadButton* _tmp1_ = NULL;
	gint _tmp1__length1 = 0;
	GtkDrawingArea* _tmp2_ = NULL;
	g_return_if_fail (self != NULL);
	_tmp0_ = _buttons;
	_tmp0__length1 = _buttons_length1;
	_tmp1_ = (_tmp0_ != NULL) ? _vala_array_dup7 (_tmp0_, _tmp0__length1) : ((gpointer) _tmp0_);
	_tmp1__length1 = _tmp0__length1;
	self->priv->buttons = (_vala_GameJoypadButton_array_free (self->priv->buttons, self->priv->buttons_length1), NULL);
	self->priv->buttons = _tmp1_;
	self->priv->buttons_length1 = _tmp1__length1;
	self->priv->_buttons_size_ = self->priv->buttons_length1;
	_tmp2_ = self->drawing_area;
	gtk_widget_queue_draw ((GtkWidget*) _tmp2_);
}


gint game_joypad_get_button_state (GameJoypad* self, guint id) {
	gint result = 0;
	g_return_val_if_fail (self != NULL, 0);
	{
		gint idx = 0;
		idx = 0;
		{
			gboolean _tmp0_ = FALSE;
			_tmp0_ = TRUE;
			while (TRUE) {
				gint _tmp2_ = 0;
				GameJoypadButton* _tmp3_ = NULL;
				gint _tmp3__length1 = 0;
				GameJoypadButton* _tmp4_ = NULL;
				gint _tmp4__length1 = 0;
				gint _tmp5_ = 0;
				GameJoypadButton _tmp6_ = {0};
				gint _tmp7_ = 0;
				guint _tmp8_ = 0U;
				GameJoypadButton* _tmp9_ = NULL;
				gint _tmp9__length1 = 0;
				gint _tmp10_ = 0;
				gint _tmp11_ = 0;
				if (!_tmp0_) {
					gint _tmp1_ = 0;
					_tmp1_ = idx;
					idx = _tmp1_ + 1;
				}
				_tmp0_ = FALSE;
				_tmp2_ = idx;
				_tmp3_ = self->priv->buttons;
				_tmp3__length1 = self->priv->buttons_length1;
				if (!(_tmp2_ < _tmp3__length1)) {
					break;
				}
				_tmp4_ = self->priv->buttons;
				_tmp4__length1 = self->priv->buttons_length1;
				_tmp5_ = idx;
				_tmp6_ = _tmp4_[_tmp5_];
				_tmp7_ = _tmp6_.id;
				_tmp8_ = id;
				if (((guint) _tmp7_) != _tmp8_) {
					continue;
				}
				_tmp9_ = self->priv->buttons;
				_tmp9__length1 = self->priv->buttons_length1;
				_tmp10_ = idx;
				_tmp11_ = g_atomic_int_get ((volatile gint *) (&_tmp9_[_tmp10_].active));
				result = _tmp11_;
				return result;
			}
		}
	}
	result = 0;
	return result;
}


static gpointer _game_joypad_thread_fn_gthread_func (gpointer self) {
	gpointer result;
	result = game_joypad_thread_fn ();
	return result;
}


void game_joypad_start (GameJoypad* self) {
	GThread* _tmp6_ = NULL;
	GThread* _tmp7_ = NULL;
	GError * _inner_error_ = NULL;
	g_return_if_fail (self != NULL);
	{
		GameJoypadRunState _tmp0_ = 0;
		_tmp0_ = self->priv->state;
		g_static_rec_mutex_lock (&self->priv->__lock_state);
		{
			gboolean _tmp1_ = FALSE;
			GameJoypadRunState _tmp2_ = 0;
			_tmp2_ = self->priv->state;
			if (_tmp2_ == GAME_JOYPAD_RUN_STATE_STOPPED) {
				_tmp1_ = TRUE;
			} else {
				GameJoypadRunState _tmp3_ = 0;
				_tmp3_ = self->priv->state;
				_tmp1_ = _tmp3_ == GAME_JOYPAD_RUN_STATE_PAUSED;
			}
			if (_tmp1_) {
				self->priv->state = GAME_JOYPAD_RUN_STATE_RUNNING;
			} else {
				{
					GameJoypadRunState _tmp4_ = 0;
					_tmp4_ = self->priv->state;
					g_static_rec_mutex_unlock (&self->priv->__lock_state);
				}
				return;
			}
		}
		__finally35:
		{
			GameJoypadRunState _tmp5_ = 0;
			_tmp5_ = self->priv->state;
			g_static_rec_mutex_unlock (&self->priv->__lock_state);
		}
		if (G_UNLIKELY (_inner_error_ != NULL)) {
			g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
			g_clear_error (&_inner_error_);
			return;
		}
	}
	_tmp7_ = g_thread_create (_game_joypad_thread_fn_gthread_func, NULL, TRUE, &_inner_error_);
	_tmp6_ = _tmp7_;
	if (G_UNLIKELY (_inner_error_ != NULL)) {
		g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
		g_clear_error (&_inner_error_);
		return;
	}
	self->priv->thread = _tmp6_;
}


void game_joypad_resume (GameJoypad* self) {
	GThread* _tmp4_ = NULL;
	GThread* _tmp5_ = NULL;
	GError * _inner_error_ = NULL;
	g_return_if_fail (self != NULL);
	{
		GameJoypadRunState _tmp0_ = 0;
		_tmp0_ = self->priv->state;
		g_static_rec_mutex_lock (&self->priv->__lock_state);
		{
			GameJoypadRunState _tmp1_ = 0;
			_tmp1_ = self->priv->state;
			if (_tmp1_ == GAME_JOYPAD_RUN_STATE_PAUSED) {
				self->priv->state = GAME_JOYPAD_RUN_STATE_RUNNING;
			} else {
				{
					GameJoypadRunState _tmp2_ = 0;
					_tmp2_ = self->priv->state;
					g_static_rec_mutex_unlock (&self->priv->__lock_state);
				}
				return;
			}
		}
		__finally36:
		{
			GameJoypadRunState _tmp3_ = 0;
			_tmp3_ = self->priv->state;
			g_static_rec_mutex_unlock (&self->priv->__lock_state);
		}
		if (G_UNLIKELY (_inner_error_ != NULL)) {
			g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
			g_clear_error (&_inner_error_);
			return;
		}
	}
	_tmp5_ = g_thread_create (_game_joypad_thread_fn_gthread_func, NULL, TRUE, &_inner_error_);
	_tmp4_ = _tmp5_;
	if (G_UNLIKELY (_inner_error_ != NULL)) {
		g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
		g_clear_error (&_inner_error_);
		return;
	}
	self->priv->thread = _tmp4_;
}


void game_joypad_stop (GameJoypad* self) {
	GThread* _tmp6_ = NULL;
	GError * _inner_error_ = NULL;
	g_return_if_fail (self != NULL);
	{
		GameJoypadRunState _tmp0_ = 0;
		_tmp0_ = self->priv->state;
		g_static_rec_mutex_lock (&self->priv->__lock_state);
		{
			gboolean _tmp1_ = FALSE;
			GameJoypadRunState _tmp2_ = 0;
			_tmp2_ = self->priv->state;
			if (_tmp2_ == GAME_JOYPAD_RUN_STATE_RUNNING) {
				_tmp1_ = TRUE;
			} else {
				GameJoypadRunState _tmp3_ = 0;
				_tmp3_ = self->priv->state;
				_tmp1_ = _tmp3_ == GAME_JOYPAD_RUN_STATE_PAUSED;
			}
			if (_tmp1_) {
				self->priv->state = GAME_JOYPAD_RUN_STATE_STOPPED;
			} else {
				{
					GameJoypadRunState _tmp4_ = 0;
					_tmp4_ = self->priv->state;
					g_static_rec_mutex_unlock (&self->priv->__lock_state);
				}
				return;
			}
		}
		__finally37:
		{
			GameJoypadRunState _tmp5_ = 0;
			_tmp5_ = self->priv->state;
			g_static_rec_mutex_unlock (&self->priv->__lock_state);
		}
		if (G_UNLIKELY (_inner_error_ != NULL)) {
			g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
			g_clear_error (&_inner_error_);
			return;
		}
	}
	_tmp6_ = self->priv->thread;
	g_thread_join (_tmp6_);
}


void game_joypad_pause (GameJoypad* self) {
	GThread* _tmp4_ = NULL;
	GError * _inner_error_ = NULL;
	g_return_if_fail (self != NULL);
	{
		GameJoypadRunState _tmp0_ = 0;
		_tmp0_ = self->priv->state;
		g_static_rec_mutex_lock (&self->priv->__lock_state);
		{
			GameJoypadRunState _tmp1_ = 0;
			_tmp1_ = self->priv->state;
			if (_tmp1_ == GAME_JOYPAD_RUN_STATE_RUNNING) {
				self->priv->state = GAME_JOYPAD_RUN_STATE_PAUSED;
			} else {
				{
					GameJoypadRunState _tmp2_ = 0;
					_tmp2_ = self->priv->state;
					g_static_rec_mutex_unlock (&self->priv->__lock_state);
				}
				return;
			}
		}
		__finally38:
		{
			GameJoypadRunState _tmp3_ = 0;
			_tmp3_ = self->priv->state;
			g_static_rec_mutex_unlock (&self->priv->__lock_state);
		}
		if (G_UNLIKELY (_inner_error_ != NULL)) {
			g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
			g_clear_error (&_inner_error_);
			return;
		}
	}
	_tmp4_ = self->priv->thread;
	g_thread_join (_tmp4_);
}


void* game_joypad_thread_fn (void) {
	void* result = NULL;
	struct sched_param param = {0};
	struct sched_param _tmp0_ = {0};
	gulong _tmp1_ = 0UL;
	gint _tmp2_ = 0;
	gint fd = 0;
	GameJoypad* _tmp3_ = NULL;
	const gchar* _tmp4_ = NULL;
	gint _tmp5_ = 0;
	struct pollfd* fds = NULL;
	gint _tmp6_ = 0;
	struct pollfd _tmp7_ = {0};
	struct pollfd* _tmp8_ = NULL;
	gint fds_length1 = 0;
	gint _fds_size_ = 0;
	struct input_event ev = {0};
	struct input_event _tmp9_ = {0};
	GameJoypadTouchSlot slots[2] = {0};
	GameJoypadTouchSlot _tmp10_[2] = {0};
	gint current_slot = 0;
	GError * _inner_error_ = NULL;
	memset (&_tmp0_, 0, sizeof (struct sched_param));
	_tmp0_.sched_priority = 70;
	param = _tmp0_;
	_tmp1_ = pthread_self ();
	_tmp2_ = pthread_setschedparam (_tmp1_, (gint) SCHED_RR, &param);
	if (_tmp2_ != 0) {
		g_warning ("gamejoypad.vala:319: [gamejoypad] pthread_setschedparam failed\n");
	}
	_tmp3_ = game_joypad_self;
	_tmp4_ = _tmp3_->priv->touch_device;
	_tmp5_ = open (_tmp4_, O_RDONLY | O_NONBLOCK, (mode_t) 0);
	fd = _tmp5_;
	_tmp6_ = fd;
	memset (&_tmp7_, 0, sizeof (struct pollfd));
	_tmp7_.fd = _tmp6_;
	_tmp7_.events = POLLIN;
	_tmp8_ = g_new0 (struct pollfd, 1);
	_tmp8_[0] = _tmp7_;
	fds = _tmp8_;
	fds_length1 = 1;
	_fds_size_ = fds_length1;
	ev = _tmp9_;
	memcpy (slots, _tmp10_, 2 * sizeof (GameJoypadTouchSlot));
	current_slot = 0;
	while (TRUE) {
		gint ret = 0;
		struct pollfd* _tmp22_ = NULL;
		gint _tmp22__length1 = 0;
		gint _tmp23_ = 0;
		gint _tmp24_ = 0;
		{
			GameJoypad* _tmp11_ = NULL;
			GameJoypadRunState _tmp12_ = 0;
			_tmp11_ = game_joypad_self;
			_tmp12_ = _tmp11_->priv->state;
			g_static_rec_mutex_lock (&_tmp11_->priv->__lock_state);
			{
				gboolean _tmp13_ = FALSE;
				GameJoypad* _tmp14_ = NULL;
				GameJoypadRunState _tmp15_ = 0;
				_tmp14_ = game_joypad_self;
				_tmp15_ = _tmp14_->priv->state;
				if (_tmp15_ == GAME_JOYPAD_RUN_STATE_STOPPED) {
					_tmp13_ = TRUE;
				} else {
					GameJoypad* _tmp16_ = NULL;
					GameJoypadRunState _tmp17_ = 0;
					_tmp16_ = game_joypad_self;
					_tmp17_ = _tmp16_->priv->state;
					_tmp13_ = _tmp17_ == GAME_JOYPAD_RUN_STATE_PAUSED;
				}
				if (_tmp13_) {
					{
						GameJoypad* _tmp18_ = NULL;
						GameJoypadRunState _tmp19_ = 0;
						_tmp18_ = game_joypad_self;
						_tmp19_ = _tmp18_->priv->state;
						g_static_rec_mutex_unlock (&_tmp18_->priv->__lock_state);
					}
					break;
				}
			}
			__finally39:
			{
				GameJoypad* _tmp20_ = NULL;
				GameJoypadRunState _tmp21_ = 0;
				_tmp20_ = game_joypad_self;
				_tmp21_ = _tmp20_->priv->state;
				g_static_rec_mutex_unlock (&_tmp20_->priv->__lock_state);
			}
			if (G_UNLIKELY (_inner_error_ != NULL)) {
				fds = (g_free (fds), NULL);
				g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
				g_clear_error (&_inner_error_);
				return NULL;
			}
		}
		_tmp22_ = fds;
		_tmp22__length1 = fds_length1;
		_tmp23_ = poll (_tmp22_, _tmp22__length1, 50);
		ret = _tmp23_;
		_tmp24_ = ret;
		if (_tmp24_ <= 0) {
			continue;
		}
		while (TRUE) {
			gint _tmp25_ = 0;
			gssize _tmp26_ = 0L;
			struct input_event _tmp27_ = {0};
			guint16 _tmp28_ = 0U;
			_tmp25_ = fd;
			_tmp26_ = read (_tmp25_, &ev, (gsize) sizeof (struct input_event));
			if (!(((gulong) _tmp26_) == sizeof (struct input_event))) {
				break;
			}
			_tmp27_ = ev;
			_tmp28_ = _tmp27_.type;
			if (_tmp28_ == EV_ABS) {
				struct input_event _tmp29_ = {0};
				guint16 _tmp30_ = 0U;
				gboolean _tmp33_ = FALSE;
				struct input_event _tmp34_ = {0};
				guint16 _tmp35_ = 0U;
				gint _tmp40_ = 0;
				struct input_event _tmp41_ = {0};
				guint16 _tmp42_ = 0U;
				struct input_event _tmp46_ = {0};
				guint16 _tmp47_ = 0U;
				struct input_event _tmp51_ = {0};
				guint16 _tmp52_ = 0U;
				_tmp29_ = ev;
				_tmp30_ = _tmp29_.code;
				if (_tmp30_ == ABS_MT_SLOT) {
					struct input_event _tmp31_ = {0};
					gint32 _tmp32_ = 0;
					_tmp31_ = ev;
					_tmp32_ = _tmp31_.value;
					current_slot = (gint) _tmp32_;
					continue;
				}
				_tmp34_ = ev;
				_tmp35_ = _tmp34_.code;
				if (_tmp35_ == ABS_MT_TRACKING_ID) {
					struct input_event _tmp36_ = {0};
					gint32 _tmp37_ = 0;
					_tmp36_ = ev;
					_tmp37_ = _tmp36_.value;
					_tmp33_ = _tmp37_ != ((gint32) -1);
				} else {
					_tmp33_ = FALSE;
				}
				if (_tmp33_) {
					struct input_event _tmp38_ = {0};
					gint32 _tmp39_ = 0;
					_tmp38_ = ev;
					_tmp39_ = _tmp38_.value;
					current_slot = (gint) _tmp39_;
				}
				_tmp40_ = current_slot;
				if (_tmp40_ > 1) {
					continue;
				}
				_tmp41_ = ev;
				_tmp42_ = _tmp41_.code;
				if (_tmp42_ == ABS_MT_TRACKING_ID) {
					gint _tmp43_ = 0;
					struct input_event _tmp44_ = {0};
					gint32 _tmp45_ = 0;
					_tmp43_ = current_slot;
					_tmp44_ = ev;
					_tmp45_ = _tmp44_.value;
					slots[_tmp43_].active = _tmp45_ != ((gint32) -1);
					continue;
				}
				_tmp46_ = ev;
				_tmp47_ = _tmp46_.code;
				if (_tmp47_ == ABS_MT_POSITION_X) {
					gint _tmp48_ = 0;
					struct input_event _tmp49_ = {0};
					gint32 _tmp50_ = 0;
					_tmp48_ = current_slot;
					_tmp49_ = ev;
					_tmp50_ = _tmp49_.value;
					slots[_tmp48_].x = (gint) _tmp50_;
					continue;
				}
				_tmp51_ = ev;
				_tmp52_ = _tmp51_.code;
				if (_tmp52_ == ABS_MT_POSITION_Y) {
					gint _tmp53_ = 0;
					struct input_event _tmp54_ = {0};
					gint32 _tmp55_ = 0;
					_tmp53_ = current_slot;
					_tmp54_ = ev;
					_tmp55_ = _tmp54_.value;
					slots[_tmp53_].y = (gint) _tmp55_;
					continue;
				}
			} else {
				struct input_event _tmp56_ = {0};
				guint16 _tmp57_ = 0U;
				_tmp56_ = ev;
				_tmp57_ = _tmp56_.type;
				if (_tmp57_ == EV_KEY) {
					gboolean _tmp58_ = FALSE;
					struct input_event _tmp59_ = {0};
					guint16 _tmp60_ = 0U;
					gboolean _tmp65_ = FALSE;
					struct input_event _tmp66_ = {0};
					guint16 _tmp67_ = 0U;
					_tmp59_ = ev;
					_tmp60_ = _tmp59_.code;
					if (_tmp60_ == BTN_TOOL_DOUBLETAP) {
						struct input_event _tmp61_ = {0};
						gint32 _tmp62_ = 0;
						_tmp61_ = ev;
						_tmp62_ = _tmp61_.value;
						_tmp58_ = _tmp62_ == ((gint32) 0);
					} else {
						_tmp58_ = FALSE;
					}
					if (_tmp58_) {
						gint _tmp63_ = 0;
						gint _tmp64_ = 0;
						_tmp64_ = current_slot;
						if (_tmp64_ == 1) {
							_tmp63_ = 0;
						} else {
							_tmp63_ = 1;
						}
						slots[_tmp63_].active = FALSE;
						continue;
					}
					_tmp66_ = ev;
					_tmp67_ = _tmp66_.code;
					if (_tmp67_ == BTN_TOUCH) {
						struct input_event _tmp68_ = {0};
						gint32 _tmp69_ = 0;
						_tmp68_ = ev;
						_tmp69_ = _tmp68_.value;
						_tmp65_ = _tmp69_ == ((gint32) 0);
					} else {
						_tmp65_ = FALSE;
					}
					if (_tmp65_) {
						slots[0].active = FALSE;
						slots[1].active = FALSE;
						continue;
					}
				} else {
					struct input_event _tmp70_ = {0};
					guint16 _tmp71_ = 0U;
					_tmp70_ = ev;
					_tmp71_ = _tmp70_.type;
					if (_tmp71_ == EV_SYN) {
						gboolean should_redraw = FALSE;
						gint _x = 0;
						GameJoypad* _tmp72_ = NULL;
						gint _tmp73_ = 0;
						gint _y = 0;
						GameJoypad* _tmp74_ = NULL;
						gint _tmp75_ = 0;
						gboolean _tmp164_ = FALSE;
						should_redraw = FALSE;
						_tmp72_ = game_joypad_self;
						_tmp73_ = g_atomic_int_get ((volatile gint *) (&_tmp72_->x));
						_x = _tmp73_;
						_tmp74_ = game_joypad_self;
						_tmp75_ = g_atomic_int_get ((volatile gint *) (&_tmp74_->y));
						_y = _tmp75_;
						{
							gint idx = 0;
							idx = 0;
							{
								gboolean _tmp76_ = FALSE;
								_tmp76_ = TRUE;
								while (TRUE) {
									gint _tmp78_ = 0;
									GameJoypad* _tmp79_ = NULL;
									GameJoypadButton* _tmp80_ = NULL;
									gint _tmp80__length1 = 0;
									gdouble btn_x = 0.0;
									GameJoypad* _tmp81_ = NULL;
									GameJoypadButton* _tmp82_ = NULL;
									gint _tmp82__length1 = 0;
									gint _tmp83_ = 0;
									GameJoypadButton _tmp84_ = {0};
									gint _tmp85_ = 0;
									GameJoypad* _tmp86_ = NULL;
									gint _tmp87_ = 0;
									gdouble btn_y = 0.0;
									GameJoypad* _tmp88_ = NULL;
									GameJoypadButton* _tmp89_ = NULL;
									gint _tmp89__length1 = 0;
									gint _tmp90_ = 0;
									GameJoypadButton _tmp91_ = {0};
									gint _tmp92_ = 0;
									GameJoypad* _tmp93_ = NULL;
									gint _tmp94_ = 0;
									gdouble btn_r = 0.0;
									GameJoypad* _tmp95_ = NULL;
									GameJoypadButton* _tmp96_ = NULL;
									gint _tmp96__length1 = 0;
									gint _tmp97_ = 0;
									GameJoypadButton _tmp98_ = {0};
									gint _tmp99_ = 0;
									GameJoypad* _tmp100_ = NULL;
									gint _tmp101_ = 0;
									gdouble btn_w = 0.0;
									GameJoypad* _tmp102_ = NULL;
									GameJoypadButton* _tmp103_ = NULL;
									gint _tmp103__length1 = 0;
									gint _tmp104_ = 0;
									GameJoypadButton _tmp105_ = {0};
									gint _tmp106_ = 0;
									GameJoypad* _tmp107_ = NULL;
									gint _tmp108_ = 0;
									gdouble btn_h = 0.0;
									GameJoypad* _tmp109_ = NULL;
									GameJoypadButton* _tmp110_ = NULL;
									gint _tmp110__length1 = 0;
									gint _tmp111_ = 0;
									GameJoypadButton _tmp112_ = {0};
									gint _tmp113_ = 0;
									GameJoypad* _tmp114_ = NULL;
									gint _tmp115_ = 0;
									gint active = 0;
									gint _tmp156_ = 0;
									gint _tmp157_ = 0;
									gboolean _btn_changed = FALSE;
									GameJoypad* _tmp158_ = NULL;
									GameJoypadButton* _tmp159_ = NULL;
									gint _tmp159__length1 = 0;
									gint _tmp160_ = 0;
									gint _tmp161_ = 0;
									gboolean _tmp162_ = FALSE;
									gboolean _tmp163_ = FALSE;
									if (!_tmp76_) {
										gint _tmp77_ = 0;
										_tmp77_ = idx;
										idx = _tmp77_ + 1;
									}
									_tmp76_ = FALSE;
									_tmp78_ = idx;
									_tmp79_ = game_joypad_self;
									_tmp80_ = _tmp79_->priv->buttons;
									_tmp80__length1 = _tmp79_->priv->buttons_length1;
									if (!(_tmp78_ < _tmp80__length1)) {
										break;
									}
									_tmp81_ = game_joypad_self;
									_tmp82_ = _tmp81_->priv->buttons;
									_tmp82__length1 = _tmp81_->priv->buttons_length1;
									_tmp83_ = idx;
									_tmp84_ = _tmp82_[_tmp83_];
									_tmp85_ = _tmp84_.x;
									_tmp86_ = game_joypad_self;
									_tmp87_ = _tmp86_->width;
									btn_x = (_tmp85_ * _tmp87_) / 100.0;
									_tmp88_ = game_joypad_self;
									_tmp89_ = _tmp88_->priv->buttons;
									_tmp89__length1 = _tmp88_->priv->buttons_length1;
									_tmp90_ = idx;
									_tmp91_ = _tmp89_[_tmp90_];
									_tmp92_ = _tmp91_.y;
									_tmp93_ = game_joypad_self;
									_tmp94_ = _tmp93_->height;
									btn_y = (_tmp92_ * _tmp94_) / 100.0;
									_tmp95_ = game_joypad_self;
									_tmp96_ = _tmp95_->priv->buttons;
									_tmp96__length1 = _tmp95_->priv->buttons_length1;
									_tmp97_ = idx;
									_tmp98_ = _tmp96_[_tmp97_];
									_tmp99_ = _tmp98_.radius;
									_tmp100_ = game_joypad_self;
									_tmp101_ = _tmp100_->width;
									btn_r = (_tmp99_ * _tmp101_) / 100.0;
									_tmp102_ = game_joypad_self;
									_tmp103_ = _tmp102_->priv->buttons;
									_tmp103__length1 = _tmp102_->priv->buttons_length1;
									_tmp104_ = idx;
									_tmp105_ = _tmp103_[_tmp104_];
									_tmp106_ = _tmp105_.width;
									_tmp107_ = game_joypad_self;
									_tmp108_ = _tmp107_->width;
									btn_w = (_tmp106_ * _tmp108_) / 100.0;
									_tmp109_ = game_joypad_self;
									_tmp110_ = _tmp109_->priv->buttons;
									_tmp110__length1 = _tmp109_->priv->buttons_length1;
									_tmp111_ = idx;
									_tmp112_ = _tmp110_[_tmp111_];
									_tmp113_ = _tmp112_.height;
									_tmp114_ = game_joypad_self;
									_tmp115_ = _tmp114_->width;
									btn_h = (_tmp113_ * _tmp115_) / 100.0;
									active = 0;
									{
										gint s = 0;
										s = 0;
										{
											gboolean _tmp116_ = FALSE;
											_tmp116_ = TRUE;
											while (TRUE) {
												gint _tmp118_ = 0;
												gint _tmp119_ = 0;
												GameJoypadTouchSlot _tmp120_ = {0};
												gboolean _tmp121_ = FALSE;
												gint rel_x = 0;
												gint _tmp122_ = 0;
												GameJoypadTouchSlot _tmp123_ = {0};
												gint _tmp124_ = 0;
												gint _tmp125_ = 0;
												gint rel_y = 0;
												gint _tmp126_ = 0;
												GameJoypadTouchSlot _tmp127_ = {0};
												gint _tmp128_ = 0;
												gint _tmp129_ = 0;
												gdouble _tmp130_ = 0.0;
												if (!_tmp116_) {
													gint _tmp117_ = 0;
													_tmp117_ = s;
													s = _tmp117_ + 1;
												}
												_tmp116_ = FALSE;
												_tmp118_ = s;
												if (!(_tmp118_ < 2)) {
													break;
												}
												_tmp119_ = s;
												_tmp120_ = slots[_tmp119_];
												_tmp121_ = _tmp120_.active;
												if (!_tmp121_) {
													continue;
												}
												_tmp122_ = s;
												_tmp123_ = slots[_tmp122_];
												_tmp124_ = _tmp123_.x;
												_tmp125_ = _x;
												rel_x = _tmp124_ - _tmp125_;
												_tmp126_ = s;
												_tmp127_ = slots[_tmp126_];
												_tmp128_ = _tmp127_.y;
												_tmp129_ = _y;
												rel_y = _tmp128_ - _tmp129_;
												_tmp130_ = btn_r;
												if (_tmp130_ > ((gdouble) 0)) {
													gdouble dx = 0.0;
													gint _tmp131_ = 0;
													gdouble _tmp132_ = 0.0;
													gdouble dy = 0.0;
													gint _tmp133_ = 0;
													gdouble _tmp134_ = 0.0;
													gdouble _tmp135_ = 0.0;
													gdouble _tmp136_ = 0.0;
													gdouble _tmp137_ = 0.0;
													gdouble _tmp138_ = 0.0;
													gdouble _tmp139_ = 0.0;
													gdouble _tmp140_ = 0.0;
													_tmp131_ = rel_x;
													_tmp132_ = btn_x;
													dx = _tmp131_ - _tmp132_;
													_tmp133_ = rel_y;
													_tmp134_ = btn_y;
													dy = _tmp133_ - _tmp134_;
													_tmp135_ = dx;
													_tmp136_ = dx;
													_tmp137_ = dy;
													_tmp138_ = dy;
													_tmp139_ = btn_r;
													_tmp140_ = btn_r;
													if (((_tmp135_ * _tmp136_) + (_tmp137_ * _tmp138_)) <= (_tmp139_ * _tmp140_)) {
														active = 1;
													}
												} else {
													gboolean _tmp141_ = FALSE;
													gboolean _tmp142_ = FALSE;
													gboolean _tmp143_ = FALSE;
													gint _tmp144_ = 0;
													gdouble _tmp145_ = 0.0;
													gdouble _tmp146_ = 0.0;
													_tmp144_ = rel_x;
													_tmp145_ = btn_x;
													_tmp146_ = btn_w;
													if (((gdouble) _tmp144_) > (_tmp145_ - (_tmp146_ / 2))) {
														gint _tmp147_ = 0;
														gdouble _tmp148_ = 0.0;
														gdouble _tmp149_ = 0.0;
														_tmp147_ = rel_x;
														_tmp148_ = btn_x;
														_tmp149_ = btn_w;
														_tmp143_ = ((gdouble) _tmp147_) < (_tmp148_ + (_tmp149_ / 2));
													} else {
														_tmp143_ = FALSE;
													}
													if (_tmp143_) {
														gint _tmp150_ = 0;
														gdouble _tmp151_ = 0.0;
														gdouble _tmp152_ = 0.0;
														_tmp150_ = rel_y;
														_tmp151_ = btn_y;
														_tmp152_ = btn_h;
														_tmp142_ = ((gdouble) _tmp150_) > (_tmp151_ - (_tmp152_ / 2));
													} else {
														_tmp142_ = FALSE;
													}
													if (_tmp142_) {
														gint _tmp153_ = 0;
														gdouble _tmp154_ = 0.0;
														gdouble _tmp155_ = 0.0;
														_tmp153_ = rel_y;
														_tmp154_ = btn_y;
														_tmp155_ = btn_h;
														_tmp141_ = ((gdouble) _tmp153_) < (_tmp154_ + (_tmp155_ / 2));
													} else {
														_tmp141_ = FALSE;
													}
													if (_tmp141_) {
														active = 1;
													}
												}
											}
										}
									}
									_tmp157_ = active;
									if (_tmp157_ == 1) {
										_tmp156_ = 0;
									} else {
										_tmp156_ = 1;
									}
									_tmp158_ = game_joypad_self;
									_tmp159_ = _tmp158_->priv->buttons;
									_tmp159__length1 = _tmp158_->priv->buttons_length1;
									_tmp160_ = idx;
									_tmp161_ = active;
									_tmp162_ = g_atomic_int_compare_and_exchange ((volatile gint *) (&_tmp159_[_tmp160_].active), _tmp156_, _tmp161_);
									_btn_changed = _tmp162_;
									_tmp163_ = _btn_changed;
									if (_tmp163_) {
										should_redraw = TRUE;
									}
								}
							}
						}
						_tmp164_ = should_redraw;
						if (_tmp164_) {
							GameJoypad* _tmp165_ = NULL;
							_tmp165_ = game_joypad_self;
							game_joypad_trigger_queue_draw (_tmp165_);
						}
					}
				}
			}
		}
	}
	result = NULL;
	fds = (g_free (fds), NULL);
	return result;
}


static gboolean _____lambda7_ (GameJoypad* self) {
	gboolean result = FALSE;
	GtkDrawingArea* _tmp2_ = NULL;
	GError * _inner_error_ = NULL;
	{
		guint _tmp0_ = 0U;
		_tmp0_ = self->priv->queue_draw_event_source_id;
		g_static_rec_mutex_lock (&self->priv->__lock_queue_draw_event_source_id);
		{
			self->priv->queue_draw_event_source_id = (guint) 0;
		}
		__finally41:
		{
			guint _tmp1_ = 0U;
			_tmp1_ = self->priv->queue_draw_event_source_id;
			g_static_rec_mutex_unlock (&self->priv->__lock_queue_draw_event_source_id);
		}
		if (G_UNLIKELY (_inner_error_ != NULL)) {
			g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
			g_clear_error (&_inner_error_);
			return FALSE;
		}
	}
	_tmp2_ = self->drawing_area;
	gtk_widget_queue_draw ((GtkWidget*) _tmp2_);
	result = FALSE;
	return result;
}


static gboolean ______lambda7__gsource_func (gpointer self) {
	gboolean result;
	result = _____lambda7_ ((GameJoypad*) self);
	return result;
}


static void game_joypad_trigger_queue_draw (GameJoypad* self) {
	GError * _inner_error_ = NULL;
	g_return_if_fail (self != NULL);
	{
		guint _tmp0_ = 0U;
		_tmp0_ = self->priv->queue_draw_event_source_id;
		g_static_rec_mutex_lock (&self->priv->__lock_queue_draw_event_source_id);
		{
			guint _tmp1_ = 0U;
			_tmp1_ = self->priv->queue_draw_event_source_id;
			if (_tmp1_ == ((guint) 0)) {
				guint _tmp2_ = 0U;
				_tmp2_ = g_idle_add_full (G_PRIORITY_DEFAULT_IDLE, ______lambda7__gsource_func, g_object_ref (self), g_object_unref);
				self->priv->queue_draw_event_source_id = _tmp2_;
			}
		}
		__finally40:
		{
			guint _tmp3_ = 0U;
			_tmp3_ = self->priv->queue_draw_event_source_id;
			g_static_rec_mutex_unlock (&self->priv->__lock_queue_draw_event_source_id);
		}
		if (G_UNLIKELY (_inner_error_ != NULL)) {
			g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
			g_clear_error (&_inner_error_);
			return;
		}
	}
}


void game_joypad_button_copy (const GameJoypadButton* self, GameJoypadButton* dest) {
	gint _tmp0_ = 0;
	const gchar* _tmp1_ = NULL;
	gchar* _tmp2_ = NULL;
	gint _tmp3_ = 0;
	gint _tmp4_ = 0;
	gint _tmp5_ = 0;
	gint _tmp6_ = 0;
	gint _tmp7_ = 0;
	gint _tmp8_ = 0;
	gboolean _tmp9_ = FALSE;
	_tmp0_ = (*self).id;
	(*dest).id = _tmp0_;
	_tmp1_ = (*self).label;
	_tmp2_ = g_strdup (_tmp1_);
	_g_free0 ((*dest).label);
	(*dest).label = _tmp2_;
	_tmp3_ = (*self).active;
	(*dest).active = _tmp3_;
	_tmp4_ = (*self).x;
	(*dest).x = _tmp4_;
	_tmp5_ = (*self).y;
	(*dest).y = _tmp5_;
	_tmp6_ = (*self).radius;
	(*dest).radius = _tmp6_;
	_tmp7_ = (*self).width;
	(*dest).width = _tmp7_;
	_tmp8_ = (*self).height;
	(*dest).height = _tmp8_;
	_tmp9_ = (*self).visible;
	(*dest).visible = _tmp9_;
}


void game_joypad_button_destroy (GameJoypadButton* self) {
	_g_free0 ((*self).label);
}


GameJoypadButton* game_joypad_button_dup (const GameJoypadButton* self) {
	GameJoypadButton* dup;
	dup = g_new0 (GameJoypadButton, 1);
	game_joypad_button_copy (self, dup);
	return dup;
}


void game_joypad_button_free (GameJoypadButton* self) {
	game_joypad_button_destroy (self);
	g_free (self);
}


GType game_joypad_button_get_type (void) {
	static volatile gsize game_joypad_button_type_id__volatile = 0;
	if (g_once_init_enter (&game_joypad_button_type_id__volatile)) {
		GType game_joypad_button_type_id;
		game_joypad_button_type_id = g_boxed_type_register_static ("GameJoypadButton", (GBoxedCopyFunc) game_joypad_button_dup, (GBoxedFreeFunc) game_joypad_button_free);
		g_once_init_leave (&game_joypad_button_type_id__volatile, game_joypad_button_type_id);
	}
	return game_joypad_button_type_id__volatile;
}


static GameJoypadTouchSlot* game_joypad_touch_slot_dup (const GameJoypadTouchSlot* self) {
	GameJoypadTouchSlot* dup;
	dup = g_new0 (GameJoypadTouchSlot, 1);
	memcpy (dup, self, sizeof (GameJoypadTouchSlot));
	return dup;
}


static void game_joypad_touch_slot_free (GameJoypadTouchSlot* self) {
	g_free (self);
}


static GType game_joypad_touch_slot_get_type (void) {
	static volatile gsize game_joypad_touch_slot_type_id__volatile = 0;
	if (g_once_init_enter (&game_joypad_touch_slot_type_id__volatile)) {
		GType game_joypad_touch_slot_type_id;
		game_joypad_touch_slot_type_id = g_boxed_type_register_static ("GameJoypadTouchSlot", (GBoxedCopyFunc) game_joypad_touch_slot_dup, (GBoxedFreeFunc) game_joypad_touch_slot_free);
		g_once_init_leave (&game_joypad_touch_slot_type_id__volatile, game_joypad_touch_slot_type_id);
	}
	return game_joypad_touch_slot_type_id__volatile;
}


static void game_joypad_class_init (GameJoypadClass * klass) {
	game_joypad_parent_class = g_type_class_peek_parent (klass);
	g_type_class_add_private (klass, sizeof (GameJoypadPrivate));
	G_OBJECT_CLASS (klass)->finalize = game_joypad_finalize;
}


static void game_joypad_instance_init (GameJoypad * self) {
	self->priv = GAME_JOYPAD_GET_PRIVATE (self);
	g_static_rec_mutex_init (&self->priv->__lock_state);
	self->width = 0;
	self->height = 0;
	g_static_rec_mutex_init (&self->priv->__lock_queue_draw_event_source_id);
	self->priv->queue_draw_event_source_id = (guint) 0;
}


static void game_joypad_finalize (GObject* obj) {
	GameJoypad * self;
	self = G_TYPE_CHECK_INSTANCE_CAST (obj, TYPE_GAME_JOYPAD, GameJoypad);
	g_static_rec_mutex_free (&self->priv->__lock_state);
	self->priv->buttons = (_vala_GameJoypadButton_array_free (self->priv->buttons, self->priv->buttons_length1), NULL);
	_g_object_unref0 (self->drawing_area);
	_g_free0 (self->priv->touch_device);
	g_static_rec_mutex_free (&self->priv->__lock_queue_draw_event_source_id);
	G_OBJECT_CLASS (game_joypad_parent_class)->finalize (obj);
}


GType game_joypad_get_type (void) {
	static volatile gsize game_joypad_type_id__volatile = 0;
	if (g_once_init_enter (&game_joypad_type_id__volatile)) {
		static const GTypeInfo g_define_type_info = { sizeof (GameJoypadClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) game_joypad_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (GameJoypad), 0, (GInstanceInitFunc) game_joypad_instance_init, NULL };
		GType game_joypad_type_id;
		game_joypad_type_id = g_type_register_static (G_TYPE_OBJECT, "GameJoypad", &g_define_type_info, 0);
		g_once_init_leave (&game_joypad_type_id__volatile, game_joypad_type_id);
	}
	return game_joypad_type_id__volatile;
}



