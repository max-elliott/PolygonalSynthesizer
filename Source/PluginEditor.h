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

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    PolygonalSynthesizerAudioProcessor& audioProcessor;
    
    juce::Slider attackSlider;
    juce::Slider decaySlider;
    juce::Slider sustainSlider;
    juce::Slider releaseSlider;
    
    juce::ComboBox waveformSelector;
    
    std::unique_ptr<SliderAttachment> attackSliderAttachment,
    decaySliderAttachment,
    sustainSliderAttachment,
    releaseSliderAttachment;
    std::unique_ptr<ComboBoxAttachment> waveformSelectorAttachment;
    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PolygonalSynthesizerAudioProcessorEditor)
};
