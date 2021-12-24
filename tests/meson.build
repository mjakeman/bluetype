test(
    'text',
    executable('text', 'text.c', dependencies: bluetype_dep),
    env: [
        'G_TEST_SRCDIR=@0@'.format(meson.current_source_dir()),
        'G_TEST_BUILDDIR=@0@'.format(meson.current_build_dir()),
    ],
)
