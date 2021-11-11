/*
  ==============================================================================

    SynthVoice.cpp
    Created: 8 Nov 2021 10:04:51pm
    Author:  Max Elliott

  ==============================================================================
*/

#include "SynthVoice.h"

bool SynthVoice::canPlaySound (juce::SynthesiserSound* sound){
    return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;
}

void SynthVoice::startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition){
    osc.setWaveFrequency(midiNoteNumber);
    adsr.noteOn();
}

void SynthVoice::stopNote (float velocity, bool allowTailOff){
    adsr.noteOff();
    
    if(!allowTailOff || !adsr.isActive()){
        clearCurrentNote();
    }
}

void SynthVoice::pitchWheelMoved (int newPitchWheelValue){
    
}

void SynthVoice::controllerMoved (int controllerNumber, int newControllerValue){
    
}

void SynthVoice::updateADSR(const float a, const float d, const float s, const float r){
    adsr.updateParameters(a, d, s, r);
}

void SynthVoice::updateFilter(const int type, const float frequency, const float resonance){
    filter.updateParameters(type, frequency, resonance);
}

void SynthVoice::prepareToPlay(double sampleRate, int samplesPerBlock, int numOutputChannels){
    
    adsr.setSampleRate(sampleRate);
    
    juce::dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = numOutputChannels;
    
    osc.prepareToPlay(spec);
    
    filter.prepareToPlay(spec);
    
    gain.prepare(spec);
    gain.setGainLinear(0.01f);
    
    isPrepared = true;
}

void SynthVoice::renderNextBlock (juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples){
    jassert(isPrepared);
    
    if (!isVoiceActive()){
        return;
    }
    
    synthBuffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);
    synthBuffer.clear();
    
    juce::dsp::AudioBlock<float> audioBlock{synthBuffer};
    osc.processNextAudioBlock(audioBlock);
    filter.process(synthBuffer);
    gain.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
    
    adsr.applyEnvelopeToBuffer(synthBuffer, 0, synthBuffer.getNumSamples());
    
    for(int channelIdx=0; channelIdx< outputBuffer.getNumChannels(); channelIdx++){
        outputBuffer.addFrom(channelIdx, startSample, synthBuffer, channelIdx, 0, numSamples);
        
        if (!adsr.isActive()){
            clearCurrentNote();
        }
    }
}
