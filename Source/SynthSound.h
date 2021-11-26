/*
  ==============================================================================

    SynthSound.h
    Created: 8 Nov 2021 10:06:27pm
    Author:  Max Elliott

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class SynthSound: public juce::SynthesiserSound{
public:
    bool appliesToNote (int midiNoteNumber) override {return true;};
    
    bool appliesToChannel (int midiChannel) override {return true;};
};
