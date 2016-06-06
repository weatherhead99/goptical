cmake_minimum_required(VERSION 3.2)
project(goptical)

include_directories(goptical_core/src)


option(BUILD_TESTS "Build tests" ON)
if(BUILD_TESTS)
  enable_testing()
endif()

#GSL library- non negotiable
find_library(gsl gsl)
if(gsl STREQUAL "gsl-NOTFOUND")
message(FATAL_ERROR "couoldn't find GSL. Can't continue build")
endif()

find_library(gslcblas gslcblas)
if(gsl STREQUAL "gslcblas-NOTFOUND")
message(FATAL_ERROR "couoldn't find GSL-CBLAS. Can't continue build")
endif()



#DIME library for DXF support
find_library(dime dime)
if(dime STREQUAL "dime-NOTFOUND")
message(WARNING "dime not found. Building without DXF support")
set(NO_DXF TRUE)
endif()

#libGD for GD export
find_library(gd gd)
if(gd STREQUAL "gd-NOTFOUND")
message(WARNING "gd not found. Building without GD rendering support")
set(NO_GD TRUE)
endif()

#plplot
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR})
find_package(PLplot)

if(NOT ${PLplot-FOUND})
message(WARNING "plplot not found. Building without plplot support")
set(NO_PLPLOT TRUE)
endif()


#enable hacks for cmake build
add_definitions(-DCMAKE_BUILD)


add_subdirectory(goptical_core)
add_subdirectory(goptical_design)