/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "UI/AdsrComponent.h"

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
    
    std::vector<juce::Component*> getComps();

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    PolygonalSynthesizerAudioProcessor& audioProcessor;
    
    AdsrComponent adsr;
    
    juce::ComboBox waveformSelector;
    std::unique_ptr<ComboBoxAttachment> waveformSelectorAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PolygonalSynthesizerAudioProcessorEditor)
};
