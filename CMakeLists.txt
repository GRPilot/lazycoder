cmake_minimum_required(VERSION 3.5) # The minimum required cmake version to use.

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

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DDEBUG)
else()
    add_definitions(-DNDEBUG)
endif()

#================================ Collecting files to include/build ===============================#

# Finding the Qt packages
find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets LinguistTools REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets LinguistTools REQUIRED)

add_subdirectory(${third_party_path}/plog-1.1.5)

load_directories_list(${PROJECT_SOURCE_DIR}/src directories)
load_sources_list(${PROJECT_SOURCE_DIR}
    sources
    translate_files
    resource_files
)

#========================================= Make executable ========================================#
add_executable_by_version(${CMAKE_PROJECT_NAME})

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${directories})
target_link_libraries(${CMAKE_PROJECT_NAME}
    PRIVATE
        Qt${QT_VERSION_MAJOR}::Widgets
        plog
)

set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(${CMAKE_PROJECT_NAME})
endif()

set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})
install(TARGETS ${CMAKE_PROJECT_NAME} DESTINATION ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})
