#include <iostream>

#include "../headers/vec3.h"
#include "../headers/color.h"

int main()
{
    const int image_width = 256;
    const int image_height = 256;

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = image_height-1; j >= 0; --j)
    {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = image_width-1; i >= 0; --i)
        {
            // red goes from fully off to fully on, from left to right
            // uses color = vec3
            color pixel_color(double(i)/(image_width-1), double(j)/(image_height-1), 0.25);
            write_color(std::cout, pixel_color);
        }
    }
    std::cerr << "\nDone.\n";
}