cmake_minimum_required(VERSION 3.9)

project("Real-Time Water Rendering")

#find_package(OpenGL REQUIRED)

# Set C++ 14
set(CMAKE_CXX_STANDARD 14) # C++14...
set(CMAKE_CXX_STANDARD_REQUIRED ON) #...is required...
set(CMAKE_CXX_EXTENSIONS OFF) #...without compiler extensions like gnu++14

# Custom cmake Find.cmake modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_subdirectory(src ../bin/)
