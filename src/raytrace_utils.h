#ifndef UTIL_H
#define UTIL_H

#include <cstdlib>

namespace float_utils {
    float random_float() {
        return static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    }

    float random_float(float min, float max) {
        return min + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(max-min)));
    }
};

#endif