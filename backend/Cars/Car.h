#pragma once
#include <iostream>
#include <ctime>
#include <random>
#include "CarSettings.h"

class Car {
public:

    CarSettings::Settings car_settings;

    CarSettings::Direction car_direction = CarSettings::Direction::Up;

    CarSettings::Turn car_turn = CarSettings::Turn::None;

    Car() = default;

    ~Car() = default;

    Car(CarSettings::Settings, CarSettings::Direction, CarSettings::Turn);

    Car(CarSettings::Direction, CarSettings::Turn);
};
