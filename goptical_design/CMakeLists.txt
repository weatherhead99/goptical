set(goptical_design_srcs src/telescope_cassegrain.cc src/telescope_newton.cc)

include_directories(src)

add_library(goptical_design SHARED ${goptical_design_srcs})
target_link_libraries(goptical_design goptical_core)

install(TARGETS goptical_design DESTINATION ${CMAKE_INSTALL_LIBDIR} EXPORT goptical)
install(DIRECTORY src/Goptical/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/Goptical)