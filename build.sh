#!/bin/bash

project_dir=$(dirname "$(realpath "$0")")

export PKG_CONFIG_PATH=$project_dir/build/default/third_party/install/lib64/pkgconfig:$PKG_CONFIG_PATH
export OPENSSL_ROOT_DIR=$project_dir/build/default/third_party/install/lib64

if [ ! -d $project_dir/build/default/install ]; then
  attempt=0
  max_attempt=5
  while  [ $attempt -lt $max_attempt ]; do
      cmake -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=OFF -DBUILD_MAVSDK_SERVER=ON -DCMAKE_INSTALL_PREFIX=$project_dir/build/default/install -DCMAKE_MODULE_PATH="$project_dir/build/default/install/lib/cmake;$project_dir/build/default/third_party/install/lib/cmake;$project_dir/build/default/third_party/install/lib64/cmake" -Bbuild/default -S. && break 
      echo "CMake command failed"
      sleep 2
      attempt=$((attempt+1))
  done
fi

cmake --build build/default -j8

cmake --build build/default --target install

# revise the illegal placement inside the $project_dir/build/default/install/lib/cmake/MAVSDK/MAVSDKTargets.cmake

sed -i 's/\$<LINK_ONLY:\([^@]*\)::[^>]*>>/\$<LINK_ONLY:\1>/g'  $project_dir/build/default/install/lib/cmake/MAVSDK/MAVSDKTargets.cmake

