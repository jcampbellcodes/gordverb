cmake_minimum_required(VERSION 3.5)

set(ADVERB_TESTS_TARGET adverb_tests)

project(${ADVERB_TESTS_TARGET} LANGUAGES CXX VERSION 0.0.1)

file(GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
add_executable(${ADVERB_TESTS_TARGET} ${SOURCES})
target_link_libraries(${ADVERB_TESTS_TARGET} Catch2::Catch2WithMain)

include(CTest)
include(Catch)
catch_discover_tests(${ADVERB_TESTS_TARGET})