cmake_minimum_required(VERSION 3.7)

set(rootProject sara_emo_detection)
project(${rootProject})

set(CMAKE_CXX_STANDARD 11)

find_package(OpenCV 3 REQUIRED)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -D_GLIBCXX_USE_CXX11_ABI=0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(/home/jeffrey/affdex-sdk/include)
#include_directories(/usr/include/libpng12)

add_executable(${rootProject} main.cpp PlottingImageListener.h StatusListener.h)
#/home/gzsierra/src/affectiva/affdex-sdk/lib/libaffdex-native.so
target_link_libraries(${rootProject} ${OpenCV_LIBS} /home/jeffrey/affdex-sdk/lib/libaffdex-native.so)