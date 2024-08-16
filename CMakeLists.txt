cmake_minimum_required(VERSION 3.22)

project(minibpe LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost)
if(Boost_FOUND)
    message(STATUS "Boost found in ${Boost_INCLUDE_DIRS}")
    include_directories(${Boost_INCLUDE_DIRS})
endif()

add_subdirectory(extern/utfcpp)
add_subdirectory(extern/googletest)
add_subdirectory(extern/benchmark)

add_subdirectory(include)
add_subdirectory(tests)
