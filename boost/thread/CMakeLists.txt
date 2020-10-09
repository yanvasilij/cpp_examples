project (thread_example)
cmake_minimum_required(VERSION 3.7)


include_directories("/opt/extra/include")
link_directories("/opt/extra/lib")

set(BOOST_ROOT /opt/extra)
#set( Boost_NO_SYSTEM_PATHS on CACHE BOOL "Do not search system for Boost" )

find_package(Boost 1.74.0)

add_executable(thread_example main.cpp)

target_link_libraries(thread_example boost_thread)

set_property(TARGET thread_example PROPERTY CXX_STANDARD 11)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -fno-builtin -gdwarf-2 -D_GLIBCXX_USE_C99 -D_QNX_SOURCE -DHAS_C9X")

