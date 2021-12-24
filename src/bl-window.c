/* bl-window.c
 *
 * Copyright 2021 Matthew Jakeman <mjakeman26@outlook.co.nz>
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#define G_LOG_DOMAIN "bluetype-window"

#include "bl-config.h"
#include "bl-window.h"

#include "bl-document-view.h"

struct _BlWindow
{
  GtkApplicationWindow  parent_instance;

  /* Template widgets */
  GtkHeaderBar        *header_bar;
  GtkTextView            *textview;
};

G_DEFINE_TYPE (BlWindow, bl_window, GTK_TYPE_APPLICATION_WINDOW)

static void
bl_window_class_init (BlWindowClass *klass)
{
    GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

    gtk_widget_class_set_template_from_resource (widget_class, "/com/mattjakeman/Bluetype/bl-window.ui");
    gtk_widget_class_bind_template_child (widget_class, BlWindow, header_bar);
    gtk_widget_class_bind_template_child (widget_class, BlWindow, textview);
}

static void
bl_window_init (BlWindow *self)
{
    g_type_ensure (BL_TYPE_DOCUMENT_VIEW);

    gtk_widget_init_template (GTK_WIDGET (self));
}
