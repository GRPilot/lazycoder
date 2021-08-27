cmake_minimum_required(VERSION 3.6.3) # The minimum required cmake version to use.

project(lazycoder LANGUAGES CXX)
message(STATUS "Project name: ${CMAKE_PROJECT_NAME}")

#============================================ includes ============================================#
set(third_party_path ${PROJECT_SOURCE_DIR}/third_party)
set(scripts_path ${PROJECT_SOURCE_DIR}/scripts/cmake)
include(${scripts_path}/version_utils.cmake)
include(${scripts_path}/recurse_utils.cmake)
include(${scripts_path}/add_exe_utils.cmake)

#======================================= Application version ======================================#
set_version(0.6.0)
make_version_file("appversion")

#====================================== CMake and Cpp options =====================================#
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Auto generating and including qt files
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Set the c++ parameters
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#================================ Collecting files to include/build ===============================#

# Finding the Qt packages
find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets LinguistTools REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets LinguistTools REQUIRED)

load_directories_list(${PROJECT_SOURCE_DIR}/src directories)
load_sources_list(${PROJECT_SOURCE_DIR}
    sources
    translate_files
    resource_files
)

set(zlib_dir ${third_party_path}/zlib-1.2.11/${CMAKE_BUILD_TYPE})
set(zlib_dll ${zlib_dir}/bin/libzlib.dll)
set(ZLIB_INCLUDE_DIR ${zlib_dir}/include)
set(ZLIB_LIBRARY ${zlib_dir}/lib)
find_package(ZLIB REQUIRED)

add_subdirectory(${third_party_path}/unzip101e)

#========================================= Make executable ========================================#
add_executable_by_version(${CMAKE_PROJECT_NAME})

target_include_directories(${CMAKE_PROJECT_NAME}
    PUBLIC
        ${directories}
        ${ZLIB_INCLUDE_DIRS}
        ${MINIZIP_INCLUDE_DIRS}
)
target_link_directories(${CMAKE_PROJECT_NAME}
    PUBLIC
        ${ZLIB_LIBRARIES}
)
target_link_libraries(${CMAKE_PROJECT_NAME}
    PUBLIC
        ${zlib_dll}
        mzip::minizip
    PRIVATE
        Qt${QT_VERSION_MAJOR}::Widgets
)

set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(${CMAKE_PROJECT_NAME})
endif()

#==================================== Installing dependencies =====================================#
set(install_dir ${PROJECT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})

install(TARGETS ${CMAKE_PROJECT_NAME} DESTINATION ${install_dir})

macro(add_copy target destination)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${target} ${destination})
endmacro()

add_copy(${zlib_dll} ${install_dir}/libzlib.dll)
