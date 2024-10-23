#pragma once
#include "../TrafficLight/LightSettings.h"
#include <iostream>

namespace UserLightSettings {
    extern LightSettings::Mode user_mode;
    extern int user_green_light_time;
    extern int user_yellow_light_time;
    extern int user_red_light_time;
}