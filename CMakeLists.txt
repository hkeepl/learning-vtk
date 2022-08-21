cmake_minimum_required(VERSION 3.16)

project(LearningVTK)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/")

find_package(VTK REQUIRED)
if (NOT VTK_FOUND)
  message("Skipping example: ${VTK_NOT_FOUND_MESSAGE}")
  return ()
endif ()

include(learningvtkPrepare)
include(learningvtkMacro)

foreach(SUBDIR chap01 chap02 chap03 chap04 chap05)
    add_subdirectory(${SUBDIR})
endforeach()
