#include "PluginEditor.h"
#include "PluginProcessor.h"

FS_ReverberatorAudioProcessorEditor::FS_ReverberatorAudioProcessorEditor(FS_ReverberatorAudioProcessor &p)
    : AudioProcessorEditor(&p), audioProcessor(p) {
    setSize(400, 450);

    setLookAndFeel(&fsTheme);

    // dry ui
    dryLabel.setText("DRY", dontSendNotification);
    dryLabel.setJustificationType(Justification::centred);
    dryLabel.attachToComponent(&drySlider, false);
    addAndMakeVisible(dryLabel);

    drySlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    drySlider.setTextBoxStyle(Slider::TextBoxBelow, false, 60, 18);
    drySlider.setTextValueSuffix(" %");
    addAndMakeVisible(drySlider);
    dryAttachment = std::make_unique<SliderAttachment>(audioProcessor.getAPVTS(), "dry", drySlider);

    // wet ui
    wetLabel.setText("WET", dontSendNotification);
    wetLabel.setJustificationType(Justification::centred);
    wetLabel.attachToComponent(&wetSlider, false);
    addAndMakeVisible(wetLabel);

    wetSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    wetSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 60, 18);
    wetSlider.setTextValueSuffix(" %");
    addAndMakeVisible(wetSlider);
    wetAttachment = std::make_unique<SliderAttachment>(audioProcessor.getAPVTS(), "wet", wetSlider);

    // preDelay ui
    preDelayLabel.setText("PRE-DELAY", dontSendNotification);
    preDelayLabel.setJustificationType(Justification::centred);
    preDelayLabel.attachToComponent(&preDelaySlider, false);
    addAndMakeVisible(preDelayLabel);

    preDelaySlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    preDelaySlider.setTextBoxStyle(Slider::TextBoxBelow, false, 60, 18);
    preDelaySlider.setTextValueSuffix(" ms"); // Пределей зазвичай у мілісекундах
    addAndMakeVisible(preDelaySlider);
    preDelayAttachment = std::make_unique<SliderAttachment>(audioProcessor.getAPVTS(), "preDelay", preDelaySlider);

    // room ui
    roomLabel.setText("ROOM SIZE", dontSendNotification);
    roomLabel.setJustificationType(Justification::centred);
    roomLabel.attachToComponent(&roomSlider, false);
    addAndMakeVisible(roomLabel);

    roomSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    roomSlider.setTextBoxStyle(Slider::TextBoxBelow, false, 70, 20);
    roomSlider.setTextValueSuffix(" %");
    addAndMakeVisible(roomSlider);
    roomAttachment = std::make_unique<SliderAttachment>(audioProcessor.getAPVTS(), "room", roomSlider);
}

void FS_ReverberatorAudioProcessorEditor::paint(juce::Graphics &g) {
    g.fillAll(Colour(FS_LookAndFeel::colorBackground));

    auto bounds = getLocalBounds().reduced(16).toFloat();

    g.setColour(Colour(FS_LookAndFeel::colorPanel));
    g.fillRoundedRectangle(bounds, 8.0f);

    g.setColour(Colour(0xff2a2e39));
    g.drawRoundedRectangle(bounds, 8.0f, 1.5f);

    auto innerFrame = bounds.reduced(10.0f);
    g.setColour(Colour(0xff1f232e));
    g.drawRoundedRectangle(innerFrame, 6.0f, 1.0f);

    g.setColour(Colour(0xff8e95a5));
    g.setFont(Font(12.0f, Font::bold));
    g.drawText("KREIA DSP", bounds.getX() + 15, bounds.getY() + 12, 100, 20, Justification::left);

    g.setColour(Colour(FS_LookAndFeel::colorAmber));
    g.setFont(Font(16.0f, Font::bold));
    g.drawFittedText("MICRO DIGITAL REVERBERATOR", 0, getHeight() - 40, getWidth(), 24, Justification::centred, 1);
}

void FS_ReverberatorAudioProcessorEditor::resized() {
    auto bounds = getLocalBounds();

    const int topRowY = 55;
    const int smallDialSize = 80;
    const int xSpacing = getWidth() / 3;

    drySlider.setBounds((xSpacing * 0) + (xSpacing - smallDialSize) / 2, topRowY, smallDialSize, smallDialSize);
    wetSlider.setBounds((xSpacing * 1) + (xSpacing - smallDialSize) / 2, topRowY, smallDialSize, smallDialSize);
    preDelaySlider.setBounds((xSpacing * 2) + (xSpacing - smallDialSize) / 2, topRowY, smallDialSize, smallDialSize);

    const int largeDialSize = 145;
    const int bottomRowY = 195;

    roomSlider.setBounds((getWidth() - largeDialSize) / 2, bottomRowY, largeDialSize, largeDialSize);
}