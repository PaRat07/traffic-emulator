#pragma once
#include <chrono>
#include "../TrafficLight/Light.h"

class LightsUpdater {
public:

    static bool UpdateLightColor(const int&, Light&);

    static bool UpdateLights(const int&); // time
};