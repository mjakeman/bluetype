/* bl-document-view.h
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

#include <gtk/gtk.h>

G_BEGIN_DECLS

#define BL_TYPE_DOCUMENT_VIEW (bl_document_view_get_type())

G_DECLARE_FINAL_TYPE (BlDocumentView, bl_document_view, BL, DOCUMENT_VIEW, GtkWidget)

BlDocumentView *bl_document_view_new (void);

G_END_DECLS
