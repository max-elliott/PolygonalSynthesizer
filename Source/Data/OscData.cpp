/*
  ==============================================================================

    OscData.cpp
    Created: 10 Nov 2021 2:25:42pm
    Author:  Max Elliott

  ==============================================================================
*/

#include "OscData.h"

void OscData::prepareToPlay(juce::dsp::ProcessSpec& spec){
    fmOsc.prepare(spec);
    prepare(spec);
}

void OscData::setWaveType(const int choice){
    
    switch(choice){
        case(0):
            initialise([](float x){ return std::sin(x);});
            break;
        case(1):
            initialise([](float x){ return x / juce::MathConstants<float>::pi;});
            break;
        case(2):
            initialise([](float x){ return x < 0 ? -1.0f : 1.0f;});
            break;
        default:
            jassertfalse;
            break;
    }
}

void OscData::processNextAudioBlock(juce::dsp::AudioBlock<float> audioBlock){
    
    for(int channelIdx=0; channelIdx < audioBlock.getNumChannels(); channelIdx++){
        for (int sampleIdx=0; sampleIdx < audioBlock.getNumSamples(); sampleIdx++){
            fmMod = fmOsc.processSample(audioBlock.getSample(channelIdx, sampleIdx)) * currentNoteFrequency * fmDepth;
        }
    }
    process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
}

void OscData::setWaveFrequency(const int midiNoteNumber){
    setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber) + fmMod);
    currentNoteFrequency = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
}

void OscData::setFmParams(const float depth, const float freq){
    fmOsc.setFrequency(freq);
    fmDepth = depth;
    setFrequency(currentNoteFrequency + fmMod);
}
