cmake_minimum_required(VERSION 3.16)

project(chap03)

foreach(TARGET_NAME 3.2_triangle_points 3.2_triangle_vertices 3.2_triangle_geometry_lines
        3.4_vtk_concept_scalars 3.6_vtk_concept_array)
  set(SRCS ${TARGET_NAME}.cpp)
  MY_ADD_EXECUTABLE(${PROJECT_NAME} ${TARGET_NAME} ${SRCS})
endforeach()
