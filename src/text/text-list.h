#pragma once

#include <glib-object.h>

#include "text-node.h"

G_BEGIN_DECLS

#define TEXT_TYPE_LIST (text_list_get_type())

G_DECLARE_FINAL_TYPE (TextList, text_list, TEXT, LIST, TextNode)

TextList *text_list_new (void);

G_END_DECLS
