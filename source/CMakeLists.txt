cmake_minimum_required(VERSION 3.25)

add_executable(hello_fmt hello_fmt.cpp)
target_link_libraries(hello_fmt PRIVATE fmt::fmt)

add_executable(day01 day01.cpp)
target_link_libraries(day01 PRIVATE fmt::fmt)