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
		// Render Settings
		int max_bounces = 1;
		int num_samples = 8;   // Count of random samples for each pixel


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
					Vec3 px_color = Vec3();
					/*if (x == 200 || y == 180) {
						px_color = Vec3(1.0, 0.0, 0.0);
					} else if (x % 10 == 0 || y % 10 == 0) {
						px_color = Vec3(0.0, 0.0, 0.0);
					} else {*/
						for (int i = 0; i < num_samples; i++) {
							Ray r = get_sample_ray(y, x);
        		    		px_color += ray_color(r, world, max_bounces, x, y);
						}
						px_color /= num_samples;
					//}
        		    
                    //if (px_color[0] != 0.5) 
                    //    std::cout << px_color << "\n";
        		    
        		    //Vec3 px_color = newVec3(float(x)/float(IMG_WIDTH - 1), float(y)/float(IMG_HEIGHT - 1), 0.25);
		
        		    write_color(img_file, px_color);
        		}
    		}

    		img_file.close();

    	}

    	Vec3 ray_color(const Ray& r, World& w, int depth, int x, int y) {
			if (x < 205 && x > 200 && y < 185 && y > 180) {
				cout << "\n" << r;
			}
    		if (depth == 0) {
    			//return r.color;
				return Vec3();
    		}
            SceneObject* obj_intersect = nullptr;
			Vec3 intersection_point = Vec3();
			bool is_intersect = w.intersect(r, obj_intersect, intersection_point);
			if (is_intersect) {
				Ray next;
				if (obj_intersect->scatter(r, intersection_point, next)) {
					
					return obj_intersect->get_material()->albedo * ray_color(next, w, depth - 1, x, y);
				} else {
					return Vec3();
				}
			} else {
				return w.background_color(r);
			}
    	}

	private:
		Ray get_sample_ray(int i, int j) {
			Vec3 sample_offset = sample_square() / (float) IMG_WIDTH * viewport_width;
			Vec3 grid_offset = Vec3((float) j, (float) i, 0.0) / (float)IMG_WIDTH * viewport_width;
			//cout << origin;
			//cout << lower_left_corner;
			//cout << grid_offset;
			return Ray(origin, lower_left_corner + grid_offset/* + sample_offset*/);
		}
        	
		// Returns the vector to a random point in the [-.5,-.5]-[+.5,+.5] unit square.
		Vec3 sample_square() const {
        	return Vec3(Vec3::random_value(-0.5, 0.5), Vec3::random_value(-0.5, 0.5), 0);
		}


};

#endif