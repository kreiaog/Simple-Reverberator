#include "PluginProcessor.h"

#include "PluginEditor.h"

FS_ReverberatorAudioProcessor::FS_ReverberatorAudioProcessor()
    : AudioProcessor(BusesProperties()
                         .withInput("Input", juce::AudioChannelSet::stereo(), true)
                         .withOutput("Output", juce::AudioChannelSet::stereo(), true)),
      apvts(*this, nullptr, "Parameters", createParameterLayout()) {
    dryParameter = apvts.getRawParameterValue("dry");
    wetParameter = apvts.getRawParameterValue("wet");
    preDelayParameter = apvts.getRawParameterValue("preDelay");
    roomParameter = apvts.getRawParameterValue("room");
}

void FS_ReverberatorAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock) {
    juce::ignoreUnused(sampleRate, samplesPerBlock);
}

void FS_ReverberatorAudioProcessor::releaseResources() {}

void FS_ReverberatorAudioProcessor::processBlock(juce::AudioBuffer<float> &buffer, juce::MidiBuffer &midiMessages) {
    juce::ignoreUnused(midiMessages);
    juce::ScopedNoDenormals noDenormals;

    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());

    if (totalNumInputChannels == 0 || buffer.getNumSamples() == 0)
        return;

    if (dryParameter != nullptr)
        reverberator.setDry(dryParameter->load());

    if (wetParameter != nullptr)
        reverberator.setWet(wetParameter->load());

    if (preDelayParameter != nullptr)
        reverberator.setPreDelay(preDelayParameter->load());

    if (roomParameter != nullptr)
        reverberator.setRoomSize(roomParameter->load());

    auto *leftChannel = buffer.getWritePointer(0);
    auto *rightChannel = (totalNumInputChannels > 1) ? buffer.getWritePointer(1) : leftChannel;

    reverberator.processBlock(leftChannel, rightChannel, buffer.getNumSamples());
}

juce::AudioProcessorEditor *FS_ReverberatorAudioProcessor::createEditor() {
    return new FS_ReverberatorAudioProcessorEditor(*this);
}

void FS_ReverberatorAudioProcessor::getStateInformation(juce::MemoryBlock &destData) {
    auto state = apvts.copyState();
    unique_ptr<XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void FS_ReverberatorAudioProcessor::setStateInformation(const void *data, int sizeInBytes) {
    unique_ptr<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    if (xmlState != nullptr && xmlState->hasTagName(apvts.state.getType()))
        apvts.replaceState(ValueTree::fromXml(*xmlState));
}

AudioProcessorValueTreeState::ParameterLayout FS_ReverberatorAudioProcessor::createParameterLayout() {
    vector<unique_ptr<RangedAudioParameter>> params;

    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{"dry", 1}, "Dry", juce::NormalisableRange<float>(0.0f, 100.0f, 0.1f), 100.0f,
        juce::AudioParameterFloatAttributes().withLabel("%")));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{"wet", 1}, "Wet", juce::NormalisableRange<float>(0.0f, 100.0f, 0.1f), 50.0f,
        juce::AudioParameterFloatAttributes().withLabel("%")));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{"preDelay", 1}, "Pre-Delay", juce::NormalisableRange<float>(0.0f, 250.0f, 0.1f, 0.5f), 20.0f,
        juce::AudioParameterFloatAttributes().withLabel("ms")));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        juce::ParameterID{"room", 1}, "Room Size", juce::NormalisableRange<float>(0.0f, 100.0f, 0.1f), 50.0f,
        juce::AudioParameterFloatAttributes().withLabel("%")));

    return {params.begin(), params.end()};
}

juce::AudioProcessor *JUCE_CALLTYPE createPluginFilter() {
    return new FS_ReverberatorAudioProcessor();
}