/*
  ==============================================================================

    OscComponent.h
    Created: 10 Nov 2021 2:51:38pm
    Author:  Max Elliott

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "CustomSliderComponent.h"

using APVTS = juce::AudioProcessorValueTreeState;
using ComboBoxAttachment = APVTS::ComboBoxAttachment;
using SliderAttachment = APVTS::SliderAttachment;

//==============================================================================
/*
*/
class OscComponent  : public juce::Component
{
public:
    OscComponent(APVTS& apvts, juce::String WaveformSelectionId, juce::String fmFreqId, juce::String fmdepthId);
    ~OscComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::ComboBox waveformSelector;
    juce::Slider fmFreqSlider;
    juce::Slider fmDepthSlider;
    
    std::unique_ptr<ComboBoxAttachment> waveformSelectorAttachment;
    std::unique_ptr<SliderAttachment> fmFreqAttachment;
    std::unique_ptr<SliderAttachment> fmDepthAttachment;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscComponent)
};
