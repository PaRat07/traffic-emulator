cmake_minimum_required(VERSION 3.10)
project(test_backend_traffic_emulator)

set(CMAKE_CXX_STANDARD 23)

add_executable(${PROJECT_NAME} main.cpp)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -fno-stack-protector")

find_package(httplib CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE httplib::httplib)
