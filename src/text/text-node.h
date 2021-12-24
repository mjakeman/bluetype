/* text-node.h
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
