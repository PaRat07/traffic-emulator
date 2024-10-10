#include <httplib.h>
#include <format>
#include "Cars/Cars.h"
#include "Process/CreateCars.h"

static auto beg_time = std::chrono::steady_clock::now();

std::string GetContent() {
    auto cur_time = std::chrono::steady_clock::now();
    auto time_gone = std::chrono::duration_cast<std::chrono::milliseconds>(cur_time - beg_time).count();
    std::string res;
    res += R"(
    {
    "cars" : 
        {
            "pos" : {
                        "x" : )" + std::to_string(Cars::cars[0].car_settings.position_x) + R"(,
                        "y" : )" + std::to_string(Cars::cars[0].car_settings.position_y) + R"(
            },
            "direction" : "1.0"
        }
    ,
    "left_up_light_color" : "green",
    "left_down_light_color" : "green",
    "right_up_light_color" : "green",
    "right_down_light_color" : "green"
    }
    )";
    Cars::UpdateCars();
    return res;
}

int main() {

    Car new_car;
    new_car.car_settings.speed = 3;
    new_car.car_turn = CarSettings::Turn::None;
    new_car.car_direction = CarSettings::Direction::Down;
    new_car.car_settings.position_x = 300;
    new_car.car_settings.position_y = 0;

    CreateCars::CreateOnCarType(new_car);

    using namespace httplib;

    Server svr;

    svr.Get("/cars", [](const Request& req, Response& res) {
        res.set_content(GetContent(), "application/json");
    });

    svr.Get("/reset", [](const Request& req, Response& res) {
        beg_time = std::chrono::steady_clock::now();
        res.set_content("", "text/plain");
    });

    svr.set_post_routing_handler([](const auto& req, auto& res) {
        static auto prev_req = std::chrono::steady_clock::now();
        auto cur = std::chrono::steady_clock::now();
        std::cout << std::format("Cur rps: {}", 1000. / std::chrono::duration_cast<std::chrono::milliseconds>(cur - prev_req).count()) << std::endl;
        prev_req = cur;
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Headers", "*");
    });


    svr.listen("0.0.0.0", 1234);
}
