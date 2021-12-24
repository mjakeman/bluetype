/* text-node.h
 *
 * Copyright 2021 Matthew Jakeman <mjakeman26@outlook.co.nz>
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * SPDX-License-Identifier: MPL-2.0
 */

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
TextNode *text_node_get_parent (TextNode *self);

// TODO: Private API - For Implementors only!
void text_node_append_child (TextNode *self, TextNode *child);

G_END_DECLS
