/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
PolygonalSynthesizerAudioProcessor::PolygonalSynthesizerAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    synth.addSound(new SynthSound());
    for(int voiceIdx=0; voiceIdx < numVoices; voiceIdx++){
        synth.addVoice(new SynthVoice());
    }
    
    
}

PolygonalSynthesizerAudioProcessor::~PolygonalSynthesizerAudioProcessor()
{
}

//==============================================================================
const juce::String PolygonalSynthesizerAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool PolygonalSynthesizerAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool PolygonalSynthesizerAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool PolygonalSynthesizerAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double PolygonalSynthesizerAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int PolygonalSynthesizerAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int PolygonalSynthesizerAudioProcessor::getCurrentProgram()
{
    return 0;
}

void PolygonalSynthesizerAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String PolygonalSynthesizerAudioProcessor::getProgramName (int index)
{
    return {};
}

void PolygonalSynthesizerAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void PolygonalSynthesizerAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    
    synth.setCurrentPlaybackSampleRate(sampleRate);
    
    for(int i=0; i < synth.getNumVoices(); ++i){
        if(auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i))){
            voice->prepareToPlay(sampleRate, samplesPerBlock, getTotalNumOutputChannels());
        }
        
    }
}

void PolygonalSynthesizerAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool PolygonalSynthesizerAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
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

void PolygonalSynthesizerAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    for(int i=0; i < synth.getNumVoices(); ++i){
        if(auto voice = dynamic_cast<juce::SynthesiserVoice*>(synth.getVoice(i))){
            // We deal with the voice parameter updates here later...
        }
    }
    
    setParams();
    
//    for(const auto metadata: midiMessages){
//        if (metadata.numBytes == 3){
//            juce::Logger::writeToLog("Timestamp: " + juce::String(metadata.getMessage().getTimeStamp()));
//        }
//    }
    
    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
//    filter.process(buffer);
}

//==============================================================================
bool PolygonalSynthesizerAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* PolygonalSynthesizerAudioProcessor::createEditor()
{
    return new PolygonalSynthesizerAudioProcessorEditor (*this);
}

//==============================================================================
void PolygonalSynthesizerAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void PolygonalSynthesizerAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PolygonalSynthesizerAudioProcessor();
}

juce::AudioProcessorValueTreeState::ParameterLayout PolygonalSynthesizerAudioProcessor::createParameterLayout(){
    
    juce::AudioProcessorValueTreeState::ParameterLayout layout;
    
    // Combo box to switch oscillator waveform
    layout.add(std::make_unique<juce::AudioParameterChoice>("OSC1 Waveform", "OSC1 Waveform", juce::StringArray{"sine", "sawtooth", "square"}, 0));
    
    // FM Frequency - float
    layout.add(std::make_unique<juce::AudioParameterFloat>("OSC1 FM Freq",
                                                           "OSC1 FM Frequency",
                                                           juce::NormalisableRange<float>{0.0f, 1000.0f},
                                                           5.0f));
    
    // FM Depth - float
    layout.add(std::make_unique<juce::AudioParameterFloat>("OSC1 FM Depth",
                                                           "OSC1 FM Depth",
                                                           juce::NormalisableRange<float>{0.0f, 1.0f},
                                                           0.5f));
    // Attack - float
    layout.add(std::make_unique<juce::AudioParameterFloat>("Envelope Attack",
                                                                 "Envelope Attack",
                                                                 juce::NormalisableRange<float>{0.02f, 2.0f, 0.01, 0.25},
                                                                 0.1f));
    // Decay - float
    layout.add(std::make_unique<juce::AudioParameterFloat>("Envelope Decay",
                                                                 "Envelope Decay",
                                                                 juce::NormalisableRange<float>{0.02f, 2.0f, 0.01, 0.25},
                                                                 0.1f));
    // Sustain - float
    layout.add(std::make_unique<juce::AudioParameterFloat>("Envelope Sustain",
                                                                 "Envelope Sustain",
                                                                 juce::NormalisableRange<float>{0.0f, 1.0f, 0.01f, 0.25},
                                                                 1.0f));
    // Release - float
    layout.add(std::make_unique<juce::AudioParameterFloat>("Envelope Release",
                                                                 "Envelope Release",
                                                                 juce::NormalisableRange<float>{0.0f, 8.0f, 0.01, 0.25},
                                                                 0.4f));
    // Mod ADSR Attack - float
    layout.add(std::make_unique<juce::AudioParameterFloat>("Mod Envelope Attack",
                                                           "Mod Envelope Attack",
                                                           juce::NormalisableRange<float>{0.02f, 2.0f, 0.01, 0.25},
                                                           0.1f));
    // Mod ADSR Decay - float
    layout.add(std::make_unique<juce::AudioParameterFloat>("Mod Envelope Decay",
                                                           "Mod Envelope Decay",
                                                           juce::NormalisableRange<float>{0.02f, 2.0f, 0.01, 0.25},
                                                           0.1f));
    // Mod ADSR Sustain - float
    layout.add(std::make_unique<juce::AudioParameterFloat>("Mod Envelope Sustain",
                                                           "Mod Envelope Sustain",
                                                           juce::NormalisableRange<float>{0.0f, 1.0f, 0.01f, 0.25},
                                                           1.0f));
    // Mod ADSR Release - float
    layout.add(std::make_unique<juce::AudioParameterFloat>("Mod Envelope Release",
                                                           "Mod Envelope Release",
                                                           juce::NormalisableRange<float>{0.0f, 8.0f, 0.01, 0.25},
                                                           0.4f));
    // Filter type - Choice
    layout.add(std::make_unique<juce::AudioParameterChoice>("Filter Type", "Filter Type", juce::StringArray{"LowPass", "BandPass", "HighPass"}, 0));
    
    // Filter frequency - float
    layout.add(std::make_unique<juce::AudioParameterFloat>("Filter Freq",
                                                           "Filter Freq",
                                                           juce::NormalisableRange<float>{20.0f, 20000.0f, 1.0f, 0.33f},
                                                           500.0f));
    
    // Filter resonance - float
    layout.add(std::make_unique<juce::AudioParameterFloat>("Filter Resonance",
                                                           "Filter Resonance",
                                                           juce::NormalisableRange<float>{0.01f, 3.0f, 0.01f, 0.33f},
                                                           1.0f));
    
    return layout;
}

void PolygonalSynthesizerAudioProcessor::setParams()
{
    setVoiceParams();
    setFilterParams();
//    setReverbParams();
}

void PolygonalSynthesizerAudioProcessor::setVoiceParams(){
    for (int i = 0; i < synth.getNumVoices(); ++i)
    {
        if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i)))
        {
            auto& attack = *apvts.getRawParameterValue ("Envelope Attack");
            auto& decay = *apvts.getRawParameterValue ("Envelope Decay");
            auto& sustain = *apvts.getRawParameterValue ("Envelope Sustain");
            auto& release = *apvts.getRawParameterValue ("Envelope Release");
            
            auto& modAttack = *apvts.getRawParameterValue ("Mod Envelope Attack");
            auto& modDecay = *apvts.getRawParameterValue ("Mod Envelope Decay");
            auto& modSustain = *apvts.getRawParameterValue ("Mod Envelope Sustain");
            auto& modRelease = *apvts.getRawParameterValue ("Mod Envelope Release");
            
            auto& osc1WaveChoice = *apvts.getRawParameterValue("OSC1 Waveform");
            auto& osc1FmFreq = *apvts.getRawParameterValue("OSC1 FM Freq");
            auto& osc1FmDepth = *apvts.getRawParameterValue("OSC1 FM Depth");
            
            auto& filterType = *apvts.getRawParameterValue ("Filter Type");
            auto& filterFrequency = *apvts.getRawParameterValue ("Filter Freq");
            auto& filterResonance = *apvts.getRawParameterValue ("Filter Resonance");
            
            voice->updateADSRMod(modAttack.load(), modDecay.load(), modSustain.load(), modRelease.load());
            voice->updateFilter(filterType.load(), filterFrequency.load(), filterResonance.load());
            voice->updateADSR(attack.load(), decay.load(), sustain.load(), release.load());
            voice->getOscillator().setFmParams(osc1FmDepth, osc1FmFreq);
            voice->getOscillator().setWaveType(osc1WaveChoice);
        }
        
    }
}

void PolygonalSynthesizerAudioProcessor::setFilterParams(){

}

