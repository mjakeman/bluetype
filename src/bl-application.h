/* bl-application.h
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
#include <adwaita.h>

G_BEGIN_DECLS

#define BL_TYPE_APPLICATION (bl_application_get_type())

G_DECLARE_FINAL_TYPE (BlApplication, bl_application, BL, APPLICATION, AdwApplication)

BlApplication *bl_application_new (gchar *application_id,
                                               GApplicationFlags  flags);

G_END_DECLS
