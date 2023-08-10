cmake_minimum_required(VERSION 3.5)

project(JsonParser LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

#add_executable(JsonParser main.cpp src/json.cpp src/parse.cpp)
add_executable(JsonParser main.cpp src/json.cpp src/parse.cpp)
