/*
  ==============================================================================

    PolygonDisplayComponent.cpp
    Created: 18 Nov 2021 4:22:06pm
    Author:  Max Elliott

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PolygonDisplayComponent.h"

//==============================================================================
PolygonDisplayComponent::PolygonDisplayComponent(PolygonalSynthesizerAudioProcessor& audioProcessor, juce::String pitchId, juce::String orderId, juce::String teethId, juce::String phaseId, juce::String gainId)
:
orderId(orderId),
teethId(teethId),
audioProcessor(audioProcessor)
{
    const auto& params = audioProcessor.getParameters();
    for (auto param: params){
        param->addListener(this);
    }
    
    order = audioProcessor.apvts.getRawParameterValue(orderId)->load();
    teeth = audioProcessor.apvts.getRawParameterValue(teethId)->load();
    
    startTimerHz(60);

}

PolygonDisplayComponent::~PolygonDisplayComponent()
{
    const auto& params = audioProcessor.getParameters();
    for (auto param: params){
        param->removeListener(this);
    }
}

void PolygonDisplayComponent::parameterValueChanged(int parameterIndex, float newValue){
    parametersChanged.set(true);
}

void PolygonDisplayComponent::timerCallback(){
    if(parametersChanged.compareAndSetBool(false, true)){
        order = audioProcessor.apvts.getRawParameterValue(orderId)->load();
        teeth = audioProcessor.apvts.getRawParameterValue(teethId)->load();
        
        
        repaint();
    }
}

void PolygonDisplayComponent::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */
    using namespace juce;
    
    g.fillAll (juce::Colours::black);
    
    auto bounds = getLocalBounds();
    auto maxDimension = std::min(bounds.getHeight(), bounds.getWidth());
    bounds = bounds.removeFromTop(maxDimension).removeFromLeft(maxDimension);
    
    const float border1Prop = 0.05f;
    juce::BorderSize<int> border(bounds.proportionOfHeight(border1Prop), bounds.proportionOfWidth(border1Prop), bounds.proportionOfHeight(border1Prop), bounds.proportionOfWidth(border1Prop));
    border.subtractFrom(bounds);
    
    g.setColour(Colours::white);
    g.fillRect(bounds);
    
    const float border2Prop = 0.05f;
    juce::BorderSize<int> border2(bounds.proportionOfHeight(border2Prop), bounds.proportionOfWidth(border2Prop), bounds.proportionOfHeight(border2Prop), bounds.proportionOfWidth(border2Prop));
    border2.subtractFrom(bounds);
    
    g.setColour(Colours::black);
    g.fillRect(bounds);
    
    const float drawAreaBorderProp = 0.1f;
    juce::BorderSize<int> borderDrawArea(bounds.proportionOfHeight(drawAreaBorderProp), bounds.proportionOfWidth(drawAreaBorderProp), bounds.proportionOfHeight(drawAreaBorderProp), bounds.proportionOfWidth(drawAreaBorderProp));
    borderDrawArea.subtractFrom(bounds);
    
//    g.setColour(Colours::black);
//    g.fillRect(bounds);
    
    std::vector<std::pair<float, float>> waveformPoints = generateWaveformPoints();
    
    const Point<int> displayCentreX = bounds.getCentre();
    const int displayRadius = bounds.getWidth() * 0.5;
    
    const double outputMinX = bounds.getX();
    const double outputMaxX = bounds.getRight();
    const double outputMinY = bounds.getY();
    const double outputMaxY = bounds.getBottom();
    const double inputMin = -1.0;
    const double inputMax = 1.0;
    auto mapX = [outputMinX, outputMaxX, inputMin, inputMax](double input){
        return jmap(input, inputMin, inputMax, outputMinX, outputMaxX);
    };
    auto mapY = [outputMinY, outputMaxY, inputMin, inputMax](double input){
        return jmap(input, inputMin, inputMax, outputMinY, outputMaxY);
    };
    
    Path polygonPath;
    
    polygonPath.startNewSubPath(mapX(waveformPoints[0].first), mapY(waveformPoints[0].second));
    
    for (int p=1; p < waveformPoints.size(); p++){
        polygonPath.lineTo(mapX(waveformPoints[p].first), mapY(waveformPoints[p].second));
    }
    
    g.setColour(Colours::white);
    g.strokePath(polygonPath, PathStrokeType(2.f));
    
}

void PolygonDisplayComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

std::vector<std::pair<float, float>> PolygonDisplayComponent::generateWaveformPoints(){
    
    std::vector<std::pair<float, float>> output;
    
    for(int i=0; i < numSamplesPerRotation * rotationsDrawn; i++){
        
        const float actualPhase = float(i) / numSamplesPerRotation * juce::MathConstants<float>::twoPi;
        const float pi = juce::MathConstants<float>::pi;
        const float twoPi = juce::MathConstants<float>::twoPi;
        const float n = order;
        const float t = teeth;
        const float phi = 0;
        const float xnOverTwoPi  = (actualPhase * n) / twoPi;
        
        //    float p = std::cos(pi / n) / (std::cos(twoPi / n * (xnOverTwoPi - (long)xnOverTwoPi) - pi / n + t));
        float p = std::cos(pi / n) / (std::cos(twoPi / n * (fmod(xnOverTwoPi, 1)) - (pi / n) + t));
        float cosValue = std::cos(actualPhase + phi) * p;
        float sinValue = std::sin(actualPhase + phi) * p;
        
        output.push_back(std::make_pair(cosValue, sinValue));
    }
//    std::cout << output.size() << std::endl;
    return output;
}
