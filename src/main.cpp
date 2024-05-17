#include "color.h"
#include "vector.h"
#include "scene_object.h"
#include "ray.h"
#include "camera.h"

#include <iostream>
#include <fstream>

#include <iterator>
#include <list>
using namespace std;

// Store list of objects
// Sort from z least to greatest (closest to camera to furthest from camera)
// iterate thru each pixel and trace ray from origin = camera_pos, dir = unit vector of pixel vector - camera vector


int main() {

    Camera cam;
        
    // Scene Setup
    World world;

    Normals normals_mat;
    Sphere s = Sphere(1.0, Vec3(0.0, 0.0, 10.0));
    s.set_material(normals_mat);
    world.add(&s);


    // Render
    cam.render("build/Camera_world_test.ppm", world);
    

    return 0;
}