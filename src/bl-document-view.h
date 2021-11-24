#pragma once

#include <gtk/gtk.h>

G_BEGIN_DECLS

#define BL_TYPE_DOCUMENT_VIEW (bl_document_view_get_type())

G_DECLARE_FINAL_TYPE (BlDocumentView, bl_document_view, BL, DOCUMENT_VIEW, GtkWidget)

BlDocumentView *bl_document_view_new (void);

G_END_DECLS
