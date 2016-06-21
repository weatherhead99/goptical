cmake_minimum_required(VERSION 3.2)
project(goptical)

include_directories(goptical_core/src)

include(GNUInstallDirs)

option(BUILD_TESTS "Build tests" ON)
if(BUILD_TESTS)
  enable_testing()
endif()


set(INCLUDE_INSTALL_DIR ${CMAKE_INSTALL_INCLUDEDIR})
#GSL library- non negotiable
find_library(gsl gsl)
if(gsl STREQUAL "gsl-NOTFOUND")
message(FATAL_ERROR "couoldn't find GSL. Can't continue build")
endif()

find_library(gslcblas gslcblas)
if(gsl STREQUAL "gslcblas-NOTFOUND")
message(FATAL_ERROR "couoldn't find GSL-CBLAS. Can't continue build")
endif()


macro(depend_lib_logic libname defname)

  if(${${libname}_FOUND})
    message(STATUS "${libname} found")
    add_definitions(-DGOPTICAL_HAVE_${defname})
  else()
    message(WARNING "${libname} not found. Building without it")
    set(NO_${libname} TRUE)
  endif()


endmacro()

find_library(dime dime)
depend_lib_logic(dime DIME)

find_library(gd gd)
depend_lib_logic(gd GD)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR})

find_package(PLplot)
depend_lib_logic(PLplot PLPLOT)


find_package(X11)
depend_lib_logic(X11 X11)


#explicitly disable op
find_package(OpenGL)
find_package(GLUT)
depend_lib_logic(OpenGL GL)



#enable hacks for cmake build
add_definitions(-DCMAKE_BUILD)


add_subdirectory(goptical_core)
add_subdirectory(goptical_design)

option(BUILD_EXAMPLES "Build examples" ON)
if(BUILD_EXAMPLES)
  add_subdirectory(examples)
endif()	

set(CMAKECONFIG_INSTALL_DIR ${CMAKE_INSTALL_LIBDIR}/cmake/goptical/)
install(EXPORT goptical FILE gopticalTargets.cmake DESTINATION ${CMAKECONFIG_INSTALL_DIR})

#cmake export stuff

set(GOPTICAL_VERSION 1.0)
include(CMakePackageConfigHelpers)

set(CMAKECONFIG_INSTALL_DIR ${CMAKE_INSTALL_LIBDIR}/cmake/goptical)

configure_package_config_file(gopticalConfig.cmake.in gopticalConfig.cmake 
			      INSTALL_DESTINATION ${CMAKECONFIG_INSTALL_DIR}
			      PATH_VARS INCLUDE_INSTALL_DIR)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/gopticalConfig.cmake DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/goptical/)

#TODO: build docs