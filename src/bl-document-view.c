#include "bl-document-view.h"

#include "bl-document-text.h"

struct _BlDocumentView
{
    GtkWidget parent_instance;

    BlDocumentText *doc;
};

G_DEFINE_FINAL_TYPE (BlDocumentView, bl_document_view, GTK_TYPE_WIDGET)

enum {
    PROP_0,
    PROP_DOCUMENT,
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
    case PROP_DOCUMENT:
        g_value_set_object (value, self->doc);
        break;
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
    case PROP_DOCUMENT:
        if (self->doc)
            g_object_unref (self->doc);

        self->doc = g_value_get_object (value);

        if (self->doc == NULL)
            self->doc = bl_document_text_new ();
        break;
    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
toggle_tag (BlDocumentView *self, const char *tag_name)
{
    g_print ("Set %s\n", tag_name);
}

static void
action_bold (BlDocumentView *self,
             const char     *action_name,
             GVariant       *param)
{
    toggle_tag (self, "bold");
}

static void
action_italic (BlDocumentView *self,
               const char     *action_name,
               GVariant       *param)
{
    toggle_tag (self, "italic");
}


static void
action_underline (BlDocumentView *self,
                  const char     *action_name,
                  GVariant       *param)
{
    toggle_tag (self, "underline");
}

static void
action_clear (BlDocumentView *self,
              const char     *action_name,
              GVariant       *param)
{
    g_print ("Clear\n");
}


static void
bl_document_view_class_init (BlDocumentViewClass *klass)
{
    GObjectClass *object_class = G_OBJECT_CLASS (klass);

    object_class->finalize = bl_document_view_finalize;
    object_class->get_property = bl_document_view_get_property;
    object_class->set_property = bl_document_view_set_property;

    properties [PROP_DOCUMENT]
        = g_param_spec_object ("document",
                               "Document",
                               "Document",
                               BL_TYPE_DOCUMENT_TEXT,
                               G_PARAM_READWRITE);

    g_object_class_install_properties (object_class, N_PROPS, properties);

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
bl_document_view_init (BlDocumentView *self)
{
    self->doc = bl_document_text_new ();
}
