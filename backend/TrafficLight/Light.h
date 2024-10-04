#pragma once
#include <iostream>
#include "LightSettings.h"

class Light {
public:
    LightSettings::Color light_color = LightSettings::Color::Red;
    LightSettings::Mode light_mode = LightSettings::Mode::Static;
    int32_t light_time = 10; /// in seconds

    Light() = default;

};