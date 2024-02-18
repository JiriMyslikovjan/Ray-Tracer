#include "ray_tracing/object.h"

// NOTE: "outward_normal" is assumed to be normalized
void Hit_record::set_face_normal(const Ray& r, const vec3& outward_normal)
{
    front_face = dot(r.direction(), outward_normal) < 0;
    normal = front_face ? outward_normal : -outward_normal;
}

Hittable_list::Hittable_list() {}
        
Hittable_list::Hittable_list(std::shared_ptr<Hittable> object)
{
    add(object);
}

void Hittable_list::clear()
{
    objects.clear();
}

void Hittable_list::add(std::shared_ptr<Hittable> object)
{
    objects.push_back(object);
    bbox = Aabb(bbox, object->bounding_box());
}

bool Hittable_list::hit(const Ray& r, Interval ray_t, Hit_record& rec) const
{
    Hit_record temp_rec;
    bool hit_anything = false;
    auto closest_dist = ray_t.max;

    for(const auto& object : objects)
    {
        if(object->hit(r, Interval(ray_t.min, closest_dist), temp_rec))
        {
            hit_anything = true;
            closest_dist = temp_rec.t;
            rec = temp_rec;
        }
    }

    return hit_anything;
}

Aabb Hittable_list::bounding_box() const
{
    return bbox;
}

point3 Sphere::sphere_center(double time) const
{
    return center1 + time * center_vec;
}

bool Sphere::hit(const Ray &r, Interval ray_t, Hit_record& rec) const
{
    point3 center = is_moving ? sphere_center(r.time()) : center1;
    vec3 oc = r.origin() - center;
    auto a = r.direction().len_squared();
    auto half_b = dot(oc, r.direction());
    auto c = oc.len_squared() - radius * radius;

    auto discriminant = half_b * half_b - a * c;

    if(discriminant < 0)
        return false;
    
    auto sqrtd = std::sqrt(discriminant);

    auto root = (-half_b - sqrtd) / a;

    if(! ray_t.surrounds(root))
    {
        root = (-half_b + sqrtd) / a;

        if(! ray_t.surrounds(root))
            return false;
    }

    rec.t = root;
    rec.p = r.at(rec.t);
    vec3 outward_normal = (rec.p - center) / radius;
    rec.set_face_normal(r, outward_normal);
    get_sphere_uv(outward_normal, rec.u, rec.v);
    rec.mat = mat;

    return true;
}

Aabb Sphere::bounding_box() const 
{
    return bbox;
}

void Sphere::get_sphere_uv(const point3& p, double& u, double&v)
{
    auto theta = acos(-p.y);
    auto phi = atan2(-p.z, p.x) + pi;

    u = phi / (2 * pi);
    v = theta / pi;
}

void Quad::set_bounding_box()
{
    bbox = Aabb(q, q + u + v).pad();
}

Aabb Quad::bounding_box() const 
{
    return bbox;
}

bool Quad::hit(const Ray &r, Interval ray_t, Hit_record& rec) const 
{
    double denom = dot(normal, r.direction());

    // No hit if the ray is parallel to the plane
    if(fabs(denom) < 1e-8)
        return false;

    double t = (d - dot(normal, r.origin())) / denom;

    // Return false of the hit point parameter t is outside the ray interval
    if(! ray_t.contains(t))
        return false;

    point3 intersection = r.at(t);
    vec3 planar_hitpt_vec = intersection - q;
    double alpha = dot(w, cross(planar_hitpt_vec, v));
    double beta = dot(w, cross(u, planar_hitpt_vec));

    if(! is_interior(alpha, beta, rec))
        return false;

    rec.t = t;
    rec.p = intersection;
    rec.mat = mat;
    rec.set_face_normal(r, normal);

    return true;
}

// Given hit point in plane coordinates, return false if it is outside the primitive
// Otherwise set the hit record U V coordinates and return true
bool Quad::is_interior(double a, double b, Hit_record& rec) const
{
    if((a < 0) || (1 < a) || (b < 0) || (1 < b))
        return false;

    rec.u = a;
    rec.v = b;

    return true;
}
