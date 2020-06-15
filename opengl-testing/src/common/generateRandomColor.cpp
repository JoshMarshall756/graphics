#include "common.hpp"

/** Generates a random float between [0.0,1.0] 
 * 
 * @return returns a float between [0.0,1.0]
 */
float generateRandomColor()
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<float> dist(0.0, std::nextafterf(1.0f, __FLT_MAX__));

    return dist(mt);
}