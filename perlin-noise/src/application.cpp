#include <cmath>

#include "ppm.hpp"
#include "perlin_noise.hpp"

int main()
{
    const int image_width = 600;
    const int image_height = 450;

    ppm image(image_width, image_height);

    long unsigned int seed = 43;
    PerlinNoise pn(seed);

    int kk = 0;
    for (int i = 0; i < image_height; ++i)
    {
        for (int j = 0; j < image_width; ++j)
        {
            double x = static_cast<double>(j) / (static_cast<double>(image_width));
            double y = static_cast<double>(i) / (static_cast<double>(image_height));

            // Normal perlin noise
            double n = (pn.noise(10 * x, 10 * y, 0.8));

            // Wood like noise
            // double n = 20 * pn.noise(x, y, 0.8);
            // n = n - floor(n);

            // Trying something weird
            // double n = 30 * pn.noise(x, y, 0.8);

            // Map values to the [0, 255] interval
            image.r[kk] = std::floor(255.0 * n);
            image.g[kk] = std::floor(255 * n);
            image.b[kk] = std::floor(255.0 * n); 
            kk++;
        }
    }

    // Save image to binary PPM file
    image.write("perlin_image.ppm");
}