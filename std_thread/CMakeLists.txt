project (std_thread)
cmake_minimum_required(VERSION 3.7)

add_executable(std_thread main.cpp)
set_property(TARGET std_thread PROPERTY CXX_STANDARD 11)
target_link_libraries(${PROJECT_NAME} pthread)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -fno-builtin -gdwarf-2 -D_GLIBCXX_USE_C99 -D_QNX_SOURCE -DHAS_C9X")

