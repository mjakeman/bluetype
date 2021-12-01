#include "bl-document-text.h"

#include "text/text-block.h"

struct _BlDocumentText
{
    GObject parent_instance;

    // Document Model
    GList *blocks;
};

G_DEFINE_FINAL_TYPE (BlDocumentText, bl_document_text, G_TYPE_OBJECT)

enum {
    PROP_0,
    N_PROPS
};

static GParamSpec *properties [N_PROPS];

BlDocumentText *
bl_document_text_new (void)
{
    return g_object_new (BL_TYPE_DOCUMENT_TEXT, NULL);
}

static void
bl_document_text_finalize (GObject *object)
{
    BlDocumentText *self = (BlDocumentText *)object;

    G_OBJECT_CLASS (bl_document_text_parent_class)->finalize (object);
}

static void
bl_document_text_get_property (GObject    *object,
                               guint       prop_id,
                               GValue     *value,
                               GParamSpec *pspec)
{
    BlDocumentText *self = BL_DOCUMENT_TEXT (object);

    switch (prop_id)
      {
      default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      }
}

static void
bl_document_text_set_property (GObject      *object,
                               guint         prop_id,
                               const GValue *value,
                               GParamSpec   *pspec)
{
    BlDocumentText *self = BL_DOCUMENT_TEXT (object);

    switch (prop_id)
      {
      default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      }
}

static void
bl_document_text_class_init (BlDocumentTextClass *klass)
{
    GObjectClass *object_class = G_OBJECT_CLASS (klass);

    object_class->finalize = bl_document_text_finalize;
    object_class->get_property = bl_document_text_get_property;
    object_class->set_property = bl_document_text_set_property;
}

GList *
bl_document_text_get_blocks (BlDocumentText *self)
{
    return self->blocks;
}

static void
bl_document_text_init (BlDocumentText *self)
{
    self->blocks = NULL;
    self->blocks = g_list_append (self->blocks, text_block_new ("Once upon a time there was a dog called Rover."));
    self->blocks = g_list_append (self->blocks, text_block_new ("There was an Old Man with a beard / Who said, \"It is just as I feared! / Two Owls and a Hen, / Four Larks and a Wren, / Have all built their nests in my beard!\""));
}
