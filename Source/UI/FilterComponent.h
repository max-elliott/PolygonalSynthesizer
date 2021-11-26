/*
  ==============================================================================

    FilterComponent.h
    Created: 11 Nov 2021 12:39:43pm
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
class FilterComponent  : public juce::Component
{
public:
    FilterComponent(APVTS& apvts, juce::String type, juce::String frequency, juce::String resonance);
    ~FilterComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    
    juce::ComboBox typeSelector;
    CustomRotarySlider freqSlider;
    CustomRotarySlider resSlider;
    
    std::unique_ptr<ComboBoxAttachment> typeSelectorAttachment;
    std::unique_ptr<SliderAttachment> freqSliderAttachment;
    std::unique_ptr<SliderAttachment> resSliderAttachment;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterComponent)
};
