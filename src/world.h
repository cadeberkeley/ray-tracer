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

		void add(SceneObject* obj) {
    		scene_objs.push_back(obj);
    	}

    	const SceneObject* intersect(const Ray& r) {
    		list<SceneObject*>::iterator obj_iter;
		
        	bool intersect = false;
        	for (obj_iter = scene_objs.begin(); obj_iter != scene_objs.end(); ++obj_iter) {
        		float intersect_at = (*obj_iter)->intersect(r);
        	    if (intersect_at > 0) {
        	        return *obj_iter;
        	    }
        	}

        	return nullptr;
    	}
    	
    	Vec3 background_color() const {
    		return Vec3(0.15, 0.58, 0.74);
    	}
};

#endif