project('cpu-query', 'c', default_options:['warning_level=3'])


libquerysrcs = files(['src/extensions.c', 'src/cache.c', 'src/info.c'])
libqueryinc = include_directories('include')
libquery = static_library('libquery', sources: [libquerysrcs], include_directories: libqueryinc)

query_dep = declare_dependency(link_with : libquery,
                               include_directories: libqueryinc)

executable('query', sources: 'src/main.c', dependencies: [query_dep])


py = import('python')

py3 = py.find_installation('python3')

pydep = py3.dependency()
py3.extension_module('pycq', 'src/pycq.c', dependencies: [pydep, query_dep])
