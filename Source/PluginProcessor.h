#pragma once
#include <juce_audio_processors/juce_audio_processors.h>

#include "DSP/ReverberatorEngine.h"

using namespace std;
using namespace juce;

class FS_ReverberatorAudioProcessor : public AudioProcessor {
public:
    FS_ReverberatorAudioProcessor();
    ~FS_ReverberatorAudioProcessor() override = default;

    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    void processBlock(AudioBuffer<float> &, MidiBuffer &) override;

    AudioProcessorEditor *createEditor() override;
    bool hasEditor() const override { return true; }

    const String getName() const override { return "Simple-Reverberator"; }
    bool acceptsMidi() const override { return false; }
    bool producesMidi() const override { return false; }
    double getTailLengthSeconds() const override { return 0.0; }

    int getNumPrograms() override { return 1; }
    int getCurrentProgram() override { return 0; }
    void setCurrentProgram(int) override {}
    const String getProgramName(int) override { return {}; }
    void changeProgramName(int, const String &) override {}

    void getStateInformation(MemoryBlock &destData) override;
    void setStateInformation(const void *data, int sizeInBytes) override;

    juce::AudioProcessorValueTreeState &getAPVTS() { return apvts; }

private:
    AudioProcessorValueTreeState apvts;
    AudioProcessorValueTreeState::ParameterLayout createParameterLayout();

    ReverberatorEngine reverberator;

    atomic<float> *dryParameter = nullptr;
    atomic<float> *wetParameter = nullptr;
    atomic<float> *preDelayParameter = nullptr;
    atomic<float> *roomParameter = nullptr;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FS_ReverberatorAudioProcessor)
};