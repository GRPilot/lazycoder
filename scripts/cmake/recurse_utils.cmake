
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
function(load_sources_list dir_path result)
    file(GLOB ts_files ${PROJECT_SOURCE_DIR}/lang/*.ts)
    file(GLOB_RECURSE sources
        ${dir_path}/*.cpp
        ${dir_path}/*.hpp
        ${dir_path}/*.h
        ${dir_path}/*.ui
        ${dir_path}/*.qrc
    )
    list(APPEND sources ${ts_files})
    list(REMOVE_DUPLICATES sources)
    set(${result} ${sources} PARENT_SCOPE)
endfunction()
