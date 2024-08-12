cmake_minimum_required(VERSION 3.22)

project(minibpe LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(extern/utfcpp)

add_subdirectory(include)
add_subdirectory(tests)
