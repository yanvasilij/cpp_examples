project (empty)
cmake_minimum_required(VERSION 3.7)

add_executable(${CMAKE_PROJECT_NAME} main.cpp)
set_property(TARGET ${CMAKE_PROJECT_NAME} PROPERTY CXX_STANDARD 11)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -fno-builtin -gdwarf-2 -D_GLIBCXX_USE_C99 -D_QNX_SOURCE -DHAS_C9X")

