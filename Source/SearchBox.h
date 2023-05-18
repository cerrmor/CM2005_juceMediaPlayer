/*
  ==============================================================================

    SearchBox.h
    Created: 7 Sep 2020 3:25:31pm
    Author:  Garrison

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>


//==============================================================================
/*
*/
class SearchBox  : public juce::Component
{
public:
    SearchBox();

    ~SearchBox() override;
    /**The paint() method gets called when a region of a component needs redrawing,
    either because the component's repaint() method has been called, or because something
    has happened on the screen that means a section of a window needs to be redrawn.*/
    void paint (juce::Graphics&) override;
    /**Called when this component's size has been changed.*/
    void resized() override;
    /**takes a string input used for searching and outputs a string if the item is found.
    if the item is not found outputs an empty string.*/
    juce::String linearSearch(juce::String item);
    
private:
    /**tokenises items in the list based off "_" and "."*/
    void tokeniser(juce::String item);
    /**stores the tokens for comparison*/
    juce::StringArray token;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SearchBox)
};
