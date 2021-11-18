/*
  ==============================================================================

    PolygonalOscData.h
    Created: 12 Nov 2021 2:15:14pm
    Author:  Max Elliott

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class PolygonalOscData : public juce::dsp::Oscillator<float>{
public:
    void prepareToPlay(juce::dsp::ProcessSpec& spec);
    void processNextAudioBlock(juce::dsp::AudioBlock<float> audioBlock);
    void setWaveFrequency(const int midiNoteNumber);
    void setGain(const float newGain);
    void setParameters(const float newOrder, const float newTeeth);
    float getOscSample(const float x);
    
private:
//    juce::dsp::Oscillator<float> fmOsc{[](float x){return std::sin(x);}};
//    float fmMod{0.0f};
//    float fmDepth{0.0f};
    double currentNoteFrequency{0.0};
    juce::dsp::Gain<float> gain;
    float order = 4.0f, teeth = 0.3f, phase = 0.0f;
    bool isPrepared{ false };
};
