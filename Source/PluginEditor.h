/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

using APVTS = juce::AudioProcessorValueTreeState;
using SliderAttachment = APVTS::SliderAttachment;
using ComboBoxAttachment = APVTS::ComboBoxAttachment;

struct CustomSlider: juce::Slider{
    CustomSlider(): juce::Slider(juce::Slider::SliderStyle::LinearHorizontal,
                                       juce::Slider::TextEntryBoxPosition::NoTextBox){
        
    }
};

//==============================================================================
/**
*/
class PolygonalSynthesizerAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    PolygonalSynthesizerAudioProcessorEditor (PolygonalSynthesizerAudioProcessor&);
    ~PolygonalSynthesizerAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
    std::vector<juce::Component*> getComps();

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    PolygonalSynthesizerAudioProcessor& audioProcessor;
    
    CustomSlider attackSlider;
    CustomSlider decaySlider;
    CustomSlider sustainSlider;
    CustomSlider releaseSlider;
    
    juce::ComboBox waveformSelector;
    
    std::unique_ptr<SliderAttachment> attackSliderAttachment,
    decaySliderAttachment,
    sustainSliderAttachment,
    releaseSliderAttachment;
    std::unique_ptr<ComboBoxAttachment> waveformSelectorAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PolygonalSynthesizerAudioProcessorEditor)
};
