#include "color.h"
#include "vector.h"
#include "scene_object.h"
#include "ray.h"
#include "camera.h"

#include <iostream>
#include <fstream>

#include <iterator>
#include <list>
#include <sstream>
#include <string>
using namespace std;

// Store list of objects
// Sort from z least to greatest (closest to camera to furthest from camera)
// iterate thru each pixel and trace ray from origin = camera_pos, dir = unit vector of pixel vector - camera vector

int main() {

    Camera cam;
    cam.max_bounces = 1;
    cam.num_samples = 1;
        
    // Scene Setup
    World world;

    world.add(new Sphere(Vec3(0.0, 0.0, 1.0), 0.5, new Diffuse(Vec3(1.0, 0.0, 0.0))));
    //world.add(new Sphere(Vec3(0.0, 2.5, 5.0), 2.0, new Metal(Vec3(1.0, 0.0, 0.0))));

    //world.add(new Sphere(Vec3(3.0, 0.0, 12.0), 1.0, new Metal(Vec3(0.8, 0.8, 0.8))));
    //world.add(new Sphere(Vec3(0.0, 100.5, 5.0), 100.5, new Diffuse(Vec3(1.0, 0.0, 0.0))));
    //world.add(new Sphere(Vec3(0.0, 100.5, 5.0), 100.5, new Metal(Vec3(1.0, 0.0, 0.0))));

    //world.add(new Sphere(Vec3(-10.0, -10.0, 15.0), 10.0, new Emissive(Vec3(1.0, 1.0, 1.0))));



    // Render
    string s;
    s.append("build/samples=").append(to_string(cam.num_samples)).append(".ppm");
    cam.render(s.c_str(), world);

    return 0;
}