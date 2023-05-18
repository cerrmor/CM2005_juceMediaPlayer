/*
  ==============================================================================

    WaveformDisplay.h
    Created: 5 Aug 2020 9:32:57pm
    Author:  Garrison

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class WaveformDisplay  : public juce::Component,
                         public juce::ChangeListener
{
public:
    /**waveform display constructor recieves the shared audioformat manager and audio
    thumbnail cache address for audio processing*/
    WaveformDisplay(juce::AudioFormatManager& formatManagerToUse,
                    juce::AudioThumbnailCache& cacheToUse);
    ~WaveformDisplay() override;
    /**The paint() method gets called when a region of a component needs redrawing,
    either because the component's repaint() method has been called, or because something
    has happened on the screen that means a section of a window needs to be redrawn.*/
    void paint (juce::Graphics&) override;
    /**Called when this component's size has been changed.*/
    void resized() override;
    /**called whenever there is a change, calls repaint() to update the playhead posistion in the display
    returns void*/
    void changeListenerCallback(juce::ChangeBroadcaster* source) override;
    /**recieves a URL and loads the file data fro displaying the sine wave*/
    void loadURL(juce::URL audioURL);

    /**set the relative position of the playhead on the sine wave image*/
    void setPosistionRelative(double pos);

private:
    bool fileLoaded;
    double position;
    juce::AudioThumbnail audioThumb;

    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveformDisplay)
};
