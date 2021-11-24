#include "bl-document-text.h"

struct _BlDocumentText
{
    GObject parent_instance;
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

static void
bl_document_text_init (BlDocumentText *self)
{
}
