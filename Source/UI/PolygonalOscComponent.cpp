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
PolygonalOscComponent::PolygonalOscComponent(APVTS& apvts, juce::String pitchId, juce::String orderId, juce::String teethId, juce::String phaseId, juce::String gainId, juce::String monoId)
:
pitchAdjustmentSliderAttachment(std::make_unique<SliderAttachment>(apvts, pitchId, pitchAdjustmentSlider)),
orderSliderAttachment(std::make_unique<SliderAttachment>(apvts, orderId, orderSlider)),
teethSliderAttachment(std::make_unique<SliderAttachment>(apvts, teethId, teethSlider)),
phaseSliderAttachment(std::make_unique<SliderAttachment>(apvts, phaseId, phaseSlider)),
gainSliderAttachment(std::make_unique<SliderAttachment>(apvts, gainId, gainSlider)),
monoButtonAttachment(std::make_unique<ButtonAttachment>(apvts, monoId, monoButton))
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    for(auto c : getComps()){
        addAndMakeVisible(c);
    }
//    addAndMakeVisible(gainSlider);
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
    int numSliders = 5;
    auto widthEach = bounds.proportionOfWidth(1.0f / float(numSliders));
    
    auto pitchAdjustmentSliderBounds = bounds.removeFromLeft(widthEach);
    auto monoButtonBounds = pitchAdjustmentSliderBounds.removeFromBottom(pitchAdjustmentSliderBounds.proportionOfHeight(0.25f));
    auto orderSliderBounds = bounds.removeFromLeft(widthEach);
    auto teethSliderBounds = bounds.removeFromLeft(widthEach);
    auto phaseSliderBounds = bounds.removeFromLeft(widthEach);
    auto gainSliderBounds = bounds.removeFromLeft(widthEach);
    
    pitchAdjustmentSlider.setBounds(pitchAdjustmentSliderBounds);
    orderSlider.setBounds(orderSliderBounds);
    teethSlider.setBounds(teethSliderBounds);
    phaseSlider.setBounds(phaseSliderBounds);
    gainSlider.setBounds(gainSliderBounds);
    monoButton.setBounds(monoButtonBounds);

}

std::vector<juce::Component*> PolygonalOscComponent::getComps(){
    return {
        &pitchAdjustmentSlider,
        &orderSlider,
        &teethSlider,
        &phaseSlider,
        &gainSlider,
        &monoButton
    };
}
