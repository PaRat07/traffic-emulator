#pragma once
#include <iostream>
#include "LightSettings.h"

class Light {
public:
    LightSettings::Color light_color = LightSettings::Color::Red;

    int color_number = 0;

    Light() = default;

    std::string get_light_color();

    void update_color();

    int get_light_time(); // in seconds
};