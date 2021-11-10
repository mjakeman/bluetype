bluetype_sources = [
    'main.c',
    'bl-window.c',
    'bl-application.c',
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

bluetype_sources += gnome.compile_resources('bluetype-resources',
    'bluetype.gresource.xml',
    dependencies: blueprints,
    c_name: 'bluetype'
)

executable('bluetype', bluetype_sources,
    dependencies: bluetype_deps,
    install: true,
)
