#include "../../Process/CreateCars.h"
#include "../../Cars/Car.h"
#include "../../Cars/Cars.h"
#include "../../UserSettings/UserCarSettings.h"

void CreateCars::CreateCar(CarSettings::Settings settings, CarSettings::Direction direction,
                           CarSettings::Turn turn) {
    Car new_car(settings, direction, turn);
    Cars::cars.push_back(new_car);
}

void CreateCars::CreateRandomCar(CarSettings::Direction direction, CarSettings::Turn turn,
                                 const double& position_x,
                                 const double& position_y, const double& angle = 180) {
    Car new_car(direction, turn);
    new_car.car_settings.angle = angle;
    new_car.car_settings.position_x = position_x;
    new_car.car_settings.position_y = position_y;
    Cars::cars.push_back(new_car);
}

void CreateCars::CreateOnCarType(Car car) {
    Cars::cars.push_back(car);
}