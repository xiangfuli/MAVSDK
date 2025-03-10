list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_LIST_DIR}/../../build/default/install/lib/cmake")
list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_LIST_DIR}/../../build/default/third_party/install/lib/cmake")
list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_LIST_DIR}/../../build/default/third_party/install/lib64/cmake")

set(OPENSSL_ROOT_DIR "${CMAKE_CURRENT_LIST_DIR}/../../build/default/third_party/install/lib64")
set(OPENSSL_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/../../build/default/third_party/install/include/openssl")

set(CURL_LIBRARY "${CMAKE_CURRENT_LIST_DIR}/../../build/default/third_party/install/lib/libcurl.a")
set(CURL_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/../../build/default/third_party/install/include/curl")

find_package(Threads REQUIRED)
find_package(CURL REQUIRED)
find_package(liblzma REQUIRED)
find_package(MAVSDK REQUIRED)