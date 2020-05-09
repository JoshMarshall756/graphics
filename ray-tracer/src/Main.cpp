#include <iostream>

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
            auto r = double(i) / (image_width-1);
            auto g = double(j) / (image_height-1);
            auto b = 0.25;

            int ir = static_cast<int>(255.999 * r);
            int ig = static_cast<int>(255.999 * g);
            int ib = static_cast<int>(255.99 * b);

            // pixels are written in rows, from left to right
            // and rows are written from top to bottom
            std::cout << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }
    std::cerr << "\nDone.\n";
}