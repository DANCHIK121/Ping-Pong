# Base settings 
cmake_minimum_required(VERSION 3.20)
project(PingPong)

# C++ settings
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add executable object with all files
add_executable(
    PingPongRelease "Ping Pong/Ping Pong.cpp" # Main file 
    "Ping Pong/Json/Json.h" "Ping Pong/Json/Json.cpp" # Json files 
    "Ping Pong/Audio/WorkWithAudio.h" "Ping Pong/Audio/WorkWithAudio.cpp" # Audio files 
    "Ping Pong/Functions/Functions.h" "Ping Pong/Functions/Functions.cpp" # Functions files
)

# Set output project directory
set_target_properties(PingPongRelease PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/x64/Release/)

# Get project source directory
message("Current source directory: ${CMAKE_CURRENT_SOURCE_DIR}")

# Include needed directories
target_include_directories(PingPongRelease PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/SFML/include
    ${CMAKE_CURRENT_SOURCE_DIR}/raylib/src
    ${CMAKE_CURRENT_SOURCE_DIR}/raygui/src
    ${CMAKE_CURRENT_SOURCE_DIR}/json/include
)

# Explicit linking of STATIC SFML libraries
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/SFML/lib/libsfml-audio-s.a")
    message(STATUS "Linking static SFML libraries")
    target_link_libraries(PingPongRelease PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/SFML/lib/libsfml-audio-s.a
        ${CMAKE_CURRENT_SOURCE_DIR}/SFML/lib/libsfml-graphics-s.a
        ${CMAKE_CURRENT_SOURCE_DIR}/SFML/lib/libsfml-window-s.a
        ${CMAKE_CURRENT_SOURCE_DIR}/SFML/lib/libsfml-system-s.a
        ${CMAKE_CURRENT_SOURCE_DIR}/SFML/lib/libsfml-network-s.a
    )
elseif(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/SFML/lib/libsfml-audio.a")
    message(STATUS "Linking static SFML libraries (.a)")
    target_link_libraries(PingPongRelease PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/SFML/lib/libsfml-audio.a
        ${CMAKE_CURRENT_SOURCE_DIR}/SFML/lib/libsfml-graphics.a
        ${CMAKE_CURRENT_SOURCE_DIR}/SFML/lib/libsfml-window.a
        ${CMAKE_CURRENT_SOURCE_DIR}/SFML/lib/libsfml-system.a
        ${CMAKE_CURRENT_SOURCE_DIR}/SFML/lib/libsfml-network.a
    )
elseif(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/SFML/lib/libsfml-audio.so")
    message(STATUS "Linking dynamic SFML libraries (static not found)")
    target_link_libraries(PingPongRelease PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/SFML/lib/libsfml-audio.so
        ${CMAKE_CURRENT_SOURCE_DIR}/SFML/lib/libsfml-graphics.so
        ${CMAKE_CURRENT_SOURCE_DIR}/SFML/lib/libsfml-window.so
        ${CMAKE_CURRENT_SOURCE_DIR}/SFML/lib/libsfml-system.so
        ${CMAKE_CURRENT_SOURCE_DIR}/SFML/lib/libsfml-network.so
    )
else()
    message(FATAL_ERROR "SFML libraries not found in ${CMAKE_CURRENT_SOURCE_DIR}/SFML/lib/")
endif()

# Raylib - looking for a static library
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/raylib/src/libraylib.a")
    message(STATUS "Found static raylib: ${CMAKE_CURRENT_SOURCE_DIR}/raylib/src/libraylib.a")
    target_link_libraries(PingPongRelease PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/raylib/src/libraylib.a)
elseif(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/raylib/raylib/libraylib.a")
    message(STATUS "Found static raylib: ${CMAKE_CURRENT_SOURCE_DIR}/raylib/raylib/libraylib.a")
    target_link_libraries(PingPongRelease PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/raylib/raylib/libraylib.a)
else()
    # Пробуем найти через find_library
    find_library(RAYLIB_LIB 
        NAMES raylib libraylib.a
        PATHS ${CMAKE_CURRENT_SOURCE_DIR}/raylib/src ${CMAKE_CURRENT_SOURCE_DIR}/raylib/raylib ${CMAKE_CURRENT_SOURCE_DIR}/raylib
        NO_DEFAULT_PATH
    )
    if(RAYLIB_LIB)
        message(STATUS "Found raylib: ${RAYLIB_LIB}")
        target_link_libraries(PingPongRelease PRIVATE ${RAYLIB_LIB})
    else()
        message(FATAL_ERROR "Raylib static library not found!")
    endif()
endif()

# System libraries for static linking
target_link_libraries(PingPongRelease PRIVATE
    pthread
    dl
    m
    X11
    Xrandr
    Xinerama
    Xi
    /usr/lib64/libXxf86vm.so.1.0.0
    Xcursor
)

# Additional dependencies for static SFML
target_link_libraries(PingPongRelease PRIVATE
    GL
    /usr/lib64/libopenal.so.1.22.2
    /usr/lib64/libFLAC.so.12.1.0
    vorbisenc
    vorbisfile
    vorbis
    ogg
    freetype
)

# Nlohmann-json
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/json/include/")
    target_include_directories(PingPongRelease PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/json/include/)
else()
    find_package(nlohmann_json REQUIRED)
    target_link_libraries(PingPongRelease PRIVATE nlohmann_json::nlohmann_json)
endif()

# fmt - looking for a static library
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/fmt/lib/libfmt.a")
    target_link_libraries(PingPongRelease PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/fmt/lib/libfmt.a)
elseif(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/fmt/bin/libfmt.a")
    target_link_libraries(PingPongRelease PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/fmt/bin/libfmt.a)
endif()