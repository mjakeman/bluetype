#pragma once

#include <glib-object.h>

G_BEGIN_DECLS

#define TEXT_TYPE_NODE (text_node_get_type())

G_DECLARE_DERIVABLE_TYPE (TextNode, text_node, TEXT, NODE, GObject)

struct _TextNodeClass
{
    GObjectClass parent_class;
};

TextNode *text_node_new (void);

TextNode *text_node_get_next_sibling (TextNode *self);
TextNode *text_node_get_prev_sibling (TextNode *self);
TextNode *text_node_get_first_child (TextNode *self);
TextNode *text_node_get_last_child (TextNode *self);
TextNode *text_node_get_parent_node (TextNode *self);

// TODO: Private API - For Implementors only!
void text_node_append_child (TextNode *self, TextNode *child);

G_END_DECLS
