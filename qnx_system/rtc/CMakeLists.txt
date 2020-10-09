project (rtc_set_example)
cmake_minimum_required(VERSION 3.7)

add_executable(rtc_set_example main.cpp)
set_property(TARGET rtc_set_example PROPERTY CXX_STANDARD 11)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -fno-builtin -gdwarf-2")

