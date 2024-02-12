#pragma once

#include<iostream>

#include "ray_tracing/utils.h"
#include "ray_tracing/vec3.h"
#include "ray_tracing/color.h"
#include "ray_tracing/ray.h"
#include "ray_tracing/object.h"
#include "ray_tracing/material.h"

class Camera
{
    public:
        double aspect_ratio    = 1.0;
        int    image_width     = 100;
        int    spp             = 10;
        int    max_depth       = 10;

        double vfov         = 90.0;
        point3 look_from    = point3(0.0, 0.0, -1.0);
        point3 look_at      = point3(0.0, 0.0, 0.0);
        vec3   vup          = vec3(0.0, 1.0, 0.0);

        double defocus_angle = 0.0;
        double focus_dist    = 10.0;

        void render(const Hittable& world);
    
    private:
        int     image_height;
        point3  center, pixel00_loc;
        vec3    pixel_delta_u, pixel_delta_v;
        vec3    u, v, w;
        vec3 defocus_disk_u, defocus_disk_v;

        void initialize();

        point3 defocus_disk_sample() const;

        Color ray_color(const Ray& ray, int depth, const Hittable& world) const;

        Ray get_ray(int i, int j) const;

        vec3 pixel_sample_square() const;
};