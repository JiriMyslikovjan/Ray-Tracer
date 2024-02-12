#pragma once

#include <vector>
#include "ray_tracing/ray.h"
#include "ray_tracing/vec3.h"
#include "ray_tracing/utils.h"
#include "ray_tracing/aabb.h"


class Material;

class Hit_record
{
    public:
        point3 p;
        vec3 normal;
        std::shared_ptr<Material> mat;
        double t;
        double u, v;
        bool front_face;

        void set_face_normal(const Ray& r, const vec3& outward_normal);

};

class Hittable
{
    public:
        virtual ~Hittable() = default;

        virtual bool hit(const Ray& r, Interval ray_t, Hit_record& rec) const = 0;

        virtual Aabb bounding_box() const = 0;
};

class Hittable_list : public Hittable
{
    public:
        std::vector<std::shared_ptr<Hittable>> objects;

        Hittable_list();
        
        Hittable_list(std::shared_ptr<Hittable> object);

        void clear();

        void add(std::shared_ptr<Hittable> object);

        bool hit(const Ray& r, Interval ray_t, Hit_record& rec) const override;

        Aabb bounding_box() const override;

        private:
            Aabb bbox;
};

class Sphere : public Hittable
{
    public:
        // Stationary sphere constructor
        Sphere(point3 _center, double _radius, std::shared_ptr<Material> _material)
         : center1(_center), radius(_radius), mat(_material), is_moving(false) 
         {
            auto rvec = vec3(radius, radius, radius);
            bbox = Aabb(center1 - rvec, center1 + rvec);
         }

        // Moving sphere constructor
        Sphere(point3 _center1, point3 _center2, double _radius, std::shared_ptr<Material> _material) 
        : center1(_center1), radius(_radius), mat(_material), is_moving(true)
        {
            auto rvec = vec3(radius, radius, radius);
            Aabb box1 = Aabb(_center1 - rvec, _center1 + rvec);
            Aabb box2 = Aabb(_center2 - rvec, _center2 + rvec);

            bbox = Aabb(box1, box2);

            center_vec = _center2 - _center1;
        }

        Aabb bounding_box() const override;

        bool hit(const Ray &r, Interval ray_t, Hit_record& rec) const override;
    
    private:
        point3 center1;
        double radius;
        std::shared_ptr<Material> mat;
        bool is_moving;
        vec3 center_vec;
        Aabb bbox;

        point3 sphere_center(double time) const;

        static void get_sphere_uv(const point3& p, double& u, double& v);
};