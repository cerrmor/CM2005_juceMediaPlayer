/*
  ==============================================================================

    DJAudioPlayer.h
    Created: 29 Jul 2020 5:47:49pm
    Author:  Garrison

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class DJAudioPlayer : public juce::AudioSource
{
public:
    /**DJAudioPlayer constructor*/
    DJAudioPlayer(juce::AudioFormatManager& formatManager);
    /**DJAudioPlayer Destructor*/
    ~DJAudioPlayer();
    
    /**builds the array of data for playback*/
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    /**passes an empty array and recieves a filled array for playback*/
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
    /**makes the data available to play*/
    void releaseResources() override;
    
    /**passes a file address and loads the data*/
    void loadURL(juce::URL audioURL);
    /**sets the volume of playback*/
    void setGain(double gain);
    /**sets the speed of playback*/
    void setSpeed(double ratio);

    /**sets the playback position, relitive to the slider position*/
    void setPosistionRelative(double pos);
    /**starts playing the file*/
    void start();
    /**stops playback of the file*/
    void pause();
    /**stops playback of the file and resets the start location*/
    void stop();
    /**gets the relative posistion of the play head between 0 and 1*/
    double getPosistionRelative();
    /**returns the meta data relative length of the song file coverted to a string*/
    juce::String getRelativeSongLength();
    /**returns true or false if the music is playing or not*/
    bool isPlaying();

private:
    void setPosistion(double posInSecs);

    juce::AudioFormatManager& formatManager;
    std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
    juce::AudioTransportSource transportSource;
    juce::ResamplingAudioSource resampleSource{ &transportSource, false, 2 };
};