/*
  ==============================================================================

    SynthVoice.h
    Created: 8 Nov 2021 10:04:51pm
    Author:  Max Elliott

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SynthSound.h"
#include "Data/AdsrData.h"
#include "Data/OscData.h"
#include "Data/FilterData.h"
#include "Data/PolygonalOscData.h"

class SynthVoice: public juce::SynthesiserVoice{
public:
    bool canPlaySound (juce::SynthesiserSound *) override;
    
    void startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition) override;
    
    void stopNote (float velocity, bool allowTailOff) override;
    
    void pitchWheelMoved (int newPitchWheelValue) override;
    
    void controllerMoved (int controllerNumber, int newControllerValue) override;
    
    void prepareToPlay(double sampleRate, int samplesPerBlock, int numOutputChannels);
    
    void renderNextBlock (juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples) override;
    
    void updateADSR(const float a, const float d, const float s, const float r);
    void updateFilter(const int type, const float frequency, const float resonance);
    void updateADSRMod(const float a, const float d, const float s, const float r);
    void setOscillatorParameters(const float newPitch, const float newOrder, const float newTeeth, const float newPhase, const float newGain);
    
    AdsrData& getADSR(){return adsr;}
    AdsrData& getADSRMod(){return adsrMod;}
    PolygonalOscData& getOscillator(){return osc;};
    
private:
    AdsrData adsr;
    PolygonalOscData osc;
    FilterData filter;
    
    AdsrData adsrMod;
    
    bool isPrepared{ false };
    
    juce::AudioBuffer<float> synthBuffer;
    float currentVelocity;
};
