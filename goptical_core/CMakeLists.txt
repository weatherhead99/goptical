    
set(goptical_core_srcs src/analysis_focus.cc	    src/curve_zernike.cc       src/io_renderer_viewport.cc	 src/material_schott.cc        src/sys_element.cc
src/analysis_pointimage.cc  src/data_discrete_set.cc   src/io_renderer_x11.cc		 src/material_sellmeier.cc     src/sys_group.cc
src/analysis_rayfan.cc	    src/data_grid.cc	       src/io_renderer_x3d.cc		 src/material_sellmeiermod.cc  src/sys_image.cc
src/analysis_spot.cc	    src/data_plot.cc	       src/io_rgb.cc			 src/material_vacuum.cc        src/sys_lens.cc
src/curve_array.cc	    src/data_sample_set.cc     src/light_ray.cc			 src/math_matrix.cc	       src/sys_mirror.cc
src/curve_base.cc	    src/data_set1d.cc	       src/light_spectral_line.cc	 src/math_transform.cc	       src/sys_optical_surface.cc
src/curve_composer.cc	    src/data_set.cc	       src/material_abbe.cc		 src/shape_base.cc	       src/sys_source.cc
src/curve_conic_base.cc     src/io_import_oslo.cc      src/material_air.cc		 src/shape_composer.cc	       src/sys_source_point.cc
src/curve_conic.cc	    src/io_import_zemax.cc     src/material_base.cc		 src/shape_disk.cc	       src/sys_source_rays.cc
src/curve_flat.cc	    src/io_renderer_2d.cc      src/material_catalog.cc		 src/shape_ellipse.cc	       src/sys_stop.cc
src/curve_foucault.cc	    src/io_renderer_axes.cc    src/material_conrady.cc		 src/shape_elliptical_ring.cc  src/sys_surface.cc
src/curve_grid.cc	    src/io_renderer.cc	       src/material_dielectric.cc	 src/shape_infinite.cc	       src/sys_system.cc
src/curve_parabola.cc	    src/material_dispersion_table.cc  src/shape_polygon.cc	       src/trace_result.cc
src/curve_polynomial.cc     src/material_herzberger.cc	 src/shape_rectangle.cc        src/trace_sequence.cc
src/curve_rotational.cc     src/io_renderer_opengl.cc  src/material_metal.cc		 src/shape_regular_polygon.cc  src/trace_tracer.cc
src/curve_sphere.cc	    src/io_renderer_plplot.cc  src/material_mirror.cc		 src/shape_ring.cc
src/curve_spline.cc	    src/io_renderer_svg.cc     src/material_proxy.cc		 src/sys_container.cc)


if(NOT NO_dime)
list(APPEND goptical_core_srcs src/io_renderer_dxf.cc)
endif()

if(NOT NO_gd)
list(APPEND goptical_core_srcs src/io_renderer_gd.cc)
endif()

add_library(goptical_core SHARED ${goptical_core_srcs})
target_link_libraries(goptical_core  gsl gslcblas ${X11_LIBRARIES} ${OPENGL_LIBRARIES} ${PLplot_LIBRARIES} ${GLUT_LIBRARIES})



if(BUILD_TESTS)


set(goptical_core_test_srcs tests/test_2d_plot.cc tests/test_coordinates.cc tests/test_discrete_set.cc tests/test_materials.cc
			    tests/test_patterns.cc tests/test_rendering.cc tests/test_shapes.cc)

foreach(testsrc ${goptical_core_test_srcs})
    get_filename_component(testsrc_abs ${testsrc} ABSOLUTE)
    get_filename_component(testname ${testsrc} NAME_WE)
    message(STATUS "adding test: ${testname} from source ${testsrc_abs}")
    add_executable(${testname} ${testsrc_abs})
    target_link_libraries(${testname} goptical_core)
    add_test(${testname} ${testname})    
endforeach()

endif()

target_compile_definitions(test_discrete_set PRIVATE -DTEST_WRITE)

#environment variable for discrete_set test 
set(ENV{srcdir} "${CMAKE_CURRENT_SOURCE_DIR}/tests/")

#TODO: include properties?
install(TARGETS goptical_core DESTINATION ${CMAKE_INSTALL_LIBDIR} EXPORT goptical)
install(DIRECTORY src/Goptical DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})


