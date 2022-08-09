## CMakeLists.txt

cmake_minimum_required(VERSION 3.23)

project(qconfig CXX)

## Set c++ standard/compile-time options
add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_17)

## Add src to build
add_subdirectory(src)
