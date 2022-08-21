cmake_minimum_required(VERSION 3.16)

project(chap02)

foreach(TARGET_NAME 2.1_render_cylinder 2.2_render_cylinder-lights 2.2_render-cylinder-camera
             2.2_texture_example 2.3_viewport 2.4_pipeline_execute 2.4_vtk_pipeline_demo 
             2.5_reference_counting)
  set(SRCS ${TARGET_NAME}.cpp)
  MY_ADD_EXECUTABLE(${PROJECT_NAME} ${TARGET_NAME} ${SRCS})
endforeach()
