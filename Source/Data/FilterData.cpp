/*
  ==============================================================================

    FilterData.cpp
    Created: 11 Nov 2021 12:04:42pm
    Author:  Max Elliott

  ==============================================================================
*/

#include "FilterData.h"

void FilterData::prepareToPlay(juce::dsp::ProcessSpec& spec){
    reset();
    filter.prepare(spec);
    isPrepared = true;
}

void FilterData::process(juce::AudioBuffer<float>& buffer ){
    jassert(isPrepared);
    
    juce::dsp::AudioBlock<float> block {buffer};
    filter.process(juce::dsp::ProcessContextReplacing<float>(block));
}

void FilterData::updateParameters(const int filterType, const float cutoffFreq, const float resonance){
    
    switch(filterType){
        case 0:
            filter.setType(juce::dsp::StateVariableTPTFilterType::lowpass);
            break;
        case 1:
            filter.setType(juce::dsp::StateVariableTPTFilterType::bandpass);
            break;
        case 2:
            filter.setType(juce::dsp::StateVariableTPTFilterType::highpass);
            break;
    }
    
    filter.setCutoffFrequency(cutoffFreq);
    filter.setResonance(resonance);
}

void FilterData::reset(){
    filter.reset();
}
