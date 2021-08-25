cmake_minimum_required(VERSION 3.0)

project(minizip LANGUAGES C)

file(GLOB_RECURSE headers ${PROJECT_SOURCE_DIR}/*.h)
file(GLOB_RECURSE sources ${PROJECT_SOURCE_DIR}/*.c)

set(MINIZIP_INCLUDE_DIRS ${PROJECT_SOURCE_DIR} PARENT_SCOPE)

add_library(minizip OBJECT ${sources} ${headers})
# install(TARGETS minizip EXPORT minizipExport ${dest_args})
# install(TARGETS minizipExport NAMESPACE mzip::)

add_library(mzip::minizip ALIAS minizip)
