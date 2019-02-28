project('CrunchLuaSol', 'cpp', default_options : ['cpp_std=c++14'])

#remove this rather bogus warning
add_project_arguments('-Wno-missing-braces', language: 'cpp')

incDirs = include_directories('.')

# meseon dependency function to find lua is not very consistent accross platforms yet, so
# we need to do a lot of manual lifting for now
foreach name : ['lua', 'lua5.3', 'lua-5.3', 'lua53']
    luaDep = dependency(name, version: '>=5.3', required: false)
    if luaDep.found()
        break
    endif
endforeach

if not luaDep.found()
    error('Lua could not be found!')
endif

incDirs = include_directories('.')

install_headers('CrunchLuaSol/CrunchLuaSol.hpp', subdir: 'CrunchLuaSol')

cc = meson.get_compiler('cpp')
if get_option('buildSubmodules') == false
    stickDep = cc.find_library('Stick')
    crunchLuaDeps = [stickDep, dependency('threads')]
else
    stickProj = subproject('Stick')
    crunchProj = subproject('Crunch')
    crunchLuaDeps = [stickProj.get_variable('stickDep'), crunchProj.get_variable('crunchDep')]
endif

if host_machine.system() == 'linux'
    crunchLuaDeps += cc.find_library('dl', required : true)
endif

crunchLuaDeps += luaDep

crunchLua = library('CrunchLuaSol', 
        'CrunchLuaSol/CrunchLuaSol.cpp',
        dependencies: crunchLuaDeps, 
        include_directories : incDirs,
        install: true)

crunchLuaDep = declare_dependency(link_with : crunchLua, 
    dependencies: crunchLuaDeps, 
    include_directories: incDirs)

# if meson.is_subproject() == false
#     subdir('Tests')
# endif
