cmake_minimum_required(VERSION 3.0)

project(minizip LANGUAGES C)

file(GLOB headers ${PROJECT_SOURCE_DIR}/*.h)
file(GLOB sources ${PROJECT_SOURCE_DIR}/*.c)
list(REMOVE_ITEM sources ${PROJECT_SOURCE_DIR}/minizip.c)
list(REMOVE_ITEM sources ${PROJECT_SOURCE_DIR}/miniunz.c)

set(MINIZIP_INCLUDE_DIRS ${PROJECT_SOURCE_DIR} PARENT_SCOPE)

add_library(minizip OBJECT ${sources} ${headers})

add_library(mzip::minizip ALIAS minizip)
