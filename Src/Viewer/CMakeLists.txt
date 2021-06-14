cmake_minimum_required (VERSION 3.8)

include_directories(../Parser/include)
add_executable(${PROJECT_NAME} main.cpp Deserialize/Deserializer.cpp Deserialize/Deserializer.h Util/timer.hpp)