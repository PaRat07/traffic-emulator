#pragma once
#include "Light.h"
#include <vector>

namespace TrafficLight {
    extern std::vector<Light> lights;

    extern std::vector<Light> get_lights();
}