/*
  ==============================================================================

    FilterComponent.cpp
    Created: 11 Nov 2021 12:39:43pm
    Author:  Max Elliott

  ==============================================================================
*/

#include <JuceHeader.h>
#include "FilterComponent.h"

//==============================================================================
FilterComponent::FilterComponent(APVTS& apvts, juce::String typeId, juce::String frequencyId, juce::String resonanceId)
:
typeSelectorAttachment(std::make_unique<ComboBoxAttachment>(apvts, typeId, typeSelector)),
freqSliderAttachment(std::make_unique<SliderAttachment>(apvts, frequencyId, freqSlider)),
resSliderAttachment(std::make_unique<SliderAttachment>(apvts, resonanceId, resSlider))
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    juce::StringArray typeChoices{"LowPass", "BandPass", "HighPass"};
    typeSelector.addItemList(typeChoices, 1);
    
    addAndMakeVisible(typeSelector);
    addAndMakeVisible(freqSlider);
    addAndMakeVisible(resSlider);
}

FilterComponent::~FilterComponent()
{
}

void FilterComponent::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (juce::Colours::black);
}

void FilterComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    auto bounds = getLocalBounds();
    auto typeBounds = bounds.removeFromTop(bounds.getHeight() * 0.35);
    auto freqBounds = bounds.removeFromLeft(bounds.getWidth() * 0.5);
    auto resBounds = bounds;
    
    typeSelector.setBounds(typeBounds);
    freqSlider.setBounds(freqBounds);
    resSlider.setBounds(resBounds);

}
