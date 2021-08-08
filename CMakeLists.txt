cmake_minimum_required(VERSION 3.5)

set(APP_VER_MAJOR 0)
set(APP_VER_MINOR 2)
set(APP_VER_PATCH 0)

project(lazycoder VERSION ${APP_VER_MAJOR}.${APP_VER_MINOR}.${APP_VER_PATCH} LANGUAGES CXX)
set(appver_dir ${PROJECT_SOURCE_DIR}/src/appversion)
configure_file(
    ${appver_dir}/appversion.h.in
    ${appver_dir}/appversion.h)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets LinguistTools REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets LinguistTools REQUIRED)

file(GLOB TS_FILES ${PROJECT_SOURCE_DIR}/lang/*.ts)

include_directories(
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/src/mainwindow
    ${PROJECT_SOURCE_DIR}/src/appversion
)

file(GLOB_RECURSE PROJECT_SOURCES
    ${PROJECT_SOURCE_DIR}/src/*.cpp
    ${PROJECT_SOURCE_DIR}/src/*.h
    ${PROJECT_SOURCE_DIR}/src/*.ui)

list(APPEND PROJECT_SOURCES ${TS_FILES})

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(lazycoder
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    add_executable(lazycoder ${PROJECT_SOURCES})

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_link_libraries(lazycoder PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(lazycoder PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(lazycoder)
endif()
