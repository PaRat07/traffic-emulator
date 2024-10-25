#include <userver/components/minimal_server_component_list.hpp>
#include <userver/clients/dns/component.hpp>
#include <userver/clients/http/component.hpp>
#include <userver/server/handlers/ping.hpp>
#include <userver/server/handlers/tests_control.hpp>
#include <userver/testsuite/testsuite_support.hpp>
#include <userver/utils/daemon_run.hpp>

#include <sstream>

#include "handlers/cars_handler.h"
#include "handlers/settings.h"


int main(int argc, char* argv[]) {
    using namespace CarSettings;

    auto component_list = userver::components::MinimalServerComponentList()
                            .Append<WebsocketsHandler>()
                            .Append<SettingsHandler>();

    return userver::utils::DaemonMain(argc, argv, component_list);
}
