#pragma once
#include <iostream>
#include "LightSettings.h"
#include "../Cars/Cars.h"

class Light {
public:
    LightSettings::Color light_color = LightSettings::Color::Red;

    int number_in_cycle = 0;

    int color_number = 0;

    Light(int _number_in_cycle = 0) : number_in_cycle(_number_in_cycle) {}

    std::string get_light_color();

    void update_color();

    int get_light_time(Cars); // in seconds
};