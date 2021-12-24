#include "text-block.h"

struct _TextBlock
{
    TextNode parent_instance;

    char *contents;
};

G_DEFINE_FINAL_TYPE (TextBlock, text_block, TEXT_TYPE_NODE)

enum {
    PROP_0,
    PROP_CONTENTS,
    N_PROPS
};

static GParamSpec *properties [N_PROPS];

TextBlock *
text_block_new (const char *initial_text)
{
    return g_object_new (TEXT_TYPE_BLOCK,
                         "contents", initial_text,
                         NULL);
}

static void
text_block_finalize (GObject *object)
{
    TextBlock *self = (TextBlock *)object;

    G_OBJECT_CLASS (text_block_parent_class)->finalize (object);
}

static void
text_block_get_property (GObject    *object,
                         guint       prop_id,
                         GValue     *value,
                         GParamSpec *pspec)
{
    TextBlock *self = TEXT_BLOCK (object);

    switch (prop_id)
    {
    case PROP_CONTENTS:
        g_value_set_string (value, self->contents);
        break;
    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
text_block_set_property (GObject      *object,
                         guint         prop_id,
                         const GValue *value,
                         GParamSpec   *pspec)
{
    TextBlock *self = TEXT_BLOCK (object);

    switch (prop_id)
    {
    case PROP_CONTENTS:
        self->contents = g_value_dup_string (value);
        break;
    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
}
}

static void
text_block_class_init (TextBlockClass *klass)
{
    GObjectClass *object_class = G_OBJECT_CLASS (klass);

    object_class->finalize = text_block_finalize;
    object_class->get_property = text_block_get_property;
    object_class->set_property = text_block_set_property;

    properties [PROP_CONTENTS]
        = g_param_spec_string ("contents",
                               "Contents",
                               "Contents",
                               NULL,
                               G_PARAM_READWRITE);

    g_object_class_install_properties (object_class, N_PROPS, properties);
}

static void
text_block_init (TextBlock *self)
{
}
