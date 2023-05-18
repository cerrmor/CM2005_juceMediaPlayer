/*
  ==============================================================================

    RecordComponent.h
    Created: 13 Sep 2020 12:11:16pm
    Author:  Garrison

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"

//==============================================================================
/*
*/
class RecordComponent  : public juce::Component
{
public:
    /**RecordComponent constructor recieves a pointer to the audio player*/
    RecordComponent(DJAudioPlayer* player);
    ~RecordComponent() override;
    /**The paint() method gets called when a region of a component needs redrawing,
    either because the component's repaint() method has been called, or because something
    has happened on the screen that means a section of a window needs to be redrawn.*/
    void paint (juce::Graphics&) override;
    /**Called when this component's size has been changed.*/
    void resized() override;
    //called everytime the position of the line has changed
    void updateRecordComponent();
    /**Called when the mouse is moved while a button is held down.
    When a mouse button is pressed inside a component, that component receives mouseDrag 
    callbacks each time the mouse moves, even if the mouse strays outside the component's bounds.*/
    void mouseDrag(const juce::MouseEvent& event) override;
    
private:
    DJAudioPlayer* player;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RecordComponent)
};
