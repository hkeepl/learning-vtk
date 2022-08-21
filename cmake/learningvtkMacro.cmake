macro(MY_ADD_EXECUTABLE proj_name targ_name)
    add_executable(${targ_name} ${ARGN})
    target_link_libraries(${targ_name} PRIVATE ${VTK_LIBRARIES})
    if(COMMAND vtk_module_autoinit)
        vtk_module_autoinit(
            TARGETS ${targ_name} 
            MODULES ${VTK_LIBRARIES})
    endif()
    set_target_properties(${targ_name} PROPERTIES FOLDER ${proj_name})
endmacro()
