#pragma once

#include <userver/components/component_list.hpp>
#include <userver/server/handlers/http_handler_base.hpp>

using namespace userver;

class SettingsHandler final : public server::handlers::HttpHandlerBase {
public:
    // `kName` is used as the component name in static config
    static constexpr std::string_view kName = "settings-handler";

    // Component is valid after construction and is able to accept requests
    using HttpHandlerBase::HttpHandlerBase;

    std::string HandleRequestThrow(const server::http::HttpRequest& request, server::request::RequestContext&) const override {
        static int cur_light_time_lu = 3;
        static int cur_light_time_ld = 3;
        static int cur_light_time_ru = 3;
        static int cur_light_time_rd = 3;
        static bool cur_adaptivness_light_time = false;
        static int max_speed = 10;
        static int min_speed = 10;
        static int view_range = 10;
        static int interval_car_spawn_l = 3;
        static int interval_car_spawn_r = 3;
        static int interval_car_spawn_d = 3;
        static int interval_car_spawn_u = 3;
        if (request.GetArg("type") == "light_time") {
            if (request.GetArg("which_light") == "lu") {
                cur_light_time_lu = std::stoi(request.GetArg("value"));
            } else if (request.GetArg("which_light") == "rd") {
                cur_light_time_rd = std::stoi(request.GetArg("value"));
            } else if (request.GetArg("which_light") == "ru") {
                cur_light_time_ru = std::stoi(request.GetArg("value"));
            } else if (request.GetArg("which_light") == "ld") {
                cur_light_time_ld = std::stoi(request.GetArg("value"));
            } else {
                request.SetResponseStatus(server::http::HttpStatus::kBadRequest);
            }
        } else if (request.GetArg("type") == "adaptive_light_time") {
            if (request.GetArg("value") == "true") {
                cur_adaptivness_light_time = true;
            } else if (request.GetArg("value") == "true") {
                cur_adaptivness_light_time = false;
            } else {
                request.SetResponseStatus(server::http::HttpStatus::kBadRequest);
            }
        } else if (request.GetArg("type") == "speed") {
            if (request.GetArg("edge") == "max") {
                max_speed = std::stoi(request.GetArg("value"));
                max_speed = std::max(max_speed, min_speed);
            } else if (request.GetArg("edge") == "min") {
                min_speed = std::stoi(request.GetArg("value"));
                min_speed = std::min(max_speed, min_speed);
            } else {
                request.SetResponseStatus(server::http::HttpStatus::kBadRequest);
            }
        } else if (request.GetArg("type") == "view_range") {
            view_range = std::stoi(request.GetArg("value"));
        } else if (request.GetArg("type") == "interval_car_spawn_l") {
            interval_car_spawn_l = std::stoi(request.GetArg("value"));
        } else if (request.GetArg("type") == "interval_car_spawn_r") {
            interval_car_spawn_r = std::stoi(request.GetArg("value"));
        } else if (request.GetArg("type") == "interval_car_spawn_d") {
            interval_car_spawn_d = std::stoi(request.GetArg("value"));
        } else if (request.GetArg("type") == "interval_car_spawn_u") {
            interval_car_spawn_u = std::stoi(request.GetArg("value"));
        } else {
            request.SetResponseStatus(server::http::HttpStatus::kBadRequest);
        }

        formats::json::ValueBuilder builder;
        builder["cur_light_time_lu"] = cur_light_time_lu;
        builder["cur_light_time_ld"] = cur_light_time_ld;
        builder["cur_light_time_ru"] = cur_light_time_ru;
        builder["cur_light_time_rd"] = cur_light_time_rd;
        builder["interval_car_spawn_l"] = interval_car_spawn_l;
        builder["interval_car_spawn_r"] = interval_car_spawn_r;
        builder["interval_car_spawn_d"] = interval_car_spawn_d;
        builder["interval_car_spawn_u"] = interval_car_spawn_u;
        builder["max_speed"] = max_speed;
        builder["min_speed"] = min_speed;
        builder["view_range"] = view_range;
        builder["cur_adaptivness_light_time"] = cur_adaptivness_light_time;
        return ToString(builder.ExtractValue());
    }
};