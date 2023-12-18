cmake_minimum_required(VERSION 3.27)
project(Monkey_Library)

set(CMAKE_CXX_STANDARD 17)

add_executable(Monkey_Library main.cpp)

target_link_libraries(Monkey_Library LINK_PUBLIC sqlite3)