#include "../../Cars/Cars.h"
#include "../../TrafficLight/TrafficLights.h"
#include <algorithm>
#include "../../Random.h"

Cars::Cars() {
    up.resize(2);
    down.resize(2);
    left.resize(2);
    right.resize(2);
}

void Cars::AddCar(Car car) {
    if (car.car_direction == CarSettings::Direction::Down) {
        down[car.car_settings.line].push_back(car);
    } else if (car.car_direction == CarSettings::Direction::Up) {
        up[car.car_settings.line].push_back(car);
    } else if (car.car_direction == CarSettings::Direction::Left) {
        left[car.car_settings.line].push_back(car);
    } else if (car.car_direction == CarSettings::Direction::Right) {
        right[car.car_settings.line].push_back(car);
    }
}

void Cars::CreateRandomCar(const int& WINDOW_X, const int& WINDOW_Y) {
    CarSettings::Direction direction;
    CarSettings::Turn turn;
    int k1 = Random::mt() % 4;
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
            new_car.car_settings.angle = 90;
            if (new_car.car_settings.line == 0) {
                new_car.car_settings.position_y = WINDOW_Y / 2 - 90;
            } else {
                new_car.car_settings.position_y = WINDOW_Y / 2 - 30;
            }
            new_car.car_settings.position_x = WINDOW_X;
            break;
        case CarSettings::Direction::Right:
            new_car.car_settings.angle = 270;
            if (new_car.car_settings.line == 0) {
                new_car.car_settings.position_y = WINDOW_Y / 2 + 30;
            } else {
                new_car.car_settings.position_y = WINDOW_Y / 2 + 90;
            }
            new_car.car_settings.position_x = 0;
            break;
        case CarSettings::Direction::Up:
            new_car.car_settings.angle = 180;
            if (new_car.car_settings.line == 0) {
                new_car.car_settings.position_x = WINDOW_X / 2 + 30;
            } else {
                new_car.car_settings.position_x = WINDOW_X / 2 + 90;
            }
            if (!up[new_car.car_settings.line].empty()) {
                new_car.car_settings.position_y = std::max(WINDOW_Y,
                        up[new_car.car_settings.line][0].car_settings.position_y + 130);
            } else {
                new_car.car_settings.position_y = WINDOW_Y;
            }
            break;
        case CarSettings::Direction::Down:
            new_car.car_settings.angle = 0;
            if (new_car.car_settings.line == 0) {
                new_car.car_settings.position_x = WINDOW_X / 2 - 40;
            } else {
                new_car.car_settings.position_x = WINDOW_X / 2 - 100;
            }
            if (!down[new_car.car_settings.line].empty()) {
                new_car.car_settings.position_y = std::min(-20,
                        down[new_car.car_settings.line][0].car_settings.position_y - 130);
            } else {
                new_car.car_settings.position_y = -20;
            }
            break;
    }
    AddCar(new_car);
}

void Cars::Update() {
    SortCars();
    UpdateSpeed();
    UpdatePositions();
}

std::vector<Car> Cars::GetCars() {
    std::vector<Car> cars;
    for (int i = 0; i < 2; ++i) {
        for (auto &t: up[i]) {
            cars.push_back(t);
        }
    }
    for (int i = 0; i < 2; ++i) {
        for (auto &t: down[i]) {
            cars.push_back(t);
        }
    }
    for (int i = 0; i < 2; ++i) {
        for (auto &t: left[i]) {
            cars.push_back(t);
        }
    }
    for (int i = 0; i < 2; ++i) {
        for (auto &t: right[i]) {
            cars.push_back(t);
        }
    }
    return cars;
}

// private

void Cars::SortCars() {
    for (int i = 0; i < 2; ++i) {
        std::sort(up[i].begin(), up[i].end(), [](auto e1, auto e2) {
            return e1.car_settings.position_y > e2.car_settings.position_y;
        });
    }
    for (int i = 0; i < 2; ++i) {
        std::sort(down[i].begin(), down[i].end(), [](auto e1, auto e2) {
            return e1.car_settings.position_y < e2.car_settings.position_y;
        });
    }
    for (int i = 0; i < 2; ++i) {
        std::sort(left[i].begin(), left[i].end(), [](auto e1, auto e2) {
            return e1.car_settings.position_x > e2.car_settings.position_x;
        });
    }
    for (int i = 0; i < 2; ++i) {
        std::sort(right[i].begin(), right[i].end(), [](auto e1, auto e2) {
            return e1.car_settings.position_x < e2.car_settings.position_x;
        });
    }
}

void Cars::UpdatePositions() {
    int up_line = 620;
    for (int i = 0; i < 2; ++i) {
        for (auto &car : up[i]) {
            if (TrafficLights::right_down_light.light_color ==
            LightSettings::Color::Red ||
            TrafficLights::right_down_light.light_color ==
            LightSettings::Color::YellowDown) {
                if (abs(car.car_settings.position_y - up_line) < 30) {
                    car.car_settings.stop = true;
                    continue;
                }
            }
            car.car_settings.stop = false;
            car.UpdatePosition();
        }
    }
    int down_line = 100;
    for (int i = 0; i < 2; ++i) {
        for (auto &car : down[i]) {
            if (TrafficLights::left_up_light.light_color ==
                LightSettings::Color::Red ||
                TrafficLights::left_up_light.light_color ==
                LightSettings::Color::YellowDown) {
                if (abs(car.car_settings.position_y - down_line) < 30) {
                    car.car_settings.stop = true;
                    continue;
                }
            }
            car.car_settings.stop = false;
            car.UpdatePosition();
        }
    }
    int left_line = 1010;
    for (int i = 0; i < 2; ++i) {
        for (auto &car : left[i]) {
            if (TrafficLights::right_up_light.light_color ==
            LightSettings::Color::Red ||
            TrafficLights::right_up_light.light_color ==
            LightSettings::Color::YellowDown) {
                if (abs(car.car_settings.position_x - left_line) < 30) {
                    car.car_settings.stop = true;
                    continue;
                }
            }
            car.car_settings.stop = false;
            car.UpdatePosition();
        }
    }
    int right_line = 490;
    for (int i = 0; i < 2; ++i) {
        for (auto &car : right[i]) {
            if (TrafficLights::left_down_light.light_color ==
                LightSettings::Color::Red ||
                TrafficLights::left_down_light.light_color ==
                LightSettings::Color::YellowDown) {
                if (abs(car.car_settings.position_x - right_line) < 30) {
                    car.car_settings.stop = true;
                    continue;
                }
            }
            car.car_settings.stop = false;
            car.UpdatePosition();
        }
    }
}

void Cars::UpdateSpeed() {
    int radius = 100;
    for (int i = 0; i < 2; ++i) {
        for (auto &car : up[i]) {
            if (car.car_settings.stop) {
                car.car_settings.speed = 0;
            } else {
                car.car_settings.speed = std::min(car.car_settings.max_speed,
                        car.car_settings.speed + car.car_settings.acceleration);
            }
        }
    }
    for (int i = 0; i < 2; ++i) {
        for (int j = up[i].size() - 2; j >= 0; --j) {
            if (up[i][j].car_settings.position_y -
            up[i][j + 1].car_settings.position_y < radius) {
                up[i][j].car_settings.speed = up[i][j + 1].car_settings.speed;
            }
        }
    }
    for (int i = 0; i < 2; ++i) {
        for (auto &car : down[i]) {
            if (car.car_settings.stop) {
                car.car_settings.speed = 0;
            } else {
                car.car_settings.speed = std::min(car.car_settings.max_speed,
                                                  car.car_settings.speed + car.car_settings.acceleration);
            }
        }
    }
    for (int i = 0; i < 2; ++i) {
        for (int j = down[i].size() - 2; j >= 0; --j) {
            if (down[i][j + 1].car_settings.position_y -
            down[i][j].car_settings.position_y < radius) {
                down[i][j].car_settings.speed = down[i][j + 1].car_settings.speed;
            }
        }
    }
    for (int i = 0; i < 2; ++i) {
        for (auto &car : left[i]) {
            if (car.car_settings.stop) {
                car.car_settings.speed = 0;
            } else {
                car.car_settings.speed = std::min(car.car_settings.max_speed,
                                                  car.car_settings.speed + car.car_settings.acceleration);
            }
        }
    }
    for (int i = 0; i < 2; ++i) {
        for (int j = left[i].size() - 2; j >= 0; --j) {
            if (left[i][j].car_settings.position_x -
            left[i][j + 1].car_settings.position_x < radius) {
                left[i][j].car_settings.speed = left[i][j + 1].car_settings.speed;
            }
        }
    }
    for (int i = 0; i < 2; ++i) {
        for (auto &car : right[i]) {
            if (car.car_settings.stop) {
                car.car_settings.speed = 0;
            } else {
                car.car_settings.speed = std::min(car.car_settings.max_speed,
                                                  car.car_settings.speed + car.car_settings.acceleration);
            }
        }
    }
    for (int i = 0; i < 2; ++i) {
        for (int j = right[i].size() - 2; j >= 0; --j) {
            if (right[i][j + 1].car_settings.position_x -
            right[i][j].car_settings.position_x < radius) {
                right[i][j].car_settings.speed = right[i][j + 1].car_settings.speed;
            }
        }
    }
}