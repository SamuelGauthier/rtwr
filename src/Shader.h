/**
 * @file Shader.h
 * @brief Helper class to load shaders
 * @author opengl-tutorial.org
 */
#ifndef INCLUDED_SHADER
#define INCLUDED_SHADER 

/**
 * @brief Loads vertex and fragment shaders given their file paths.
 *
 * @param vertex_file_path The vertex shader file path
 * @param fragment_file_path The fragment shader file path
 *
 * @return The created program object reference.
 */
GLuint LoadShaders(const char * vertex_file_path, const char*
        fragment_file_path);

#endif /* ifndef INCLUDED_SHADER */
