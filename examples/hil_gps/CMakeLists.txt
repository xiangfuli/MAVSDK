cmake_minimum_required(VERSION 3.10.2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(hil_gps)

add_executable(hil_gps
hil_gps.cpp
)

find_package(MAVSDK REQUIRED)

target_link_libraries(hil_gps
    MAVSDK::mavsdk
)

if(NOT MSVC)
    add_compile_options(hil_gps PRIVATE -Wall -Wextra)
else()
    add_compile_options(hil_gps PRIVATE -W2)
endif()

if(MINGW OR MSVC)
    # For M_PI
    add_target_definitions(hil_gps "-D_USE_MATH_DEFINES")
endif()
