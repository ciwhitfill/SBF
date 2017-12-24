/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "CustomLookAndFeel.h"


//==============================================================================
/**
*/
class SbfAudioProcessorEditor  : public AudioProcessorEditor,
                                 public Slider::Listener,
                                 private Timer
{
public:
    SbfAudioProcessorEditor (SbfAudioProcessor&);
    ~SbfAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    
    void sliderValueChanged (Slider* slider) override
    {
        if (slider == &filterFreq)
        {
            *processor.freq = (float) slider->getValue();
        }
    }
    
    void sliderDragStarted (Slider* slider) override
    {
        if (slider == &filterFreq)
        {
            processor.freq->beginChangeGesture();
        }
    }
    
    void sliderDragEnded (Slider* slider) override
    {
        if (slider == &filterFreq)
        {
            processor.freq->endChangeGesture();
        }
    }
    private:
    void timerCallback() override
    {
        filterFreq.setValue(*processor.freq);
        freqLabel.setText(String(*processor.freq, 0), dontSendNotification);
    }
    

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SbfAudioProcessor& processor;
    
    CustomLookAndFeel customLookAndFeel;
    Label titleLabel;
    Slider filterFreq;
    Label freqLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SbfAudioProcessorEditor)
};
