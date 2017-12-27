/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
SbfAudioProcessor::SbfAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    addParameter(freq = new AudioParameterFloat ("freq", // parameterID
                                                 "Filter Frequency", // parameter name
                                                 10.0f,   // mininum value
                                                 360.0f,   // maximum value
                                                 80.0f)); // default value
    
    addParameter(slope = new AudioParameterBool ("bool",
                                                 "Filter Slope",
                                                 false));
}

SbfAudioProcessor::~SbfAudioProcessor()
{
}

//==============================================================================
const String SbfAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SbfAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SbfAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SbfAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SbfAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SbfAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int SbfAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SbfAudioProcessor::setCurrentProgram (int index)
{
}

const String SbfAudioProcessor::getProgramName (int index)
{
    return {};
}

void SbfAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void SbfAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    currentSampleRate = sampleRate;
    filter.reserve(2);
    filter[0].init();
    filter[1].init();
}

void SbfAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SbfAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void SbfAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    const int totalNumInputChannels  = getTotalNumInputChannels();
    const int totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    for (int sample = 0; sample < buffer.getNumSamples(); sample ++)
    {
        if (*freq != prevFreq)
        {
            filter[0].setParams(*freq, currentSampleRate);
            filter[1].setParams(*freq, currentSampleRate);
            prevFreq = *freq;
        }
        
        
        mid = 0.5*(buffer.getSample(0, sample)+buffer.getSample(1, sample));
        side = filter[0].linearHighPass(0.5*(buffer.getSample(0, sample)-buffer.getSample(1, sample)));
        if (*slope == true)
        {
            side = filter[1].linearHighPass(side);
        }
        buffer.setSample(0, sample, mid+side);
        buffer.setSample(1, sample, mid-side);
        
    }
}

//==============================================================================
bool SbfAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* SbfAudioProcessor::createEditor()
{
    return new SbfAudioProcessorEditor (*this);
}

//==============================================================================
void SbfAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    ScopedPointer<XmlElement> xml (new XmlElement ("SBF"));
    xml->setAttribute("freq", (double) *freq);
    xml->setAttribute("slope", (bool) *slope);
}

void SbfAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    ScopedPointer<XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));
    
    if (xmlState != nullptr)
    {
        if (xmlState->hasTagName ("SBF"))
        {
            *freq = (float) xmlState->getDoubleAttribute ("freq", 60.0);
            *slope = xmlState->getBoolAttribute ("slope", false);
        }
    }}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SbfAudioProcessor();
}
