cmake_minimum_required(VERSION 3.10.2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(mocap)

add_executable(mocap
mocap.cpp
)

find_package(MAVSDK REQUIRED)

target_link_libraries(mocap
    MAVSDK::mavsdk
)

if(NOT MSVC)
    add_compile_options(mocap PRIVATE -Wall -Wextra)
else()
    add_compile_options(mocap PRIVATE -W2)
endif()

if(MINGW OR MSVC)
    # For M_PI
    add_target_definitions(mocap "-D_USE_MATH_DEFINES")
endif()
