bluetype_sources = [
    'main.c',
    'bl-window.c',
    'bl-application.c',
]

bluetype_deps = [
    dependency('gtk4'),
]

gnome = import('gnome')

bluetype_sources += gnome.compile_resources('bluetype-resources',
    'bluetype.gresource.xml',
    c_name: 'bluetype'
)

executable('bluetype', bluetype_sources,
    dependencies: bluetype_deps,
    install: true,
)
