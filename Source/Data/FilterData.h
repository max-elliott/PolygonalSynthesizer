/*
  ==============================================================================

    FilterData.h
    Created: 11 Nov 2021 12:04:42pm
    Author:  Max Elliott

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class FilterData{
public:
    void prepareToPlay(juce::dsp::ProcessSpec& spec);
    void process(juce::AudioBuffer<float>& buffer );
    void updateParameters(const int filterType, const float cutoffFreq, const float resonance);
    void reset();
private:
    juce::dsp::StateVariableTPTFilter<float> filter;
    bool isPrepared{ false };
};
