cmake_minimum_required(VERSION 2.6.4 FATAL_ERROR)

find_package(libgeodecomp REQUIRED)

add_executable(main main.cpp)
target_link_libraries(main geodecomp)
