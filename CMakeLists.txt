cmake_minimum_required(VERSION 3.15)

project(Adverb VERSION 0.0.1)

# build universal on macOS
set(CMAKE_OSX_ARCHITECTURES "arm64;x86_64")
add_subdirectory(submodules/JUCE)
add_subdirectory(submodules/Catch2)

# this is the actual plugin
add_subdirectory(src)

# unit tests
add_subdirectory(tests)