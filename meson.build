project('CrunchLuaSol', 'cpp', default_options : ['cpp_std=c++14'])

#remove this rather bogus warning
add_global_arguments('-Wno-missing-braces', language: 'cpp')

incDirs = include_directories('.')

install_headers('CrunchLuaSol/CrunchLuaSol.hpp', subdir: 'CrunchLuaSol')

subdir('Tests')
