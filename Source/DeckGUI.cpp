/*
  ==============================================================================

    DeckGUI.cpp
    Created: 30 Jul 2020 9:20:38pm
    Author:  Garrison

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DeckGUI.h"

//==============================================================================
DeckGUI::DeckGUI(DJAudioPlayer* _player,
                 juce::AudioFormatManager& formatManagerToUse,
                 juce::AudioThumbnailCache& cacheToUse
                 ) : player(_player), 
                 waveformDisplay(formatManagerToUse,cacheToUse)
{
    addAndMakeVisible(playButton);
    addAndMakeVisible(stopButton);
    addAndMakeVisible(loadButton);

    addAndMakeVisible(volSlider);
    addAndMakeVisible(speedSlider);
    addAndMakeVisible(posSlider);

    addAndMakeVisible(waveformDisplay);
    addAndMakeVisible(recordComponent);

    playButton.addListener(this);
    stopButton.addListener(this);
    loadButton.addListener(this);

    volSlider.addListener(this);
    speedSlider.addListener(this);
    posSlider.addListener(this);

    volSlider.setRange(0.0f, 1.0f, 0.01f);
    speedSlider.setRange(0.0f, 10.0f, 0.01f);
    posSlider.setRange(0.0f, 1.0f);

    startTimer(50);
}

DeckGUI::~DeckGUI()
{
    stopTimer();
}

void DeckGUI::paint(juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour(juce::Colours::grey);
    g.drawRect(getLocalBounds(), 1);   // draw an outline around the component

    g.setColour(juce::Colours::white);
    g.setFont(14.0f);
    g.drawText("DeckGUI", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text

    volSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    volSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 40, 20);
    volLabel.setFont(15.0f);
    volLabel.setText("Vol", juce::NotificationType::dontSendNotification);
    volLabel.setJustificationType(juce::Justification::centredTop);
    volLabel.attachToComponent(&volSlider, false);

    speedSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    speedSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 40, 20);
    speedLabel.setFont(15.0f);
    speedLabel.setText("Speed", juce::NotificationType::dontSendNotification);
    speedLabel.setJustificationType(juce::Justification::centredTop);
    speedLabel.attachToComponent(&speedSlider, false);

}

void DeckGUI::resized()
{
    double rowH = getHeight() / 8;
    double rowW = getWidth() / 7;

    playButton.setBounds(0, 0, (rowW * 3.5), rowH);
    stopButton.setBounds(rowW * 3.5, 0, (rowW * 3.5), rowH);

    volSlider.setBounds(0, rowH * 2, 100, rowH * 2);
    speedSlider.setBounds(rowW, rowH * 2, 100, rowH * 2);
    posSlider.setBounds(0, rowH * 4, getWidth(), rowH);

    waveformDisplay.setBounds(0, rowH * 5, getWidth(), rowH * 2);
    recordComponent.setBounds(rowW * 4, rowH * 1.25, rowW * 1.75, rowH * 2.69);
    
    loadButton.setBounds(0, rowH * 7, getWidth(), rowH);
    
}

void DeckGUI::buttonClicked(juce::Button* button)
{
    if (button == &playButton)
    {
        DBG("the Play Button was clicked!!!!");
        player->start();
    }
    if (button == &stopButton)
    {
        DBG("the Stop Button was Clicked!!!");
        player->stop();
        posSlider.setValue(0.0f);
    }
    if (button == &loadButton)
    {
        juce::FileChooser chooser{ "select a file..." };
        if (chooser.browseForFileToOpen())
        {
            player->loadURL(juce::URL{ chooser.getResult() });
            waveformDisplay.loadURL(juce::URL{ chooser.getResult() });
            playlistLogic.addToPlaylist(juce::URL{ chooser.getResult() }, player->getRelativeSongLength());
        }
    }
}

void DeckGUI::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &volSlider)
    {
        player->setGain(slider->getValue());
    }
    if (slider == &speedSlider)
    {
        player->setSpeed(slider->getValue());
    }
    if (slider == &posSlider)
    {
        player->setPosistionRelative(slider->getValue());
    }
}

bool DeckGUI::isInterestedInFileDrag(const juce::StringArray& files)
{
    DBG("DeckGUI::isInterestedInFileDrag");
    return true;
}

void DeckGUI::filesDropped(const juce::StringArray& files, int x, int y)
{
    DBG("DeckGUI::filesDropped");
    if (files.size() == 1)
    {
        for (juce::String filename : files)
        {
            DBG("DeckGUI::filesDropped " << filename);
            juce::URL fileURL = juce::URL{ juce::File{filename} };
            player->loadURL(fileURL);
            waveformDisplay.loadURL(fileURL);
            playlistLogic.addToPlaylist(fileURL, player->getRelativeSongLength());
            return;
        }
    }
    else
    {
        player->loadURL(juce::URL{ juce::File{files[0]} });
        waveformDisplay.loadURL(juce::URL{ juce::File{files[0]} });
        playlistLogic.addToPlaylist(juce::URL{ juce::File{files[0]} }, 
                                    player->getRelativeSongLength());
        return;
    }
}

void DeckGUI::timerCallback()
{
    waveformDisplay.setPosistionRelative(player->getPosistionRelative());
    if (player->getPosistionRelative() > posSlider.getValue())
    {
        posSlider.setValue(player->getPosistionRelative());
    }
    recordComponent.updateRecordComponent();
}

void DeckGUI::playFromPlaylist(juce::URL audioURL)
{
    player->loadURL(audioURL);
    waveformDisplay.loadURL(audioURL);
    posSlider.setValue(0.0);
    player->start();

}


