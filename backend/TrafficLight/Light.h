#pragma once
#include <iostream>
#include "LightSettings.h"

class Light {
public:
    LightSettings::Color light_color = LightSettings::Color::Red;
    LightSettings::Mode light_mode = LightSettings::Mode::Static;
    int32_t light_time = 3; /// in seconds

    Light() = default;

    std::string get_light_color();

    void update_color();

};