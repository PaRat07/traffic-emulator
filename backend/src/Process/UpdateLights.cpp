#include "../../Process/UpdateLights.h"
#include "../../TrafficLight/TrafficLights.h"
#include "../../TrafficLight/Light.h"

bool LightsUpdater::UpdateLightColor(const int& get_time,
                                Light& light) {
    if (get_time >= light.get_light_time()) {
        light.color_number++;
        light.update_color();
        return true;
    }
    return false;
}

bool LightsUpdater::UpdateLights(const int& get_time) {
    // in cycle
    /*
    if (TrafficLights::light_number == 1) { // right_down
        UpdateLightColor(get_time, TrafficLights::right_down_light);
    }
    if (TrafficLights::light_number == 2) { // right_up
        UpdateLightColor(get_time, TrafficLights::right_up_light);
    }
    if (TrafficLights::light_number == 3) { // left_up
        UpdateLightColor(get_time, TrafficLights::left_up_light);
    }
    if (TrafficLights::light_number == 4) { // left_down
        UpdateLightColor(get_time, TrafficLights::left_down_light);
    }
    return false;
     */
    if (get_time >= 3) {
        TrafficLights::right_down_light.update_color();
        return true;
    }
    return false;
}