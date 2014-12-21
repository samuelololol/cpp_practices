include_directories(curlcpp/include)
project(try_curl)
ADD_DEFINITIONS(
        -std=c++11 
    )
set(try_curl_SOURCES
    try_curl.cpp
    )
include_directories(curlcpp/include)
add_executable(try_curl ${try_curl_SOURCES})
add_subdirectory(curlcpp)
