#include "controls.hpp"

glm::mat4 viewMatrix;
glm::mat4 projectionMatrix;

glm::mat4 getViewMatrix()
{
    return viewMatrix;
}

glm::mat4 getProjectionMatrix()
{
    return projectionMatrix;
}

// position
glm::vec3 position = glm::vec3(4,3,3);
// horizontal angle: toward -Z
float horizontalAngle = 3.14f;
// vertical angle: 0, look at the horizon
float verticalAngle = 0.0f;
// initial FoV
float initialFoV = 45.0f;

// 3 units / second
float speed = 3.0f;
float mouseSpeed = 0.05f;

float aspectRatio = 4.0f / 3.0f; 

void computeMatricesFromInputs(GLFWwindow *window)
{
    // glfwGetTime is called only once, the first time the function is called
    static double lastTime = glfwGetTime();

    // Compute the time difference between current and last frame
    double currentTime = glfwGetTime();
    float deltaTime = float(currentTime - lastTime);


    double xPos, yPos;
    glfwGetCursorPos(window, &xPos, &yPos);
    
    int windowWidth, windowHeight;
    glfwGetWindowSize(window, &windowWidth, &windowHeight);
    glfwSetCursorPos(window, windowWidth/2, windowHeight/2);

    // Compute new orientation
    horizontalAngle += mouseSpeed * deltaTime * float(windowWidth/2 - xPos);
    verticalAngle += mouseSpeed * deltaTime * float(windowHeight/2 - yPos);

    glm::vec3 direction(
        cos(verticalAngle) * sin(horizontalAngle),
        sin(verticalAngle),
        cos(verticalAngle) * cos(horizontalAngle)
    );

    // Right vector
    glm::vec3 right = glm::vec3(
        sin(horizontalAngle - 3.14f/2.0f),
        0,
        cos(horizontalAngle - 3.14f/2.0f)
    );

    // Up vector: perp to both direction and right
    glm::vec3 up = glm::cross(right, direction);

    // Move forward
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        position += direction * deltaTime * speed;
    }

    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        position -= direction * deltaTime * speed;
    }

    // Strafe right
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        position += right * deltaTime * speed;
    }

    // Strafe left
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        position -= right * deltaTime * speed;
    }

    float FoV = initialFoV; // TODO: implement mouse wheel FoV
    projectionMatrix = glm::perspective(glm::radians(FoV), aspectRatio, 0.1f, 100.0f);
    // Camera Matrix
    viewMatrix = glm::lookAt(
        position,               // Camera is here
        position+direction,     // and looks here
        up                      // Head is up
    );

    // For the next frame, the lastTime will be "now"
    lastTime = currentTime;
}