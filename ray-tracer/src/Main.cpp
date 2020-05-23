#include <iostream>

#include "../headers/vec3.h"
#include "../headers/color.h"
#include "../headers/ray.h"

double hit_sphere(const point3& center, double radius, const ray& r)
{
    vec3 oc = r.origin() - center;
    auto a = dot(r.direction(), r.direction());
    auto b = 2.0 * dot(oc, r.direction());
    auto c = dot(oc, oc) - radius*radius;
    auto discriminant = b*b - 4*a*c;
    if (discriminant < 0) 
    {
        return -1.0;
    }
    else
    {
        return (-b - sqrt(discriminant)) / (2.0*a);
    }
}

// Linearly blends white and blue depending on height of y
color ray_color(const ray& r) 
{
    auto t = hit_sphere(point3(0, 0, -1), 0.5, r);
    if (t > 0.0)
    {
        vec3 N = unit_vector(r.at(t) - vec3(0, 0, -1));
        return 0.5*color(N.x()+1, N.y()+1, N.z()+1);
    }
    // scale vector down to unit length -1.0 < y < 1.0
    vec3 unit_direction = unit_vector(r.direction());
    // looking at the y component of the unit vector, and scale to 0.0 <= t <= 1.0
    t = 0.5*(unit_direction.y() + 1.0);
    // standard linear blend/linear interpolation/lerp
    return (1.0-t)*color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1.0);
}

int main()
{
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 256;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    // Initial line for PPM file
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    
    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0;

    point3 origin(0.0, 0.0, 0.0);
    vec3 horizontal(viewport_width, 0.0, 0.0);
    vec3 vertical(0.0, viewport_height, 0.0);
    point3 lower_left_corner = origin - horizontal/2 - vertical/2 - vec3(0, 0, focal_length);

    for (int j = image_height-1; j >= 0; --j)
    {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = image_width-1; i >= 0; --i)
        {
            auto u = double(i) / (image_width-1);
            auto v = double(j) / (image_height-1);
            ray r(origin, lower_left_corner + u*horizontal + v*vertical);
            color pixel_color = ray_color(r);
            write_color(std::cout, pixel_color);
        }
    }
    std::cerr << "\nDone.\n";
}