cmake_minimum_required(VERSION 3.17)
project(search_engine)

set(CMAKE_CXX_STANDARD 14)

set(JSON_BuildTests OFF CACHE INTERNAL "")

add_subdirectory(nlohmann_json)

add_executable(search_engine src/main.cpp src/allExceptions.cpp src/ConverterJSON.cpp src/InvertedIndex.cpp include/InvertedIndex.h src/SearchServer.cpp include/SearchServer.h)

target_include_directories(search_engine PUBLIC src include resources)

target_link_libraries(search_engine PRIVATE nlohmann_json::nlohmann_json)



include(FetchContent)
FetchContent_Declare(googletest URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})


set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)



target_link_libraries(search_engine PRIVATE gtest_main)
include(GoogleTest)
gtest_discover_tests(search_engine)
