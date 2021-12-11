cmake_minimum_required(VERSION 3.20)
project(aoc2021)

set(CMAKE_CXX_STANDARD 20)
set(DAY "11")

add_executable(part1 src/day${DAY}/part1.cpp)
add_executable(part2 src/day${DAY}/part2.cpp)
