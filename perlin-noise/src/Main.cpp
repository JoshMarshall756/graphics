#include <cmath>

#include "../headers/ppm.h"
#include "../headers/PerlinNoise.h"

int main()
{
    const int image_width = 600;
    const int image_height = 450;

    ppm image(image_width, image_height);


    int seed = 69;
    // Create pn object with the reference permutation vector
    PerlinNoise pn(seed);

    int kk = 0;
    for (int i = 0; i < image_height; ++i)
    {
        for (int j = 0; j < image_width; ++j)
        {
            double x = (double)j / ((double)image_width);
            double y = (double)i / ((double) image_height);

            // Normal perlin noise
            double n = pn.noise(10 * x, 10 * y, 0.8);

            // Wood like noise
            // double n = 20 * pn.noise(x, y, 0.8);
            // n = n - floor(n);

            // Trying something weird
            // double n = 30 * pn.noise(x, y, 0.8);

            // Map values to the [0, 255] interval
            image.r[kk] = floor(255 * n);
            image.g[kk] = floor(255 * n);
            image.b[kk] = floor(255 * n);
            kk++;
        }
    }

    // Save image to binary PPM file
    image.write("perlin_image.ppm");
}