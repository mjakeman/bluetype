/* bl-application.c
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

#define G_LOG_DOMAIN "bluetype-application"

#include "bl-application.h"

#include "bl-window.h"

struct _BlApplication
{
  AdwApplication parent_instance;
};

G_DEFINE_TYPE (BlApplication, bl_application, ADW_TYPE_APPLICATION)

BlApplication *
bl_application_new (gchar *application_id,
                          GApplicationFlags  flags)
{
  return g_object_new (BL_TYPE_APPLICATION,
                       "application-id", application_id,
                       "flags", flags,
                       NULL);
}

static void
bl_application_finalize (GObject *object)
{
  BlApplication *self = (BlApplication *)object;

  G_OBJECT_CLASS (bl_application_parent_class)->finalize (object);
}

static void
bl_application_activate (GApplication *app)
{
    GtkWindow *window;

    /* It's good practice to check your parameters at the beginning of the
    * function. It helps catch errors early and in development instead of
    * by your users.
    */
    g_assert (GTK_IS_APPLICATION (app));

    // Add CSS Stylesheet
    GtkCssProvider *css_provider = gtk_css_provider_new ();
    gtk_css_provider_load_from_resource (css_provider, "/com/mattjakeman/Bluetype/style.css");

    GdkDisplay *display = gdk_display_get_default ();
    gtk_style_context_add_provider_for_display (display, GTK_STYLE_PROVIDER (css_provider),
                                                GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    /* Get the current window or create one if necessary. */
    window = gtk_application_get_active_window (GTK_APPLICATION (app));
    if (window == NULL)
    window = g_object_new (BL_TYPE_WINDOW,
                           "application", app,
                           NULL);

    /* Ask the window manager/compositor to present the window. */
    gtk_window_present (window);
}


static void
bl_application_class_init (BlApplicationClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  GApplicationClass *app_class = G_APPLICATION_CLASS (klass);

  object_class->finalize = bl_application_finalize;

  /*
   * We connect to the activate callback to create a window when the application
   * has been launched. Additionally, this callback notifies us when the user
   * tries to launch a "second instance" of the application. When they try
   * to do that, we'll just present any existing window.
   */
  app_class->activate = bl_application_activate;
}

static void
bl_application_show_about (GSimpleAction *action,
                                 GVariant      *parameter,
                                 gpointer       user_data)
{
  BlApplication *self = BL_APPLICATION (user_data);
  GtkWindow *window = NULL;
  const gchar *authors[] = {"Matthew Jakeman", NULL};

  g_return_if_fail (BL_IS_APPLICATION (self));

  window = gtk_application_get_active_window (GTK_APPLICATION (self));

  gtk_show_about_dialog (window,
                         "authors", authors,
                         "comments", "A fast and lightweight word processor.",
                         "copyright", "Copyright © 2021 Matthew Jakeman",
                         "license-type", GTK_LICENSE_LGPL_3_0,
                         "logo-icon-name", "com.mattjakeman.Bluetype",
                         "program-name", "bluetype",
                         "version", "0.1.0",
                         "website", "https://github.com/mjakeman/bluetype-next",
                         NULL);
}


static void
bl_application_init (BlApplication *self)
{
    GSimpleAction *quit_action = g_simple_action_new ("quit", NULL);
    g_signal_connect_swapped (quit_action, "activate", G_CALLBACK (g_application_quit), self);
    g_action_map_add_action (G_ACTION_MAP (self), G_ACTION (quit_action));

    GSimpleAction *about_action = g_simple_action_new ("about", NULL);
    g_signal_connect (about_action, "activate", G_CALLBACK (bl_application_show_about), self);
    g_action_map_add_action (G_ACTION_MAP (self), G_ACTION (about_action));

    const char *accels[] = {"<primary>q", NULL};
    gtk_application_set_accels_for_action (GTK_APPLICATION (self), "app.quit", accels);
}
