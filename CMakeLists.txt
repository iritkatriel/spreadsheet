cmake_minimum_required(VERSION 3.3)
project(spreadsheet)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(BOOST_ROOT "C:\\src\\boost_1_58_0")
set(BOOSTROOT "C:\\src\\boost_1_58_0")

find_package(Boost 1.58.0)

if(NOT Boost_FOUND)
    message(FATAL_ERROR "Could not find boost!")
endif()

include_directories(${Boost_INCLUDE_DIRS})
include_directories("../streamulus/src")
include_directories(".")

add_definitions(-DUSE_MAIN)


add_executable(spreadsheet main.cpp)
