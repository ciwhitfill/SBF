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
                                 public Button::Listener,
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
    
    
    void buttonClicked (Button* button) override
    {
        if (button == &shallowSlopeButton)
            *processor.slope = false;
        if (button == &steepSlopeButton)
            *processor.slope = true;
    }
    
    private:
    void timerCallback() override
    {
        filterFreq.setValue(*processor.freq);
        freqLabel.setText(String(*processor.freq, 0), dontSendNotification);
        
        if (*processor.slope)
            steepSlopeButton.setToggleState (true, dontSendNotification);
        else
            shallowSlopeButton.setToggleState (true, dontSendNotification);
    }
    

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SbfAudioProcessor& processor;
    
    CustomLookAndFeel customLookAndFeel;
    Label titleLabel;
    Slider filterFreq;
    Label freqLabel;
    TextButton shallowSlopeButton;
    TextButton steepSlopeButton;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SbfAudioProcessorEditor)
};
