/*
  ==============================================================================

    PolygonalOscData.h
    Created: 12 Nov 2021 2:15:14pm
    Author:  Max Elliott

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "CustomOscillator.h"

class PolygonalOscData : private juce::dsp::CustomOscillator<float>{
public:
    void prepareToPlay(juce::dsp::ProcessSpec& spec);
    void processNextAudioBlock(juce::dsp::AudioBlock<float> audioBlock);
    void setWaveFrequency(const int midiNoteNumber);
    void updatePhaseDelta();
    float updateCurrentPhase();
    void setGain(const float newGain);
    void setParameters(const float newPitch, const float newOrder, const float newTeeth, const float newPhase, const float newGain, const bool newMono);
    float getOscSample(const float x);
    std::pair<float, float> getOscSamplePair(const float x);
    
private:
//    juce::dsp::Oscillator<float> fmOsc{[](float x){return std::sin(x);}};
//    float fmMod{0.0f};
//    float fmDepth{0.0f};
    double currentNoteFrequency{0.0};
    juce::dsp::Gain<float> gain;
    float pitchAdjustment = 0.0f, order = 4.0f, teeth = 0.3f, phaseRotation = 0.0f, phaseDelta = 0.0f, currentPhase = 0.0f;
    bool isPrepared{ false };
};
