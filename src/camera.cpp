#include "ray_tracing/camera.h"

void Camera::initialize()
{
    image_height = static_cast<int>(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    center = look_from;

    //auto focal_length = (look_from - look_at).len();
    auto theta = degrees_to_radians(vfov);
    auto h = std::tan(theta / 2.0);
    auto viewport_height = 2.0 * h * focus_dist;
    auto viewport_width = viewport_height * (static_cast<double>(image_width) / image_height);

    w = unit_vector(look_from - look_at);
    u = unit_vector(cross(vup, w));
    v = cross(w, u);
       
    auto viewport_u = viewport_width * u;
    auto viewport_v = viewport_height * -v;

    pixel_delta_u = viewport_u / image_width;
    pixel_delta_v = viewport_v / image_height;

    auto viewport_upper_left = center - (focus_dist * w) - viewport_u / 2.0 - viewport_v / 2.0; 
    pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    auto defocus_radius = focus_dist * std::tan(degrees_to_radians(defocus_angle / 2.0));
    defocus_disk_u = u * defocus_radius;
    defocus_disk_v = v * defocus_radius;
}

void Camera::render(const Hittable& world)
{
    initialize();

    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    for(int i = 0; i < image_height; ++i)
    {
        std::clog << "\rScanlines remaining: " << (image_height - i) << " " << std::flush;
        for(int j = 0; j < image_width; ++j)
        {
            Color pixel_color(0.0, 0.0, 0.0);

            for(int sample = 0; sample < spp; ++sample)
            {
                Ray r = get_ray(j, i);
                pixel_color += ray_color(r, max_depth, world);
            }
            
            write_color(std::cout, pixel_color, spp);
        }
    }
}

point3 Camera::defocus_disk_sample() const
{
    auto p = random_in_unit_disc();

    return center + (p.x * defocus_disk_u) + (p.y * defocus_disk_v);
}

Color Camera::ray_color(const Ray& ray, int depth, const Hittable& world) const
{
    Hit_record rec;

    if(depth <= 0)
        return Color(0.0, 0.0, 0.0);

    if(world.hit(ray, Interval(0.001, infinity), rec))
    {
        Ray scattered;
        Color attenuation;

        if(rec.mat->scatter(ray, rec, attenuation, scattered))
            return attenuation * ray_color(scattered, depth - 1, world);

        return Color(0.0, 0.0, 0.0);
    }

    vec3 unit_direction = ray.direction();
    unit_direction.normalize();

    auto a = 0.5 * (unit_direction.y + 1.0);

    return (1.0 - a) * Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0);
}

Ray Camera::get_ray(int i, int j) const
{
    auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
    auto pixel_sample = pixel_center + pixel_sample_square();

    auto ray_origin = (defocus_angle <= 0) ? center : defocus_disk_sample();
    auto ray_direction = pixel_sample - ray_origin;
    auto ray_time = random_double(); 

    return Ray(ray_origin, ray_direction, ray_time);
}

vec3 Camera::pixel_sample_square() const
{
    auto px = -0.5 + random_double();
    auto py = -0.5 + random_double();

    return (px * pixel_delta_u) + (py * pixel_delta_v);
}