cmake_minimum_required(VERSION 3.10)
# set(CMAKE_TOOLCHAIN_FILE /opt/vcpkg-master/scripts/buildsystems/vcpkg.cmake)
project(test_backend_traffic_emulator)
set(CMAKE_CXX_STANDARD 23)
add_executable(${PROJECT_NAME} main.cpp
        Cars/Car.h
        src/Cars/Car.cpp
        src/Cars/Cars.cpp
        TrafficLight/Light.h
        src/TrafficLight/Light.cpp
        TrafficLight/TrafficLights.h
        src/TrafficLight/TrafficLights.cpp
        TrafficLight/LightSettings.h
        Cars/CarSettings.h
        src/UserSettings/UserLightSettings.cpp
        UserSettings/UserCarSettings.h
        src/UserSettings/UserCarSettings.cpp
        Random.h
        src/Random.cpp
        Process/UpdateLights.h
        src/Process/UpdateLights.cpp)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -fno-stack-protector")
find_package(httplib CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE httplib::httplib)