cmake_minimum_required(VERSION 3.16)

project(chap03)

find_package(VTK REQUIRED)
if (NOT VTK_FOUND)
  message("Skipping example: ${VTK_NOT_FOUND_MESSAGE}")
  return ()
endif ()

foreach(TARGET_NAME 3.2_triangle_points 3.2_triangle_vertices 3.2_triangle_geometry_lines
        3.4_vtk_concept_scalars 3.6_vtk_concept_array)
  set(SRCS ${TARGET_NAME}.cpp)
  MY_ADD_EXECUTABLE(${PROJECT_NAME} ${TARGET_NAME} ${SRCS})
endforeach()
