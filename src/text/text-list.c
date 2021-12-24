/* text-list.c
 *
 * Copyright 2021 Matthew Jakeman <mjakeman26@outlook.co.nz>
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#define G_LOG_DOMAIN "text-list"

#include "text-list.h"

struct _TextList
{
    TextNode parent_instance;
};

G_DEFINE_FINAL_TYPE (TextList, text_list, TEXT_TYPE_NODE)

enum {
    PROP_0,
    N_PROPS
};

static GParamSpec *properties [N_PROPS];

TextList *
text_list_new (void)
{
    return g_object_new (TEXT_TYPE_LIST, NULL);
}

static void
text_list_finalize (GObject *object)
{
    TextList *self = (TextList *)object;

    G_OBJECT_CLASS (text_list_parent_class)->finalize (object);
}

static void
text_list_get_property (GObject    *object,
                        guint       prop_id,
                        GValue     *value,
                        GParamSpec *pspec)
{
    TextList *self = TEXT_LIST (object);

    switch (prop_id)
      {
      default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      }
}

static void
text_list_set_property (GObject      *object,
                        guint         prop_id,
                        const GValue *value,
                        GParamSpec   *pspec)
{
    TextList *self = TEXT_LIST (object);

    switch (prop_id)
      {
      default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      }
}

static void
text_list_class_init (TextListClass *klass)
{
    GObjectClass *object_class = G_OBJECT_CLASS (klass);

    object_class->finalize = text_list_finalize;
    object_class->get_property = text_list_get_property;
    object_class->set_property = text_list_set_property;
}

static void
text_list_init (TextList *self)
{
}
