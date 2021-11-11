#include "bl-document-view.h"

struct _BlDocumentView
{
    GtkTextView parent_instance;
};

G_DEFINE_FINAL_TYPE (BlDocumentView, bl_document_view, GTK_TYPE_TEXT_VIEW)

enum {
    PROP_0,
    N_PROPS
};

static GParamSpec *properties [N_PROPS];

BlDocumentView *
bl_document_view_new (void)
{
    return g_object_new (BL_TYPE_DOCUMENT_VIEW, NULL);
}

static void
bl_document_view_finalize (GObject *object)
{
    BlDocumentView *self = (BlDocumentView *)object;

    G_OBJECT_CLASS (bl_document_view_parent_class)->finalize (object);
}

static void
bl_document_view_get_property (GObject    *object,
                               guint       prop_id,
                               GValue     *value,
                               GParamSpec *pspec)
{
    BlDocumentView *self = BL_DOCUMENT_VIEW (object);

    switch (prop_id)
      {
      default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      }
}

static void
bl_document_view_set_property (GObject      *object,
                               guint         prop_id,
                               const GValue *value,
                               GParamSpec   *pspec)
{
    BlDocumentView *self = BL_DOCUMENT_VIEW (object);

    switch (prop_id)
      {
      default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      }
}

static void
action_bold (BlDocumentView *self,
             const char     *action_name,
             GVariant       *param)
{
    GtkTextIter start_iter, end_iter;

    GtkTextBuffer *buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (self));
    gtk_text_buffer_get_selection_bounds (buffer, &start_iter, &end_iter);

    gtk_text_buffer_apply_tag_by_name (buffer, "bold", &start_iter, &end_iter);
}

static void
action_italic (BlDocumentView *self,
               const char     *action_name,
               GVariant       *param)
{
    GtkTextIter start_iter, end_iter;

    GtkTextBuffer *buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (self));
    gtk_text_buffer_get_selection_bounds (buffer, &start_iter, &end_iter);

    gtk_text_buffer_apply_tag_by_name (buffer, "italic", &start_iter, &end_iter);
}


static void
action_underline (BlDocumentView *self,
                  const char     *action_name,
                  GVariant       *param)
{
    GtkTextIter start_iter, end_iter;

    GtkTextBuffer *buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (self));
    gtk_text_buffer_get_selection_bounds (buffer, &start_iter, &end_iter);

    gtk_text_buffer_apply_tag_by_name (buffer, "underline", &start_iter, &end_iter);
}

static void
action_clear (BlDocumentView *self,
              const char     *action_name,
              GVariant       *param)
{
    GtkTextIter start_iter, end_iter;

    GtkTextBuffer *buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (self));
    gtk_text_buffer_get_selection_bounds (buffer, &start_iter, &end_iter);

    gtk_text_buffer_remove_all_tags (buffer, &start_iter, &end_iter);
}


static void
bl_document_view_class_init (BlDocumentViewClass *klass)
{
    GObjectClass *object_class = G_OBJECT_CLASS (klass);

    object_class->finalize = bl_document_view_finalize;
    object_class->get_property = bl_document_view_get_property;
    object_class->set_property = bl_document_view_set_property;

    GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

    gtk_widget_class_install_action (widget_class, "docview.bold", NULL, action_bold);
    gtk_widget_class_install_action (widget_class, "docview.italic", NULL, action_italic);
    gtk_widget_class_install_action (widget_class, "docview.underline", NULL, action_underline);
    gtk_widget_class_install_action (widget_class, "docview.clear", NULL, action_clear);

    gtk_widget_class_add_binding_action (widget_class, GDK_KEY_b, GDK_CONTROL_MASK, "docview.bold", NULL);
    gtk_widget_class_add_binding_action (widget_class, GDK_KEY_i, GDK_CONTROL_MASK, "docview.italic", NULL);
    gtk_widget_class_add_binding_action (widget_class, GDK_KEY_u, GDK_CONTROL_MASK, "docview.underline", NULL);
    gtk_widget_class_add_binding_action (widget_class, GDK_KEY_f, GDK_CONTROL_MASK|GDK_SHIFT_MASK, "docview.clear", NULL);

    gtk_widget_class_set_css_name (widget_class, "docview");
}

static void
cb_buffer_notify (BlDocumentView *self,
                  GParamSpec     *pspec)
{
    GtkTextBuffer *buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (self));

    if (!GTK_IS_TEXT_BUFFER (buffer))
        return;

    gtk_text_buffer_create_tag (buffer, "bold",
                                "weight", PANGO_WEIGHT_BOLD,
                                NULL);

    gtk_text_buffer_create_tag (buffer, "italic",
                                "style", PANGO_STYLE_ITALIC,
                                NULL);

    gtk_text_buffer_create_tag (buffer, "underline",
                                "underline", PANGO_UNDERLINE_SINGLE,
                                NULL);
}

static void
bl_document_view_init (BlDocumentView *self)
{
    g_signal_connect (self, "notify::buffer", G_CALLBACK (cb_buffer_notify), NULL);
}
