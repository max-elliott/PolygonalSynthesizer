/*
  ==============================================================================

    AdsrComponent.cpp
    Created: 10 Nov 2021 1:10:58pm
    Author:  Max Elliott

  ==============================================================================
*/

#include <JuceHeader.h>
#include "AdsrComponent.h"
#include "ComponentUtilities.h"

//==============================================================================
AdsrComponent::AdsrComponent(juce::AudioProcessorValueTreeState& apvts)
:
attackSliderAttachment(std::make_unique<SliderAttachment>(apvts, "Envelope Attack", attackSlider)),
decaySliderAttachment(std::make_unique<SliderAttachment>(apvts, "Envelope Decay", decaySlider)),
sustainSliderAttachment(std::make_unique<SliderAttachment>(apvts, "Envelope Sustain", sustainSlider)),
releaseSliderAttachment(std::make_unique<SliderAttachment>(apvts, "Envelope Release", releaseSlider))
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    addAndMakeVisible(attackSlider);
    addAndMakeVisible(decaySlider);
    addAndMakeVisible(sustainSlider);
    addAndMakeVisible(releaseSlider);
}

AdsrComponent::~AdsrComponent()
{
}

void AdsrComponent::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (juce::Colours::black);   // clear the background

}

void AdsrComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    auto bounds = getBounds();
    int envelopeHeight = bounds.getHeight();
    
    attackSlider.setBounds(bounds.removeFromTop(envelopeHeight * 0.25));
    decaySlider.setBounds(bounds.removeFromTop(envelopeHeight * 0.25));
    sustainSlider.setBounds(bounds.removeFromTop(envelopeHeight * 0.25));
    releaseSlider.setBounds(bounds.removeFromTop(envelopeHeight * 0.25));
}
