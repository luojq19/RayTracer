#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>

#include "image.hpp"

#include "ray.hpp"
#include "utils.hpp"
#include "ncolor.hpp"
#include "hittable_list.hpp"
#include "nsphere.hpp"
#include "ncamera.hpp"
#include "scenes.hpp"
#include "aarect.hpp"
#include "ntriangle.hpp"
#include "mesh.hpp"

color ray_color(const Ray& r, const color& background, const hittable& world, int depth) {
    hit_record rec;
    // If we've exceeded the ray bounce limit, no more light is gathered.
    if (depth <= 0)
        return color(0,0,0);

    if (!world.hit(r, 0.001, infinity, rec))
        return background;

    Ray scattered;
    color attenuation;
    color emitted = rec.mat_ptr->emitted(rec.u, rec.v, rec.p);

    if (!rec.mat_ptr->scatter(r, rec, attenuation, scattered))
        return emitted;

    return emitted + attenuation * ray_color(scattered, background, world, depth-1);
}

int main(int argc, char *argv[]) {
    // Scene
    Scene scene = final_scene();

    if (!strcmp(argv[1], "0"))
        scene = random_scene();
    else if (!strcmp(argv[1], "1"))
        scene = random_scene_motion();
    else if (!strcmp(argv[1], "2"))
        scene = random_scene_motion_texture();
    else if (!strcmp(argv[1], "3"))
        scene = two_spheres();
    else if (!strcmp(argv[1], "4"))
        scene = two_perlin_spheres();
    else if (!strcmp(argv[1], "5"))
        scene = earth();
    else if (!strcmp(argv[1], "6"))
        scene = simple_light();
    else if (!strcmp(argv[1], "7"))
        scene = cornell_box();
    else if (!strcmp(argv[1], "8"))
        scene = cornell_box_smoke();
    else if (!strcmp(argv[1], "9"))
        scene = final_scene();
    else if (!strcmp(argv[1], "10"))
        scene = meshTest();
    else if (!strcmp(argv[1], "11"))
        scene = allObjects();
    

    // Image
    const auto aspect_ratio = scene.aspect_ratio;
    const int image_width = 1080;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 5000;
    const int max_depth = 50;
    color background = scene.background;

    // World
    Group world = scene.world;

    // Camera
    camera cam = scene.cam;

    // Render
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = image_height-1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            color pixel_color(0, 0, 0);
            for (int s = 0; s < samples_per_pixel; ++s) {
                auto u = (i + random_double()) / (image_width-1);
                auto v = (j + random_double()) / (image_height-1);
                Ray r = cam.get_ray(u, v);
                pixel_color += ray_color(r, background, world, max_depth);
            }
            write_color(std::cout, pixel_color, samples_per_pixel);
        }
    }

    std::cerr << "\nDone.\n";
}