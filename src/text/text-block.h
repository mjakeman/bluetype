/* text-block.h
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

#include "text-node.h"

G_BEGIN_DECLS

#define TEXT_TYPE_BLOCK (text_block_get_type())

G_DECLARE_FINAL_TYPE (TextBlock, text_block, TEXT, BLOCK, TextNode)

TextBlock *text_block_new (const char *initial_text);

G_END_DECLS
