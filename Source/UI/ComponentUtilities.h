/*
  ==============================================================================

    ComponentUtilities.h
    Created: 10 Nov 2021 2:59:33pm
    Author:  Max Elliott

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

static void logComponentBounds(const juce::Component& comp){
    juce::Logger::writeToLog("Component Start = (" + juce::String(comp.getX()) + ", " + juce::String(comp.getY()) + ")");
    juce::Logger::writeToLog("Component Width and Height = (" + juce::String(comp.getWidth()) + ", " + juce::String(comp.getHeight()) + ")");
}
