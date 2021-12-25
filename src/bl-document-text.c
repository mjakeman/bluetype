/* bl-document-text.c
 *
 * Copyright 2021 Matthew Jakeman <mjakeman26@outlook.co.nz>
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * SPDX-License-Identifier: MPL-2.0
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
    self->blocks = g_list_append (self->blocks, text_block_new ("A limerick (/ˈlɪmərɪk/ LIM-ər-ik) is a form of verse, usually humorous and frequently rude, in five-line, predominantly anapestic trimeter with a strict rhyme scheme of AABBA, in which the first, second and fifth line rhyme, while the third and fourth lines are shorter and share a different rhyme."));
    self->blocks = g_list_append (self->blocks, text_block_new ("The following example is a limerick of unknown origin:"));

    TextList *list = text_list_new ();
    text_node_append_child (TEXT_NODE (list), text_block_new ("The limerick packs laughs anatomical"));
    text_node_append_child (TEXT_NODE (list), text_block_new ("Into space that is quite economical."));
    text_node_append_child (TEXT_NODE (list), text_block_new ("  But the good ones I've seen"));
    text_node_append_child (TEXT_NODE (list), text_block_new ("  So seldom are clean"));
    text_node_append_child (TEXT_NODE (list), text_block_new ("And the clean ones so seldom are comical."));
    self->blocks = g_list_append (self->blocks, list);

    self->blocks = g_list_append (self->blocks, text_block_new ("Source: Wikipedia [CC BY-SA 3.0]"));
    self->blocks = g_list_append (self->blocks, text_block_new ("Here's one from somewhere on the internet:"));

    list = text_list_new ();
    text_node_append_child (TEXT_NODE (list), text_block_new ("There was an Old Man with a beard"));
    text_node_append_child (TEXT_NODE (list), text_block_new ("Who said, \"It is just as I feared!"));
    text_node_append_child (TEXT_NODE (list), text_block_new ("  Two Owls and a Hen,"));
    text_node_append_child (TEXT_NODE (list), text_block_new ("  Four Larks and a Wren,"));
    text_node_append_child (TEXT_NODE (list), text_block_new ("Have all built their nests in my beard!\""));
    self->blocks = g_list_append (self->blocks, list);

    self->blocks = g_list_append (self->blocks, text_block_new ("And an old classic:"));

    list = text_list_new ();
    text_node_append_child (TEXT_NODE (list), text_block_new ("There was an old man of Blackheath"));
    text_node_append_child (TEXT_NODE (list), text_block_new ("Who sat on his set of false teeth."));
    text_node_append_child (TEXT_NODE (list), text_block_new ("  Said he, with a start,"));
    text_node_append_child (TEXT_NODE (list), text_block_new ("  \"Oh, bless my heart!"));
    text_node_append_child (TEXT_NODE (list), text_block_new ("I've bitten myself underneath!\""));
    self->blocks = g_list_append (self->blocks, list);

    TextTable *table = text_table_new (3, 3);
    text_node_append_child (TEXT_NODE (table), text_block_new ("A table is an arrangement of information or data, typically in rows and columns, or possibly in a more complex structure."));
    text_node_append_child (TEXT_NODE (table), text_block_new ("Tables are widely used in communication, research, and data analysis."));
    text_node_append_child (TEXT_NODE (table), text_block_new ("Tables appear in print media, handwritten notes, computer software, architectural ornamentation, traffic signs, and many other places."));
    text_node_append_child (TEXT_NODE (table), text_block_new ("The precise conventions and terminology for describing tables vary depending on the context."));
    text_node_append_child (TEXT_NODE (table), text_block_new ("Further, tables differ significantly in variety, structure, flexibility, notation, representation and use."));
    text_node_append_child (TEXT_NODE (table), text_block_new ("Information or data conveyed in table form is said to be in tabular format (adjective)."));
    text_node_append_child (TEXT_NODE (table), text_block_new ("In books and technical articles, tables are typically presented apart from the main text in numbered and captioned floating blocks."));
    text_node_append_child (TEXT_NODE (table), text_block_new (NULL));
    text_node_append_child (TEXT_NODE (table), text_block_new (NULL));
    self->blocks = g_list_append (self->blocks, table);
}
