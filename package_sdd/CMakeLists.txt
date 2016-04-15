#@author wangchuanjun
#@email chuanjun.wang@outlook.com
#@time 2016-4-12 2:14 AM

cmake_minimum_required(VERSION 2.8)

project(shadow)

#设置需要的编译器
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++0x")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")

#导入opencv的文件
find_package(OpenCV REQUIRED)


file(GLOB_RECURSE main_source *.cpp)
file(GLOB_RECURSE main_include *.h)
file(GLOB main main.cc)

#添加头文件搜索路径
include_directories(${CMAKE_SOURCE_DIR})

#编译函数动态库
add_library(shadow SHARED ${main_source})
target_link_libraries(shadow ${OpenCV_LIBS})
set_property(TARGET shadow PROPERTY PUBLIC_HEADER ${main_include})

#编译可执行文件
add_executable(shadow_bin ${main})
target_link_libraries(shadow_bin ${OpenCV_LIBS} shadow)
set_target_properties(shadow_bin PROPERTIES OUTPUT_NAME shadow)



