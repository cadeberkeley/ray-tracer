#ifndef WORLD_H
#define WORLD_H

#include "ray.h"
#include "scene_object.h"
#include <list>
#include <queue>

using namespace std;

class World {
/*
	private struct SceneObjectComparator {  
		bool operator()(const SceneObject& a, const SceneObject& b) {  
			return distance;  
		}  
	};
*/
	public:
		list<SceneObject*> scene_objs;
		// priority_queue<SceneObject*, Vector<SceneObject*>, SceneObjectComparator > scene_objects;

		// TODO:
		// Shadows are only happening on the top sphere because of the sorting order of scene_objs?
		void add(SceneObject* obj) {
    		scene_objs.push_back(obj);
    	}

    	const bool intersect(const Ray& r, SceneObject*& obj_intersect, Vec3& intersection_point) {
    		list<SceneObject*>::iterator obj_iter;
		
        	for (obj_iter = scene_objs.begin(); obj_iter != scene_objs.end(); ++obj_iter) {
        		float intersect_at = (*obj_iter)->intersect(r);
        	    if (intersect_at > 0.001) {
        	        obj_intersect = *obj_iter;
					intersection_point = r.at(intersect_at);
					return true;
        	    }
        	}
        	return false;
    	}
    	
		// LERP light blue gradient
    	Vec3 background_color(const Ray& r) const {
    		/*
			Vec3 unit_direction = r.dir.normalized();
    		auto a = 0.5*(unit_direction[1] + 1.0);
    		return (1.0-a)*Vec3(1.0, 1.0, 1.0) + a*Vec3(0.5, 0.7, 1.0);
			*/
			return Vec3(1.0, 1.0, 1.0);
    	}
};

#endif