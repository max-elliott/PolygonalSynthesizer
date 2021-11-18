/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "UI/ComponentUtilities.h"

//==============================================================================
PolygonalSynthesizerAudioProcessorEditor::PolygonalSynthesizerAudioProcessorEditor (PolygonalSynthesizerAudioProcessor& p)
    : AudioProcessorEditor (&p),
audioProcessor (p),
adsrVolume(audioProcessor.apvts, "Envelope Attack", "Envelope Decay", "Envelope Sustain", "Envelope Release"),
adsrMod(audioProcessor.apvts, "Mod Envelope Attack", "Mod Envelope Decay", "Mod Envelope Sustain", "Mod Envelope Release"),
//osc1(audioProcessor.apvts, "OSC1 Waveform", "OSC1 FM Freq", "OSC1 FM Depth"),
osc1(audioProcessor.apvts, "OSC1 Pitch", "OSC1 Order", "OSC1 Teeth", "OSC1 Phase Rotation", "OSC1 Gain"),
filter(audioProcessor.apvts, "Filter Type", "Filter Freq", "Filter Resonance")
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    for(auto c : getComps()){
        addAndMakeVisible(c);
    }
    
    setSize (800, 600);
}

PolygonalSynthesizerAudioProcessorEditor::~PolygonalSynthesizerAudioProcessorEditor()
{
}

//==============================================================================
void PolygonalSynthesizerAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
//    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    g.fillAll (juce::Colours::black);
}

void PolygonalSynthesizerAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    auto bounds = getLocalBounds();
    juce::BorderSize<int> border(bounds.proportionOfHeight(0.1), bounds.proportionOfWidth(0.1), bounds.proportionOfHeight(0.1), bounds.proportionOfWidth(0.1));
    
    border.subtractFrom(bounds);
    auto mainTopBar = bounds.removeFromTop(bounds.proportionOfHeight(0.1f));
    auto envelopeArea = bounds.removeFromTop(bounds.proportionOfHeight(0.5f));
    auto envelopeVolumeArea = envelopeArea.removeFromLeft(envelopeArea.proportionOfWidth(0.5f));
    auto envelopeModArea = envelopeArea;
    auto oscArea = bounds.removeFromLeft(bounds.proportionOfWidth(0.5f));
    auto filterArea = bounds;
    
    // Set bounds of Adsr
    adsrVolume.setBounds(envelopeVolumeArea);
    adsrMod.setBounds(envelopeModArea);
    osc1.setBounds(oscArea);
    filter.setBounds(filterArea);
    
    logComponentBounds(adsrMod);
    if (adsrMod.isVisible()){
        juce::Logger::writeToLog(juce::String("adsrMod is visible"));
    }
    
}

std::vector<juce::Component*> PolygonalSynthesizerAudioProcessorEditor::getComps(){
    return {
        &adsrVolume,
        &adsrMod,
        &osc1,
        &filter
    };
}
