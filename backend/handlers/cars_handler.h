#pragma once

#include <userver/components/minimal_server_component_list.hpp>
#include <userver/server/websocket/websocket_handler.hpp>
#include <userver/utils/daemon_run.hpp>
#include <userver/engine/sleep.hpp>

#include "../Cars/Cars.h"
#include "../Random.h"
#include "../TrafficLight/TrafficLights.h"
#include "../Process/UpdateLights.h"

static auto beg_time = std::chrono::steady_clock::now();
auto last_time = std::chrono::steady_clock::now();

const int WINDOW_X = 1498;
const int WINDOW_Y = 723;

Cars RoadCars{};

void CAR() {
    auto cur = std::chrono::steady_clock::now();
    auto get_time = std::chrono::duration_cast<std::chrono::seconds>
            (cur - last_time).count();
    if (LightsUpdater::UpdateLights(static_cast<int>(get_time),
                                    RoadCars)) {
        last_time = cur;
    }
    RoadCars.Update();
    if (Random::mt() % 100 > 96) {
        RoadCars.CreateRandomCar();
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



using namespace std::chrono_literals;

class WebsocketsHandler final : public userver::server::websocket::WebsocketHandlerBase {
public:
    static constexpr std::string_view kName = "websocket-handler";
 
    using WebsocketHandlerBase::WebsocketHandlerBase;
 
    void Handle(userver::server::websocket::WebSocketConnection& chat, userver::server::request::RequestContext&) const override {
        while (!userver::engine::current_task::ShouldCancel()) {
            userver::server::websocket::Message message;
            message.data = GetCars();
            message.is_text = true;
            chat.Send(std::move(message));
            userver::engine::SleepFor((1000ms) / 60);
        }
    }
};