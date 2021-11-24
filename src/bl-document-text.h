#pragma once

#include <glib-object.h>

G_BEGIN_DECLS

#define BL_TYPE_DOCUMENT_TEXT (bl_document_text_get_type())

G_DECLARE_FINAL_TYPE (BlDocumentText, bl_document_text, BL, DOCUMENT_TEXT, GObject)

BlDocumentText *bl_document_text_new (void);

G_END_DECLS
