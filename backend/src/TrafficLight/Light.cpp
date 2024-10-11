#include "../../TrafficLight/Light.h"

std::string Light::get_light_color() {
    if (light_color == LightSettings::Color::Red) {
        return "red";
    } else if (light_color == LightSettings::Color::YellowUp ||
    light_color == LightSettings::Color::YellowDown) {
        return "yellow";
    } else if (light_color == LightSettings::Color::Green) {
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