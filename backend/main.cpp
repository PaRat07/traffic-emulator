#include <httplib.h>
#include <format>

static auto beg_time = std::chrono::steady_clock::now();

std::string GetContent() {
    auto cur_time = std::chrono::steady_clock::now();
    auto time_gone = std::chrono::duration_cast<std::chrono::milliseconds>(cur_time - beg_time).count();
    static int pos = 0;
    return R"(
{
    "cars" : 
    [
        {
            "pos" : {
                        "x" : )" + std::to_string(pos++) + R"(,
                        "y" : 200
            },
            "direction" : "1.0"
        },
        {
            "pos" : {
                        "x" : 400,
                        "y" : 200
            },
            "direction" : "1.0"
        }
    ],
    "left_up_light_color" : "green",
    "left_down_light_color" : "green",
    "right_up_light_color" : "green",
    "right_down_light_color" : "green"
}
)";
}

int main() {
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
