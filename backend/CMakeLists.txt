cmake_minimum_required(VERSION 3.10)
project(test_backend_traffic_emulator)

set(CMAKE_CXX_STANDARD 23)

add_executable(${PROJECT_NAME} main.cpp
        Cars/Car.h
        src/Cars/Car.cpp
        TrafficLight/Light.h
        src/TrafficLight/Light.cpp
        TrafficLight/TrafficLight.h
        src/TrafficLight/TrafficLight.cpp
        TrafficLight/LightSettings.h
        Cars/CarSettings.h
        Cars/Cars.h
        src/Cars/Cars.cpp
        Process/CreateCars.h
        src/Process/CreateCars.cpp
        src/UserSettings/UserLightSettings.cpp
        src/UserSettings/UserLightSettings.cpp
        UserSettings/UserCarSettings.h
        src/UserSettings/UserCarSettings.cpp
        Random.h
        src/Random.cpp
        Process/UpdateCars.h
        src/Process/UpdateCars.cpp)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -fno-stack-protector")

find_package(httplib CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE httplib::httplib)
