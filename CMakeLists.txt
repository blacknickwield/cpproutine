cmake_minimum_required(VERSION 3.26)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
project(cpproutine)


include_directories(include)

add_executable(${PROJECT_NAME}  src/stackful.cpp src/context.cpp src/scheduler.cpp main.cpp)
