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

class SynthVoice: public juce::SynthesiserVoice{
public:
    bool canPlaySound (juce::SynthesiserSound *) override;
    
    void startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition) override;
    
    void stopNote (float velocity, bool allowTailOff) override;
    
    void pitchWheelMoved (int newPitchWheelValue) override;
    
    void controllerMoved (int controllerNumber, int newControllerValue) override;
    
    void prepareToPlay(double sampleRate, int samplesPerBlock, int numOutputChannels);
    
    void renderNextBlock (juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples) override;
    
    void update(const float a, const float d, const float s, const float r);
    
    AdsrData& getADSR(){return adsr;}
    OscData& getOscillator(){return osc;};
    
private:
    AdsrData adsr;
    OscData osc;
//    juce::dsp::Oscillator<float> osc {[](float x){return std::sin(x);}};
    juce::dsp::Gain<float> gain;
    bool isPrepared{ false };
    
    juce::AudioBuffer<float> synthBuffer;
};
