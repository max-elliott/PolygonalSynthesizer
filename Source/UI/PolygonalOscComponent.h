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
using ButtonAttachment = APVTS::ButtonAttachment;

//==============================================================================
/*
*/
class PolygonalOscComponent  : public juce::Component
{
public:
    PolygonalOscComponent(APVTS& apvts, juce::String pitchId, juce::String orderId, juce::String teethId, juce::String phaseId, juce::String gainId, juce::String monoId);
    ~PolygonalOscComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    CustomVerticalSlider pitchAdjustmentSlider;
    CustomVerticalSlider orderSlider;
    CustomVerticalSlider teethSlider;
    CustomVerticalSlider phaseSlider;
    CustomVerticalSlider gainSlider;
    juce::ToggleButton monoButton;
    
    std::unique_ptr<SliderAttachment> pitchAdjustmentSliderAttachment;
    std::unique_ptr<SliderAttachment> orderSliderAttachment;
    std::unique_ptr<SliderAttachment> teethSliderAttachment;
    std::unique_ptr<SliderAttachment> phaseSliderAttachment;
    std::unique_ptr<SliderAttachment> gainSliderAttachment;
    std::unique_ptr<ButtonAttachment> monoButtonAttachment;
    
    std::vector<juce::Component*> getComps();
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PolygonalOscComponent)
};
