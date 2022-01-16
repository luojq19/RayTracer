#ifndef MESH_H
#define MESH_H
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <utility>
#include <sstream>
#include <vector>
#include "hittable.hpp"
#include "ntriangle.hpp"
#include "Vector2f.h"
#include "Vector3f.h"


class Mesh : public hittable {

public:
    Mesh(const char *filename, shared_ptr<material> m);

    struct TriangleIndex {
        TriangleIndex() {
            x[0] = 0; x[1] = 0; x[2] = 0;
        }
        int &operator[](const int i) { return x[i]; }
        // By Computer Graphics convention, counterclockwise winding is front face
        int x[3]{};
    };

    std::vector<Vector3f> v;
    std::vector<TriangleIndex> t;
    std::vector<Vector3f> n;
    virtual bool hit(const Ray& r, double t_min, double t_max, hit_record& rec) const override;
    virtual bool bounding_box(double _time0, double _time1, aabb& output_box) const override;

private:
    shared_ptr<material> mat_ptr;
    // Normal can be used for light estimation
    void computeNormal();
};

bool Mesh::hit(const Ray& r, double t_min, double t_max, hit_record& rec) const {

    // Optional: Change this brute force method into a faster one.
    bool result = false;
    for (int triId = 0; triId < (int) t.size(); ++triId) {
        TriangleIndex triIndex = t[triId];
        triangle tri(v[triIndex[0]], v[triIndex[1]], v[triIndex[2]], mat_ptr);
        tri.normal = n[triId];
        result |= tri.hit(r, t_min, t_max, rec);
    }
    return result;
}

Mesh::Mesh(const char *filename, shared_ptr<material> m) : mat_ptr(m) {

    // Optional: Use tiny obj loader to replace this simple one.
    std::ifstream f;
    f.open(filename);
    if (!f.is_open()) {
        std::cout << "Cannot open " << filename << "\n";
        return;
    }
    std::string line;
    std::string vTok("v");
    std::string fTok("f");
    std::string texTok("vt");
    char bslash = '/', space = ' ';
    std::string tok;
    int texID;
    while (true) {
        std::getline(f, line);
        if (f.eof()) {
            break;
        }
        if (line.size() < 3) {
            continue;
        }
        if (line.at(0) == '#') {
            continue;
        }
        std::stringstream ss(line);
        ss >> tok;
        if (tok == vTok) {
            Vector3f vec;
            ss >> vec[0] >> vec[1] >> vec[2];
            v.push_back(vec);
        } else if (tok == fTok) {
            if (line.find(bslash) != std::string::npos) {
                std::replace(line.begin(), line.end(), bslash, space);
                std::stringstream facess(line);
                TriangleIndex trig;
                facess >> tok;
                for (int ii = 0; ii < 3; ii++) {
                    facess >> trig[ii] >> texID;
                    trig[ii]--;
                }
                t.push_back(trig);
            } else {
                TriangleIndex trig;
                for (int ii = 0; ii < 3; ii++) {
                    ss >> trig[ii];
                    trig[ii]--;
                }
                t.push_back(trig);
            }
        } else if (tok == texTok) {
            Vector2f texcoord;
            ss >> texcoord[0];
            ss >> texcoord[1];
        }
    }
    computeNormal();

    f.close();
}

void Mesh::computeNormal() {
    n.resize(t.size());
    for (int triId = 0; triId < (int) t.size(); ++triId) {
        TriangleIndex& triIndex = t[triId];
        Vector3f a = v[triIndex[1]] - v[triIndex[0]];
        Vector3f b = v[triIndex[2]] - v[triIndex[0]];
        b = Vector3f::cross(a, b);
        n[triId] = b / b.length();
    }
}

bool Mesh::bounding_box(double _time0, double _time1, aabb& box) const {
    std::vector<triangle> list;
    for (int triId = 0; triId < (int) t.size(); ++triId) {
        TriangleIndex triIndex = t[triId];
        triangle tri(v[triIndex[0]], v[triIndex[1]], v[triIndex[2]], mat_ptr);
        list.push_back(tri);
    }

    if (list.size() < 1)
		return false;
	aabb temp_box;
	bool first_true = list[0].bounding_box(_time0, _time1, temp_box);

	if (!first_true)
		return false;
	else
		box = temp_box;

	for (int i = 1; i < list.size(); i++) {
		if (list[i].bounding_box(_time0, _time1, temp_box))
			box = surrounding_box(box, temp_box);
		else
			return false;
	}

	return true;
}

#endif
