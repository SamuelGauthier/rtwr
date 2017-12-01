find_package(OpenGL REQUIRED)

set(TARGET_H
    Shader.h
    stb_image.h
    Skybox.h
    Plane.h
    )

set(TARGET_SRC
    Shader.cpp
    Skybox.cpp
    Plane.cpp
    )
# As alternative use a glob
# file(GLOB TARGET_FILES "*.h" "*.cpp")

# add_executable(rtwr main.cpp Shader.cpp)
add_executable(rtwr main.cpp ${TARGET_SRC} ${TARGET_H})

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
