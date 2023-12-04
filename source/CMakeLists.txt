cmake_minimum_required(VERSION 3.25)

add_executable(hello_fmt hello_fmt.cpp)
target_link_libraries(hello_fmt PRIVATE fmt::fmt)

add_executable(day01 day01.cpp)
target_link_libraries(day01 PRIVATE fmt::fmt)

add_executable(day02_s1 day02_s1.cpp)
target_link_libraries(day02_s1 PRIVATE fmt::fmt)

add_executable(day02_s2 day02_s2.cpp)
target_link_libraries(day02_s2 PRIVATE fmt::fmt)

add_executable(day03_s1 day03_s1.cpp)
target_link_libraries(day03_s1 PRIVATE fmt::fmt std::mdspan)

add_executable(day03_s2 day03_s2.cpp)
target_link_libraries(day03_s2 PRIVATE fmt::fmt std::mdspan)