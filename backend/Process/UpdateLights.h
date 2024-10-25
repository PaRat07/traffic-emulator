#pragma once
#include <chrono>
#include "../TrafficLight/Light.h"
#include "../Cars/Cars.h"

class LightsUpdater {
public:

    static bool UpdateLightColor(const int&, Light&, Cars);

    static bool UpdateLights(const int&, Cars); // time
};