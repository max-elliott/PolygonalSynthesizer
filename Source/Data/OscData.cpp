/*
  ==============================================================================

    OscData.cpp
    Created: 10 Nov 2021 2:25:42pm
    Author:  Max Elliott

  ==============================================================================
*/

#include "OscData.h"

void OscData::setWaveType(const int choice){
    
    switch(choice){
        case(0):
            initialise([](float x){ return std::sin(x);});
            break;
        case(1):
            initialise([](float x){ return x / juce::MathConstants<float>::pi;});
            break;
        case(2):
            initialise([](float x){ return x < 0 ? -1.0f : 1.0f;});
            break;
        default:
            jassertfalse;
            break;
    }
}
