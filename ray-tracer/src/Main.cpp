#include <iostream>

#include "../headers/util.h"
#include "../headers/hittable_list.h"
#include "../headers/sphere.h"
#include "../headers/color.h"
#include "../headers/camera.h"
#include "../headers/material.h"

// Linearly blends white and blue depending on height of y
color ray_color(const ray& r, const hittable& world, int depth) 
{
    hit_record rec;

    // If we've exceeded the ray bounce limit, no more light is gathered
    if (depth <= 0)
        return color(0,0,0);

    // Fixing 'shadow acne' by calculating reflected ray origins with tolerance
    if(world.hit(r, 0.001, infinity, rec))
    {
        ray scattered;
        color attenuation;
        if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
            return attenuation * ray_color(scattered, world, depth-1);
        return color(0,0,0);
    }
    // scale vector down to unit length -1.0 < y < 1.0
    vec3 unit_direction = unit_vector(r.direction());
    // looking at the y component of the unit vector, and scale to 0.0 <= t <= 1.0
    auto t = 0.5*(unit_direction.y() + 1.0);
    // standard linear blend/linear interpolation/lerp
    return (1.0-t)*color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1.0);
}

int main()
{
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 384;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 100;
    const int max_depth = 50;

    // Initial line for PPM file
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    hittable_list world;

    world.add(make_shared<sphere>(
        point3(0,0,-1), 0.5, make_shared<lambertian>(color(0.1, 0.2, 0.5))));

    world.add(make_shared<sphere>(
        point3(0,-100.5,-1), 100, make_shared<lambertian>(color(0.8, 0.8, 0.0))));

    world.add(make_shared<sphere>(point3(1,0,-1), 0.5, make_shared<metal>(color(.8,.6,.2), 0.3)));
    world.add(make_shared<sphere>(point3(-1,0,-1), 0.5, make_shared<dielectric>(1.5)));
    world.add(make_shared<sphere>(point3(-1,0,-1), -0.45 , make_shared<dielectric>(1.5)));

    camera cam(point3(-2, 2, 1), point3(0, 0, -1), vec3(0, 1, 0), 20, aspect_ratio);
    
    for (int j = image_height-1; j >= 0; --j)
    {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i)
        {
            // Rendering with multi-sampled pixels
            color pixel_color(0,0,0);
            for (int s=0; s < samples_per_pixel; ++s)
            {
                auto u = (i + random_double()) / (image_width-1);
                auto v = (j + random_double()) / (image_height-1);
                ray r = cam.get_ray(u,v);
                pixel_color += ray_color(r, world, max_depth);
            }
            write_color(std::cout, pixel_color, samples_per_pixel);
        }
    }
    std::cerr << "\nDone.\n";
}