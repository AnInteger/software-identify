project(software-identify-test)

cmake_minimum_required(VERSION 3.22)

file (GLOB SOURCES 
    "../src/*.cpp"
)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
    set(CMAKE_CXX_FLAGS_DEBUG "-Wall -g")
endif()

message("CMAKE_BUILD_TYPE = ${CMAKE_BUILD_TYPE}")

add_executable(${PROJECT_NAME} identify_test.cpp ${SOURCES})
