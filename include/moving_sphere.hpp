#ifndef MOVING_SPHERE_H
#define MOVING_SPHERE_H

#include "utils.hpp"
#include "hittable.hpp"
#include "aabb.hpp"

aabb surrounding_box(aabb box0, aabb box1);

class moving_sphere : public hittable {
    public:
        moving_sphere() {}
        moving_sphere(point3 cen0, point3 cen1, double _time0, double _time1, double r, shared_ptr<material> m): center0(cen0), center1(cen1), time0(_time0), time1(_time1), radius(r), mat_ptr(m){};

        virtual bool hit(const Ray& r, double t_min, double t_max, hit_record& rec) const override;
        virtual bool bounding_box(double _time0, double _time1, aabb& output_box) const override;

        point3 center(double time) const;

    public:
        point3 center0, center1;
        double time0, time1;
        double radius;
        shared_ptr<material> mat_ptr;
};

point3 moving_sphere::center(double time) const {
    return center0 + ((time - time0) / (time1 - time0))*(center1 - center0);
}

bool moving_sphere::hit(const Ray& r, double t_min, double t_max, hit_record& rec) const {
    Vector3f oc = r.getOrigin() - center(r.getTime());
    auto a = r.getDirection().squaredLength();
    auto half_b = Vector3f::dot(oc, r.getDirection());
    auto c = oc.squaredLength() - radius*radius;

    auto discriminant = half_b*half_b - a*c;
    if (discriminant < 0) return false;
    auto sqrtd = sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range.
    auto root = (-half_b - sqrtd) / a;
    if (root < t_min || t_max < root) {
        root = (-half_b + sqrtd) / a;
        if (root < t_min || t_max < root)
            return false;
    }

    rec.t = root;
    rec.p = r.pointAtParameter(rec.t);
    auto outward_normal = (rec.p - center(r.getTime())) / radius;
    rec.set_face_normal(r, outward_normal);
    rec.mat_ptr = mat_ptr;

    return true;
}

bool moving_sphere::bounding_box(double _time0, double _time1, aabb& output_box) const {
    aabb box0(
        center(_time0) - Vector3f(radius, radius, radius),
        center(_time0) + Vector3f(radius, radius, radius));
    aabb box1(
        center(_time1) - Vector3f(radius, radius, radius),
        center(_time1) + Vector3f(radius, radius, radius));
    output_box = surrounding_box(box0, box1);
    return true;
}

#endif