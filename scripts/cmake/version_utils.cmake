
# This macro sets the version for making appversion file and project in all
macro(set_version version)
    set(PROJECT_VERSION ${version})
    string(REPLACE "." ";" version_list ${version})
    list(POP_FRONT version_list APP_VER_MAJOR)
    list(POP_FRONT version_list APP_VER_MINOR)
    list(POP_FRONT version_list APP_VER_PATCH)
    set(PROJECT_VERSION_MAJOR ${APP_VER_MAJOR})
    set(PROJECT_VERSION_MINOR ${APP_VER_MINOR})
    set(PROJECT_VERSION_PATCH ${APP_VER_PATCH})
    message(STATUS "Application version: ${PROJECT_VERSION}")
endmacro()

# This function generates the version file
function(make_version_file filename)
    set(appver_dir ${PROJECT_SOURCE_DIR}/src/appversion)
    configure_file(
        ${appver_dir}/${filename}.h.in
        ${appver_dir}/${filename}.h
    )
endfunction()
