#ifndef WORLD_H
#define WORLD_H

#include "ray.h"
#include "scene_object.h"
#include <list>

using namespace std;

class World {
	public:
		list<SceneObject*> scene_objs;

		void add(SceneObject* obj) {
    		scene_objs.push_front(obj);
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
    		return Vec3(0.5, 0.5, 0.5);
    	}
};

#endif