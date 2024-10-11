#include "../../Process/UpdateLights.h"
#include "../../TrafficLight/TrafficLight.h"

bool LightsUpdater::UpdateLights(const int& get_time) {
    if (get_time >= 3) {
        TrafficLight::left_down_light.update_color();
        TrafficLight::left_up_light.update_color();
        TrafficLight::right_down_light.update_color();
        TrafficLight::right_up_light.update_color();
        return true;
    }
    return false;
}