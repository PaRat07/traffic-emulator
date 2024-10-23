#include <httplib.h>
#include <format>
#include <sstream>
#include "Cars/Cars.h"
#include "Random.h"
#include "TrafficLight/TrafficLights.h"
#include "Process/UpdateLights.h"

static auto beg_time = std::chrono::steady_clock::now();
auto last_time = std::chrono::steady_clock::now();

const int WINDOW_X = 1498;
const int WINDOW_Y = 723;

Cars RoadCars{};

void CAR() {
    auto cur = std::chrono::steady_clock::now();
    auto get_time = std::chrono::duration_cast<std::chrono::seconds>
            (cur - last_time).count();
    if (LightsUpdater::UpdateLights(static_cast<int>(get_time))) {
        last_time = cur;
    }
    RoadCars.Update();
    if (Random::mt() % 100 > 94) {
        RoadCars.CreateRandomCar(WINDOW_X, WINDOW_Y);
    }
}

std::string GetCars() {
    std::vector<std::string> cars_data;
    std::string res;
    std::vector<Car> cars = RoadCars.GetCars();
    for (size_t i = 0; i < cars.size(); ++i) {
        std::string local_res;
        local_res += R"(
                {
                    "pos" : {
                        "x" : )" + std::to_string(cars[i].car_settings.position_x) + R"(,
                                "y" : )" + std::to_string(cars[i].car_settings.position_y) + R"(
                }, )";
        local_res += R"( "direction" : )" + std::to_string(cars[i].car_settings.angle) + R"( })";
        if (i < cars.size() - 1) {
            local_res += ",";
        }
        cars_data.push_back(local_res);
    }
    res += R"( {"cars" : [ )";
    for (size_t i = 0; i < cars.size(); ++i) {
        res += cars_data[i];
    }
    res += "],";
    res += R"(
    "left_up_light_color" : ")" + TrafficLights::left_up_light.get_light_color()
    + R"(",
    "left_down_light_color" : ")" + TrafficLights::left_down_light.get_light_color()
    + R"(",
    "right_up_light_color" : ")" + TrafficLights::right_up_light.get_light_color() + R"(",
    "right_down_light_color" : ")" + TrafficLights::right_down_light.get_light_color()
    + R"(" } )";
    // std::cout << res << '\n';
    CAR();
    return res;
}

int main() {
    using namespace CarSettings;

    using namespace httplib;

    Server svr;

    svr.Get("/cars", [](const Request& req, Response& res) {
        res.set_content(GetCars(), "application/json");
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
