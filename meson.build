project('cpu-query', 'c')

libquerysrcs = ['src/extensions.c', 'src/cache.c', 'src/info.c']
libqueryinc = include_directories('include')
libquery = static_library('libquery', sources: [libquerysrcs], include_directories: libqueryinc)

query_dep = declare_dependency(link_with : libquery,
                               include_directories: libqueryinc)

executable('query', sources: 'src/main.c', dependencies: [query_dep])
