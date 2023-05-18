/*
  ==============================================================================

    DeckGUI.h
    Created: 30 Jul 2020 9:20:38pm
    Author:  Garrison

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"
#include "WaveformDisplay.h"
#include "PlaylistLogic.h"
#include "RecordComponent.h"
//==============================================================================
/*
*/
class DeckGUI  : public juce::Component,
                 public juce::Button::Listener,
                 public juce::Slider::Listener,
                 public juce::FileDragAndDropTarget,
                 public juce::Timer
{
public:
    /**DeckGUI constructor takes a pointer to the DJAudioPlayer, 
    and refrences the memory address of the juce audioFormatManager for music processing
    and AudioThumbnailCache for storing sine wave processing*/
    DeckGUI(DJAudioPlayer* player,
            juce::AudioFormatManager& formatManagerToUse,
            juce::AudioThumbnailCache& cacheToUse);
    
    /**DeckGUI deconstructor*/
    ~DeckGUI() override;

    /**The paint() method gets called when a region of a component needs redrawing,
    either because the component's repaint() method has been called, or because something
    has happened on the screen that means a section of a window needs to be redrawn.*/
    void paint (juce::Graphics&) override;

    /**called to repaint the DeckGUI when the window is resized*/
    void resized() override;

    /** implement Button::Listener */
    void buttonClicked(juce::Button* button) override;

    /** implement Slider::Listener*/
    void sliderValueChanged(juce::Slider* slider) override;

    /**takes a string input representing a file URL and outputs true while file is being dragged*/
    bool isInterestedInFileDrag(const juce::StringArray &files) override;

    /**takes a string input representing a file URL, and the x and y inputs of the mouse.
    outputs the file URL to DJAudioPlayer loadURL() and the WaveformDisplay loadURL()*/
    void filesDropped(const juce::StringArray &files, int x, int y) override;

    /**Gets called regularly every n time cycles used for updating the playhead 
    and the record posistion during playback*/
    void timerCallback() override;

    /**takes a string input from the PlaylistComponent representing a URL and calls
    DJAudioPlayer/WaveformDisplay loadURL() and starts playback*/
    void playFromPlaylist(juce::URL audioURL);
    
private:
    
    juce::TextButton playButton{ "PLAY/PAUSE" };
    juce::TextButton stopButton{ "STOP" };
    juce::TextButton loadButton{ "LOAD" };

    juce::Slider volSlider;
    juce::Slider speedSlider;
    juce::Slider posSlider;

    juce::Label volLabel;
    juce::Label speedLabel;

    DJAudioPlayer* player;

    WaveformDisplay waveformDisplay;

    PlaylistLogic playlistLogic;

    RecordComponent recordComponent{player};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DeckGUI)
};
