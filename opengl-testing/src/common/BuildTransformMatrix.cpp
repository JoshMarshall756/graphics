#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

glm::mat4 buildTransformationMatrix()
{
    glm::mat4 transformationMatrix = glm::mat4(1.0f);
    transformationMatrix = glm::translate(transformationMatrix, glm::vec3(2.0f,0.0f,0.0f));
    transformationMatrix = glm::scale(transformationMatrix, glm::vec3(1.5f, 1.5f, 1.5f));
    transformationMatrix = glm::rotate(transformationMatrix, glm::radians(180.0f), glm::vec3(0.0f,0.0f,1.0f));

    return transformationMatrix;
}