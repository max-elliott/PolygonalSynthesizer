/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
PolygonalSynthesizerAudioProcessorEditor::PolygonalSynthesizerAudioProcessorEditor (PolygonalSynthesizerAudioProcessor& p)
    : AudioProcessorEditor (&p),
audioProcessor (p),
//attackSlider(*audioProcessor.apvts.getParameter("Envelope Attack"), "s")),
//decaySlider(*audioProcessor.apvts.getParameter("Envelope Decay"), "s")),
//sustainSlider(*audioProcessor.apvts.getParameter("Envelope Sustain"), "")),
//releaseSlider(*audioProcessor.apvts.getParameter("Envelope Release"), "s")),
//waveformSelector(*audioProcessor.apvts.getParameter("Waveform"), "")),
attackSliderAttachment(std::make_unique<SliderAttachment>(audioProcessor.apvts, "Envelope Attack", attackSlider)),
decaySliderAttachment(std::make_unique<SliderAttachment>(audioProcessor.apvts, "Envelope Decay", decaySlider)),
sustainSliderAttachment(std::make_unique<SliderAttachment>(audioProcessor.apvts, "Envelope Sustain", sustainSlider)),
releaseSliderAttachment(std::make_unique<SliderAttachment>(audioProcessor.apvts, "Envelope Release", releaseSlider)),
waveformSelectorAttachment(std::make_unique<ComboBoxAttachment>(audioProcessor.apvts, "Waveform", waveformSelector))
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    for(auto c : getComps()){
        addAndMakeVisible(c);
    }
    
    setSize (600, 400);
}

PolygonalSynthesizerAudioProcessorEditor::~PolygonalSynthesizerAudioProcessorEditor()
{
}

//==============================================================================
void PolygonalSynthesizerAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    g.fillAll (juce::Colours::black);

//    g.setColour (juce::Colours::white);
//    g.setFont (15.0f);
//    g.drawFittedText ("Hello World!jjj", getLocalBounds(), juce::Justification::centred, 1);
}

void PolygonalSynthesizerAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    auto bounds = getLocalBounds();
    
    auto envelopeArea = bounds.removeFromTop(bounds.getHeight() * 0.8);
    int envelopeHeight = envelopeArea.getHeight();
    
    attackSlider.setBounds(envelopeArea.removeFromTop(envelopeHeight * 0.25));
    decaySlider.setBounds(envelopeArea.removeFromTop(envelopeHeight * 0.25));
    sustainSlider.setBounds(envelopeArea.removeFromTop(envelopeHeight * 0.25));
    releaseSlider.setBounds(envelopeArea.removeFromTop(envelopeHeight * 0.25));
    
    waveformSelector.setBounds(bounds);
    
//    auto responseArea = bounds.removeFromTop(bounds.getHeight() * 0.33);
//
//    auto lowCutArea = bounds.removeFromLeft(bounds.getWidth() * 0.33);
//    auto highCutArea = bounds.removeFromRight(bounds.getWidth() * 0.5);
//
//    lowCutFreqSlider.setBounds(lowCutArea.removeFromTop(lowCutArea.getHeight() * 0.5));
//    lowCutSlopeSlider.setBounds(lowCutArea);
//    highCutFreqSlider.setBounds(highCutArea.removeFromTop(highCutArea.getHeight() * 0.5));
//    highCutSlopeSlider.setBounds(highCutArea);
//
//    peakFreqSlider.setBounds(bounds.removeFromTop(bounds.getHeight() * 0.33));
//    peakGainSlider.setBounds(bounds.removeFromTop(bounds.getHeight() * 0.5));
//    peakQualitySlider.setBounds(bounds);
}

std::vector<juce::Component*> PolygonalSynthesizerAudioProcessorEditor::getComps(){
    return {
        &attackSlider,
        &decaySlider,
        &sustainSlider,
        &releaseSlider,
        &waveformSelector};
}
