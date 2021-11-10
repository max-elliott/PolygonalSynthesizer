/*
  ==============================================================================

    OscComponent.cpp
    Created: 10 Nov 2021 2:51:38pm
    Author:  Max Elliott

  ==============================================================================
*/

#include <JuceHeader.h>
#include "OscComponent.h"
#include "ComponentUtilities.h"

//==============================================================================
OscComponent::OscComponent(APVTS& apvts, juce::String WaveformSelectionId, juce::String fmFreqId, juce::String fmdepthId)
:
fmFreqSlider(juce::Slider::SliderStyle::RotaryVerticalDrag,
             juce::Slider::TextEntryBoxPosition::TextBoxRight),
fmDepthSlider(juce::Slider::SliderStyle::RotaryVerticalDrag,
              juce::Slider::TextEntryBoxPosition::TextBoxRight),
waveformSelectorAttachment(std::make_unique<ComboBoxAttachment>(apvts, WaveformSelectionId, waveformSelector)),
fmFreqAttachment(std::make_unique<SliderAttachment>(apvts, fmFreqId, fmFreqSlider)),
fmDepthAttachment(std::make_unique<SliderAttachment>(apvts, fmdepthId, fmDepthSlider))
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    juce::StringArray choices {"Sine", "Saw", "Square"};
    waveformSelector.addItemList(choices, 1);
    
    addAndMakeVisible(waveformSelector);
    addAndMakeVisible(fmFreqSlider);
    addAndMakeVisible(fmDepthSlider);
}

OscComponent::~OscComponent()
{
}

void OscComponent::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (juce::Colours::black);
}

void OscComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    auto bounds = getLocalBounds();
    auto waveformSelectorBounds = bounds.removeFromLeft(bounds.getWidth() * 0.5);
    
    waveformSelector.setBounds(waveformSelectorBounds);
    fmFreqSlider.setBounds(bounds.removeFromTop(bounds.getHeight() * 0.5));
    fmDepthSlider.setBounds(bounds);

}
