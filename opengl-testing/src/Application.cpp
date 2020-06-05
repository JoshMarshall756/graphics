#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// GLM maths library
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>

#include <iostream>
#include "common/loadShader.cpp"

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

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
    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Application", NULL, NULL);
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
    std::cout << "INFO: OPENGL VERSION " << glGetString(GL_VERSION) << std::endl;

    // Positions of a triangle in 2D space
    float vertexPositions[9] = {
        // X,    Y,    Z
        -0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f,
         0.5f, -0.5f, 0.0f};

    // Creating a vertex buffer of positions for the triangle
    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 9, vertexPositions, GL_STATIC_DRAW);

    // Using an VBA
    unsigned int vbo;
    glGenVertexArrays(1, &vbo);
    glBindVertexArray(vbo);

    // Define the structure of the data
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

    unsigned int shaderProgram = createShaderProgram("shaders/vertexShader.glsl", "shaders/fragmentShader.glsl");
    glUseProgram(shaderProgram);

    // Model View Projection Matrix 
    // Projection matrix (perspective view)
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);
    // Projection matrix (orthographic view)
    //glm::mat4 projection = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f);

    // View/Camera matrix
    glm::mat4 view = glm::lookAt(glm::vec3(0,0, 5), glm::vec3(0,0,0), glm::vec3(0,1,0));

    // Model matrix: an identity matrix (model at the origin)
    glm::mat4 model = glm::mat4(1.0f);

    // Build a transformation matrix
    glm::mat4 transformationMatrix = glm::mat4(1.0f);
    transformationMatrix = glm::translate(transformationMatrix, glm::vec3(2.0f,0.0f,0.0f));
    transformationMatrix = glm::scale(transformationMatrix, glm::vec3(1.5f, 1.5f, 1.5f));
    transformationMatrix = glm::rotate(transformationMatrix, glm::radians(180.0f), glm::vec3(0.0f,0.0f,1.0f));

    // Apply transformation matrix to every column in model matrix
    for (int i = 0; i < 4; i++)
    {
        model[i] = transformationMatrix * model[i];
    }

    // The ModelViewProjection matrix
    glm::mat4 mvp = projection * view * model;

    // Get a handle for the "MVP" uniform
    unsigned int matrixID = glGetUniformLocation(shaderProgram, "MVP");

    // Send our matrix to the currently bound shader, in the "MVP" uniform
    glUniformMatrix4fv(matrixID, 1, GL_FALSE, &mvp[0][0]);

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window) || glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
    {
        /* Render here */
        glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}