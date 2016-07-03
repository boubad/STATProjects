cmake_minimum_required(VERSION 2.6)
project(infodata)
include_directories(/usr/include/eigen3 datalib)
add_executable(infodata infotestdata.cpp infodatafixture.cpp main.cpp test_indiv.cpp)
target_link_libraries(infodata datalib UnitTest++ cpprest pthread)
install(TARGETS infodata RUNTIME DESTINATION bin)

add_subdirectory(datalib)