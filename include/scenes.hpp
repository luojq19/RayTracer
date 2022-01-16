#ifndef SCENES_H
#define SCENES_H

#include "hittable_list.hpp"
#include "ncolor.hpp"
#include "utils.hpp"
#include "nsphere.hpp"
#include "moving_sphere.hpp"
#include "ntriangle.hpp"
#include "bvh.hpp"
#include "aarect.hpp"
#include "box.hpp"
#include "translate.hpp"
#include "constant_medium.hpp"
#include "mesh.hpp"

struct Scene {
    Group world;
    color background;
    double aspect_ratio;
    camera cam;
};

Scene random_scene();
Scene random_scene_motion();
Scene random_scene_motion_texture();
Scene two_spheres();
Scene two_perlin_spheres();
Scene earth();
Scene simple_light();
Scene cornell_box();
Scene cornell_box_smoke();
Scene final_scene();
Scene meshTest();
Scene allObjects();

Scene random_scene() {
    Group world;
    double aspect_ratio = 16.0 / 9.0;
    color background(0.7, 0.8, 1.0);
    point3 lookfrom(13, 2, 3);
    point3 lookat(0, 0, 0);
    Vector3f vup(0,1,0);
    auto dist_to_focus = 10.0;
    auto aperture = 0.1;
    double vfov = 20.0;
    camera cam(lookfrom, lookat, vup, vfov, aspect_ratio, aperture, dist_to_focus, aperture, 1.0);

    auto ground_material = make_shared<lambertian>(color(0.5, 0.5, 0.5));
    world.add(make_shared<sphere>(point3(0,-1000,0), 1000, ground_material));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = random_double();
            point3 center(a + 0.9*random_double(), 0.2, b + 0.9*random_double());

            if ((center - point3(4, 0.2, 0)).length() > 0.9) {
                shared_ptr<material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = randomV() * randomV();
                    sphere_material = make_shared<lambertian>(albedo);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                } else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = randomV(0.5, 1);
                    auto fuzz = random_double(0, 0.5);
                    sphere_material = make_shared<metal>(albedo, fuzz);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                } else {
                    // glass
                    sphere_material = make_shared<dielectric>(1.5);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }
    auto material1 = make_shared<dielectric>(1.5);
    world.add(make_shared<sphere>(point3(0, 1, 0), 1.0, material1));

    auto material2 = make_shared<lambertian>(color(0.4, 0.2, 0.1));
    world.add(make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));

    auto material3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
    world.add(make_shared<sphere>(point3(4, 1, 0), 1.0, material3));

    Scene s{Group(make_shared<bvh_node>(world, 0.0, 1.0)), background, aspect_ratio, cam};

    return s;
}

Scene random_scene_motion() {
    Group world;
    double aspect_ratio = 16.0 / 9.0;
    color background(0.7, 0.8, 1.0);
    point3 lookfrom(13, 2, 3);
    point3 lookat(0, 0, 0);
    Vector3f vup(0,1,0);
    auto dist_to_focus = 10.0;
    auto aperture = 0.1;
    double vfov = 20.0;
    camera cam(lookfrom, lookat, vup, vfov, aspect_ratio, aperture, dist_to_focus, aperture, 1.0);

    auto ground_material = make_shared<lambertian>(color(0.5, 0.5, 0.5));
    world.add(make_shared<sphere>(point3(0,-1000,0), 1000, ground_material));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = random_double();
            point3 center(a + 0.9*random_double(), 0.2, b + 0.9*random_double());

            if ((center - point3(4, 0.2, 0)).length() > 0.9) {
                shared_ptr<material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = randomV() * randomV();
                    sphere_material = make_shared<lambertian>(albedo);
                    auto center2 = center + Vector3f(0, random_double(0,.5), 0);
                    world.add(make_shared<moving_sphere>(center, center2, 0.0, 1.0, 0.2, sphere_material));
                } else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = randomV(0.5, 1);
                    auto fuzz = random_double(0, 0.5);
                    sphere_material = make_shared<metal>(albedo, fuzz);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                } else {
                    // glass
                    sphere_material = make_shared<dielectric>(1.5);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }
    auto material1 = make_shared<dielectric>(1.5);
    world.add(make_shared<sphere>(point3(0, 1, 0), 1.0, material1));

    auto material2 = make_shared<lambertian>(color(0.4, 0.2, 0.1));
    world.add(make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));

    auto material3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
    world.add(make_shared<sphere>(point3(4, 1, 0), 1.0, material3));

    Scene s{Group(make_shared<bvh_node>(world, 0.0, 1.0)), background, aspect_ratio, cam};

    return s;
}

Scene random_scene_motion_texture() {
    Group world;
    double aspect_ratio = 16.0 / 9.0;
    color background(0.7, 0.8, 1.0);
    point3 lookfrom(13, 2, 3);
    point3 lookat(0, 0, 0);
    Vector3f vup(0,1,0);
    auto dist_to_focus = 10.0;
    auto aperture = 0.1;
    double vfov = 20.0;
    camera cam(lookfrom, lookat, vup, vfov, aspect_ratio, aperture, dist_to_focus, aperture, 1.0);

    auto ground_material = make_shared<lambertian>(color(0.5, 0.5, 0.5));
    world.add(make_shared<sphere>(point3(0,-1000,0), 1000, ground_material));

    auto checker = make_shared<checker_texture>(color(0.2, 0.3, 0.1), color(0.9, 0.9, 0.9));
    world.add(make_shared<sphere>(point3(0,-1000,0), 1000, make_shared<lambertian>(checker)));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = random_double();
            point3 center(a + 0.9*random_double(), 0.2, b + 0.9*random_double());

            if ((center - point3(4, 0.2, 0)).length() > 0.9) {
                shared_ptr<material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = randomV() * randomV();
                    sphere_material = make_shared<lambertian>(albedo);
                    auto center2 = center + Vector3f(0, random_double(0,.5), 0);
                    world.add(make_shared<moving_sphere>(center, center2, 0.0, 1.0, 0.2, sphere_material));
                } else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = randomV(0.5, 1);
                    auto fuzz = random_double(0, 0.5);
                    sphere_material = make_shared<metal>(albedo, fuzz);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                } else {
                    // glass
                    sphere_material = make_shared<dielectric>(1.5);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }
    auto material1 = make_shared<dielectric>(1.5);
    world.add(make_shared<sphere>(point3(0, 1, 0), 1.0, material1));

    auto material2 = make_shared<lambertian>(color(0.4, 0.2, 0.1));
    world.add(make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));

    auto material3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
    world.add(make_shared<sphere>(point3(4, 1, 0), 1.0, material3));

    Scene s{Group(make_shared<bvh_node>(world, 0.0, 1.0)), background, aspect_ratio, cam};

    return s;
}

Scene two_spheres() {
    Group objects;
    double aspect_ratio = 16.0 / 9.0;
    color background(0.7, 0.8, 1.0);
    point3 lookfrom(13, 2, 3);
    point3 lookat(0, 0, 0);
    Vector3f vup(0,1,0);
    auto dist_to_focus = 10.0;
    auto aperture = 0.0;
    double vfov = 20.0;
    camera cam(lookfrom, lookat, vup, vfov, aspect_ratio, aperture, dist_to_focus, 0.0, 1.0);

    auto checker = make_shared<checker_texture>(color(0.2, 0.3, 0.1), color(0.9, 0.9, 0.9));

    objects.add(make_shared<sphere>(point3(0,-10, 0), 10, make_shared<lambertian>(checker)));
    objects.add(make_shared<sphere>(point3(0, 10, 0), 10, make_shared<lambertian>(checker)));

    Scene s{objects, background, aspect_ratio, cam};

    return s;
}

Scene two_perlin_spheres() {
    Group objects;
    double aspect_ratio = 16.0 / 9.0;
    color background(0.7, 0.8, 1.0);
    point3 lookfrom(13, 2, 3);
    point3 lookat(0, 0, 0);
    Vector3f vup(0,1,0);
    auto dist_to_focus = 10.0;
    auto aperture = 0.0;
    double vfov = 20.0;
    camera cam(lookfrom, lookat, vup, vfov, aspect_ratio, aperture, dist_to_focus, 0.0, 1.0);

    auto pertext = make_shared<noise_texture>(8);
    objects.add(make_shared<sphere>(point3(0,-1000,0), 1000, make_shared<lambertian>(pertext)));
    objects.add(make_shared<sphere>(point3(0, 2, 0), 2, make_shared<lambertian>(pertext)));

    Scene s{objects, background, aspect_ratio, cam};

    return s;
}

Scene earth() {
    Group objects;
    double aspect_ratio = 16.0 / 9.0;
    color background(0.7, 0.8, 1.0);
    point3 lookfrom(0, 0, 12);
    point3 lookat(0, 0, 0);
    Vector3f vup(0,1,0);
    auto dist_to_focus = 10.0;
    auto aperture = 0.0;
    double vfov = 20.0;
    camera cam(lookfrom, lookat, vup, vfov, aspect_ratio, aperture, dist_to_focus, 0.0, 1.0);
    const char* filename = "textures/earthmap.jpg";
    auto earth_texture = make_shared<image_texture>(filename);
    auto earth_surface = make_shared<lambertian>(earth_texture);
    auto globe = make_shared<sphere>(point3(0,0,0), 2, earth_surface);
    objects.add(globe);

    Scene s{objects, background, aspect_ratio, cam};

    return s;
}

Scene simple_light() {
    Group objects;
    double aspect_ratio = 16.0 / 9.0;
    color background(0, 0, 0);
    point3 lookfrom(26, 3, 6);
    point3 lookat(0, 2, 0);
    Vector3f vup(0,1,0);
    auto dist_to_focus = 10.0;
    auto aperture = 0.0;
    double vfov = 20.0;
    camera cam(lookfrom, lookat, vup, vfov, aspect_ratio, aperture, dist_to_focus, 0.0, 1.0);

    auto pertext = make_shared<noise_texture>(4);
    objects.add(make_shared<sphere>(point3(0,-1000,0), 1000, make_shared<lambertian>(pertext)));
    objects.add(make_shared<sphere>(point3(0,2,0), 2, make_shared<lambertian>(pertext)));

    auto difflight = make_shared<diffuse_light>(color(4,4,4));
    objects.add(make_shared<xy_rect>(3, 5, 1, 3, -2, difflight));

    Scene s{objects, background, aspect_ratio, cam};

    return s;
}

Scene cornell_box() {
    Group objects;
    double aspect_ratio = 1.0;
    color background(0, 0, 0);
    point3 lookfrom(278, 278, -800);
    point3 lookat(278, 278, 0);
    Vector3f vup(0,1,0);
    auto dist_to_focus = 10.0;
    auto aperture = 0.0;
    double vfov = 40.0;
    camera cam(lookfrom, lookat, vup, vfov, aspect_ratio, aperture, dist_to_focus, 0.0, 1.0);

    auto red   = make_shared<lambertian>(color(.65, .05, .05));
    auto white = make_shared<lambertian>(color(.73, .73, .73));
    auto green = make_shared<lambertian>(color(.12, .45, .15));
    auto light = make_shared<diffuse_light>(color(15, 15, 15));

    objects.add(make_shared<yz_rect>(0, 555, 0, 555, 555, green));
    objects.add(make_shared<yz_rect>(0, 555, 0, 555, 0, red));
    objects.add(make_shared<xz_rect>(213, 343, 227, 332, 554, light));
    objects.add(make_shared<xz_rect>(0, 555, 0, 555, 0, white));
    objects.add(make_shared<xz_rect>(0, 555, 0, 555, 555, white));
    objects.add(make_shared<xy_rect>(0, 555, 0, 555, 555, white));
    shared_ptr<hittable> box1 = make_shared<box>(point3(0, 0, 0), point3(165, 330, 165), white);
    box1 = make_shared<rotate_y>(box1, 15);
    box1 = make_shared<translate>(box1, Vector3f(265,0,295));
    objects.add(box1);

    shared_ptr<hittable> box2 = make_shared<box>(point3(0,0,0), point3(165,165,165), white);
    box2 = make_shared<rotate_y>(box2, -18);
    box2 = make_shared<translate>(box2, Vector3f(130,0,65));
    objects.add(box2);

    Scene s{objects, background, aspect_ratio, cam};

    return s;
}

Scene cornell_box_smoke() {
    Group objects;
    double aspect_ratio = 1.0;
    color background(0, 0, 0);
    point3 lookfrom(278, 278, -800);
    point3 lookat(278, 278, 0);
    Vector3f vup(0,1,0);
    auto dist_to_focus = 10.0;
    auto aperture = 0.0;
    double vfov = 40.0;
    camera cam(lookfrom, lookat, vup, vfov, aspect_ratio, aperture, dist_to_focus, 0.0, 1.0);

    auto red   = make_shared<lambertian>(color(.65, .05, .05));
    auto white = make_shared<lambertian>(color(.73, .73, .73));
    auto green = make_shared<lambertian>(color(.12, .45, .15));
    auto light = make_shared<diffuse_light>(color(7, 7, 7));

    objects.add(make_shared<yz_rect>(0, 555, 0, 555, 555, green));
    objects.add(make_shared<yz_rect>(0, 555, 0, 555, 0, red));
    objects.add(make_shared<xz_rect>(113, 443, 127, 432, 554, light));
    objects.add(make_shared<xz_rect>(0, 555, 0, 555, 555, white));
    objects.add(make_shared<xz_rect>(0, 555, 0, 555, 0, white));
    objects.add(make_shared<xy_rect>(0, 555, 0, 555, 555, white));

    shared_ptr<hittable> box1 = make_shared<box>(point3(0,0,0), point3(165,330,165), white);
    box1 = make_shared<rotate_y>(box1, 15);
    box1 = make_shared<translate>(box1, Vector3f(265,0,295));

    shared_ptr<hittable> box2 = make_shared<box>(point3(0,0,0), point3(165,165,165), white);
    box2 = make_shared<rotate_y>(box2, -18);
    box2 = make_shared<translate>(box2, Vector3f(130,0,65));

    objects.add(make_shared<constant_medium>(box1, 0.01, color(0,0,0)));
    objects.add(make_shared<constant_medium>(box2, 0.01, color(1,1,1)));

    Scene s{objects, background, aspect_ratio, cam};

    return s;
}

Scene final_scene() {
    Group boxes1;
    double aspect_ratio = 3.0 / 2.0;
    color background(0, 0, 0);
    point3 lookfrom(478, 278, -600);
    point3 lookat(278, 278, 0);
    Vector3f vup(0,1,0);
    auto dist_to_focus = (lookfrom - lookat).length();
    auto aperture = 0.0;
    double vfov = 40.0;
    camera cam(lookfrom, lookat, vup, vfov, aspect_ratio, aperture, dist_to_focus, 0.0, 1.0);
    auto ground = make_shared<lambertian>(color(0.48, 0.83, 0.53));

    const int boxes_per_side = 20;
    for (int i = 0; i < boxes_per_side; i++) {
        for (int j = 0; j < boxes_per_side; j++) {
            auto w = 100.0;
            auto x0 = -1000.0 + i*w;
            auto z0 = -1000.0 + j*w;
            auto y0 = 0.0;
            auto x1 = x0 + w;
            auto y1 = random_double(1,101);
            auto z1 = z0 + w;

            boxes1.add(make_shared<box>(point3(x0,y0,z0), point3(x1,y1,z1), ground));
        }
    }

    Group objects;

    objects.add(make_shared<bvh_node>(boxes1, 0, 1));

    auto light = make_shared<diffuse_light>(color(7, 7, 7));
    objects.add(make_shared<xz_rect>(123, 423, 147, 412, 554, light));

    auto center1 = point3(400, 400, 200);
    auto center2 = center1 + Vector3f(30,0,0);
    auto moving_sphere_material = make_shared<lambertian>(color(0.7, 0.3, 0.1));
    objects.add(make_shared<moving_sphere>(center1, center2, 0, 1, 50, moving_sphere_material));

    objects.add(make_shared<sphere>(point3(260, 150, 45), 50, make_shared<dielectric>(1.5)));
    objects.add(make_shared<sphere>(
        point3(0, 150, 145), 50, make_shared<metal>(color(0.8, 0.8, 0.9), 1.0)
    ));

    auto boundary = make_shared<sphere>(point3(360,150,145), 70, make_shared<dielectric>(1.5));
    objects.add(boundary);
    objects.add(make_shared<constant_medium>(boundary, 0.2, color(0.2, 0.4, 0.9)));
    boundary = make_shared<sphere>(point3(0, 0, 0), 5000, make_shared<dielectric>(1.5));
    objects.add(make_shared<constant_medium>(boundary, .0001, color(1,1,1)));

    auto emat = make_shared<lambertian>(make_shared<image_texture>("textures/earthmap.jpg"));
    objects.add(make_shared<sphere>(point3(400,200,400), 100, emat));
    auto pertext = make_shared<noise_texture>(0.1);
    objects.add(make_shared<sphere>(point3(220,280,300), 80, make_shared<lambertian>(pertext)));

    Group boxes2;
    auto white = make_shared<lambertian>(color(.73, .73, .73));
    int ns = 1000;
    for (int j = 0; j < ns; j++) {
        boxes2.add(make_shared<sphere>(point3(random_double(0,165), random_double(0,165), random_double(0,165)), 10, white));
    }

    objects.add(make_shared<translate>(
        make_shared<rotate_y>(
            make_shared<bvh_node>(boxes2, 0.0, 1.0), 15),
            Vector3f(-100,270,395)
        )
    );

    Scene s{objects, background, aspect_ratio, cam};

    return s;
}

Scene meshTest() {
    Group world;
    double aspect_ratio = 3.0 / 2.0;
    color background(0, 0, 0);
    point3 lookfrom(0, 1, 2);
    point3 lookat(0, 0.2, 0);
    Vector3f vup(0,1,0);
    auto dist_to_focus = (lookfrom - lookat).length();
    auto aperture = 0.0;
    double vfov = 30.0;
    camera cam(lookfrom, lookat, vup, vfov, aspect_ratio, aperture, dist_to_focus, 0.0, 1.0);

    auto material_obj = make_shared<lambertian>(color(0.8, 0.6, 0.2));
    auto light = make_shared<diffuse_light>(color(7, 7, 7));
    auto ground_material = make_shared<lambertian>(color(0.5, 0.5, 0.5));
    auto glass = make_shared<dielectric>(1.5);
    auto metal1 = make_shared<metal>(color(0.5, 0.5, 0.5), 0.1);
    const char* filename = "textures/earthmap.jpg";
    auto earth_texture = make_shared<image_texture>(filename);
    auto earth_surface = make_shared<lambertian>(earth_texture);
    auto checker = make_shared<checker_texture>(color(0.2, 0.3, 0.1), color(0.9, 0.9, 0.9));

    world.add(make_shared<sphere>(point3(0,-1000,0), 1000, make_shared<lambertian>(checker)));
    Group rabbit;
    rabbit.add(make_shared<Mesh>("mesh/bunny_1k.obj", material_obj));
    world.add(make_shared<bvh_node>(rabbit, 0, 0));
    world.add(make_shared<sphere>(point3(0.3, 0.2, 0.3), 0.15, earth_surface));
    world.add(make_shared<sphere>(point3(-0.5, 0.3, -0.2), 0.3, metal1));
    world.add(make_shared<sphere>(point3(0.3, 0.2, -0.3), 0.2, glass));
    world.add(make_shared<xz_rect>(-1, 1, -1, 1, 2, light));

    Scene s{world, background, aspect_ratio, cam};
    return s;
}

Scene allObjects() {
    Group world;
    double aspect_ratio = 3.0 / 2.0;
    color background(1.0, 1.0, 1.0);
    point3 lookfrom(1, 1, 1);
    point3 lookat(0, 0, 0);
    Vector3f vup(0,1,0);
    auto dist_to_focus = (lookfrom - lookat).length();
    auto aperture = 0.0;
    double vfov = 40.0;
    camera cam(lookfrom, lookat, vup, vfov, aspect_ratio, aperture, dist_to_focus, 0.0, 1.0);

    auto material_obj = make_shared<metal>(color(0.8, 0.6, 0.2), 0.1);
    auto light = make_shared<diffuse_light>(color(7, 7, 7));
    auto ground_material = make_shared<lambertian>(color(0.5, 0.5, 0.5));
    auto glass = make_shared<dielectric>(1.5);

    world.add(make_shared<sphere>(point3(0,-1000,0), 1000, ground_material));
    world.add(make_shared<Mesh>("mesh/bunny_200.obj", material_obj));
    // world.add(make_shared<xz_rect>(5, -5, 5, -5, 0.5, light));
    world.add(make_shared<sphere>(point3(0.3, 0.3, 0), 0.1, light));
    world.add(make_shared<sphere>(point3(-0.3, 0.3, 0), 0.1, glass));

    Scene s{world, background, aspect_ratio, cam};
    return s;
}

#endif