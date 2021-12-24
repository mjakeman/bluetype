/* bl-document-text.c
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

#define G_LOG_DOMAIN "bluetype-document-text"

#include "bl-document-text.h"

#include "text/text.h"

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

    TextList *node = text_list_new ();
    text_node_append_child (TEXT_NODE (node), text_block_new ("List Item :)"));
    text_node_append_child (TEXT_NODE (node), text_block_new ("Another one"));
    text_node_append_child (TEXT_NODE (node), text_block_new ("Three! How fancy"));
    self->blocks = g_list_append (self->blocks, node);

    self->blocks = g_list_append (self->blocks, text_block_new ("Laborum dolor ut quaerat nostrum illum. Itaque ex ab officia. Odit harum corporis dolor ducimus et. Accusamus illum pariatur ut quisquam maxime assumenda. Voluptatum eius ratione saepe similique."));
}
