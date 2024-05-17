#ifndef VEC3_H
#define VEC3_H

#include "color.h"
#include "vector.h"
#include "world.h"

#include <cmath>
#include <iostream>

#include <fstream>

#include <iterator>
#include <list>

using namespace std;

class Camera {
    public:
        // Viewport
        float viewport_height = 2.0;
        const float ASPECT_RATIO = 16.0/9.0;
    	float viewport_width = ASPECT_RATIO * viewport_height;
        const int IMG_WIDTH  = 400;
    	const int IMG_HEIGHT = static_cast<int>(IMG_WIDTH / ASPECT_RATIO);

    	// Camera
        Vec3 origin = Vec3(0.0, 0.0, 0.0);
    	float focal_length = 5.0;
    	Vec3 horizontal = Vec3(viewport_width, 0, 0);
    	Vec3 vertical = Vec3(0, viewport_height, 0);
    	Vec3 lower_left_corner = origin - horizontal/2 - vertical/2 + Vec3(0, 0, focal_length);

    	void render(const char* filename, World& world) {

    		std::ofstream img_file;
    		img_file.open(filename);
    		img_file << "P3\n" << IMG_WIDTH << ' ' << IMG_HEIGHT << "\n255\n";

    		for (int y = 0; y < IMG_HEIGHT; y++) {
        	std::cout << "\rScanlines remaining: " << y << ' ' << std::flush;
        		for (int x = 0; x < IMG_WIDTH; x++) {
        		    Ray r(origin, lower_left_corner + Vec3((float) x/IMG_WIDTH * viewport_width, (float) y/IMG_HEIGHT * viewport_height, 0.0));
        		    
        		    Vec3 px_color = ray_color(r, world, 1);
                    if (px_color[0] != 0.5) 
                        std::cout << px_color << "\n";
        		    
        		    //Vec3 px_color = newVec3(float(x)/float(IMG_WIDTH - 1), float(y)/float(IMG_HEIGHT - 1), 0.25);
		
        		    write_color(img_file, px_color);
        		}
    		}

    		img_file.close();

    	}

    	Vec3 ray_color(const Ray& r, World& w, int depth) const {
    		if (depth == 0) {
    			return Vec3(0.0, 0.0, 0.0);
    		}
            const SceneObject* obj_intersect = w.intersect(r);
            if (obj_intersect != nullptr) {
                Vec3 color = obj_intersect->color_at(r);
                Material mat = obj_intersect->get_material();
                return color;
            } else {
                return w.background_color();
            }
    	}
};

#endif