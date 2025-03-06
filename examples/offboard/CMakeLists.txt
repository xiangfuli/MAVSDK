cmake_minimum_required(VERSION 3.10.2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(offboard)

message (STATUS "${PROJECT_SOURCE_DIR}")

list(APPEND CMAKE_PREFIX_PATH "${PROJECT_SOURCE_DIR}/../../build/default/install/lib/cmake")
list(APPEND CMAKE_PREFIX_PATH "${PROJECT_SOURCE_DIR}/../../build/default/third_party/install/lib/cmake")
list(APPEND CMAKE_PREFIX_PATH "${PROJECT_SOURCE_DIR}/../../build/default/third_party/install/lib64/cmake")

set(OPENSSL_ROOT_DIR "${PROJECT_SOURCE_DIR}/../../build/default/third_party/install/lib64")
set(OPENSSL_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/../../build/default/third_party/install/include/openssl")

set(CURL_LIBRARY "${PROJECT_SOURCE_DIR}/../../build/default/third_party/install/lib/libcurl.a")
set(CURL_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/../../build/default/third_party/install/include/curl")

find_package(Threads REQUIRED)
find_package(CURL REQUIRED)
find_package(liblzma REQUIRED)
find_package(MAVSDK REQUIRED)

add_executable(offboard
    offboard.cpp
)

target_link_libraries(offboard
    MAVSDK::mavsdk
)

if(NOT MSVC)
    add_compile_options(offboard PRIVATE -Wall -Wextra)
else()
    add_compile_options(offboard PRIVATE -W2)
endif()

if(MINGW OR MSVC)
    # For M_PI
    add_target_definitions(offboard "-D_USE_MATH_DEFINES")
endif()
