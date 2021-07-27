project('cq', 'c', default_options:['warning_level=3'])


libcqsrcs = files(['src/extensions.c', 'src/cache.c', 'src/info.c'])
libcqinc = include_directories('include')
libcq = static_library('libcq', sources: [libcqsrcs], include_directories: libcqinc)

cq_dep = declare_dependency(link_with : libcq,
                               include_directories: libcqinc)

executable('cq', sources: 'src/main.c', dependencies: [cq_dep])

# Python extension
py = import('python')
py3 = py.find_installation('python3')
pydep = py3.dependency()
py3.extension_module('pycq', 'src/pycq.c', dependencies: [pydep, cq_dep])
