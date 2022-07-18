cmake_minimum_required(VERSION 3.5)

set(gordverb_TESTS_TARGET gordverb_tests)

project(${gordverb_TESTS_TARGET} LANGUAGES CXX VERSION 0.0.1)

set(BINARY_TARGET_NAME GVBinaryData)
file( GLOB BINARY_RESOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/../resources/**/*.wav
)
juce_add_binary_data(${BINARY_TARGET_NAME} HEADER_NAME "gv_data.h" 
                    SOURCES 
                    ${BINARY_RESOURCES}
        )

file(GLOB SOURCES 
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/*.h     
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/early_reflections/*.h     
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/early_reflections/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/late_reflections/*.h     
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/late_reflections/*.cpp

    # add standalone fx from Daisy explicitly
    ${CMAKE_CURRENT_SOURCE_DIR}/../submodules/DaisySP/Source/Effects/reverbsc.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../submodules/DaisySP/Source/Effects/reverbsc.cpp
    )
 
add_executable(${gordverb_TESTS_TARGET} ${SOURCES})

target_include_directories( ${gordverb_TESTS_TARGET}  
PUBLIC
${CMAKE_CURRENT_SOURCE_DIR}/../src
${CMAKE_CURRENT_SOURCE_DIR}/../early_reflections
${CMAKE_CURRENT_SOURCE_DIR}/../late_reflections
${CMAKE_CURRENT_SOURCE_DIR}/../submodules/DaisySP/Source/Effects)


target_link_libraries(${gordverb_TESTS_TARGET}
        PRIVATE
            juce::juce_audio_utils
            juce::juce_dsp
            ${BINARY_TARGET_NAME}
            Catch2::Catch2WithMain
        PUBLIC
            juce::juce_recommended_config_flags
            juce::juce_recommended_lto_flags
            juce::juce_recommended_warning_flags)

include(CTest)
include(Catch)
catch_discover_tests(${gordverb_TESTS_TARGET})
