cmake_minimum_required(VERSION 2.6.4 FATAL_ERROR)

find_package(libgeodecomp REQUIRED)
include_directories(${libgeodecomp_INCLUDE_DIRS})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${libgeodecomp_FLAGS}")

add_executable(main main.cpp)
target_link_libraries(main geodecomp)
