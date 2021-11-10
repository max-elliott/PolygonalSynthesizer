/*
  ==============================================================================

    AdsrComponent.h
    Created: 10 Nov 2021 1:10:58pm
    Author:  Max Elliott

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "CustomSliderComponent.h"

using APVTS = juce::AudioProcessorValueTreeState;
using SliderAttachment = APVTS::SliderAttachment;

//==============================================================================
/*
*/
class AdsrComponent  : public juce::Component
{
public:
    AdsrComponent(APVTS& apvts);
    ~AdsrComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    
    CustomSlider attackSlider;
    CustomSlider decaySlider;
    CustomSlider sustainSlider;
    CustomSlider releaseSlider;
    
    std::unique_ptr<SliderAttachment> attackSliderAttachment,
    decaySliderAttachment,
    sustainSliderAttachment,
    releaseSliderAttachment;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AdsrComponent)
};
