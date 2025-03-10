#!/bin/bash

project_dir=$(dirname "$(realpath "$0")")

# try to build the offboard example
cd examples/offboard
rm -rf build
mkdir build
cd build
cmake ..
cmake --build .
