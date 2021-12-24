#include "bl-document-view.h"

#include "bl-document-text.h"

#include "text/text.h"

#include <pango/pango.h>

struct _BlDocumentView
{
    GtkWidget parent_instance;

    BlDocumentText *doc;
    GtkIMContext *im_context;

    // TODO: Very temporary - replace with BlDocumentText
    GtkEntryBuffer *buffer;
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

    g_object_unref (g_steal_pointer (&self->doc));
    g_object_unref (g_steal_pointer (&self->im_context));

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
text_block_snapshot (TextBlock    *block,
                     PangoContext *context,
                     int           width,
                     GtkSnapshot  *snapshot)
{
    char *text;
    g_object_get (block,
                  "contents", &text,
                  NULL);

    g_print ("Buffer: %s\n", text);

    GdkRGBA black;
    gdk_rgba_parse (&black, "black");

    PangoLayout *layout = pango_layout_new (context);
    pango_layout_set_text (layout, text, -1);
    pango_layout_set_width (layout, width * PANGO_SCALE);
    pango_layout_set_wrap (layout, PANGO_WRAP_WORD_CHAR);

    int index =  pango_layout_get_line_count (layout) - 1;
    PangoLayoutLine* last_line = pango_layout_get_line (layout, index);

    int height, spacing;
    pango_layout_line_get_height (last_line, &height);
    spacing = (height / PANGO_SCALE) * 0.5f;

    int descent;
    pango_layout_get_pixel_size (layout, NULL, &descent);

    gtk_snapshot_append_layout (snapshot, layout, &black);
    gtk_snapshot_translate (snapshot, &GRAPHENE_POINT_INIT (0, descent + spacing));

    g_object_unref (layout);
}

static void
text_list_snapshot (TextList     *list,
                    PangoContext *context,
                    int           width,
                    GtkSnapshot  *snapshot)
{
    gtk_snapshot_translate (snapshot, &GRAPHENE_POINT_INIT (50, 0));

    TextNode *node;
    for (node = text_node_get_first_child (TEXT_NODE (list));
         node != NULL;
         node = text_node_get_next_sibling (node))
    {
        text_block_snapshot (TEXT_BLOCK (node), context, width - 50, snapshot);
    }

    gtk_snapshot_translate (snapshot, &GRAPHENE_POINT_INIT (-50, 0));
}

static void
bl_document_view_snapshot (GtkWidget *widget, GtkSnapshot *snapshot)
{
    BlDocumentView *self = BL_DOCUMENT_VIEW (widget);

    int width = gtk_widget_get_allocated_width (widget);
    PangoContext *context = gtk_widget_get_pango_context (widget);

    GList *list = bl_document_text_get_blocks (self->doc);
    for (; list != NULL; list = list->next)
    {
        /*if (descent > height)
            return;*/

        if (TEXT_IS_LIST (list->data))
            text_list_snapshot (TEXT_LIST (list->data), context, width, snapshot);
        else if (TEXT_IS_BLOCK (list->data))
            text_block_snapshot (TEXT_BLOCK (list->data), context, width, snapshot);
        else
            g_warning ("Skipping %s\n", g_type_name_from_instance ((GTypeInstance*)list->data));

    }

    // const char *text = gtk_entry_buffer_get_text (self->buffer);
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

    widget_class->snapshot = bl_document_view_snapshot;

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
bl_document_view_commit (GtkIMContext   *im_context,
                         gchar          *str,
                         BlDocumentView *self)
{
    g_print ("Text Commit: %s\n", str);
    uint end_position = gtk_entry_buffer_get_length (self->buffer);
    gtk_entry_buffer_insert_text (self->buffer, end_position, str, -1);
    gtk_widget_queue_draw (GTK_WIDGET (self));
}

static void
bl_document_view_preedit_start (GtkIMContext   *im_context,
                                BlDocumentView *self)
{
    g_print ("Text Preedit Start\n");
}

static void
bl_document_view_preedit_changed (GtkIMContext   *im_context,
                                  BlDocumentView *self)
{
    g_print ("Text Preedit Changed\n");
}

static void
bl_document_view_preedit_end (GtkIMContext   *im_context,
                              BlDocumentView *self)
{
    g_print ("Text Preedit End\n");
}

static void
bl_document_view_retrieve_surrounding (GtkIMContext   *im_context,
                                       BlDocumentView *self)
{
    g_print ("Text Preedit Retrieve Surrounding\n");
}

static gboolean
bl_document_view_delete_surrounding (GtkIMContext   *im_context,
                                     gint            offset,
                                     gint            n_chars,
                                     BlDocumentView *self)
{
    g_print ("Text Preedit Delete Surrounding\n");
}


static void
bl_document_view_pressed (GtkGestureClick *gesture,
                          int              n_press,
                          double           x,
                          double           y,
                          BlDocumentView  *self)
{
    gtk_widget_grab_focus (GTK_WIDGET (self));
}


static void
bl_document_view_init (BlDocumentView *self)
{
    self->doc = bl_document_text_new ();
    self->buffer = gtk_entry_buffer_new (NULL, -1);

    // Widget Properties
    gtk_widget_set_focusable (GTK_WIDGET (self), TRUE);
    gtk_widget_set_can_focus (GTK_WIDGET (self), TRUE);
    gtk_widget_set_focus_on_click (GTK_WIDGET (self), TRUE);
    gtk_widget_set_cursor_from_name (GTK_WIDGET (self), "text");

    // Setup Input Method
    self->im_context = gtk_im_multicontext_new ();

    g_signal_connect (self->im_context, "commit",
                      G_CALLBACK (bl_document_view_commit), self);
    g_signal_connect (self->im_context, "preedit-start",
                      G_CALLBACK (bl_document_view_preedit_start), self);
    g_signal_connect (self->im_context, "preedit-changed",
                      G_CALLBACK (bl_document_view_preedit_changed), self);
    g_signal_connect (self->im_context, "preedit-end",
                      G_CALLBACK (bl_document_view_preedit_end), self);
    g_signal_connect (self->im_context, "retrieve-surrounding",
                      G_CALLBACK (bl_document_view_retrieve_surrounding), self);
    g_signal_connect (self->im_context, "delete-surrounding",
                      G_CALLBACK (bl_document_view_delete_surrounding), self);


    // Setup Event Controllers
    GtkEventController *key_controller = gtk_event_controller_key_new ();
    gtk_event_controller_key_set_im_context (GTK_EVENT_CONTROLLER_KEY (key_controller), self->im_context);
    gtk_widget_add_controller (GTK_WIDGET (self), key_controller);

    GtkGesture *click_gesture = gtk_gesture_click_new ();
    g_signal_connect (click_gesture, "pressed", G_CALLBACK (bl_document_view_pressed), self);
    gtk_widget_add_controller (GTK_WIDGET (self), GTK_EVENT_CONTROLLER (click_gesture));
}
