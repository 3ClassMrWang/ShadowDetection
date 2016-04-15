cmake_minimum_required(VERSION 2.8)

project(bgs)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++0x")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")

IF(UNIX)
  # add some standard warnings
  ADD_DEFINITIONS(-Wno-variadic-macros -Wno-long-long -Wall -Wextra -Winit-self -Woverloaded-virtual -Wsign-promo -Wno-unused-parameter -pedantic -Woverloaded-virtual -Wno-unknown-pragmas)
  
  # -ansi does not compile with sjn module
  #ADD_DEFINITIONS(-ansi)

  # if you like to have warinings about conversions, e.g. double->int or double->float etc., or float compare
  #ADD_DEFINITIONS(-Wconversion -Wfloat-equal)
endif(UNIX)

find_package(OpenCV REQUIRED)

if(${OpenCV_VERSION} VERSION_LESS 2.3.1)
  message (FATAL_ERROR "OpenCV version is not compatible: ${OpenCV_VERSION}")
endif()

file(GLOB sources FrameProcessor.cpp PreProcessor.cpp VideoAnalysis.cpp  VideoCapture.cpp videofolder/VideoFolder.cpp)
file(GLOB bgs Bgs.cpp)
file(GLOB demo Demo.cpp)
file(GLOB stats Stats.cpp)
file(GLOB sdd Sdd.cpp)

list(REMOVE_ITEM sources ${demo})
list(REMOVE_ITEM sources ${stats})
list(REMOVE_ITEM sources ${sdd})

file(GLOB_RECURSE analysis package_analysis/*.cpp)
file(GLOB_RECURSE bgs_sdd package_bgs/*.cpp package_bgs/*.c package_sdd/*.cpp)
file(GLOB_RECURSE bgs_sdd_include package_bgs/*.h videofolder/*.h)

# GMG is not available in older OpenCV versions
if(${OpenCV_VERSION} VERSION_LESS 2.4.3)
  file(GLOB gmg package_bgs/GMG.cpp)
  list(REMOVE_ITEM bgs_sdd ${gmg})
endif()

include_directories(${CMAKE_SOURCE_DIR})

add_library(bgs_sdd SHARED ${sources} ${bgs_sdd} ${analysis})
target_link_libraries(bgs_sdd ${OpenCV_LIBS})
set_property(TARGET bgs_sdd PROPERTY PUBLIC_HEADER ${bgs_sdd_include})

add_executable(bgs ${bgs})
target_link_libraries(bgs ${OpenCV_LIBS} bgs_sdd)

add_executable(demo ${demo})
target_link_libraries(demo ${OpenCV_LIBS} bgs_sdd)

add_executable(stats ${stats})
target_link_libraries(stats ${OpenCV_LIBS} bgs_sdd)

add_executable(sdd ${sdd})
target_link_libraries(sdd ${OpenCV_LIBS} bgs_sdd)

#INSTALL(TARGETS bgs
#	bgs_demo
#	bgs_bin
#  RUNTIME DESTINATION bin COMPONENT app
#  LIBRARY DESTINATION lib COMPONENT runtime
#  ARCHIVE DESTINATION lib COMPONENT runtime
#  PUBLIC_HEADER DESTINATION include/package_bgs COMPONENT dev
#  FRAMEWORK DESTINATION "/Library/Frameworks"
#)

