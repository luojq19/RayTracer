#ifndef NTRIANGLE_H
#define NTRIANGLE_H

#include "hittable.hpp"
#include "vecmath.h"
#include "nmaterial.hpp"

class triangle: public hittable {
    public:
        triangle() {}
        triangle(const Vector3f& a, const Vector3f& b, const Vector3f& c, shared_ptr<material> m, float s=1.0): mat_ptr(m), scale(s) {
            vertices[0] = a;
            vertices[1] = b;
            vertices[2] = c;
            e1 = b - a;
            e2 = c - a;
            normal = Vector3f::cross(e1, e2).normalized();
            d = Vector3f::dot(normal, a);
        }
        virtual bool hit(const Ray& r, double t_min, double t_max, hit_record& rec) const override;
        virtual bool bounding_box(double _time0, double _time1, aabb& output_box) const override;

    public:
        Vector3f normal;
        Vector3f vertices[3];
        Vector3f e1, e2;
        shared_ptr<material> mat_ptr;
        float area;
        float d;
        float scale;
};

bool triangle::hit(const Ray& ray, double t_min, double t_max, hit_record& rec) const {
    Vector3f a = vertices[0], b = vertices[1], c = vertices[2];
    Vector3f pvec = Vector3f::cross(ray.getDirection(), e2);
    float aNum = Vector3f::dot(pvec, e1);

    // Backfacing / nearly parallel, or close to the limit of precision ?
    if (abs(aNum) < 1e-8f) return false;

    Vector3f tvec = ray.getOrigin() - a;
    float u = Vector3f::dot(pvec, tvec) / aNum;
    if (u < 0.0f || u > 1.0f) return false;

    Vector3f qVec = Vector3f::cross(tvec, e1);
    float v = Vector3f::dot(qVec, ray.getDirection()) / aNum;
    if (v < 0.0 || u + v > 1.0f) return false;

    float t = Vector3f::dot(qVec, e2) / aNum;
    if (t < t_min || t > t_max) return false;

    // valid intersection
    rec.u = (a.u() * (1.0f - u - v) + b.u() * u + c.u() * v);
    rec.v = (a.v() * (1.0f - u - v) + b.v() * u + c.v() * v);
    rec.t = t;
    rec.p = ray.pointAtParameter(rec.t);
    rec.normal = normal;
    rec.mat_ptr = mat_ptr;
    return true;
}

bool triangle::bounding_box(double _time0, double _time1, aabb& output_box) const {
    double minx = fmin(vertices[0].x(),fmin(vertices[1].x(),vertices[2].x()));
	double miny = fmin(vertices[0].y(),fmin(vertices[1].y(),vertices[2].y()));
	double minz = fmin(vertices[0].z(),fmin(vertices[1].z(),vertices[2].z()));

	double maxx = fmax(vertices[0].x(),fmax(vertices[1].x(),vertices[2].x()));
	double maxy = fmax(vertices[0].y(),fmax(vertices[1].y(),vertices[2].y()));
	double maxz = fmax(vertices[0].z(),fmax(vertices[1].z(),vertices[2].z()));
	double eps = 1e-5;
	
	Vector3f min = Vector3f(minx-eps,miny-eps,minz-eps);
	Vector3f max = Vector3f(maxx+eps,maxy+eps,maxz+eps);
	//std::cout << "min = " << min << std::endl;
	//std::cout << "max = " << max << std::endl;
	output_box = aabb(min,max);
	return true;
}

#endif