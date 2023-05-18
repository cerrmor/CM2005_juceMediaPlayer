#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"
#include "DeckGUI.h"
#include "PlaylistComponent.h"
#include "SearchBox.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent : public juce::AudioAppComponent
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;


    //==============================================================================
    /**Tells the source to prepare for playing.
    The prepareToPlay() method is guaranteed to be called at least once on an 
    'unprepared' source to put it into a 'prepared' state before any calls will 
    be made to getNextAudioBlock(). This callback allows the source to initialise 
    any resources it might need when playing.*/
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    /**Called repeatedly to fetch subsequent blocks of audio data.
    After calling the prepareToPlay() method, this callback will be made each time the 
    audio playback hardware (or whatever other destination the audio data is going to) 
    needs another block of data*/
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
    /**Allows the source to release anything it no longer needs after playback has stopped.
    This will be called when the source is no longer going to have its getNextAudioBlock() 
    method called, so it should release any spare memory, etc. that it might have allocated 
    during the prepareToPlay() call.*/
    void releaseResources() override;

    //==============================================================================
    /**The paint() method gets called when a region of a component needs redrawing, 
    either because the component's repaint() method has been called, or because something 
    has happened on the screen that means a section of a window needs to be redrawn.*/
    void paint(juce::Graphics& g) override;
    /**Called when this component's size has been changed.*/
    void resized() override;

private:
    //==============================================================================
    // Your private member variables go here...
    
    juce::AudioFormatManager formatManager;
    juce::AudioThumbnailCache thumbCache{ 100 };

    DJAudioPlayer player1{ formatManager };
    DeckGUI deckGUI1{ &player1, formatManager, thumbCache };
    DJAudioPlayer player2{ formatManager };
    DeckGUI deckGUI2{ &player2, formatManager, thumbCache };

    juce::MixerAudioSource mixerSource;
    
    PlaylistComponent playlistComponent{&deckGUI1, &deckGUI2};
    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
