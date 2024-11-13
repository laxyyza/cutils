cutils_src = files(
    'src/array.c',
    'src/mmframes.c',
    'src/nlog.c',
    'src/cutil_string.c',
)

cutils_include = include_directories('include/')

libcutils = library('cutils', cutils_src, 
    include_directories: cutils_include
)
