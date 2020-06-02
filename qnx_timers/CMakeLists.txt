project (qnx_timers)
cmake_minimum_required(VERSION 3.7)

add_executable(qnx_timers main.cpp)
set_property(TARGET qnx_timers PROPERTY CXX_STANDARD 11)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -fno-builtin -gdwarf-2 -std=gnu++11 -D_GLIBCXX_USE_C99 -D_QNX_SOURCE -DHAS_C9X")

