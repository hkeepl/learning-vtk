cmake_minimum_required(VERSION 3.16)

project(LearningVTK)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/")

find_package(VTK REQUIRED)
if (NOT VTK_FOUND)
  message("Skipping example: ${VTK_NOT_FOUND_MESSAGE}")
  return ()
endif ()

set(ROOT_PATH "${CMAKE_SOURCE_DIR}")
configure_file(config.h.in "${CMAKE_BINARY_DIR}/include/config.h")
include_directories("${CMAKE_BINARY_DIR}/include")

include(learningvtkPrepare)
include(learningvtkMacro)

foreach(SUBDIR chap01 chap02 chap03 chap04 chap05 chap06 chap07 chap08)
    add_subdirectory(${SUBDIR})
endforeach()
