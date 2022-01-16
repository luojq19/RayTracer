#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.hpp"
#include "vecmath.h"
#include "aabb.hpp"

class material;

struct hit_record {
    point3 p;
    Vector3f normal;
    shared_ptr<material> mat_ptr;
    double t;
    bool front_face;
    double u;
    double v;

    //this function sets the normal always points againt the direction of the ray
    inline void set_face_normal(const Ray& r, const Vector3f& outward_normal) {
        front_face = Vector3f::dot(r.getDirection(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

class hittable {
    public:
        virtual bool hit(const Ray& r, double t_min, double t_max, hit_record& rec) const = 0;
        virtual bool bounding_box(double time0, double time1, aabb& output_box) const = 0;

    protected:
        shared_ptr<material> mat_ptr;
};

#endif //new