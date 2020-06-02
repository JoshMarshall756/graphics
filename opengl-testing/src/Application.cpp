#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include "common/loadShader.cpp"

int main(void)
{
    GLFWwindow *window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Application", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    // Must be called after creating a valid OpenGL Rendering Context4
    if (glewInit() != GLEW_OK)
        std::cout << "ERROR: GLEW ERROR!!" << std::endl;
    else
        // Initiliazation succeeded and
        std::cout << "LOG: GLEW OK!!" << std::endl;

    // Print opengl version
    std::cout << "LOG: OPENGL VERSION " << glGetString(GL_VERSION) << std::endl;

    // Positions of a triangle in 2D space
    float vertexPositions[6] = {
        // X,    Y
        -0.5f, -0.5f,
        0.0f, 0.5f,
        0.5f, -0.5f};

    // Creating a vertex buffer of positions for the triangle
    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6, vertexPositions, GL_STATIC_DRAW);

    // Using an VBA
    unsigned int vbo;
    glGenVertexArrays(1, &vbo);
    glBindVertexArray(vbo);

    // Define the structure of the data
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);


    unsigned int shaderProgram = createShader("shaders/vertexShader.glsl", "shaders/fragmentShader.glsl");
    glUseProgram(shaderProgram);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}