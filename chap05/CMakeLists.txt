cmake_minimum_required(VERSION 3.16)

project(chap05)

find_package(VTK REQUIRED)
if (NOT VTK_FOUND)
  message("Skipping example: ${VTK_NOT_FOUND_MESSAGE}")
  return ()
endif ()

file(GLOB SRCS "${CMAKE_CURRENT_LIST_DIR}/*.cpp")
foreach(SRC ${SRCS})
  string(REGEX REPLACE ".+/(.+)\\..+" "\\1" TARGET_NAME ${SRC})
  MY_ADD_EXECUTABLE(${PROJECT_NAME} ${TARGET_NAME} ${SRC})
endforeach()
