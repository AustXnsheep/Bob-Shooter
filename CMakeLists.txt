cmake_minimum_required(VERSION 3.5)
project(Game)

set(CMAKE_CXX_STANDARD 11)

# Fetch Raylib via CMake
include(FetchContent)
FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG        master
)

set(FETCHCONTENT_QUIET OFF)
FetchContent_MakeAvailable(raylib)


add_executable(Game main.cpp
        entities/livingentities/player.cpp
        entities/livingentities/bullet.cpp
        world.cpp
        uuid/uuid.cpp
        settings.cpp
        entities/livingentities/bob.cpp)

target_link_libraries(Game raylib)

if(UNIX AND NOT APPLE)
    target_link_libraries(Game m pthread dl rt X11)
endif()
