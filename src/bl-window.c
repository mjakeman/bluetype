/* bl-window.c
 *
 * Copyright 2022 Matthew Jakeman <mjakeman26@outlook.co.nz>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#define G_LOG_DOMAIN "bluetype-window"

#include "bl-config.h"
#include "bl-window.h"

#include <text-engine/ui/display.h>
#include <text-engine/format/import.h>

struct _BlWindow
{
  GtkApplicationWindow  parent_instance;

  /* Template widgets */
  GtkHeaderBar        *header_bar;
  TextDisplay         *textview;
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
    TextDocument *document;
    TextFrame *frame;
    gchar *test;

    g_type_ensure (TEXT_TYPE_DISPLAY);

    gtk_widget_init_template (GTK_WIDGET (self));

    // test = "<p><i><b>Beowulf</b></i> (<span class=\"rt-commentedText nowrap\"><span class=\"IPA nopopups noexcerpt\"><a href=\"/wiki/Help:IPA/English\" title=\"Help:IPA/English\">/<span style=\"border-bottom:1px dotted\"><span title=\"/ˈ/: primary stress follows\">ˈ</span><span title=\"&#39;b&#39; in &#39;buy&#39;\">b</span><span title=\"/eɪ/: &#39;a&#39; in &#39;face&#39;\">eɪ</span><span title=\"/ə/: &#39;a&#39; in &#39;about&#39;\">ə</span><span title=\"&#39;w&#39; in &#39;wind&#39;\">w</span><span title=\"/ʊ/: &#39;u&#39; in &#39;push&#39;\">ʊ</span><span title=\"&#39;l&#39; in &#39;lie&#39;\">l</span><span title=\"&#39;f&#39; in &#39;find&#39;\">f</span></span>/</a></span></span>;<sup id=\"cite_ref-1\" class=\"reference\"><a href=\"#cite_note-1\">&#91;1&#93;</a></sup> <a href=\"/wiki/Old_English_language\" class=\"mw-redirect\" title=\"Old English language\">Old English</a>&#58; <span title=\"Old English (ca. 450-1100)-language text\"><i lang=\"ang\">Bēowulf</i></span> <small></small><span title=\"Representation in the International Phonetic Alphabet (IPA)\" class=\"IPA\"><a href=\"/wiki/Help:IPA/Old_English\" title=\"Help:IPA/Old English\">[ˈbeːowuɫf]</a></span>) is an Old English <a href=\"/wiki/Epic_poetry\" title=\"Epic poetry\">epic poem</a> in the tradition of <a href=\"/wiki/Germanic_heroic_legend\" title=\"Germanic heroic legend\">Germanic heroic legend</a> consisting of 3,182 <a href=\"/wiki/Alliterative_verse\" title=\"Alliterative verse\">alliterative lines</a>. It is one of the most important and <a href=\"/wiki/List_of_translations_of_Beowulf\" title=\"List of translations of Beowulf\">most often translated</a> works of <a href=\"/wiki/Old_English_literature\" title=\"Old English literature\">Old English literature</a>. The date of composition is a matter of contention among scholars; the only certain dating is for the manuscript, which was produced between 975 and 1025.<sup id=\"cite_ref-FOOTNOTEStanley19819–22_2-0\" class=\"reference\"><a href=\"#cite_note-FOOTNOTEStanley19819–22-2\">&#91;2&#93;</a></sup> Scholars call the anonymous author the \"<i>Beowulf</i> poet\".<sup id=\"cite_ref-FOOTNOTERobinson2002143_3-0\" class=\"reference\"><a href=\"#cite_note-FOOTNOTERobinson2002143-3\">&#91;3&#93;</a></sup><br><p>Source: wikipedia.org [CC BY-SA 3.0]</p>";
    test = "<p>There was an Old Man with <b>a</b> beard</p><p>Who said, &quot;It is just as I feared!</p><p> &gt; Two Owls and a Hen,<br> &gt; Four Larks and a Wren,</p><p>Have all built their nests in my beard!&quot;</p>";
    frame = format_parse_html (test);
    document = text_document_new ();
    document->frame = frame;

    g_object_set (self->textview, "document", document, NULL);
}
