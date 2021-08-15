
# This macro just makes executable and translations by the Qt version
macro(add_executable_by_version target)
    # Make build target and translation
    message(Translate files: ${translate_files})

    add_custom_target(translation ALL DEPENDS ${translate_files})
    add_custom_target(resources ALL DEPENDS ${resources_files})

    add_dependencies(resources translation)

    if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
        qt_add_executable(${target} MANUAL_FINALIZATION ${sources} ${resources_files})
        qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${translate_files})
    else()
        add_executable(${target} ${sources} ${resources_files})
        qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${translate_files})
    endif()
endmacro()
