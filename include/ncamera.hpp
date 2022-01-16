#ifndef NCAMERA_H
#define NCAMERA_H

#include "utils.hpp"

class camera {
    public:
        camera(point3 lookfrom, point3 lookat, Vector3f vup, double vfov, double aspect_ratio, double aperture, double focus_dist, double _time0, double _time1) {
            auto theta = degrees_to_radians(vfov);
            auto h = tan(theta/2);
            auto viewport_height = 2.0 * h;
            auto viewport_width = aspect_ratio * viewport_height;

            w = (lookfrom - lookat).normalized();
            u = Vector3f::cross(vup, w);
            v = Vector3f::cross(w, u);

            origin = lookfrom;
            horizontal = focus_dist * viewport_width * u;
            vertical = focus_dist * viewport_height * v;
            lower_left_corner = origin - horizontal/2 - vertical/2 - focus_dist*w;

            lens_radius = aperture / 2;
            time0 = _time0;
            time1 = _time1;
        }


        Ray get_ray(double s, double t) const {
            Vector3f rd = lens_radius * random_in_unit_disk();
            Vector3f offset = u * rd.x() + v * rd.y();

            return Ray(origin + offset, lower_left_corner + s*horizontal + t*vertical - origin - offset, random_double(time0, time1));
        }

    private:
        point3 origin;
        point3 lower_left_corner;
        Vector3f horizontal;
        Vector3f vertical;
        Vector3f u, v, w;
        double lens_radius;
        double time0, time1;
};
#endif