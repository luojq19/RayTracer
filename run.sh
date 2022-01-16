#!/bin/bash

if [[ ! -d build ]]; then
    echo "good"
else
    rm -rf build
fi
mkdir -p build
cd build
cmake ..
make -j
cd ..

mkdir -p output
# time bin/PA1 0 > output/random_scene.ppm
# time bin/PA1 1 > output/random_scene_motion.ppm
# time bin/PA1 2 > output/random_scene_motion_texture.ppm
# time bin/PA1 3 > output/two_spheres.ppm
# time bin/PA1 4 > output/two_perlin_spheres.ppm
# time bin/PA1 5 > output/earth.ppm
# time bin/PA1 6 > output/simple_light.ppm
# time bin/PA1 7 > output/cornell_box.ppm
# time bin/PA1 8 > output/cornell_box_smoke.ppm
# time bin/PA1 9 > output/final_scene.ppm
time bin/PA1 10 > output/meshTest.ppm
# time bin/PA1 11 > output/allObjects.ppm