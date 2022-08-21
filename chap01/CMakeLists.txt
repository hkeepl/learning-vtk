cmake_minimum_required(VERSION 3.16)

project(chap01)

foreach(TARGET_NAME 1.3_test_vtk_install)
  set(SRCS ${TARGET_NAME}.cpp)
  MY_ADD_EXECUTABLE(${PROJECT_NAME} ${TARGET_NAME} ${SRCS})
endforeach()
