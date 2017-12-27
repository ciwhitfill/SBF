/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
SbfAudioProcessorEditor::SbfAudioProcessorEditor (SbfAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    LookAndFeel::setDefaultLookAndFeel (&customLookAndFeel);
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (300, 300);
    
    /* Title */
    titleLabel.setText ("SBF", dontSendNotification);
    titleLabel.setFont(customLookAndFeel.titleFont().withHeight(64));
    titleLabel.setJustificationType(juce::Justification::centredTop);
    addAndMakeVisible (&titleLabel);

    
    /* Frequency Label */
    freqLabel.setText(String(*processor.freq, 0), dontSendNotification);
    freqLabel.setFont(customLookAndFeel.freqFont().withHeight(112));
    freqLabel.setJustificationType(juce::Justification::horizontallyCentred);
    addAndMakeVisible(&freqLabel);
    /* Frequency Slider */
    filterFreq.setSliderStyle(juce::Slider::Rotary);
    filterFreq.setRange(processor.freq->range.start, processor.freq->range.end, 1);
    filterFreq.setDoubleClickReturnValue(true, 60);
    filterFreq.setTextBoxStyle(juce::Slider::NoTextBox, false, 60, 30);
    filterFreq.setValue(*processor.freq);
    filterFreq.setSkewFactorFromMidPoint(60);
    filterFreq.setPopupDisplayEnabled(true, true, &filterFreq);
    filterFreq.addListener(this);
    addAndMakeVisible (&filterFreq);
    

    shallowSlopeButton.setConnectedEdges(2);
    shallowSlopeButton.setButtonText("6dB");
    shallowSlopeButton.setClickingTogglesState(true);
    shallowSlopeButton.setRadioGroupId(1);
    shallowSlopeButton.addListener(this);
    addAndMakeVisible(&shallowSlopeButton);
    
    steepSlopeButton.setConnectedEdges(1);
    steepSlopeButton.setButtonText("12dB");
    shallowSlopeButton.setClickingTogglesState(true);
    steepSlopeButton.setRadioGroupId(1);
    steepSlopeButton.addListener(this);

    addAndMakeVisible(&steepSlopeButton);
    
    
    startTimer(30);
}

SbfAudioProcessorEditor::~SbfAudioProcessorEditor()
{
}

//==============================================================================
void SbfAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
}

void SbfAudioProcessorEditor::resized()
{
    //auto r = getLocalBounds();
    titleLabel.setBounds(75, -5, 150, 150);
    filterFreq.setBounds(37.5f, 52.5f, 225.0f, 225.0f);
    freqLabel.setBounds(100, 107.5f, 100, 100);
    shallowSlopeButton.setBounds(111, 255, 40, 30);
    steepSlopeButton.setBounds(149, 255, 40, 30);
}
