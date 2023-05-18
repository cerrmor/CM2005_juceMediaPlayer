/*
  ==============================================================================

    WaveformDisplay.cpp
    Created: 5 Aug 2020 9:32:57pm
    Author:  Garrison

  ==============================================================================
*/

#include <JuceHeader.h>
#include "WaveformDisplay.h"

//==============================================================================
WaveformDisplay::WaveformDisplay(juce::AudioFormatManager& formatManagerToUse,
                                 juce::AudioThumbnailCache& cacheToUse) :
                                 audioThumb(1000, formatManagerToUse, cacheToUse),
                                 fileLoaded(false),
                                 position(0)
{
    audioThumb.addChangeListener(this);
}

WaveformDisplay::~WaveformDisplay()
{
}

void WaveformDisplay::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::orange);

    if (fileLoaded)
    {
        /**draws the sine wave representing the music file to the screen*/
        audioThumb.drawChannel(g, getLocalBounds(), 0, audioThumb.getTotalLength(), 0, 1.0f);
        g.setColour(juce::Colours::lightgreen);
        g.drawRect(position * getWidth(), 0, getWidth() / 70, getHeight());
    }
    else
    {
        /**writes text indicating no file has been loaded*/
        g.setFont(20.0f);
        g.drawText("File not loaded...", getLocalBounds(),
        juce::Justification::centred, true);   // draw some placeholder text
    }
}

void WaveformDisplay::resized()
{
   
}

void WaveformDisplay::loadURL(juce::URL audioURL) 
{
    audioThumb.clear();
    fileLoaded = audioThumb.setSource(new juce::URLInputSource(audioURL));

    if (fileLoaded)
    {
        DBG("loaded URL wavform");
    }
    else
    {
        DBG("NOT loaded URL wavform");
    }
}

void WaveformDisplay::changeListenerCallback(juce::ChangeBroadcaster* source)
{
    repaint();
}

void WaveformDisplay::setPosistionRelative(double pos)
{
    if (pos != position && pos == pos)
    {
        position = pos;
        repaint();
    }
}