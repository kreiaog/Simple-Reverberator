#pragma once

#include "GUI/FS_LookAndFeel.h"
#include "PluginProcessor.h"

using namespace juce;

using SliderAttachment = AudioProcessorValueTreeState::SliderAttachment;

class FS_ReverberatorAudioProcessorEditor : public juce::AudioProcessorEditor {
public:
    explicit FS_ReverberatorAudioProcessorEditor(FS_ReverberatorAudioProcessor &);
    ~FS_ReverberatorAudioProcessorEditor() { setLookAndFeel(nullptr); };

    void paint(juce::Graphics &) override;
    void resized() override;

private:
    FS_LookAndFeel fsTheme;

    FS_ReverberatorAudioProcessor &audioProcessor;

    Label dryLabel;
    Slider drySlider;
    unique_ptr<SliderAttachment> dryAttachment;

    Label wetLabel;
    Slider wetSlider;
    unique_ptr<SliderAttachment> wetAttachment;

    Label preDelayLabel;
    Slider preDelaySlider;
    unique_ptr<SliderAttachment> preDelayAttachment;

    Label roomLabel;
    Slider roomSlider;
    unique_ptr<SliderAttachment> roomAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FS_ReverberatorAudioProcessorEditor)
};