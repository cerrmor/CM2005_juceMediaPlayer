/*
  ==============================================================================

    DJAudioPlayer.cpp
    Created: 29 Jul 2020 5:47:49pm
    Author:  Garrison

  ==============================================================================
*/

#include "DJAudioPlayer.h"

DJAudioPlayer::DJAudioPlayer(juce::AudioFormatManager& _formatManager) 
                             : formatManager(_formatManager)
{
    
}

DJAudioPlayer::~DJAudioPlayer()
{

}

void DJAudioPlayer::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    resampleSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void DJAudioPlayer::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    if (readerSource.get() == nullptr)
    {
        bufferToFill.clearActiveBufferRegion();
        return;
    }
    resampleSource.getNextAudioBlock(bufferToFill);
}

void DJAudioPlayer::releaseResources()
{
    transportSource.releaseResources();
    resampleSource.releaseResources();
}

void DJAudioPlayer::loadURL(juce::URL audioURL)
{
    auto* reader = formatManager.createReaderFor(audioURL.createInputStream(false));
    if (reader != nullptr) // good file!
    {
        std::unique_ptr<juce::AudioFormatReaderSource> newSource(new juce::AudioFormatReaderSource(reader, true));
        transportSource.setSource(newSource.get(), 0, nullptr, reader->sampleRate);
        readerSource.reset(newSource.release());
    }
}

void DJAudioPlayer::setGain(double gain)
{
    if (gain < 0.0 || gain > 1.0)
    {
        DBG("DJAudioPlayer::setGain gain should be between 0 and 1");
    }
    else
    {
        transportSource.setGain(gain);
    }
}

void DJAudioPlayer::setSpeed(double ratio)
{
    if (ratio < 0.0 || ratio > 100.0)
    {
        DBG("DJAudioPlayer::setSpeed ratio should be between 0 and 100");
    }
    else
    {
        resampleSource.setResamplingRatio(ratio);
    }
}


void DJAudioPlayer::setPosistion(double posInSecs)
{
    transportSource.setPosition(posInSecs);
}

void DJAudioPlayer::setPosistionRelative(double pos)
{
    if (pos < 0.0 || pos > 1.0)
    {
        DBG("DJAudioPlayer::setPositionRelative pos should be between 0 and 1");
    }
    else
    {
        double posInSecs = transportSource.getLengthInSeconds() * pos;
        setPosistion(posInSecs);
    }
}

void DJAudioPlayer::start()
{
    if (!transportSource.isPlaying())
    {
        transportSource.start();
    }
    else pause();
}

void DJAudioPlayer::pause()
{
    transportSource.stop();
}

void DJAudioPlayer::stop()
{
    transportSource.stop();
    transportSource.setPosition(0.0);
}

double DJAudioPlayer::getPosistionRelative()
{
    return transportSource.getCurrentPosition() / transportSource.getLengthInSeconds();
}

juce::String DJAudioPlayer::getRelativeSongLength()
{
    int totalSeconds = transportSource.getLengthInSeconds();
    int minutes = floor(totalSeconds % 3600 / 60);
    int seconds = floor(totalSeconds % 3600 % 60);
    
    juce::String time = std::to_string(minutes) + "min:" + std::to_string(seconds) + "sec";

    return time;
}

bool DJAudioPlayer::isPlaying()
{

    return transportSource.isPlaying();
    
}
