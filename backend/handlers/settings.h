#pragma once

#include <userver/components/component_list.hpp>
#include <userver/server/handlers/http_handler_base.hpp>
#include <userver/http/common_headers.hpp>
#include "../UserSettings/UserCarSettings.h"
#include "../UserSettings/UserLightSettings.h"

using namespace userver;
using namespace std::string_literals;

class SettingsHandler final : public server::handlers::HttpHandlerJsonBase {
public:
    // `kName` is used as the component name in static config
    static constexpr std::string_view kName = "settings-handler";

    // Component is valid after construction and is able to accept requests
    using HttpHandlerJsonBase::HttpHandlerJsonBase;

    formats::json::Value HandleRequestJsonThrow(const server::http::HttpRequest &req, const formats::json::Value& json, server::request::RequestContext&) const override {
        static int cur_light_time_yellow = UserLightSettings::user_yellow_light_time;
        static int cur_light_time_green = UserLightSettings::user_green_light_time;
        static int cur_light_time_red = UserLightSettings::user_red_light_time;
        static bool cur_adaptivness_light_time =
                !(UserLightSettings::user_mode == LightSettings::Mode::Static);
        static int max_speed = UserCarSettings::maximal_speed;
        static int min_speed = UserCarSettings::minimal_speed;
        static int view_range = UserCarSettings::vision_radius;
        static int interval_car_spawn_l = 3;
        static int interval_car_spawn_r = 3;
        static int interval_car_spawn_d = 3;
        static int interval_car_spawn_u = 3;
        if (json.IsEmpty()) {
            req.GetHttpResponse().SetStatus(server::http::HttpStatus::kOk);
            req.GetHttpResponse().SetHeader(std::string("Access-Control-Allow-Origin"), std::string("*"));
            req.GetHttpResponse().SetHeader(std::string("Access-Control-Allow-Headers"), std::string("Authorization, Content-Type"));
            return {};
        }
        if (json["type"].As<std::string>() == "light_time") {
            if (json["which_light"].As<std::string>() == "green") {
                cur_light_time_green = json["value"].As<int>();
            } else if (json["which_light"].As<std::string>() == "red") {
                cur_light_time_red = json["value"].As<int>();
            } else if (json["which_light"].As<std::string>() == "yellow") {
                cur_light_time_yellow = json["value"].As<int>();
            } else {
                throw std::runtime_error("incorrect query");
            }
        } else if (json["type"].As<std::string>() == "adaptive_light_time") {
            if (json["value"].As<bool>()) {
                cur_adaptivness_light_time = true;
            } else {
                cur_adaptivness_light_time = false;
            }
        } else if (json["type"].As<std::string>() == "speed") {
            if (json["edge"].As<std::string>() == "max") {
                max_speed = json["value"].As<int>();
                max_speed = std::max(max_speed, min_speed);
            } else if (json["edge"].As<std::string>() == "min") {
                min_speed = json["value"].As<int>();
                min_speed = std::min(max_speed, min_speed);
            } else {
                throw std::runtime_error("incorrect query");
            }
        } else if (json["type"].As<std::string>() == "view_range") {
            view_range = json["value"].As<int>();
        } else if (json["type"].As<std::string>() == "interval_car_spawn_l") {
            interval_car_spawn_l = json["value"].As<int>();
        } else if (json["type"].As<std::string>() == "interval_car_spawn_r") {
            interval_car_spawn_r = json["value"].As<int>();
        } else if (json["type"].As<std::string>() == "interval_car_spawn_d") {
            interval_car_spawn_d = json["value"].As<int>();
        } else if (json["type"].As<std::string>() == "interval_car_spawn_u") {
            interval_car_spawn_u = json["value"].As<int>();
        } else {
            throw std::runtime_error("incorrect query");
        }
        req.GetHttpResponse().SetStatus(server::http::HttpStatus::kOk);
        req.GetHttpResponse().SetHeader(std::string("Access-Control-Allow-Origin"), std::string("*"));
        req.GetHttpResponse().SetHeader(std::string("Access-Control-Allow-Headers"), std::string("Authorization, Content-Type"));


        formats::json::ValueBuilder builder;
        builder["cur_light_time_yellow"] = cur_light_time_yellow;
        builder["cur_light_time_green"] = cur_light_time_green;
        builder["cur_light_time_red"] = cur_light_time_red;
        builder["interval_car_spawn_l"] = interval_car_spawn_l;
        builder["interval_car_spawn_r"] = interval_car_spawn_r;
        builder["interval_car_spawn_d"] = interval_car_spawn_d;
        builder["interval_car_spawn_u"] = interval_car_spawn_u;
        builder["max_speed"] = max_speed;
        builder["min_speed"] = min_speed;
        builder["view_range"] = view_range;
        builder["cur_adaptivness_light_time"] = cur_adaptivness_light_time;
        return builder.ExtractValue();
    }
};