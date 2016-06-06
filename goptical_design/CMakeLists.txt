set(goptical_design_srcs src/telescope_cassegrain.cc src/telescope_newton.cc)

include_directories(src)

add_library(goptical_design ${goptical_design_srcs})


