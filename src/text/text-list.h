/* text-list.h
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

#define TEXT_TYPE_LIST (text_list_get_type())

G_DECLARE_FINAL_TYPE (TextList, text_list, TEXT, LIST, TextNode)

TextList *text_list_new (void);

G_END_DECLS
