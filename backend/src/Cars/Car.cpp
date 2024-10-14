#include "../../Cars/Car.h"
#include "../../UserSettings/UserCarSettings.h"
#include "../../Random.h"

Car::Car(CarSettings::Settings settings, CarSettings::Direction direction,
         CarSettings::Turn turn) {
    car_settings = settings;
    car_direction = direction;
    car_turn = turn;
    car_settings.speed = static_cast<int32_t>(Random::mt() % UserCarSettings::maximal_speed)
                         + UserCarSettings::minimal_speed;
}

Car::Car(CarSettings::Direction direction, CarSettings::Turn turn) {
    car_direction = direction;
    car_turn = turn;
    car_settings.line = Random::mt() % 2;
    car_settings.speed = static_cast<int32_t>(Random::mt() % UserCarSettings::maximal_speed)
            + UserCarSettings::minimal_speed;
}

void Car::UpdatePosition() {
    if (car_direction == CarSettings::Direction::Down) {
        car_settings.position_y += car_settings.speed;
    } else if (car_direction == CarSettings::Direction::Up) {
        car_settings.position_y -= car_settings.speed;
    } else if (car_direction == CarSettings::Direction::Left) {
        car_settings.position_x -= car_settings.speed;
    } else if (car_direction == CarSettings::Direction::Right) {
        car_settings.position_x += car_settings.speed;
    }
}