cutils_src = files(
    'src/array.c',
    'src/mmframes.c',
)

cutils_include = include_directories('include/')

libcutils = library('cutils', cutils_src, 
    include_directories: cutils_include
)
