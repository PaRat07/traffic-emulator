#include "../../Process/CreateCars.h"
#include "../../Cars/Car.h"
#include "../../Cars/Cars.h"
#include "../../UserSettings/UserCarSettings.h"
#include "../../Random.h"

void CreateCars::CreateCar(CarSettings::Settings settings, CarSettings::Direction direction,
                           CarSettings::Turn turn) {
    Car new_car(settings, direction, turn);
    Cars::cars.push_back(new_car);
}

void CreateCars::CreateRandomCar(const int& WINDOW_X,
                                 const int& WINDOW_Y) {
    CarSettings::Direction direction;
    CarSettings::Turn turn;
    int k1 = Random::mt() % 2;
    int k2 = Random::mt() % 3;
    switch (k1) {
        case 0:
            direction = CarSettings::Direction::Down;
            break;
        case 1:
            direction = CarSettings::Direction::Up;
            break;
        case 2:
            direction = CarSettings::Direction::Left;
            break;
        case 3:
            direction = CarSettings::Direction::Right;
            break;
    }
    switch (k2) {
        case 0:
            turn = CarSettings::Turn::Left;
            break;
        case 1:
            turn = CarSettings::Turn::Right;
            break;
        case 2:
            turn = CarSettings::Turn::None;
            break;
    }
    Car new_car(direction, turn);
    switch (direction) {
        case CarSettings::Direction::Left:
            new_car.car_settings.position_x = 0;
            new_car.car_settings.position_y = WINDOW_Y / 2;
            break;
        case CarSettings::Direction::Right:
            new_car.car_settings.position_x = WINDOW_X;
            new_car.car_settings.position_y = WINDOW_Y / 2;
            break;
        case CarSettings::Direction::Up:
            new_car.car_settings.position_x = WINDOW_X / 2;
            new_car.car_settings.position_y = 0;
            break;
        case CarSettings::Direction::Down:
            new_car.car_settings.position_x = WINDOW_X / 2;
            new_car.car_settings.position_y = WINDOW_Y;
            break;
    }
    Cars::cars.push_back(new_car);
}

void CreateCars::CreateOnCarType(Car car) {
    Cars::cars.push_back(car);
}