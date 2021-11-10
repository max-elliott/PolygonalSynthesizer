/*
  ==============================================================================

    CustomSliderComponent.h
    Created: 10 Nov 2021 1:15:17pm
    Author:  Max Elliott

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
//class CustomSliderComponent  : public juce::Component
//{
//public:
//    CustomSliderComponent();
//    ~CustomSliderComponent() override;
//
//    void paint (juce::Graphics&) override;
//    void resized() override;
//
//private:
//    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CustomSliderComponent)
//};

struct CustomSlider: juce::Slider{
    CustomSlider(): juce::Slider(juce::Slider::SliderStyle::LinearHorizontal,
                                 juce::Slider::TextEntryBoxPosition::NoTextBox){
        
    }
};
