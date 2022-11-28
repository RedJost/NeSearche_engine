cmake_minimum_required(VERSION 3.17)
project(search_engine)

set(CMAKE_CXX_STANDARD 14)

set(JSON_BuildTests OFF CACHE INTERNAL "")

add_subdirectory(nlohmann_json)

add_executable(search_engine src/main.cpp src/allExceptions.cpp src/ConverterJSON.cpp src/InverterIndex.cpp include/InverterIndex.h src/SearchServer.cpp include/SearchServer.h)

target_include_directories(search_engine PUBLIC src include resources)

target_link_libraries(search_engine PRIVATE nlohmann_json::nlohmann_json)




