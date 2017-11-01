find_package(OpenGL REQUIRED)

add_executable(rtwr main.cpp)

find_package (GLEW)
if (GLEW_FOUND)
  include_directories(${GLEW_INCLUDE_DIRS})
  target_link_libraries (rtwr ${GLEW_LIBRARIES})
endif (GLEW_FOUND)


find_package(GLFW REQUIRED)
include_directories(${GLFW_INCLUDE_DIRS})
set(LIBS ${LIBS} ${GLFW_LIBRARIES})

target_link_libraries(rtwr ${OPENGL_gl_LIBRARY})
target_link_libraries(rtwr ${LIBS})
