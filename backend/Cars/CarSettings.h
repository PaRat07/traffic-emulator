#pragma once
#include <iostream>

namespace CarSettings {
    struct Settings {
        int32_t car_type = 0;
        double angle = 0;
        int32_t dist_to_light = 0;
        int speed = 0;
        int max_speed = 0;
        bool stop = false;
        double position_x = 0;
        double position_y = 0;
        int32_t line = 0;
        int acceleration = 0;
    };

    enum class Direction {
        Up, Down, Left, Right
    };

    enum class Turn {
        Left, None, Right
    };
}