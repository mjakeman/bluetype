/* bl-document-text.h
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

#define BL_TYPE_DOCUMENT_TEXT (bl_document_text_get_type())

G_DECLARE_FINAL_TYPE (BlDocumentText, bl_document_text, BL, DOCUMENT_TEXT, GObject)

BlDocumentText *bl_document_text_new (void);
GList *bl_document_text_get_blocks (BlDocumentText *self);

G_END_DECLS
