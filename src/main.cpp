#include "color.h"
#include "vector.h"
//#include "vec3.h"
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
    world.add(new Sphere(1.0, newVec3(0.0, 0.0, 10.0)));

    // Render
    cam.render("Camera_world_test.ppm", world);
    

    return 0;
}