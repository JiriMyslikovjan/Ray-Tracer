#include "ray_tracing/bvh.h"

BvhNode::BvhNode(const std::vector<std::shared_ptr<Hittable>>& src_objects, size_t start, size_t end)
{
    auto objects = src_objects;

    int axis = random_int(0, 2);
    auto comparator = (axis == 0) ? box_x_compare
                    : (axis == 1) ? box_y_compare
                                  : box_z_compare;

    size_t object_span = end - start;

    if(object_span == 1)
        left = right = objects[start];
    
    else if(object_span == 2)
    {
        if(comparator(objects[start], objects[start + 1]))
        {
            left = objects[start];
            right = objects[start + 1];
        }

        else
        {
            left = objects[start + 1];
            right = objects[start];
        }
    }

    else
    {
        std::sort(objects.begin() + start, objects.begin() + end, comparator);

        auto mid = start + object_span / 2;

        left = std::make_shared<BvhNode>(objects, start, mid);
        right = std::make_shared<BvhNode>(objects, mid, end);
    }

    bbox = Aabb(left->bounding_box(), right->bounding_box());
}

bool BvhNode::box_compare(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b, int axis_index)
{
    return a->bounding_box().axis(axis_index).min < b->bounding_box().axis(axis_index).min;
}

bool BvhNode::box_x_compare (const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b)
{
    return box_compare(a, b, 0);
}

bool BvhNode::box_y_compare (const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b)
{
    return box_compare(a, b, 1);
}

bool BvhNode::box_z_compare (const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b)
{
    return box_compare(a, b, 2);
}

bool BvhNode::hit(const Ray& r, Interval ray_t, Hit_record& rec) const 
{
    if(! bbox.hit(r, ray_t))
        return false;

    bool left_hit  = left->hit(r, ray_t, rec);
    bool right_hit = right->hit(r, Interval(ray_t.min, left_hit ? rec.t : ray_t.max), rec);

    return left_hit || right_hit;
}

Aabb BvhNode::bounding_box() const 
{
    return bbox;
}