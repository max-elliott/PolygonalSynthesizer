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
OscComponent::OscComponent(APVTS& apvts, juce::String WaveformSelectionId)
:
waveformSelectorAttachment(std::make_unique<ComboBoxAttachment>(apvts, WaveformSelectionId, waveformSelector))
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    juce::StringArray choices {"Sine", "Saw", "Square"};
    waveformSelector.addItemList(choices, 1);
    
    addAndMakeVisible(waveformSelector);
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
    waveformSelector.setBounds(getLocalBounds());

}
