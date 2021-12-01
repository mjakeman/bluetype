#include <glib.h>
#include <locale.h>

#include "../src/text/text-block.h"

typedef struct {
  TextBlock *obj;
  // OtherObject *helper;
} TextFixture;

static void
text_fixture_set_up (TextFixture   *fixture,
                     gconstpointer  initial_text)
{
    fixture->obj = text_block_new (initial_text);
}

static void
text_fixture_tear_down (TextFixture   *fixture,
                        gconstpointer  user_data)
{
    g_clear_object (&fixture->obj);
}

static void
test_text_test1 (TextFixture   *fixture,
                 gconstpointer  user_data)
{
    char *contents;
    g_object_get (fixture->obj, "contents", &contents, NULL);
    g_assert_cmpstr (contents, ==, (char *)user_data);
}

int
main (int argc, char *argv[])
{
    setlocale (LC_ALL, "");

    g_test_init (&argc, &argv, NULL);

    // Define the tests.
    g_test_add ("/text/test1", TextFixture, "Sample text goes here...",
                text_fixture_set_up, test_text_test1,
                text_fixture_tear_down);

    return g_test_run ();
}
