/*
  ==============================================================================

    PlaylistLogic.h
    Created: 6 Sep 2020 11:55:57am
    Author:  Garrison

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class PlaylistLogic 

{
public:
    
    PlaylistLogic();
    ~PlaylistLogic();
    /**recieves a URL and String from the deckGUI for adding the meta data to the 
    XML document that stores the playlist data.
    Builds the XML document and add new entries.*/
    void addToPlaylist(juce::URL audioURL, juce::String time);
    /**recieves an int representing row number, an int representing column id and string
    representing a specific track.
    outputs a string to the playlist component for display, loads the playlist into the box model*/
    juce::String loadPlaylist(int num, int columnID, juce::String string);
    

private:
    std::string count;
    std::string trackNum;

};