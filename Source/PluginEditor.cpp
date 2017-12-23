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
    
    /* Frequency Slider */
    filterFreq.setSliderStyle(juce::Slider::Rotary);
    //filterFreq.setRange(processor.freq->range.start, processor.freq->range.end, 1);
    //filterFreq.setDoubleClickReturnValue(true, 60);
    filterFreq.setTextBoxStyle(juce::Slider::NoTextBox, false, 60, 30);
    //filterFreq.setTextValueSuffix (" Hz");
    //filterFreq.setValue(*processor.freq);
    //filterFreq.setSkewFactorFromMidPoint(60);
    //filterFreq.setPopupDisplayEnabled(true, true, &filterFreq);
    //filterFreq.addListener(this);
    addAndMakeVisible (&filterFreq);
}

SbfAudioProcessorEditor::~SbfAudioProcessorEditor()
{
}

//==============================================================================
void SbfAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (64.0f);
    g.drawFittedText ("SBF", getLocalBounds(), Justification::centredTop, 1);
}

void SbfAudioProcessorEditor::resized()
{
    filterFreq.setBounds(37.5f, 52.5f, 225, 225);
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
