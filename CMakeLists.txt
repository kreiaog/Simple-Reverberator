cmake_minimum_required(VERSION 3.22)

project(Simple_Reverberator VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
    JUCE
    GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
    GIT_TAG        7.0.12
    GIT_SUBMODULES_RECURSE TRUE
)

FetchContent_MakeAvailable(JUCE)

juce_add_plugin(Simple_Reverberator
    COMPANY_NAME "KreiaDSP"
    IS_SYNTH FALSE
    NEEDS_MIDI_INPUT FALSE
    NEEDS_MIDI_OUTPUT FALSE
    IS_MIDI_EFFECT FALSE
    EDITOR_WANTS_KEYBOARD_FOCUS FALSE
    COPY_PLUGIN_AFTER_BUILD TRUE
    PLUGIN_MANUFACTURER_CODE Krei
    PLUGIN_CODE Rev1
    FORMATS VST3 Standalone
    PRODUCT_NAME "Simple-Reverberator"
)

target_sources(Simple_Reverberator PRIVATE
    Source/PluginProcessor.h
    Source/PluginProcessor.cpp
    Source/PluginEditor.h
    Source/PluginEditor.cpp
    Source/DSP/ReverberatorEngine.h
    Source/GUI/FS_LookAndFeel.h
)

target_link_libraries(Simple_Reverberator PRIVATE
    juce::juce_audio_utils
    juce::juce_dsp
    juce::juce_recommended_config_flags
    juce::juce_recommended_warning_flags
)

target_include_directories(Simple_Reverberator PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Source
)

target_compile_definitions(Simple_Reverberator PRIVATE
    JUCE_VST3_CAN_REPLACE_VST2=0
)