cmake_minimum_required(VERSION 2.6)
project(infodata)

add_executable(infodata main.cpp)

install(TARGETS infodata RUNTIME DESTINATION bin)
