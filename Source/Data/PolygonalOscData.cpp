/*
  ==============================================================================

    PolygonalOscData.cpp
    Created: 12 Nov 2021 2:15:14pm
    Author:  Max Elliott

  ==============================================================================
*/

#include "PolygonalOscData.h"
#include <cmath>



void PolygonalOscData::prepareToPlay(juce::dsp::ProcessSpec& spec){
    gain.prepare(spec);
    gain.setGainLinear(1.0f);
    prepare(spec);
    initialise([&](float x){return getOscSamplePair(x);});
    
    isPrepared = true;
}

void PolygonalOscData::processNextAudioBlock(juce::dsp::AudioBlock<float> audioBlock){
    jassert(isPrepared);
    
//    for(int channelIdx=0; channelIdx < audioBlock.getNumChannels(); channelIdx++){
//        for (int sampleIdx=0; sampleIdx < audioBlock.getNumSamples(); sampleIdx++){
//        }
//    }
    
    process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
    gain.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
}

void PolygonalOscData::setWaveFrequency(const int midiNoteNumber){
    setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber));
    currentNoteFrequency = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
}

void PolygonalOscData::setGain(const float newGain){
    gain.setGainLinear(newGain);
}

void PolygonalOscData::setParameters(const float newPitch, const float newOrder, const float newTeeth, const float newPhaseRotation, const float newGain){
    pitchAdjustment = newPitch;
    order = newOrder;
    teeth = newTeeth;
    phaseRotation = newPhaseRotation;
    
    setFrequency(currentNoteFrequency * pitchAdjustment);
    updatePhaseDelta();
    gain.setGainLinear(newGain);
}

void PolygonalOscData::updatePhaseDelta(){
    phaseDelta = phaseRotation / getSampleRate() * juce::MathConstants<float>::twoPi;
}

float PolygonalOscData::updateCurrentPhase(){
    currentPhase += phaseDelta;
    if (currentPhase >= juce::MathConstants<float>::twoPi){
        currentPhase -= juce::MathConstants<float>::twoPi;
    }
    return currentPhase;
}

float PolygonalOscData::getOscSample(const float x){
    
    const float actualPhase = x + juce::MathConstants<float>::pi;
    const float pi = juce::MathConstants<float>::pi;
    const float twoPi = juce::MathConstants<float>::twoPi;
    const float n = order;
    const float t = teeth;
    const float phi = updateCurrentPhase();
    const float xnOverTwoPi  = (actualPhase * n) / twoPi;
    
//    float p = std::cos(pi / n) / (std::cos(twoPi / n * (xnOverTwoPi - (long)xnOverTwoPi) - pi / n + t));
    float p = std::cos(pi / n) / (std::cos(twoPi / n * (fmod(xnOverTwoPi, 1)) - (pi / n) + t));
    return std::cos(actualPhase + phi) * p;
}

std::pair<float, float> PolygonalOscData::getOscSamplePair(const float x){
    
    const float actualPhase = x + juce::MathConstants<float>::pi;
    const float pi = juce::MathConstants<float>::pi;
    const float twoPi = juce::MathConstants<float>::twoPi;
    const float n = order;
    const float t = teeth;
    const float phi = updateCurrentPhase();
    const float xnOverTwoPi  = (actualPhase * n) / twoPi;
    
    float p = std::cos(pi / n) / (std::cos(twoPi / n * (fmod(xnOverTwoPi, 1)) - (pi / n) + t));
    float cosValue = std::cos(actualPhase + phi) * p;
    float sinValue = std::sin(actualPhase + phi) * p;
    return std::make_pair(cosValue, sinValue);
}
