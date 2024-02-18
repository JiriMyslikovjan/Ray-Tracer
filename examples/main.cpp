#include <iostream>
#include "ray_tracing/vec3.h"
#include "ray_tracing/Color.h"
#include "ray_tracing/ray.h"
#include "ray_tracing/object.h"
#include "ray_tracing/utils.h"
#include "ray_tracing/camera.h"
#include "ray_tracing/material.h"
#include "ray_tracing/bvh.h"

void random_spheres()
{
        // World
    Hittable_list world;

    auto checker = std::make_shared<CheckerTexture>(0.32, Color(.2, .3, .1), Color(.9, .9, .9));
    world.add(std::make_shared<Sphere>(point3(0,-1000,0), 1000, std::make_shared<Lambertian>(checker)));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = random_double();
            point3 center(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());

            if ((center - point3(4, 0.2, 0)).len() > 0.9) {
                std::shared_ptr<Material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = Color::random() * Color::random();
                    sphere_material = std::make_shared<Lambertian>(albedo);
                    auto center2 = center + vec3(0, random_double(0,.5), 0);
                    world.add(std::make_shared<Sphere>(center, center2, 0.2, sphere_material));
                } else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = Color::random(0.5, 1);
                    auto fuzz = random_double(0, 0.5);
                    sphere_material = std::make_shared<Metal>(albedo, fuzz);
                    world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
                } else {
                    // glass
                    sphere_material = std::make_shared<Dielectric>(1.5);
                    world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = std::make_shared<Dielectric>(1.5);
    world.add(std::make_shared<Sphere>(point3(0, 1, 0), 1.0, material1));

    auto material2 = std::make_shared<Lambertian>(Color(0.4, 0.2, 0.1));
    world.add(std::make_shared<Sphere>(point3(-4, 1, 0), 1.0, material2));

    auto material3 = std::make_shared<Metal>(Color(0.7, 0.6, 0.5), 0.0);
    world.add(std::make_shared<Sphere>(point3(4, 1, 0), 1.0, material3));

    world = Hittable_list(std::make_shared<BvhNode>(world));
    
    Camera cam;

    cam.aspect_ratio      = 16.0 / 9.0;
    cam.image_width       = 400;
    cam.spp               = 100;
    cam.max_depth         = 50;

    cam.vfov      = 20;
    cam.look_from = point3(13,2,3);
    cam.look_at   = point3(0,0,0);
    cam.vup       = vec3(0,1,0);

    cam.defocus_angle = 0.6;
    cam.focus_dist    = 10.0;

    cam.render(world); 
}

void two_spheres() {
    Hittable_list world;

    auto checker = std::make_shared<CheckerTexture>(0.8, Color(.2, .3, .1), Color(.9, .9, .9));

    world.add(std::make_shared<Sphere>(point3(0,-10, 0), 10, std::make_shared<Lambertian>(checker)));
    world.add(std::make_shared<Sphere>(point3(0, 10, 0), 10, std::make_shared<Lambertian>(checker)));

    Camera cam;

    cam.aspect_ratio      = 16.0 / 9.0;
    cam.image_width       = 400;
    cam.spp = 100;
    cam.max_depth         = 50;

    cam.vfov     = 20;
    cam.look_from = point3(13,2,3);
    cam.look_at   = point3(0,0,0);
    cam.vup      = vec3(0,1,0);

    cam.defocus_angle = 0;

    cam.render(world);
}

void two_perlin_spheres() {
    Hittable_list world;

    auto pertext = std::make_shared<NoiseTexture>(4);
    world.add(std::make_shared<Sphere>(point3(0,-1000,0), 1000, std::make_shared<Lambertian>(pertext)));
    world.add(std::make_shared<Sphere>(point3(0,2,0), 2, std::make_shared<Lambertian>(pertext)));

    Camera cam;

    cam.aspect_ratio      = 16.0 / 9.0;
    cam.image_width       = 400;
    cam.spp = 100;
    cam.max_depth         = 50;

    cam.vfov     = 20;
    cam.look_from = point3(13,2,3);
    cam.look_at   = point3(0,0,0);
    cam.vup      = vec3(0,1,0);

    cam.defocus_angle = 0;

    cam.render(world);
}

void earth() {
    auto earth_texture = std::make_shared<ImageTexture>("earthmap.jpg");
    auto earth_surface = std::make_shared<Lambertian>(earth_texture);
    auto globe = std::make_shared<Sphere>(point3(0,0,0), 2, earth_surface);

    Camera cam;

    cam.aspect_ratio      = 16.0 / 9.0;
    cam.image_width       = 400;
    cam.spp = 100;
    cam.max_depth         = 50;

    cam.vfov     = 20;
    cam.look_from = point3(0,0,12);
    cam.look_at   = point3(0,0,0);
    cam.vup      = vec3(0,1,0);

    cam.defocus_angle = 0;

    cam.render(Hittable_list(globe));
}

void quads() {
    Hittable_list world;

    // Materials
    auto left_red     = std::make_shared<Lambertian>(Color(1.0, 0.2, 0.2));
    auto back_green   = std::make_shared<Lambertian>(Color(0.2, 1.0, 0.2));
    auto right_blue   = std::make_shared<Lambertian>(Color(0.2, 0.2, 1.0));
    auto upper_orange = std::make_shared<Lambertian>(Color(1.0, 0.5, 0.0));
    auto lower_teal   = std::make_shared<Lambertian>(Color(0.2, 0.8, 0.8));

    // Quads
    world.add(std::make_shared<Quad>(point3(-3,-2, 5), vec3(0, 0,-4), vec3(0, 4, 0), left_red));
    world.add(std::make_shared<Quad>(point3(-2,-2, 0), vec3(4, 0, 0), vec3(0, 4, 0), back_green));
    world.add(std::make_shared<Quad>(point3( 3,-2, 1), vec3(0, 0, 4), vec3(0, 4, 0), right_blue));
    world.add(std::make_shared<Quad>(point3(-2, 3, 1), vec3(4, 0, 0), vec3(0, 0, 4), upper_orange));
    world.add(std::make_shared<Quad>(point3(-2,-3, 5), vec3(4, 0, 0), vec3(0, 0,-4), lower_teal));

    Camera cam;

    cam.aspect_ratio      = 1.0;
    cam.image_width       = 400;
    cam.spp               = 100;
    cam.max_depth         = 50;

    cam.vfov      = 80;
    cam.look_from = point3(0,0,9);
    cam.look_at   = point3(0,0,0);
    cam.vup       = vec3(0,1,0);

    cam.defocus_angle = 0;

    cam.render(world);
}

// TODO: Add lights

int main()
{   
    switch (5)
    {
        case 1:
            random_spheres();
            break;
        
        case 2:
            two_spheres();
            break;

        case 3:
            earth();
            break;
        
        case 4:
            two_perlin_spheres();
            break;
        
        case 5:
            quads();
            break;
        
        default:
            break;
    }
    return 0;
}