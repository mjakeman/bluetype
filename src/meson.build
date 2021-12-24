bluetype_sources = [
    'bl-window.c',
    'bl-application.c',
    'bl-document-view.c',
    'bl-document-text.c',

    # Text Sources
    'text/text-node.c',
    'text/text-block.c',
    'text/text-list.c'
]

bluetype_deps = [
    dependency('gtk4'),
    dependency('libadwaita-1')
]

gnome = import('gnome')

blueprints = custom_target('blueprints',
  input: files(
    'bl-window.blp'
  ),
  output: '.',
  command: [find_program('gtk-blueprint-tool'), 'batch-compile', '@OUTPUT@', '@INPUT@'],
)

# Create a static library so we can test it
libbluetype = static_library('bluetype',
    bluetype_sources,
    dependencies: bluetype_deps,
    install: false,
)

bluetype_dep = declare_dependency(
  link_with: libbluetype,
  dependencies: bluetype_deps
)

# Compile resources into executable
bluetype_resources = gnome.compile_resources('bluetype-resources',
    'bluetype.gresource.xml',
    dependencies: blueprints,
    c_name: 'bluetype'
)

executable('bluetype',
    [
        'main.c',
        bluetype_resources,
    ],
    dependencies: bluetype_dep,
    install: true,
)
