#include "../../Process/UpdateCars.h"
#include "../../Cars/Cars.h"

void CarsUpdater::UpdateCars() {
    for (auto& CAR : Cars::cars) {
        // update position without turn to left and right
        switch (CAR.car_direction) {
            case CarSettings::Direction::Up:
                CAR.car_settings.position_y -= CAR.car_settings.speed;
                break;
            case CarSettings::Direction::Down:
                CAR.car_settings.position_y += CAR.car_settings.speed;
                break;
            case CarSettings::Direction::Left:
                CAR.car_settings.position_x += CAR.car_settings.speed;
                break;
            case CarSettings::Direction::Right:
                CAR.car_settings.position_x -= CAR.car_settings.speed;
                break;
        }
    }
}