/*
  ==============================================================================

    PolygonalOscComponent.cpp
    Created: 12 Nov 2021 2:15:26pm
    Author:  Max Elliott

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PolygonalOscComponent.h"

//==============================================================================
PolygonalOscComponent::PolygonalOscComponent(APVTS& apvts, juce::String gainId)
:
gainSliderAttachment(std::make_unique<SliderAttachment>(apvts, gainId, gainSlider))
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    addAndMakeVisible(gainSlider);
}

PolygonalOscComponent::~PolygonalOscComponent()
{
}

void PolygonalOscComponent::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (juce::Colours::black);
}

void PolygonalOscComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    auto bounds = getLocalBounds();
    
    gainSlider.setBounds(bounds);

}
