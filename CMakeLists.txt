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

#add_executable(rtwr main.cpp)

#find_package (GLEW)
#if (GLEW_FOUND)
#  include_directories(${GLEW_INCLUDE_DIRS})
#  target_link_libraries (rtwr ${GLEW_LIBRARIES})
#endif (GLEW_FOUND)
#
#
#find_package(GLFW REQUIRED)
#include_directories(${GLFW_INCLUDE_DIRS})
#set(LIBS ${LIBS} ${GLFW_LIBRARIES})
#
#target_link_libraries(rtwr ${OPENGL_gl_LIBRARY})
#target_link_libraries(rtwr ${LIBS})
