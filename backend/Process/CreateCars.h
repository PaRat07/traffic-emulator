#pragma once
#include "../Cars/CarSettings.h"
#include "../Cars/Car.h"


class CreateCars {
public:
    static void CreateCar(CarSettings::Settings, CarSettings::Direction, CarSettings::Turn);

    static void CreateRandomCar(const int&, const int&);

    static void CreateOnCarType(Car);
};