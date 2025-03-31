project('cutils', 'c')

cutils_src = files(
    'src/array.c',
    'src/mmframes.c',
    'src/nlog.c',
    'src/cutil_string.c',
    'src/nano_timer.c',
)

cutils_include = include_directories('include/')

libcutils = library('cutils', cutils_src, 
    include_directories: cutils_include
)
