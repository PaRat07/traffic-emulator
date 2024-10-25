#include "../../TrafficLight/Light.h"
#include "../../UserSettings/UserLightSettings.h"
#include "../../Cars/Cars.h"

std::string Light::get_light_color() {
    if (light_color == LightSettings::Color::Red) {
        return "red";
    }
    if (light_color == LightSettings::Color::YellowUp ||
    light_color == LightSettings::Color::YellowDown) {
        return "yellow";
    }
    if (light_color == LightSettings::Color::Green) {
        return "green";
    }
    return "green";
}

void Light::update_color() {
    if (light_color == LightSettings::Color::Green) {
        light_color = LightSettings::Color::YellowUp;
    } else if (light_color == LightSettings::Color::YellowUp) {
        light_color = LightSettings::Color::Red;
    } else if (light_color == LightSettings::Color::Red) {
        light_color = LightSettings::Color::YellowDown;
    } else if (light_color == LightSettings::Color::YellowDown) {
        light_color = LightSettings::Color::Green;
    }
}

int Light::get_light_time(Cars RoadCars) {
    if (UserLightSettings::user_mode == LightSettings::Mode::Static) {
        if (light_color == LightSettings::Color::Red) {
            return UserLightSettings::user_red_light_time;
        }
        if (light_color == LightSettings::Color::YellowDown ||
        light_color == LightSettings::Color::YellowUp) {
            return UserLightSettings::user_yellow_light_time;
        }
        if (light_color == LightSettings::Color::Green) {
            return UserLightSettings::user_green_light_time;
        }
    }
    if (UserLightSettings::user_mode == LightSettings::Mode::Dynamic) {
        int sz = 0;
        if (number_in_cycle == 0) {
            sz = RoadCars.up[0].size() + RoadCars.up[1].size();
        } else if (number_in_cycle == 1) {
            sz = RoadCars.left[0].size() + RoadCars.left[1].size();
        } else if (number_in_cycle == 2) {
            sz = RoadCars.down[0].size() + RoadCars.down[1].size();
        } else if (number_in_cycle == 3) {
            sz = RoadCars.right[0].size() + RoadCars.right[1].size();
        }
        if (light_color == LightSettings::Color::Red ||
        light_color == LightSettings::Color::Green) {
            return std::min(5, (sz + 1) / 2);
        }
        if (light_color == LightSettings::Color::YellowDown ||
            light_color == LightSettings::Color::YellowUp) {
            return 3;
        }
    }
}