#pragma once
#include "../Cars/CarSettings.h"


class CreateCars {
public:
    static void CreateCar(CarSettings::Settings, CarSettings::Direction, CarSettings::Turn);

    static void CreateRandomCar(CarSettings::Direction, CarSettings::Turn,
                                const double&, const double&, const double&);
};