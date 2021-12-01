#pragma once

#include <glib-object.h>

G_BEGIN_DECLS

#define TEXT_TYPE_BLOCK (text_block_get_type())

G_DECLARE_FINAL_TYPE (TextBlock, text_block, TEXT, BLOCK, GObject)

TextBlock *text_block_new (const char *initial_text);

G_END_DECLS
