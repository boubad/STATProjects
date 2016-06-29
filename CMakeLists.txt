cmake_minimum_required(VERSION 2.6)
project(infodata)
include_directories(/usr/include/eigen3)
add_executable(infodata infotestdata.cpp main.cpp)

install(TARGETS infodata RUNTIME DESTINATION bin)
