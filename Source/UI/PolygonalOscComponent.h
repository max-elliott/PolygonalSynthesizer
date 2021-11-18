/*
  ==============================================================================

    PolygonalOscComponent.h
    Created: 12 Nov 2021 2:15:26pm
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
class PolygonalOscComponent  : public juce::Component
{
public:
    PolygonalOscComponent(APVTS& apvts, juce::String gainId);
    ~PolygonalOscComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    CustomRotarySlider gainSlider;
    
    std::unique_ptr<SliderAttachment> gainSliderAttachment;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PolygonalOscComponent)
};
