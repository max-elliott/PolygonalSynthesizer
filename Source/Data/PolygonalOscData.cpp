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
    initialise([&](float x){return getOscSample(x);});
    
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

void PolygonalOscData::setParameters(const float newOrder, const float newTeeth){
    order = newOrder;
    teeth = newTeeth;
}

float PolygonalOscData::getOscSample(const float x){
    
    const float actualPhase = x + juce::MathConstants<float>::pi;
    const float pi = juce::MathConstants<float>::pi;
    const float twoPi = juce::MathConstants<float>::twoPi;
    const float n = order;
    const float t = teeth;
    const float phi = phase;
    const float xnOverTwoPi  = (actualPhase * n) / twoPi;
    
//    float p = std::cos(pi / n) / (std::cos(twoPi / n * (xnOverTwoPi - (long)xnOverTwoPi) - pi / n + t));
    float p = std::cos(pi / n) / (std::cos(twoPi / n * (fmod(xnOverTwoPi, 1)) - (pi / n) + t));
    return std::cos(actualPhase) * p;
}
