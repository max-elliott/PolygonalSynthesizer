/*
  ==============================================================================

    OscData.h
    Created: 10 Nov 2021 2:25:42pm
    Author:  Max Elliott

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class OscData : public juce::dsp::Oscillator<float>{
public:
    void prepareToPlay(juce::dsp::ProcessSpec& spec);
    void setWaveType(const int choice);
    void processNextAudioBlock(juce::dsp::AudioBlock<float> audioBlock);
    void setWaveFrequency(const int midiNoteNumber);
    void setFmParams(const float depth, const float freq);
    
private:
    juce::dsp::Oscillator<float> fmOsc{[](float x){return std::sin(x);}};
    float fmMod{0.0f};
    float fmDepth{0.0f};
    double currentNoteFrequency{0.0};
};
