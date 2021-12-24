/* text-node.c
 *
 * Copyright 2021 Matthew Jakeman <mjakeman26@outlook.co.nz>
 *
 * This file is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation; either version 3 of the
 * License, or (at your option) any later version.
 *
 * This file is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * SPDX-License-Identifier: LGPL-3.0-or-later
 */

#define G_LOG_DOMAIN "text-node"

#include "text-node.h"

typedef struct
{
    // Node Tree
    TextNode *first_child;
    TextNode *last_child;

    TextNode *prev_sibling;
    TextNode *next_sibling;

    TextNode *parent;

} TextNodePrivate;

G_DEFINE_TYPE_WITH_PRIVATE (TextNode, text_node, G_TYPE_OBJECT)

enum {
    PROP_0,
    N_PROPS
};

static GParamSpec *properties [N_PROPS];

/**
 * text_node_new:
 *
 * Create a new #TextNode.
 *
 * Returns: (transfer full): a newly created #TextNode
 */
TextNode *
text_node_new (void)
{
    return g_object_new (TEXT_TYPE_NODE, NULL);
}

static void
text_node_finalize (GObject *object)
{
    TextNode *self = (TextNode *)object;
    TextNodePrivate *priv = text_node_get_instance_private (self);

    G_OBJECT_CLASS (text_node_parent_class)->finalize (object);
}

static void
text_node_get_property (GObject    *object,
                        guint       prop_id,
                        GValue     *value,
                        GParamSpec *pspec)
{
    TextNode *self = TEXT_NODE (object);

    switch (prop_id)
      {
      default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      }
}

static void
text_node_set_property (GObject      *object,
                        guint         prop_id,
                        const GValue *value,
                        GParamSpec   *pspec)
{
    TextNode *self = TEXT_NODE (object);

    switch (prop_id)
      {
      default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      }
}

TextNode *
text_node_get_next_sibling (TextNode *self)
{
    TextNodePrivate *priv = text_node_get_instance_private (self);
    return priv->next_sibling;
}

TextNode *
text_node_get_prev_sibling (TextNode *self)
{
    TextNodePrivate *priv = text_node_get_instance_private (self);
    return priv->prev_sibling;
}

TextNode *
text_node_get_first_child (TextNode *self)
{
    TextNodePrivate *priv = text_node_get_instance_private (self);
    return priv->first_child;
}

TextNode *
text_node_get_last_child (TextNode *self)
{
    TextNodePrivate *priv = text_node_get_instance_private (self);
    return priv->last_child;
}

TextNode *
text_node_get_parent_node (TextNode *self)
{
    TextNodePrivate *priv = text_node_get_instance_private (self);
    return priv->parent;
}

void
text_node_append_child (TextNode *self, TextNode *child)
{
    TextNodePrivate *priv = text_node_get_instance_private (self);
    TextNodePrivate *child_priv = text_node_get_instance_private (child);

    if (priv->first_child == NULL)
    {
        priv->first_child = child;
        priv->last_child = child;
        child_priv->parent = self;
        return;
    }

    TextNode *last_child = text_node_get_last_child (self);
    TextNodePrivate *last_child_priv = text_node_get_instance_private (last_child);
    last_child_priv->next_sibling = child;
    child_priv->prev_sibling = last_child;
    child_priv->parent = self;
    priv->last_child = child;
}

void
text_node_insert_child (TextNode *self, TextNode *child)
{
    // self->first
}

static void
text_node_class_init (TextNodeClass *klass)
{
    GObjectClass *object_class = G_OBJECT_CLASS (klass);

    object_class->finalize = text_node_finalize;
    object_class->get_property = text_node_get_property;
    object_class->set_property = text_node_set_property;
}

static void
text_node_init (TextNode *self)
{
}
