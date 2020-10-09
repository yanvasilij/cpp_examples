project (i2c_example)
cmake_minimum_required(VERSION 3.7)

add_executable(i2c_example main.cpp)
set_property(TARGET i2c_example PROPERTY CXX_STANDARD 11)

target_link_libraries(i2c_example i2c-master)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -fno-builtin -gdwarf-2")

