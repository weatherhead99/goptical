
#curve_model
add_executable(curve_model curve_model/usercurve.cc)
target_link_libraries(curve_model goptical_core)


#hierarchical_design
add_executable(hierarchical_design hierarchical_design/newton.cc)
target_include_directories(hierarchical_design PRIVATE ${CMAKE_SOURCE_DIR}/goptical_design/src)
target_link_libraries(hierarchical_design goptical_core goptical_design)


#segmented_mirror
add_executable(segmented_mirror segmented_mirror/segmented.cc)
target_link_libraries(segmented_mirror goptical_core)

#simple refractor
add_executable(simple_refractor simple_refractor/refractor.cc)
target_link_libraries(simple_refractor goptical_core)

#tessar_lens 
add_executable(tessar_lens tessar_lens/tessar.cc)
target_link_libraries(tessar_lens goptical_core)

#render_3d
if(NOT NO_X11)
  add_executable(render_3d_x11 render_3d/x11_app.cc)
  target_include_directories(render_3d_x11 PRIVATE ${CMAKE_SOURCE_DIR}/goptical_design/src)
  target_link_libraries(render_3d_x11 goptical_core goptical_design)
endif()


if(GLUT_FOUND)
  add_executable(render_3d_opengl render_3d/opengl_app.cc)
  target_include_directories(render_3d_opengl PRIVATE ${CMAKE_SOURCE_DIR}/goptical_design/src ${OPENGL_INCLUDE_DIR})
  target_link_libraries(render_3d_opengl goptical_core goptical_design)
else()
  message(WARNING "no GLUT, can't build render_3d openGL example")
  
endif()