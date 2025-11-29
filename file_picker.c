/* valac --pkg gtk+-2.0 --pkg gee-0.8 simple_file_picker.vala*/

#include <glib.h>
#include <glib-object.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include <gee.h>
#include <float.h>
#include <math.h>
#include <pango/pango.h>
#include <gdk/gdk.h>
#include <stdio.h>
#include <glib/gstdio.h>


#define TYPE_SIMPLE_FILE_PICKER (simple_file_picker_get_type ())
#define SIMPLE_FILE_PICKER(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_SIMPLE_FILE_PICKER, SimpleFilePicker))
#define SIMPLE_FILE_PICKER_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_SIMPLE_FILE_PICKER, SimpleFilePickerClass))
#define IS_SIMPLE_FILE_PICKER(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_SIMPLE_FILE_PICKER))
#define IS_SIMPLE_FILE_PICKER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_SIMPLE_FILE_PICKER))
#define SIMPLE_FILE_PICKER_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_SIMPLE_FILE_PICKER, SimpleFilePickerClass))

typedef struct _SimpleFilePicker SimpleFilePicker;
typedef struct _SimpleFilePickerClass SimpleFilePickerClass;
typedef struct _SimpleFilePickerPrivate SimpleFilePickerPrivate;
#define _g_object_unref0(var) ((var == NULL) ? NULL : (var = (g_object_unref (var), NULL)))
#define _g_free0(var) (var = (g_free (var), NULL))
typedef struct _Block6Data Block6Data;
#define _gtk_tree_path_free0(var) ((var == NULL) ? NULL : (var = (gtk_tree_path_free (var), NULL)))
#define _g_dir_close0(var) ((var == NULL) ? NULL : (var = (g_dir_close (var), NULL)))
#define _g_error_free0(var) ((var == NULL) ? NULL : (var = (g_error_free (var), NULL)))

struct _SimpleFilePicker {
	GtkWindow parent_instance;
	SimpleFilePickerPrivate * priv;
};

struct _SimpleFilePickerClass {
	GtkWindowClass parent_class;
};

struct _SimpleFilePickerPrivate {
	GtkListStore* store;
	GtkTreeView* tree;
	gchar* cwd;
	GtkLabel* path_label;
	gchar* current_dir;
};

struct _Block6Data {
	int _ref_count_;
	SimpleFilePicker* self;
	GtkScrolledWindow* scrolled;
	gulong destroy_handler_id;
	gchar* full;
	gboolean is_dragging;
	gdouble press_y;
	guint32 press_time;
	gdouble last_y;
	guint32 last_time;
	gdouble _delta;
	GeeSet* ext;
};


static gpointer simple_file_picker_parent_class = NULL;

GType simple_file_picker_get_type (void) G_GNUC_CONST;
#define SIMPLE_FILE_PICKER_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), TYPE_SIMPLE_FILE_PICKER, SimpleFilePickerPrivate))
enum  {
	SIMPLE_FILE_PICKER_DUMMY_PROPERTY
};
SimpleFilePicker* simple_file_picker_new (GtkWindow* parent, GeeSet* ext, const gchar* start_dir, GError** error);
SimpleFilePicker* simple_file_picker_construct (GType object_type, GtkWindow* parent, GeeSet* ext, const gchar* start_dir, GError** error);
static Block6Data* block6_data_ref (Block6Data* _data6_);
static void block6_data_unref (void * _userdata_);
static void __lambda36_ (SimpleFilePicker* self, GtkObject* event);
static void ___lambda36__gtk_object_destroy (GtkObject* _sender, gpointer self);
static void __lambda37_ (SimpleFilePicker* self);
static void ___lambda37__gtk_button_clicked (GtkButton* _sender, gpointer self);
static gboolean __lambda38_ (SimpleFilePicker* self, GdkEventScroll* event);
static gboolean ___lambda38__gtk_widget_scroll_event (GtkWidget* _sender, GdkEventScroll* event, gpointer self);
static gboolean __lambda39_ (Block6Data* _data6_, GdkEventButton* event);
static gboolean simple_file_picker_get_path_at_event (SimpleFilePicker* self, GdkEventButton* event, gboolean* is_dir, gchar** full);
static gboolean ___lambda39__gtk_widget_button_press_event (GtkWidget* _sender, GdkEventButton* event, gpointer self);
static gboolean __lambda40_ (Block6Data* _data6_, GdkEventMotion* event);
static gboolean ___lambda40__gtk_widget_motion_notify_event (GtkWidget* _sender, GdkEventMotion* event, gpointer self);
static gboolean __lambda41_ (Block6Data* _data6_, GdkEventButton* event);
static void simple_file_picker_change_dir (SimpleFilePicker* self, const gchar* path, GeeSet* extensions);
static gboolean ___lambda41__gtk_widget_button_release_event (GtkWidget* _sender, GdkEventButton* event, gpointer self);
static gint ___lambda42_ (SimpleFilePicker* self, const gchar* a, const gchar* b);
static gint ____lambda42__gcompare_data_func (gconstpointer a, gconstpointer b, gpointer self);
static gint ___lambda43_ (SimpleFilePicker* self, const gchar* a, const gchar* b);
static gint ____lambda43__gcompare_data_func (gconstpointer a, gconstpointer b, gpointer self);
static void g_cclosure_user_marshal_VOID__STRING_STRING (GClosure * closure, GValue * return_value, guint n_param_values, const GValue * param_values, gpointer invocation_hint, gpointer marshal_data);
static void simple_file_picker_finalize (GObject* obj);


static gpointer _g_object_ref0 (gpointer self) {
	return self ? g_object_ref (self) : NULL;
}


static Block6Data* block6_data_ref (Block6Data* _data6_) {
	g_atomic_int_inc (&_data6_->_ref_count_);
	return _data6_;
}


static void block6_data_unref (void * _userdata_) {
	Block6Data* _data6_;
	_data6_ = (Block6Data*) _userdata_;
	if (g_atomic_int_dec_and_test (&_data6_->_ref_count_)) {
		SimpleFilePicker* self;
		self = _data6_->self;
		_g_free0 (_data6_->full);
		_g_object_unref0 (_data6_->scrolled);
		_g_object_unref0 (_data6_->ext);
		_g_object_unref0 (self);
		g_slice_free (Block6Data, _data6_);
	}
}


static void __lambda36_ (SimpleFilePicker* self, GtkObject* event) {
	const gchar* _tmp0_ = NULL;
	g_return_if_fail (event != NULL);
	_tmp0_ = self->priv->current_dir;
	g_signal_emit_by_name (self, "file-selected", NULL, _tmp0_);
}


static void ___lambda36__gtk_object_destroy (GtkObject* _sender, gpointer self) {
	__lambda36_ ((SimpleFilePicker*) self, _sender);
}


static void __lambda37_ (SimpleFilePicker* self) {
	gtk_object_destroy ((GtkObject*) self);
}


static void ___lambda37__gtk_button_clicked (GtkButton* _sender, gpointer self) {
	__lambda37_ ((SimpleFilePicker*) self);
}


static gboolean __lambda38_ (SimpleFilePicker* self, GdkEventScroll* event) {
	gboolean result = FALSE;
	g_return_val_if_fail (event != NULL, FALSE);
	result = TRUE;
	return result;
}


static gboolean ___lambda38__gtk_widget_scroll_event (GtkWidget* _sender, GdkEventScroll* event, gpointer self) {
	gboolean result;
	result = __lambda38_ ((SimpleFilePicker*) self, event);
	return result;
}


static gboolean __lambda39_ (Block6Data* _data6_, GdkEventButton* event) {
	SimpleFilePicker* self;
	gboolean result = FALSE;
	FILE* _tmp0_ = NULL;
	GdkEventButton _tmp1_ = {0};
	gdouble _tmp2_ = 0.0;
	GdkEventButton _tmp3_ = {0};
	gdouble _tmp4_ = 0.0;
	GdkEventButton _tmp5_ = {0};
	guint32 _tmp6_ = 0U;
	GdkEventButton _tmp7_ = {0};
	gdouble _tmp8_ = 0.0;
	GdkEventButton _tmp9_ = {0};
	gdouble _tmp10_ = 0.0;
	GdkEventButton _tmp11_ = {0};
	guint32 _tmp12_ = 0U;
	GdkEventButton _tmp13_ = {0};
	guint32 _tmp14_ = 0U;
	gchar* _full = NULL;
	GdkEventButton _tmp15_ = {0};
	gchar* _tmp16_ = NULL;
	gboolean _tmp17_ = FALSE;
	self = _data6_->self;
	g_return_val_if_fail (event != NULL, FALSE);
	_tmp0_ = stdout;
	_tmp1_ = *event;
	_tmp2_ = _tmp1_.x;
	_tmp3_ = *event;
	_tmp4_ = _tmp3_.y;
	_tmp5_ = *event;
	_tmp6_ = _tmp5_.time;
	fprintf (_tmp0_, "button_press_event: x: %f y: %f time: %d\n", _tmp2_, _tmp4_, (gint) _tmp6_);
	_tmp7_ = *event;
	_tmp8_ = _tmp7_.y;
	_data6_->press_y = _tmp8_;
	_tmp9_ = *event;
	_tmp10_ = _tmp9_.y;
	_data6_->last_y = _tmp10_;
	_tmp11_ = *event;
	_tmp12_ = _tmp11_.time;
	_data6_->press_time = _tmp12_;
	_tmp13_ = *event;
	_tmp14_ = _tmp13_.time;
	_data6_->last_time = _tmp14_;
	_data6_->is_dragging = FALSE;
	_tmp15_ = *event;
	_tmp17_ = simple_file_picker_get_path_at_event (self, &_tmp15_, NULL, &_tmp16_);
	_g_free0 (_full);
	_full = _tmp16_;
	if (_tmp17_) {
		const gchar* _tmp18_ = NULL;
		gchar* _tmp19_ = NULL;
		_tmp18_ = _full;
		_tmp19_ = g_strdup (_tmp18_);
		_g_free0 (_data6_->full);
		_data6_->full = _tmp19_;
	}
	result = FALSE;
	_g_free0 (_full);
	return result;
}


static gboolean ___lambda39__gtk_widget_button_press_event (GtkWidget* _sender, GdkEventButton* event, gpointer self) {
	gboolean result;
	result = __lambda39_ (self, event);
	return result;
}


static gboolean __lambda40_ (Block6Data* _data6_, GdkEventMotion* event) {
	SimpleFilePicker* self;
	gboolean result = FALSE;
	GdkEventMotion _tmp0_ = {0};
	GdkModifierType _tmp1_ = 0;
	self = _data6_->self;
	g_return_val_if_fail (event != NULL, FALSE);
	_tmp0_ = *event;
	_tmp1_ = _tmp0_.state;
	if ((_tmp1_ & GDK_BUTTON1_MASK) != 0) {
		GtkAdjustment* vadj = NULL;
		GtkScrolledWindow* _tmp2_ = NULL;
		GtkAdjustment* _tmp3_ = NULL;
		GtkAdjustment* _tmp4_ = NULL;
		gint s_height = 0;
		GtkScrolledWindow* _tmp5_ = NULL;
		GtkAllocation _tmp6_ = {0};
		gint _tmp7_ = 0;
		gdouble delta = 0.0;
		gdouble _tmp8_ = 0.0;
		GdkEventMotion _tmp9_ = {0};
		gdouble _tmp10_ = 0.0;
		gboolean _tmp11_ = FALSE;
		gboolean _tmp12_ = FALSE;
		gboolean _tmp13_ = FALSE;
		gboolean _tmp33_ = FALSE;
		gboolean _tmp34_ = FALSE;
		gdouble _tmp35_ = 0.0;
		gdouble _tmp46_ = 0.0;
		GdkEventMotion _tmp47_ = {0};
		gdouble _tmp48_ = 0.0;
		_tmp2_ = _data6_->scrolled;
		_tmp3_ = gtk_scrolled_window_get_vadjustment (_tmp2_);
		_tmp4_ = _g_object_ref0 (_tmp3_);
		vadj = _tmp4_;
		_tmp5_ = _data6_->scrolled;
		_tmp6_ = ((GtkWidget*) _tmp5_)->allocation;
		_tmp7_ = _tmp6_.height;
		s_height = _tmp7_;
		_tmp8_ = _data6_->last_y;
		_tmp9_ = *event;
		_tmp10_ = _tmp9_.y;
		delta = _tmp8_ - _tmp10_;
		_tmp13_ = _data6_->is_dragging;
		if (_tmp13_) {
			GtkAdjustment* _tmp14_ = NULL;
			gdouble _tmp15_ = 0.0;
			gdouble _tmp16_ = 0.0;
			gdouble _tmp17_ = 0.0;
			_tmp14_ = vadj;
			_tmp15_ = gtk_adjustment_get_value (_tmp14_);
			_tmp16_ = _tmp15_;
			_tmp17_ = delta;
			_tmp12_ = (_tmp16_ + _tmp17_) > ((gdouble) 0);
		} else {
			_tmp12_ = FALSE;
		}
		if (_tmp12_) {
			GtkAdjustment* _tmp18_ = NULL;
			gdouble _tmp19_ = 0.0;
			gdouble _tmp20_ = 0.0;
			gint _tmp21_ = 0;
			GtkAdjustment* _tmp22_ = NULL;
			gdouble _tmp23_ = 0.0;
			gdouble _tmp24_ = 0.0;
			gdouble _tmp25_ = 0.0;
			_tmp18_ = vadj;
			_tmp19_ = gtk_adjustment_get_upper (_tmp18_);
			_tmp20_ = _tmp19_;
			_tmp21_ = s_height;
			_tmp22_ = vadj;
			_tmp23_ = gtk_adjustment_get_value (_tmp22_);
			_tmp24_ = _tmp23_;
			_tmp25_ = delta;
			_tmp11_ = (_tmp20_ - _tmp21_) > (_tmp24_ + _tmp25_);
		} else {
			_tmp11_ = FALSE;
		}
		if (_tmp11_) {
			GtkAdjustment* _tmp26_ = NULL;
			GtkAdjustment* _tmp27_ = NULL;
			gdouble _tmp28_ = 0.0;
			gdouble _tmp29_ = 0.0;
			gdouble _tmp30_ = 0.0;
			GtkScrolledWindow* _tmp31_ = NULL;
			GtkAdjustment* _tmp32_ = NULL;
			_tmp26_ = vadj;
			_tmp27_ = vadj;
			_tmp28_ = gtk_adjustment_get_value (_tmp27_);
			_tmp29_ = _tmp28_;
			_tmp30_ = delta;
			gtk_adjustment_set_value (_tmp26_, _tmp29_ + _tmp30_);
			_tmp31_ = _data6_->scrolled;
			_tmp32_ = vadj;
			gtk_scrolled_window_set_vadjustment (_tmp31_, _tmp32_);
		}
		_tmp35_ = _data6_->_delta;
		if (_tmp35_ < ((gdouble) 0)) {
			gdouble _tmp36_ = 0.0;
			_tmp36_ = delta;
			_tmp34_ = _tmp36_ > ((gdouble) 0);
		} else {
			_tmp34_ = FALSE;
		}
		if (_tmp34_) {
			_tmp33_ = TRUE;
		} else {
			gboolean _tmp37_ = FALSE;
			gdouble _tmp38_ = 0.0;
			_tmp38_ = _data6_->_delta;
			if (_tmp38_ > ((gdouble) 0)) {
				gdouble _tmp39_ = 0.0;
				_tmp39_ = delta;
				_tmp37_ = _tmp39_ < ((gdouble) 0);
			} else {
				_tmp37_ = FALSE;
			}
			_tmp33_ = _tmp37_;
		}
		if (_tmp33_) {
			FILE* _tmp40_ = NULL;
			gdouble _tmp41_ = 0.0;
			GdkEventMotion _tmp42_ = {0};
			gdouble _tmp43_ = 0.0;
			GdkEventMotion _tmp44_ = {0};
			guint32 _tmp45_ = 0U;
			_tmp40_ = stdout;
			_tmp41_ = delta;
			fprintf (_tmp40_, "switched direction motion_notify_event delta %f\n", _tmp41_);
			_tmp42_ = *event;
			_tmp43_ = _tmp42_.y;
			_data6_->press_y = _tmp43_;
			_tmp44_ = *event;
			_tmp45_ = _tmp44_.time;
			_data6_->press_time = _tmp45_;
		}
		_tmp46_ = delta;
		_data6_->_delta = _tmp46_;
		_tmp47_ = *event;
		_tmp48_ = _tmp47_.y;
		_data6_->last_y = _tmp48_;
		_data6_->is_dragging = TRUE;
		_g_object_unref0 (vadj);
	}
	result = FALSE;
	return result;
}


static gboolean ___lambda40__gtk_widget_motion_notify_event (GtkWidget* _sender, GdkEventMotion* event, gpointer self) {
	gboolean result;
	result = __lambda40_ (self, event);
	return result;
}


static gboolean __lambda41_ (Block6Data* _data6_, GdkEventButton* event) {
	SimpleFilePicker* self;
	gboolean result = FALSE;
	gdouble delta_y = 0.0;
	GdkEventButton _tmp0_ = {0};
	gdouble _tmp1_ = 0.0;
	gdouble _tmp2_ = 0.0;
	gdouble delta_t = 0.0;
	GdkEventButton _tmp3_ = {0};
	guint32 _tmp4_ = 0U;
	guint32 _tmp5_ = 0U;
	FILE* _tmp6_ = NULL;
	GdkEventButton _tmp7_ = {0};
	gdouble _tmp8_ = 0.0;
	GdkEventButton _tmp9_ = {0};
	gdouble _tmp10_ = 0.0;
	gdouble _tmp11_ = 0.0;
	gdouble _tmp12_ = 0.0;
	GdkEventButton _tmp13_ = {0};
	guint32 _tmp14_ = 0U;
	GdkEventButton _tmp15_ = {0};
	gdouble _tmp16_ = 0.0;
	gdouble _tmp17_ = 0.0;
	gdouble _tmp18_ = 0.0;
	gboolean is_dir = FALSE;
	gchar* _full = NULL;
	gboolean _tmp19_ = FALSE;
	GdkEventButton _tmp20_ = {0};
	gboolean _tmp21_ = FALSE;
	gchar* _tmp22_ = NULL;
	gboolean _tmp23_ = FALSE;
	gboolean _tmp26_ = FALSE;
	self = _data6_->self;
	g_return_val_if_fail (event != NULL, FALSE);
	_tmp0_ = *event;
	_tmp1_ = _tmp0_.y;
	_tmp2_ = _data6_->press_y;
	delta_y = _tmp1_ - _tmp2_;
	_tmp3_ = *event;
	_tmp4_ = _tmp3_.time;
	_tmp5_ = _data6_->press_time;
	delta_t = (gdouble) (_tmp4_ - _tmp5_);
	_tmp6_ = stdout;
	_tmp7_ = *event;
	_tmp8_ = _tmp7_.x;
	_tmp9_ = *event;
	_tmp10_ = _tmp9_.y;
	_tmp11_ = delta_y;
	_tmp12_ = delta_t;
	_tmp13_ = *event;
	_tmp14_ = _tmp13_.time;
	fprintf (_tmp6_, "button_release_event: x: %f y: %f delta_y: %f delta_t: %f time: %d\n", _tmp8_, _tmp10_, _tmp11_, _tmp12_, (gint) _tmp14_);
	_tmp15_ = *event;
	_tmp16_ = _tmp15_.y;
	_tmp17_ = _data6_->press_y;
	_tmp18_ = fabs (_tmp16_ - _tmp17_);
	if (_tmp18_ > ((gdouble) 5)) {
		result = FALSE;
		return result;
	}
	_tmp20_ = *event;
	_tmp23_ = simple_file_picker_get_path_at_event (self, &_tmp20_, &_tmp21_, &_tmp22_);
	is_dir = _tmp21_;
	_g_free0 (_full);
	_full = _tmp22_;
	if (!_tmp23_) {
		_tmp19_ = TRUE;
	} else {
		const gchar* _tmp24_ = NULL;
		const gchar* _tmp25_ = NULL;
		_tmp24_ = _data6_->full;
		_tmp25_ = _full;
		_tmp19_ = g_strcmp0 (_tmp24_, _tmp25_) != 0;
	}
	if (_tmp19_) {
		result = FALSE;
		_g_free0 (_full);
		return result;
	}
	_tmp26_ = is_dir;
	if (_tmp26_) {
		const gchar* _tmp27_ = NULL;
		GeeSet* _tmp28_ = NULL;
		GtkTreePath* _path = NULL;
		GtkTreePath* _tmp29_ = NULL;
		GtkTreeView* _tmp30_ = NULL;
		GtkTreePath* _tmp31_ = NULL;
		_tmp27_ = _data6_->full;
		_tmp28_ = _data6_->ext;
		simple_file_picker_change_dir (self, _tmp27_, _tmp28_);
		_tmp29_ = gtk_tree_path_new_from_indices (0, -1, -1);
		_path = _tmp29_;
		_tmp30_ = self->priv->tree;
		_tmp31_ = _path;
		gtk_tree_view_scroll_to_cell (_tmp30_, _tmp31_, NULL, TRUE, 0.0f, 0.0f);
		_gtk_tree_path_free0 (_path);
	} else {
		gulong _tmp32_ = 0UL;
		const gchar* _tmp33_ = NULL;
		const gchar* _tmp34_ = NULL;
		_tmp32_ = _data6_->destroy_handler_id;
		g_signal_handler_disconnect ((GObject*) self, _tmp32_);
		_tmp33_ = _data6_->full;
		_tmp34_ = self->priv->current_dir;
		g_signal_emit_by_name (self, "file-selected", _tmp33_, _tmp34_);
		gtk_object_destroy ((GtkObject*) self);
	}
	result = FALSE;
	_g_free0 (_full);
	return result;
}


static gboolean ___lambda41__gtk_widget_button_release_event (GtkWidget* _sender, GdkEventButton* event, gpointer self) {
	gboolean result;
	result = __lambda41_ (self, event);
	return result;
}


SimpleFilePicker* simple_file_picker_construct (GType object_type, GtkWindow* parent, GeeSet* ext, const gchar* start_dir, GError** error) {
	SimpleFilePicker * self = NULL;
	Block6Data* _data6_;
	GeeSet* _tmp0_ = NULL;
	GeeSet* _tmp1_ = NULL;
	gchar* ui_template = NULL;
	gchar* _tmp2_ = NULL;
	GtkBuilder* builder = NULL;
	GtkBuilder* _tmp3_ = NULL;
	gint _tmp4_ = 0;
	gint _tmp5_ = 0;
	GtkWindow* _tmp6_ = NULL;
	GtkVBox* main_vbox = NULL;
	GObject* _tmp8_ = NULL;
	GtkVBox* _tmp9_ = NULL;
	GtkVBox* _tmp10_ = NULL;
	GObject* _tmp11_ = NULL;
	GtkLabel* _tmp12_ = NULL;
	GObject* _tmp13_ = NULL;
	GtkScrolledWindow* _tmp14_ = NULL;
	GtkListStore* _tmp15_ = NULL;
	GObject* _tmp16_ = NULL;
	GtkTreeView* _tmp17_ = NULL;
	GtkTreeView* _tmp18_ = NULL;
	GtkTreeView* _tmp19_ = NULL;
	GtkTreeView* _tmp20_ = NULL;
	GtkListStore* _tmp21_ = NULL;
	GtkCellRendererText* renderer = NULL;
	GtkCellRendererText* _tmp22_ = NULL;
	GtkCellRendererText* _tmp23_ = NULL;
	GValue _tmp24_ = {0};
	GtkCellRendererText* _tmp25_ = NULL;
	GtkCellRendererText* _tmp26_ = NULL;
	GtkTreeViewColumn* col = NULL;
	GtkTreeViewColumn* _tmp27_ = NULL;
	GtkTreeViewColumn* _tmp28_ = NULL;
	GtkCellRendererText* _tmp29_ = NULL;
	GtkTreeViewColumn* _tmp30_ = NULL;
	GtkCellRendererText* _tmp31_ = NULL;
	GtkTreeView* _tmp32_ = NULL;
	GtkTreeViewColumn* _tmp33_ = NULL;
	GtkTreeView* _tmp34_ = NULL;
	GtkTreeSelection* _tmp35_ = NULL;
	GtkButton* cancel_button = NULL;
	GObject* _tmp36_ = NULL;
	GtkButton* _tmp37_ = NULL;
	gulong _tmp38_ = 0UL;
	GtkButton* _tmp39_ = NULL;
	GtkTreeView* _tmp40_ = NULL;
	gchar* _tmp41_ = NULL;
	GtkTreeView* _tmp42_ = NULL;
	GtkTreeView* _tmp43_ = NULL;
	GtkTreeView* _tmp44_ = NULL;
	gchar* _tmp45_ = NULL;
	const gchar* _tmp46_ = NULL;
	gchar* _tmp50_ = NULL;
	const gchar* _tmp51_ = NULL;
	GeeSet* _tmp52_ = NULL;
	GError * _inner_error_ = NULL;
	g_return_val_if_fail (parent != NULL, NULL);
	g_return_val_if_fail (ext != NULL, NULL);
	g_return_val_if_fail (start_dir != NULL, NULL);
	_data6_ = g_slice_new0 (Block6Data);
	_data6_->_ref_count_ = 1;
	_tmp0_ = ext;
	_tmp1_ = _g_object_ref0 (_tmp0_);
	_g_object_unref0 (_data6_->ext);
	_data6_->ext = _tmp1_;
	self = (SimpleFilePicker*) g_object_new (object_type, NULL);
	_data6_->self = g_object_ref (self);
	gtk_window_set_title ((GtkWindow*) self, "L:A_N:application_ID:gambatte_PC:N_O:URL_DM:PZ_O:U");
	_tmp2_ = g_strdup ("\n" \
"        <interface>\n" \
"            <object class=\"GtkVBox\" id=\"main_vbox\">\n" \
"                <property name=\"border_width\">10</property>\n" \
"                <property name=\"spacing\">5</property>\n" \
"                <child>\n" \
"                    <object class=\"GtkHBox\" id=\"hbox1\">\n" \
"                        <child>\n" \
"                            <object class=\"GtkButton\" id=\"cancel_bu" \
"tton\">\n" \
"                                <property name=\"label\" translatable=" \
"\"yes\">cancel</property>\n" \
"                            </object>\n" \
"                            <packing>\n" \
"                                <property name=\"expand\">False</prope" \
"rty>\n" \
"                                <property name=\"fill\">False</propert" \
"y>\n" \
"                            </packing>\n" \
"                        </child>\n" \
"                        <child>\n" \
"                            <object class=\"GtkLabel\" id=\"label1\">\n" \
"                                <property name=\"label\" translatable=" \
"\"yes\">label</property>\n" \
"                            </object>\n" \
"                            <packing>\n" \
"                                <property name=\"expand\">False</prope" \
"rty>\n" \
"                                <property name=\"fill\">False</propert" \
"y>\n" \
"                                <property name=\"padding\">10</propert" \
"y>\n" \
"                            </packing>\n" \
"                        </child>\n" \
"                    </object>\n" \
"                    <packing>\n" \
"                        <property name=\"expand\">False</property>\n" \
"                        <property name=\"fill\">False</property>\n" \
"                    </packing>\n" \
"                </child>              \n" \
"                <child>\n" \
"                    <object class=\"GtkScrolledWindow\" id=\"scrolledw" \
"indow1\">\n" \
"                        <property name=\"hscrollbar_policy\">never</pr" \
"operty>\n" \
"                        <child>\n" \
"                            <object class=\"GtkTreeView\" id=\"treevie" \
"w1\">\n" \
"                            </object>\n" \
"                        </child>\n" \
"                    </object>\n" \
"                    <packing>\n" \
"                    </packing>\n" \
"                </child>              \n" \
"            </object>\n" \
"        </interface>        \n" \
"        ");
	ui_template = _tmp2_;
	_tmp3_ = gtk_builder_new ();
	builder = _tmp3_;
	_tmp4_ = strlen (ui_template);
	_tmp5_ = _tmp4_;
	gtk_builder_add_from_string (builder, ui_template, (gsize) _tmp5_, &_inner_error_);
	if (G_UNLIKELY (_inner_error_ != NULL)) {
		g_propagate_error (error, _inner_error_);
		_g_object_unref0 (builder);
		_g_free0 (ui_template);
		block6_data_unref (_data6_);
		_data6_ = NULL;
		_g_object_unref0 (self);
		return NULL;
	}
	_tmp6_ = parent;
	if (_tmp6_ != NULL) {
		GtkWindow* _tmp7_ = NULL;
		_tmp7_ = parent;
		gtk_window_set_transient_for ((GtkWindow*) self, _tmp7_);
		gtk_window_set_modal ((GtkWindow*) self, TRUE);
	}
	_tmp8_ = gtk_builder_get_object (builder, "main_vbox");
	_tmp9_ = _g_object_ref0 (G_TYPE_CHECK_INSTANCE_TYPE (_tmp8_, GTK_TYPE_VBOX) ? ((GtkVBox*) _tmp8_) : NULL);
	main_vbox = _tmp9_;
	_tmp10_ = main_vbox;
	gtk_container_add ((GtkContainer*) self, (GtkWidget*) _tmp10_);
	_tmp11_ = gtk_builder_get_object (builder, "label1");
	_tmp12_ = _g_object_ref0 (G_TYPE_CHECK_INSTANCE_TYPE (_tmp11_, GTK_TYPE_LABEL) ? ((GtkLabel*) _tmp11_) : NULL);
	_g_object_unref0 (self->priv->path_label);
	self->priv->path_label = _tmp12_;
	_tmp13_ = gtk_builder_get_object (builder, "scrolledwindow1");
	_tmp14_ = _g_object_ref0 (G_TYPE_CHECK_INSTANCE_TYPE (_tmp13_, GTK_TYPE_SCROLLED_WINDOW) ? ((GtkScrolledWindow*) _tmp13_) : NULL);
	_data6_->scrolled = _tmp14_;
	_tmp15_ = gtk_list_store_new (3, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_BOOLEAN);
	_g_object_unref0 (self->priv->store);
	self->priv->store = _tmp15_;
	_tmp16_ = gtk_builder_get_object (builder, "treeview1");
	_tmp17_ = _g_object_ref0 (G_TYPE_CHECK_INSTANCE_TYPE (_tmp16_, GTK_TYPE_TREE_VIEW) ? ((GtkTreeView*) _tmp16_) : NULL);
	_g_object_unref0 (self->priv->tree);
	self->priv->tree = _tmp17_;
	_tmp18_ = self->priv->tree;
	gtk_tree_view_set_headers_visible (_tmp18_, FALSE);
	_tmp19_ = self->priv->tree;
	gtk_tree_view_set_rules_hint (_tmp19_, FALSE);
	_tmp20_ = self->priv->tree;
	_tmp21_ = self->priv->store;
	gtk_tree_view_set_model (_tmp20_, (GtkTreeModel*) _tmp21_);
	_tmp22_ = (GtkCellRendererText*) gtk_cell_renderer_text_new ();
	g_object_ref_sink (_tmp22_);
	renderer = _tmp22_;
	_tmp23_ = renderer;
	g_value_init (&_tmp24_, G_TYPE_STRING);
	g_value_set_string (&_tmp24_, "Sans 16");
	g_object_set_property ((GObject*) _tmp23_, "font", &_tmp24_);
	G_IS_VALUE (&_tmp24_) ? (g_value_unset (&_tmp24_), NULL) : NULL;
	_tmp25_ = renderer;
	g_object_set (_tmp25_, "wrap-mode", PANGO_WRAP_WORD_CHAR, NULL);
	_tmp26_ = renderer;
	gtk_cell_renderer_set_padding ((GtkCellRenderer*) _tmp26_, 6, 8);
	_tmp27_ = gtk_tree_view_column_new ();
	g_object_ref_sink (_tmp27_);
	col = _tmp27_;
	_tmp28_ = col;
	_tmp29_ = renderer;
	gtk_cell_layout_pack_start ((GtkCellLayout*) _tmp28_, (GtkCellRenderer*) _tmp29_, TRUE);
	_tmp30_ = col;
	_tmp31_ = renderer;
	gtk_cell_layout_add_attribute ((GtkCellLayout*) _tmp30_, (GtkCellRenderer*) _tmp31_, "text", 0);
	_tmp32_ = self->priv->tree;
	_tmp33_ = col;
	gtk_tree_view_append_column (_tmp32_, _tmp33_);
	_tmp34_ = self->priv->tree;
	_tmp35_ = gtk_tree_view_get_selection (_tmp34_);
	gtk_tree_selection_set_mode (_tmp35_, GTK_SELECTION_SINGLE);
	_tmp36_ = gtk_builder_get_object (builder, "cancel_button");
	_tmp37_ = _g_object_ref0 (G_TYPE_CHECK_INSTANCE_TYPE (_tmp36_, GTK_TYPE_BUTTON) ? ((GtkButton*) _tmp36_) : NULL);
	cancel_button = _tmp37_;
	_tmp38_ = g_signal_connect_object ((GtkObject*) self, "destroy", (GCallback) ___lambda36__gtk_object_destroy, self, 0);
	_data6_->destroy_handler_id = _tmp38_;
	_tmp39_ = cancel_button;
	g_signal_connect_object (_tmp39_, "clicked", (GCallback) ___lambda37__gtk_button_clicked, self, 0);
	_tmp40_ = self->priv->tree;
	g_signal_connect_object ((GtkWidget*) _tmp40_, "scroll-event", (GCallback) ___lambda38__gtk_widget_scroll_event, self, 0);
	_tmp41_ = g_strdup ("");
	_data6_->full = _tmp41_;
	_data6_->is_dragging = FALSE;
	_data6_->press_y = -1.0;
	_data6_->press_time = (guint32) 0;
	_data6_->last_y = -1.0;
	_data6_->last_time = (guint32) 0;
	_tmp42_ = self->priv->tree;
	g_signal_connect_data ((GtkWidget*) _tmp42_, "button-press-event", (GCallback) ___lambda39__gtk_widget_button_press_event, block6_data_ref (_data6_), (GClosureNotify) block6_data_unref, 0);
	_data6_->_delta = 0.0;
	_tmp43_ = self->priv->tree;
	g_signal_connect_data ((GtkWidget*) _tmp43_, "motion-notify-event", (GCallback) ___lambda40__gtk_widget_motion_notify_event, block6_data_ref (_data6_), (GClosureNotify) block6_data_unref, 0);
	_tmp44_ = self->priv->tree;
	g_signal_connect_data ((GtkWidget*) _tmp44_, "button-release-event", (GCallback) ___lambda41__gtk_widget_button_release_event, block6_data_ref (_data6_), (GClosureNotify) block6_data_unref, 0);
	_tmp46_ = start_dir;
	if (_tmp46_ != NULL) {
		const gchar* _tmp47_ = NULL;
		gchar* _tmp48_ = NULL;
		_tmp47_ = start_dir;
		_tmp48_ = g_strdup (_tmp47_);
		_g_free0 (_tmp45_);
		_tmp45_ = _tmp48_;
	} else {
		gchar* _tmp49_ = NULL;
		_tmp49_ = g_get_current_dir ();
		_g_free0 (_tmp45_);
		_tmp45_ = _tmp49_;
	}
	_tmp50_ = g_strdup (_tmp45_);
	_g_free0 (self->priv->cwd);
	self->priv->cwd = _tmp50_;
	_tmp51_ = self->priv->cwd;
	_tmp52_ = _data6_->ext;
	simple_file_picker_change_dir (self, _tmp51_, _tmp52_);
	gtk_widget_show_all ((GtkWidget*) self);
	_g_free0 (_tmp45_);
	_g_object_unref0 (cancel_button);
	_g_object_unref0 (col);
	_g_object_unref0 (renderer);
	_g_object_unref0 (main_vbox);
	_g_object_unref0 (builder);
	_g_free0 (ui_template);
	block6_data_unref (_data6_);
	_data6_ = NULL;
	return self;
}


SimpleFilePicker* simple_file_picker_new (GtkWindow* parent, GeeSet* ext, const gchar* start_dir, GError** error) {
	return simple_file_picker_construct (TYPE_SIMPLE_FILE_PICKER, parent, ext, start_dir, error);
}


static gboolean simple_file_picker_get_path_at_event (SimpleFilePicker* self, GdkEventButton* event, gboolean* is_dir, gchar** full) {
	gboolean _vala_is_dir = FALSE;
	gchar* _vala_full = NULL;
	gboolean result = FALSE;
	gint tx = 0;
	GdkEventButton _tmp0_ = {0};
	gdouble _tmp1_ = 0.0;
	gint ty = 0;
	GdkEventButton _tmp2_ = {0};
	gdouble _tmp3_ = 0.0;
	GtkTreePath* path = NULL;
	GtkTreeViewColumn* column = NULL;
	gint cx = 0;
	gint cy = 0;
	GtkTreeView* _tmp4_ = NULL;
	gint _tmp5_ = 0;
	gint _tmp6_ = 0;
	GtkTreePath* _tmp7_ = NULL;
	GtkTreeViewColumn* _tmp8_ = NULL;
	gint _tmp9_ = 0;
	gint _tmp10_ = 0;
	gboolean _tmp11_ = FALSE;
	GtkTreeViewColumn* _tmp12_ = NULL;
	GtkTreeIter iter = {0};
	GtkTreeModel* model = NULL;
	GtkTreeView* _tmp13_ = NULL;
	GtkTreeModel* _tmp14_ = NULL;
	GtkTreeModel* _tmp15_ = NULL;
	GtkTreeModel* _tmp16_ = NULL;
	GtkTreePath* _tmp17_ = NULL;
	GtkTreeIter _tmp18_ = {0};
	gboolean _tmp19_ = FALSE;
	GtkListStore* _tmp20_ = NULL;
	GtkTreeIter _tmp21_ = {0};
	g_return_val_if_fail (self != NULL, FALSE);
	g_return_val_if_fail (event != NULL, FALSE);
	_tmp0_ = *event;
	_tmp1_ = _tmp0_.x;
	tx = (gint) _tmp1_;
	_tmp2_ = *event;
	_tmp3_ = _tmp2_.y;
	ty = (gint) _tmp3_;
	_tmp4_ = self->priv->tree;
	_tmp5_ = tx;
	_tmp6_ = ty;
	_tmp11_ = gtk_tree_view_get_path_at_pos (_tmp4_, _tmp5_, _tmp6_, &_tmp7_, &_tmp8_, &_tmp9_, &_tmp10_);
	_gtk_tree_path_free0 (path);
	path = _tmp7_;
	_g_object_unref0 (column);
	_tmp12_ = _g_object_ref0 (_tmp8_);
	column = _tmp12_;
	cx = _tmp9_;
	cy = _tmp10_;
	if (!_tmp11_) {
		result = FALSE;
		_g_object_unref0 (column);
		_gtk_tree_path_free0 (path);
		if (is_dir) {
			*is_dir = _vala_is_dir;
		}
		if (full) {
			*full = _vala_full;
		} else {
			_g_free0 (_vala_full);
		}
		return result;
	}
	_tmp13_ = self->priv->tree;
	_tmp14_ = gtk_tree_view_get_model (_tmp13_);
	_tmp15_ = _g_object_ref0 (_tmp14_);
	model = _tmp15_;
	_tmp16_ = model;
	_tmp17_ = path;
	_tmp19_ = gtk_tree_model_get_iter (_tmp16_, &_tmp18_, _tmp17_);
	iter = _tmp18_;
	if (!_tmp19_) {
		result = FALSE;
		_g_object_unref0 (model);
		_g_object_unref0 (column);
		_gtk_tree_path_free0 (path);
		if (is_dir) {
			*is_dir = _vala_is_dir;
		}
		if (full) {
			*full = _vala_full;
		} else {
			_g_free0 (_vala_full);
		}
		return result;
	}
	_tmp20_ = self->priv->store;
	_tmp21_ = iter;
	gtk_tree_model_get ((GtkTreeModel*) _tmp20_, &_tmp21_, 2, &_vala_is_dir, 1, &_vala_full, -1);
	result = TRUE;
	_g_object_unref0 (model);
	_g_object_unref0 (column);
	_gtk_tree_path_free0 (path);
	if (is_dir) {
		*is_dir = _vala_is_dir;
	}
	if (full) {
		*full = _vala_full;
	} else {
		_g_free0 (_vala_full);
	}
	return result;
}


static gint ___lambda42_ (SimpleFilePicker* self, const gchar* a, const gchar* b) {
	gint result = 0;
	gint _tmp0_ = 0;
	const gchar* _tmp1_ = NULL;
	const gchar* _tmp2_ = NULL;
	g_return_val_if_fail (a != NULL, 0);
	g_return_val_if_fail (b != NULL, 0);
	_tmp1_ = a;
	_tmp2_ = b;
	if (g_strcmp0 (_tmp1_, _tmp2_) == 0) {
		_tmp0_ = 0;
	} else {
		gint _tmp3_ = 0;
		const gchar* _tmp4_ = NULL;
		const gchar* _tmp5_ = NULL;
		_tmp4_ = a;
		_tmp5_ = b;
		if (g_strcmp0 (_tmp4_, _tmp5_) > 0) {
			_tmp3_ = 1;
		} else {
			_tmp3_ = -1;
		}
		_tmp0_ = _tmp3_;
	}
	result = _tmp0_;
	return result;
}


static gint ____lambda42__gcompare_data_func (gconstpointer a, gconstpointer b, gpointer self) {
	gint result;
	result = ___lambda42_ ((SimpleFilePicker*) self, (const gchar*) a, (const gchar*) b);
	return result;
}


static gint ___lambda43_ (SimpleFilePicker* self, const gchar* a, const gchar* b) {
	gint result = 0;
	gint _tmp0_ = 0;
	const gchar* _tmp1_ = NULL;
	const gchar* _tmp2_ = NULL;
	g_return_val_if_fail (a != NULL, 0);
	g_return_val_if_fail (b != NULL, 0);
	_tmp1_ = a;
	_tmp2_ = b;
	if (g_strcmp0 (_tmp1_, _tmp2_) == 0) {
		_tmp0_ = 0;
	} else {
		gint _tmp3_ = 0;
		const gchar* _tmp4_ = NULL;
		const gchar* _tmp5_ = NULL;
		_tmp4_ = a;
		_tmp5_ = b;
		if (g_strcmp0 (_tmp4_, _tmp5_) > 0) {
			_tmp3_ = 1;
		} else {
			_tmp3_ = -1;
		}
		_tmp0_ = _tmp3_;
	}
	result = _tmp0_;
	return result;
}


static gint ____lambda43__gcompare_data_func (gconstpointer a, gconstpointer b, gpointer self) {
	gint result;
	result = ___lambda43_ ((SimpleFilePicker*) self, (const gchar*) a, (const gchar*) b);
	return result;
}


static void simple_file_picker_change_dir (SimpleFilePicker* self, const gchar* path, GeeSet* extensions) {
	const gchar* _tmp0_ = NULL;
	gchar* _tmp1_ = NULL;
	GError * _inner_error_ = NULL;
	g_return_if_fail (self != NULL);
	g_return_if_fail (path != NULL);
	g_return_if_fail (extensions != NULL);
	_tmp0_ = path;
	_tmp1_ = g_strdup (_tmp0_);
	_g_free0 (self->priv->current_dir);
	self->priv->current_dir = _tmp1_;
	{
		GtkListStore* _tmp2_ = NULL;
		const gchar* _tmp3_ = NULL;
		GeeArrayList* dirs = NULL;
		GeeArrayList* _tmp11_ = NULL;
		GeeArrayList* files = NULL;
		GeeArrayList* _tmp12_ = NULL;
		GDir* dir = NULL;
		const gchar* _tmp13_ = NULL;
		GDir* _tmp14_ = NULL;
		gchar* name = NULL;
		GeeArrayList* _tmp41_ = NULL;
		GeeArrayList* _tmp42_ = NULL;
		const gchar* _tmp85_ = NULL;
		gchar* _tmp86_ = NULL;
		GtkLabel* _tmp87_ = NULL;
		const gchar* _tmp88_ = NULL;
		_tmp2_ = self->priv->store;
		gtk_list_store_clear (_tmp2_);
		_tmp3_ = path;
		if (g_strcmp0 (_tmp3_, "/") != 0) {
			GtkTreeIter pit = {0};
			GtkListStore* _tmp4_ = NULL;
			GtkTreeIter _tmp5_ = {0};
			GtkListStore* _tmp6_ = NULL;
			GtkTreeIter _tmp7_ = {0};
			const gchar* _tmp8_ = NULL;
			gchar* _tmp9_ = NULL;
			gchar* _tmp10_ = NULL;
			_tmp4_ = self->priv->store;
			gtk_list_store_append (_tmp4_, &_tmp5_);
			pit = _tmp5_;
			_tmp6_ = self->priv->store;
			_tmp7_ = pit;
			_tmp8_ = path;
			_tmp9_ = g_path_get_dirname (_tmp8_);
			_tmp10_ = _tmp9_;
			gtk_list_store_set (_tmp6_, &_tmp7_, 0, "..", 1, _tmp10_, 2, TRUE, -1);
			_g_free0 (_tmp10_);
		}
		_tmp11_ = gee_array_list_new (G_TYPE_STRING, (GBoxedCopyFunc) g_strdup, g_free, NULL, NULL, NULL);
		dirs = _tmp11_;
		_tmp12_ = gee_array_list_new (G_TYPE_STRING, (GBoxedCopyFunc) g_strdup, g_free, NULL, NULL, NULL);
		files = _tmp12_;
		_tmp13_ = path;
		_tmp14_ = g_dir_open (_tmp13_, (guint) 0, &_inner_error_);
		dir = _tmp14_;
		if (G_UNLIKELY (_inner_error_ != NULL)) {
			_g_object_unref0 (files);
			_g_object_unref0 (dirs);
			goto __catch47_g_error;
		}
		while (TRUE) {
			GDir* _tmp15_ = NULL;
			const gchar* _tmp16_ = NULL;
			gchar* _tmp17_ = NULL;
			const gchar* _tmp18_ = NULL;
			gchar* full = NULL;
			const gchar* _tmp19_ = NULL;
			const gchar* _tmp20_ = NULL;
			gchar* _tmp21_ = NULL;
			gboolean is_dir = FALSE;
			const gchar* _tmp22_ = NULL;
			gboolean _tmp23_ = FALSE;
			gboolean _tmp24_ = FALSE;
			_tmp15_ = dir;
			_tmp16_ = g_dir_read_name (_tmp15_);
			_tmp17_ = g_strdup (_tmp16_);
			_g_free0 (name);
			name = _tmp17_;
			_tmp18_ = name;
			if (!(_tmp18_ != NULL)) {
				break;
			}
			_tmp19_ = path;
			_tmp20_ = name;
			_tmp21_ = g_build_filename (_tmp19_, _tmp20_, NULL);
			full = _tmp21_;
			_tmp22_ = full;
			_tmp23_ = g_file_test (_tmp22_, G_FILE_TEST_IS_DIR);
			is_dir = _tmp23_;
			_tmp24_ = is_dir;
			if (_tmp24_) {
				GeeArrayList* _tmp25_ = NULL;
				const gchar* _tmp26_ = NULL;
				_tmp25_ = dirs;
				_tmp26_ = name;
				gee_abstract_collection_add ((GeeAbstractCollection*) _tmp25_, _tmp26_);
				_g_free0 (full);
				continue;
			}
			{
				GeeIterator* _suffix_it = NULL;
				GeeSet* _tmp27_ = NULL;
				GeeIterator* _tmp28_ = NULL;
				_tmp27_ = extensions;
				_tmp28_ = gee_iterable_iterator ((GeeIterable*) _tmp27_);
				_suffix_it = _tmp28_;
				while (TRUE) {
					GeeIterator* _tmp29_ = NULL;
					gboolean _tmp30_ = FALSE;
					gchar* suffix = NULL;
					GeeIterator* _tmp31_ = NULL;
					gpointer _tmp32_ = NULL;
					const gchar* _tmp33_ = NULL;
					const gchar* _tmp34_ = NULL;
					gchar* _tmp35_ = NULL;
					gchar* _tmp36_ = NULL;
					gboolean _tmp37_ = FALSE;
					gboolean _tmp38_ = FALSE;
					_tmp29_ = _suffix_it;
					_tmp30_ = gee_iterator_next (_tmp29_);
					if (!_tmp30_) {
						break;
					}
					_tmp31_ = _suffix_it;
					_tmp32_ = gee_iterator_get (_tmp31_);
					suffix = (gchar*) _tmp32_;
					_tmp33_ = name;
					_tmp34_ = suffix;
					_tmp35_ = g_strconcat (".", _tmp34_, NULL);
					_tmp36_ = _tmp35_;
					_tmp37_ = g_str_has_suffix (_tmp33_, _tmp36_);
					_tmp38_ = _tmp37_;
					_g_free0 (_tmp36_);
					if (_tmp38_) {
						GeeArrayList* _tmp39_ = NULL;
						const gchar* _tmp40_ = NULL;
						_tmp39_ = files;
						_tmp40_ = name;
						gee_abstract_collection_add ((GeeAbstractCollection*) _tmp39_, _tmp40_);
						_g_free0 (suffix);
						break;
					}
					_g_free0 (suffix);
				}
				_g_object_unref0 (_suffix_it);
			}
			_g_free0 (full);
		}
		_tmp41_ = dirs;
		gee_list_sort ((GeeList*) _tmp41_, ____lambda42__gcompare_data_func, g_object_ref (self), g_object_unref);
		_tmp42_ = files;
		gee_list_sort ((GeeList*) _tmp42_, ____lambda43__gcompare_data_func, g_object_ref (self), g_object_unref);
		{
			GeeArrayList* _d_list = NULL;
			GeeArrayList* _tmp43_ = NULL;
			GeeArrayList* _tmp44_ = NULL;
			gint _d_size = 0;
			GeeArrayList* _tmp45_ = NULL;
			gint _tmp46_ = 0;
			gint _tmp47_ = 0;
			gint _d_index = 0;
			_tmp43_ = dirs;
			_tmp44_ = _g_object_ref0 (_tmp43_);
			_d_list = _tmp44_;
			_tmp45_ = _d_list;
			_tmp46_ = gee_abstract_collection_get_size ((GeeCollection*) _tmp45_);
			_tmp47_ = _tmp46_;
			_d_size = _tmp47_;
			_d_index = -1;
			while (TRUE) {
				gint _tmp48_ = 0;
				gint _tmp49_ = 0;
				gint _tmp50_ = 0;
				gchar* d = NULL;
				GeeArrayList* _tmp51_ = NULL;
				gint _tmp52_ = 0;
				gpointer _tmp53_ = NULL;
				gchar* full = NULL;
				const gchar* _tmp54_ = NULL;
				const gchar* _tmp55_ = NULL;
				gchar* _tmp56_ = NULL;
				GtkTreeIter it = {0};
				GtkListStore* _tmp57_ = NULL;
				GtkTreeIter _tmp58_ = {0};
				GtkListStore* _tmp59_ = NULL;
				GtkTreeIter _tmp60_ = {0};
				const gchar* _tmp61_ = NULL;
				gchar* _tmp62_ = NULL;
				gchar* _tmp63_ = NULL;
				const gchar* _tmp64_ = NULL;
				_tmp48_ = _d_index;
				_d_index = _tmp48_ + 1;
				_tmp49_ = _d_index;
				_tmp50_ = _d_size;
				if (!(_tmp49_ < _tmp50_)) {
					break;
				}
				_tmp51_ = _d_list;
				_tmp52_ = _d_index;
				_tmp53_ = gee_abstract_list_get ((GeeAbstractList*) _tmp51_, _tmp52_);
				d = (gchar*) _tmp53_;
				_tmp54_ = path;
				_tmp55_ = d;
				_tmp56_ = g_build_filename (_tmp54_, _tmp55_, NULL);
				full = _tmp56_;
				_tmp57_ = self->priv->store;
				gtk_list_store_append (_tmp57_, &_tmp58_);
				it = _tmp58_;
				_tmp59_ = self->priv->store;
				_tmp60_ = it;
				_tmp61_ = d;
				_tmp62_ = g_strconcat (_tmp61_, "/", NULL);
				_tmp63_ = _tmp62_;
				_tmp64_ = full;
				gtk_list_store_set (_tmp59_, &_tmp60_, 0, _tmp63_, 1, _tmp64_, 2, TRUE, -1);
				_g_free0 (_tmp63_);
				_g_free0 (full);
				_g_free0 (d);
			}
			_g_object_unref0 (_d_list);
		}
		{
			GeeArrayList* _f_list = NULL;
			GeeArrayList* _tmp65_ = NULL;
			GeeArrayList* _tmp66_ = NULL;
			gint _f_size = 0;
			GeeArrayList* _tmp67_ = NULL;
			gint _tmp68_ = 0;
			gint _tmp69_ = 0;
			gint _f_index = 0;
			_tmp65_ = files;
			_tmp66_ = _g_object_ref0 (_tmp65_);
			_f_list = _tmp66_;
			_tmp67_ = _f_list;
			_tmp68_ = gee_abstract_collection_get_size ((GeeCollection*) _tmp67_);
			_tmp69_ = _tmp68_;
			_f_size = _tmp69_;
			_f_index = -1;
			while (TRUE) {
				gint _tmp70_ = 0;
				gint _tmp71_ = 0;
				gint _tmp72_ = 0;
				gchar* f = NULL;
				GeeArrayList* _tmp73_ = NULL;
				gint _tmp74_ = 0;
				gpointer _tmp75_ = NULL;
				gchar* full = NULL;
				const gchar* _tmp76_ = NULL;
				const gchar* _tmp77_ = NULL;
				gchar* _tmp78_ = NULL;
				GtkTreeIter it = {0};
				GtkListStore* _tmp79_ = NULL;
				GtkTreeIter _tmp80_ = {0};
				GtkListStore* _tmp81_ = NULL;
				GtkTreeIter _tmp82_ = {0};
				const gchar* _tmp83_ = NULL;
				const gchar* _tmp84_ = NULL;
				_tmp70_ = _f_index;
				_f_index = _tmp70_ + 1;
				_tmp71_ = _f_index;
				_tmp72_ = _f_size;
				if (!(_tmp71_ < _tmp72_)) {
					break;
				}
				_tmp73_ = _f_list;
				_tmp74_ = _f_index;
				_tmp75_ = gee_abstract_list_get ((GeeAbstractList*) _tmp73_, _tmp74_);
				f = (gchar*) _tmp75_;
				_tmp76_ = path;
				_tmp77_ = f;
				_tmp78_ = g_build_filename (_tmp76_, _tmp77_, NULL);
				full = _tmp78_;
				_tmp79_ = self->priv->store;
				gtk_list_store_append (_tmp79_, &_tmp80_);
				it = _tmp80_;
				_tmp81_ = self->priv->store;
				_tmp82_ = it;
				_tmp83_ = f;
				_tmp84_ = full;
				gtk_list_store_set (_tmp81_, &_tmp82_, 0, _tmp83_, 1, _tmp84_, 2, FALSE, -1);
				_g_free0 (full);
				_g_free0 (f);
			}
			_g_object_unref0 (_f_list);
		}
		_tmp85_ = path;
		_tmp86_ = g_strdup (_tmp85_);
		_g_free0 (self->priv->cwd);
		self->priv->cwd = _tmp86_;
		_tmp87_ = self->priv->path_label;
		_tmp88_ = self->priv->cwd;
		gtk_label_set_label (_tmp87_, _tmp88_);
		_g_free0 (name);
		_g_dir_close0 (dir);
		_g_object_unref0 (files);
		_g_object_unref0 (dirs);
	}
	goto __finally47;
	__catch47_g_error:
	{
		GError* e = NULL;
		FILE* _tmp89_ = NULL;
		const gchar* _tmp90_ = NULL;
		GError* _tmp91_ = NULL;
		const gchar* _tmp92_ = NULL;
		e = _inner_error_;
		_inner_error_ = NULL;
		_tmp89_ = stderr;
		_tmp90_ = path;
		_tmp91_ = e;
		_tmp92_ = _tmp91_->message;
		fprintf (_tmp89_, "Cannot open directory %s: %s\n", _tmp90_, _tmp92_);
		_g_error_free0 (e);
	}
	__finally47:
	{
	}
	if (G_UNLIKELY (_inner_error_ != NULL)) {
		g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
		g_clear_error (&_inner_error_);
		return;
	}
}


static void g_cclosure_user_marshal_VOID__STRING_STRING (GClosure * closure, GValue * return_value, guint n_param_values, const GValue * param_values, gpointer invocation_hint, gpointer marshal_data) {
	typedef void (*GMarshalFunc_VOID__STRING_STRING) (gpointer data1, const char* arg_1, const char* arg_2, gpointer data2);
	register GMarshalFunc_VOID__STRING_STRING callback;
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
	callback = (GMarshalFunc_VOID__STRING_STRING) (marshal_data ? marshal_data : cc->callback);
	callback (data1, g_value_get_string (param_values + 1), g_value_get_string (param_values + 2), data2);
}


static void simple_file_picker_class_init (SimpleFilePickerClass * klass) {
	simple_file_picker_parent_class = g_type_class_peek_parent (klass);
	g_type_class_add_private (klass, sizeof (SimpleFilePickerPrivate));
	G_OBJECT_CLASS (klass)->finalize = simple_file_picker_finalize;
	g_signal_new ("file_selected", TYPE_SIMPLE_FILE_PICKER, G_SIGNAL_RUN_LAST, 0, NULL, NULL, g_cclosure_user_marshal_VOID__STRING_STRING, G_TYPE_NONE, 2, G_TYPE_STRING, G_TYPE_STRING);
}


static void simple_file_picker_instance_init (SimpleFilePicker * self) {
	self->priv = SIMPLE_FILE_PICKER_GET_PRIVATE (self);
}


static void simple_file_picker_finalize (GObject* obj) {
	SimpleFilePicker * self;
	self = G_TYPE_CHECK_INSTANCE_CAST (obj, TYPE_SIMPLE_FILE_PICKER, SimpleFilePicker);
	_g_object_unref0 (self->priv->store);
	_g_object_unref0 (self->priv->tree);
	_g_free0 (self->priv->cwd);
	_g_object_unref0 (self->priv->path_label);
	_g_free0 (self->priv->current_dir);
	G_OBJECT_CLASS (simple_file_picker_parent_class)->finalize (obj);
}


GType simple_file_picker_get_type (void) {
	static volatile gsize simple_file_picker_type_id__volatile = 0;
	if (g_once_init_enter (&simple_file_picker_type_id__volatile)) {
		static const GTypeInfo g_define_type_info = { sizeof (SimpleFilePickerClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) simple_file_picker_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (SimpleFilePicker), 0, (GInstanceInitFunc) simple_file_picker_instance_init, NULL };
		GType simple_file_picker_type_id;
		simple_file_picker_type_id = g_type_register_static (GTK_TYPE_WINDOW, "SimpleFilePicker", &g_define_type_info, 0);
		g_once_init_leave (&simple_file_picker_type_id__volatile, simple_file_picker_type_id);
	}
	return simple_file_picker_type_id__volatile;
}



