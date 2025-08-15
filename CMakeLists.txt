cmake_minimum_required(VERSION 3.20)
project(PingPong)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(PingPong "./Ping Pong/Ping Pong.cpp")

set(CMAKE_TOOLCHAIN_FILE "C:/vcpkg/scripts/buildsystems/vcpkg.cmake")

# SFML
find_package(SFML COMPONENTS Network Graphics Window Audio System CONFIG REQUIRED)
target_link_libraries(PingPong PRIVATE SFML::Network SFML::Graphics SFML::Window SFML::Audio SFML::System)

# Raylib
find_path(RAYLIB_INCLUDE_DIRS "raylib.h")
target_link_libraries(PingPong PRIVATE raylib)

# Raygui
find_path(RAYGUI_INCLUDE_DIRS "raygui.h")
target_include_directories(PingPong PRIVATE ${RAYGUI_INCLUDE_DIRS})

# Nlohmann-json
find_path(nlohmann_json_DIRS "./nlohmann/")
find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(PingPong PRIVATE nlohmann_json::nlohmann_json)
set(nlohmann-json_IMPLICIT_CONVERSIONS OFF)

# fmt
find_path(fmt_DIR "./fmt/")
target_link_libraries(PingPong PRIVATE fmt::fmt)
