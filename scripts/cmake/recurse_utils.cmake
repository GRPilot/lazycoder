
# This function collects the directories in dir_path
function(load_directories_list dir_path result)
    file(GLOB_RECURSE headers_list ${dir_path}/*.h)
    set(dir_list "")
    foreach(file_path ${headers_list})
        get_filename_component(dir_path ${file_path} PATH) 
        set(dir_list "${dir_list};${dir_path}")
    endforeach()
    list(REMOVE_DUPLICATES dir_list)
    set(${result} ${dir_list} PARENT_SCOPE)
endfunction()

# This function puts cpp, h, hpp, ui, qrc and ts files into result
function(load_sources_list dir_path src ts res)
    file(GLOB qrc_files ${dir_path}/res/*.qrc)
    file(GLOB ts_files ${dir_path}/lang/*.ts)
    file(GLOB_RECURSE sources
        ${dir_path}/src/*.cpp
        ${dir_path}/src/*.hpp
        ${dir_path}/src/*.h
        ${dir_path}/src/*.ui
    )
    # list(APPEND sources ${ts_files})
    # list(APPEND sources ${qrc_files})
    list(REMOVE_DUPLICATES sources)
    set(${src} ${sources} PARENT_SCOPE)
    set(${ts} ${ts_files} PARENT_SCOPE)
    set(${res} ${qrc_files} PARENT_SCOPE)
endfunction()
