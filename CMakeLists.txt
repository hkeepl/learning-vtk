cmake_minimum_required(VERSION 3.16)

project(LearningVTK)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/")

include(learningvtkPrepare)
include(learningvtkMacro)

foreach(SUBDIR chap01 chap02 chap03 chap04 chap05)
    add_subdirectory(${SUBDIR})
endforeach()
