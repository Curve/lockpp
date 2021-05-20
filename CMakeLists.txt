cmake_minimum_required(VERSION 3.1)
project(lockpp VERSION 1.0 DESCRIPTION "A C++ Library to manage mutex guarding variables")

add_library(lockpp INTERFACE)
target_include_directories(lockpp INTERFACE lock/include)

target_compile_features(lockpp INTERFACE cxx_std_17)
set_target_properties  (lockpp PROPERTIES 
                        CXX_STANDARD 17
                        CXX_EXTENSIONS OFF
                        CXX_STANDARD_REQUIRED ON)

set_target_properties(lockpp PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(lockpp PROPERTIES PROJECT_NAME ${PROJECT_NAME})