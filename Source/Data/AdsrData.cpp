/*
  ==============================================================================

    AdsrData.cpp
    Created: 10 Nov 2021 1:12:26pm
    Author:  Max Elliott

  ==============================================================================
*/

#include "AdsrData.h"

void AdsrData::updateParameters(const float a, const float d, const float s, const float r){
    adsrParams.attack = a;
    adsrParams.decay = d;
    adsrParams.sustain = s;
    adsrParams.release = r;
    
    setParameters(adsrParams);
}
