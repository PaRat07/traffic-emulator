#include "../../Process/UpdateLights.h"
#include "../../TrafficLight/TrafficLights.h"

bool LightsUpdater::UpdateLightColor(const int& get_time,
                                Light& light) {
    if (get_time >= light.get_light_time()) {
        light.color_number++;
        if (light.color_number == 4) {
            (TrafficLights::light_number %= 4)++;
            light.color_number = 0;
        }
        light.update_color();
        return true;
    }
    return false;
}

bool LightsUpdater::UpdateLights(const int& get_time) {
    // in cycle
    if (TrafficLights::light_number == 1) { // right_down
        return UpdateLightColor(get_time, TrafficLights::right_down_light);
    }
    if (TrafficLights::light_number == 2) { // right_up
        return UpdateLightColor(get_time, TrafficLights::right_up_light);
    }
    if (TrafficLights::light_number == 3) { // left_up
        return UpdateLightColor(get_time, TrafficLights::left_up_light);
    }
    if (TrafficLights::light_number == 4) { // left_down
        return UpdateLightColor(get_time, TrafficLights::left_down_light);
    }
    return false;
}