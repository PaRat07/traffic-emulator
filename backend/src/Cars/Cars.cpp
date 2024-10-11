#include "../../Cars/Cars.h"

namespace Cars {
    std::vector<Car> cars;

    void UpdateCars() {
        for (auto& car : cars) {
            // update position without turn to left and right
            switch (car.car_direction) {
                case CarSettings::Direction::Up:
                    car.car_settings.position_y -= car.car_settings.speed;
                    break;
                case CarSettings::Direction::Down:
                    car.car_settings.position_y += car.car_settings.speed;
                    break;
                case CarSettings::Direction::Left:
                    car.car_settings.position_x += car.car_settings.speed;
                    break;
                case CarSettings::Direction::Right:
                    car.car_settings.position_x -= car.car_settings.speed;
                    break;
            }
        }
    }
}