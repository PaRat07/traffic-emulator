#include "../../TrafficLight/Light.h"
#include "../../UserSettings/UserLightSettings.h"

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
        light_color = LightSettings::Color::YellowDown;
    } else if (light_color == LightSettings::Color::YellowDown) {
        light_color = LightSettings::Color::Red;
    } else if (light_color == LightSettings::Color::Red) {
        light_color = LightSettings::Color::YellowUp;
    } else if (light_color == LightSettings::Color::YellowUp) {
        light_color = LightSettings::Color::Green;
    }
}

int Light::get_light_time() {
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
        return 3; // add calc cars
    }
    return 3;
}