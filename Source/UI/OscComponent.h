/*
  ==============================================================================

    OscComponent.h
    Created: 10 Nov 2021 2:51:38pm
    Author:  Max Elliott

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

using APVTS = juce::AudioProcessorValueTreeState;
using ComboBoxAttachment = APVTS::ComboBoxAttachment;

//==============================================================================
/*
*/
class OscComponent  : public juce::Component
{
public:
    OscComponent(APVTS& apvts);
    ~OscComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::ComboBox waveformSelector;
    std::unique_ptr<ComboBoxAttachment> waveformSelectorAttachment;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscComponent)
};
