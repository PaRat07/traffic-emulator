#pragma once
#include <iostream>
#include <vector>
#include "Car.h"
#include "../Random.h"

class Cars {
public:

    std::vector<std::vector<Car>> up;
    std::vector<std::vector<Car>> down;
    std::vector<std::vector<Car>> left;
    std::vector<std::vector<Car>> right;

    Cars();

    void AddCar(Car car);

    void CreateRandomCar();

    void Update();

    std::vector<Car> GetCars();


private:

    void SortCars();

    void UpdatePositions();

    void UpdateSpeed();

    void ClearCars();

    void UpdateAngels(); // rotate cars
};