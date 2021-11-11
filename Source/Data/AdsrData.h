/*
  ==============================================================================

    AdsrData.h
    Created: 10 Nov 2021 1:12:26pm
    Author:  Max Elliott

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class AdsrData : public juce::ADSR{

public:
    
    void updateParameters(const float a, const float d, const float s, const float r);
    
private:
    juce::ADSR::Parameters adsrParams;

};
