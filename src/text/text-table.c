/* text-table.c
 *
 * Copyright 2021 Matthew Jakeman <mjakeman26@outlook.co.nz>
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#include "text-table.h"

struct _TextTable
{
    TextNode parent_instance;

    int rows;
    int cols;
};

G_DEFINE_FINAL_TYPE (TextTable, text_table, TEXT_TYPE_NODE)

enum {
    PROP_0,
    PROP_ROWS,
    PROP_COLS,
    N_PROPS
};

static GParamSpec *properties [N_PROPS];

TextTable *
text_table_new (int rows, int cols)
{
    return g_object_new (TEXT_TYPE_TABLE,
                         "rows", rows,
                         "cols", cols,
                         NULL);
}

static void
text_table_finalize (GObject *object)
{
    TextTable *self = (TextTable *)object;

    G_OBJECT_CLASS (text_table_parent_class)->finalize (object);
}

static void
text_table_get_property (GObject    *object,
                         guint       prop_id,
                         GValue     *value,
                         GParamSpec *pspec)
{
    TextTable *self = TEXT_TABLE (object);

    switch (prop_id)
    {
    case PROP_ROWS:
        g_value_set_int (value, self->rows);
        return;
    case PROP_COLS:
        g_value_set_int (value, self->cols);
        return;
    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
text_table_set_property (GObject      *object,
                         guint         prop_id,
                         const GValue *value,
                         GParamSpec   *pspec)
{
    TextTable *self = TEXT_TABLE (object);

    switch (prop_id)
    {
    case PROP_ROWS:
        self->rows = g_value_get_int (value);
        return;
    case PROP_COLS:
        self->cols = g_value_get_int (value);
        return;
    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
text_table_class_init (TextTableClass *klass)
{
    GObjectClass *object_class = G_OBJECT_CLASS (klass);

    object_class->finalize = text_table_finalize;
    object_class->get_property = text_table_get_property;
    object_class->set_property = text_table_set_property;

    properties [PROP_ROWS] =
        g_param_spec_int ("rows",
                          "Rows",
                          "Rows",
                          1, G_MAXINT, 2,
                          G_PARAM_READWRITE|G_PARAM_CONSTRUCT_ONLY);

    properties [PROP_COLS] =
        g_param_spec_int ("cols",
                          "Cols",
                          "Cols",
                          1, G_MAXINT, 2,
                          G_PARAM_READWRITE|G_PARAM_CONSTRUCT_ONLY);

    g_object_class_install_properties (object_class, N_PROPS, properties);
}

static void
text_table_init (TextTable *self)
{
}
