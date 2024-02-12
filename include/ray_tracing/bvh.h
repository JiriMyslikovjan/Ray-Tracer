#pragma once

#include <algorithm>
#include "ray_tracing/object.h"

class BvhNode : public Hittable
{
    public:
        BvhNode(const Hittable_list& list) : BvhNode(list.objects, 0, list.objects.size()) {}

        BvhNode(const std::vector<std::shared_ptr<Hittable>>& src_objects, size_t start, size_t end);

        bool hit(const Ray& r, Interval ray_t, Hit_record& rec) const override;

        Aabb bounding_box() const override;

    private:
        std::shared_ptr<Hittable> left;
        std::shared_ptr<Hittable> right;
        Aabb bbox;

        static bool box_compare(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b, int axis_index);

        static bool box_x_compare (const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b);

        static bool box_y_compare (const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b);

        static bool box_z_compare (const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b);
};