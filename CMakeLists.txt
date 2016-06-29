cmake_minimum_required(VERSION 2.6)
project(infodata)
include_directories(/usr/include/eigen3)
add_executable(infodata infotestdata.cpp main.cpp)
target_link_libraries(infodata datalib UnitTest++)
install(TARGETS infodata RUNTIME DESTINATION bin)

add_subdirectory(datalib)