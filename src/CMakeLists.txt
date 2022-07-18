set(gordverb_TARGET gordverb)

project(${gordverb_TARGET} VERSION 0.0.1)

set(BINARY_TARGET_NAME GVBinaryData)

juce_add_plugin(${gordverb_TARGET}
    COMPANY_NAME "Keen Coyote"
    IS_SYNTH FALSE
    NEEDS_MIDI_INPUT FALSE
    NEEDS_MIDI_OUTPUT FALSE
    IS_MIDI_EFFECT FALSE 
    COPY_PLUGIN_AFTER_BUILD TRUE
    PLUGIN_MANUFACTURER_CODE Keen
    PLUGIN_CODE GorD                        
    FORMATS AU VST3 Standalone # Other valid formats are: AAX Unity VST AU AUv3
    PRODUCT_NAME "gordverb")


file( GLOB BINARY_RESOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/../resources/**/*.wav
)


file(GLOB SOURCES 
    ${CMAKE_CURRENT_SOURCE_DIR}/*.h     
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/early_reflections/*.h     
    ${CMAKE_CURRENT_SOURCE_DIR}/early_reflections/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/late_reflections/*.h     
    ${CMAKE_CURRENT_SOURCE_DIR}/late_reflections/*.cpp

    # add standalone fx from Daisy explicitly
    ${CMAKE_CURRENT_SOURCE_DIR}/../submodules/DaisySP/Source/Effects/reverbsc.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../submodules/DaisySP/Source/Effects/reverbsc.cpp
    )
 
target_include_directories( ${gordverb_TARGET}  
PUBLIC
${CMAKE_CURRENT_SOURCE_DIR}
${CMAKE_CURRENT_SOURCE_DIR}/early_reflections
${CMAKE_CURRENT_SOURCE_DIR}/late_reflections
${CMAKE_CURRENT_SOURCE_DIR}/../submodules/DaisySP/Source/Effects)

target_sources(${gordverb_TARGET}
    PRIVATE
        ${SOURCES})

target_compile_definitions(${gordverb_TARGET}
    PUBLIC
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_VST3_CAN_REPLACE_VST2=0)

target_link_libraries(${gordverb_TARGET}
    PRIVATE
        juce::juce_audio_utils
        juce::juce_dsp
        ${BINARY_TARGET_NAME}
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags)
