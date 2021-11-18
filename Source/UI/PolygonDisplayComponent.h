/*
  ==============================================================================

    PolygonDisplayComponent.h
    Created: 18 Nov 2021 4:22:06pm
    Author:  Max Elliott

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../PluginProcessor.h"

//==============================================================================
/*
*/
class PolygonDisplayComponent  : public juce::Component,
juce::AudioProcessorParameter::Listener, juce::Timer
{
public:
    PolygonDisplayComponent(PolygonalSynthesizerAudioProcessor& audioProcessor, juce::String pitchId, juce::String orderId, juce::String teethId, juce::String phaseId, juce::String gainId);
    ~PolygonDisplayComponent() override;
    
    void parameterValueChanged(int parameterIndex, float newValue) override;
    void parameterGestureChanged(int parameterIndex, bool gestureIsStarting) override {}
    
    void timerCallback() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    std::vector<std::pair<float, float>> generateWaveformPoints();

private:
    const int numSamplesPerRotation = 250;
    juce::Atomic<bool> parametersChanged{false};
    juce::String orderId, teethId;
    float order, teeth;
    PolygonalSynthesizerAudioProcessor& audioProcessor;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PolygonDisplayComponent)
};
