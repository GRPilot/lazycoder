
# This macro just makes executable and translations by the Qt version
macro(add_executable_by_version target)
    # Make build target and translation
    if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
        qt_add_executable(${target} MANUAL_FINALIZATION ${sources})
        qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
    else()
        add_executable(${target} ${sources})
        qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
    endif()
endmacro()
