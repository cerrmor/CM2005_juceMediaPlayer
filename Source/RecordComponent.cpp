/*
  ==============================================================================

    RecordComponent.cpp
    Created: 13 Sep 2020 12:11:16pm
    Author:  Garrison

  ==============================================================================
*/

#include <JuceHeader.h>
#include "RecordComponent.h"

//==============================================================================
RecordComponent::RecordComponent(DJAudioPlayer* _player) : player(_player)
{
    setOpaque(true);
}

RecordComponent::~RecordComponent()
{
}

void RecordComponent::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    
    juce::Rectangle<float> areaEllipse(0, 0, getWidth(), getHeight());
    juce::Rectangle<float> areaEllipse2(5, 5, getWidth()-10, getHeight()-10);
    juce::Point<float> startPoint, endPoint;
    juce::Line<float> line;
    //represeting the first 20 numbers of the standard pi veriable
    const double pi = 3.14159265358979323846;
    //calculates the angle of rotation relative to the position in the song playback
    float angle = player->getPosistionRelative() * 360 - 90;
    //converts the angle to radians
    float piAngle = (angle * pi / 180) * 16;
    //draws the first ellipse to the screen
    g.setColour(juce::Colours::grey);
    g.fillEllipse(areaEllipse);
    //draws the second ellipse to the screen
    g.setColour(juce::Colours::black);
    g.fillEllipse(areaEllipse2);
    //sets the colour of the line
    g.setColour(juce::Colours::white);
    
    startPoint.x = areaEllipse.getWidth() / 2;
    startPoint.y = areaEllipse.getHeight() / 2;
    //sets the starting point of the rotating line
    line.setStart(startPoint);
    
    if (player->isPlaying())
    {
        endPoint.x = (areaEllipse2.getWidth() / 2) + (areaEllipse2.getWidth() / 2) * std::cos(piAngle);
        endPoint.y = (areaEllipse2.getHeight() / 2) + (areaEllipse2.getHeight() / 2) * std::sin(piAngle);
    }
    else
    {
        endPoint.x = 5;
        endPoint.y = areaEllipse2.getHeight() / 2;
    }
    //sets the endpoint of the rotating line
    line.setEnd(endPoint);
    //draws the line to the screen
    g.drawLine(line);
}

void RecordComponent::resized()
{
           
}

void RecordComponent::updateRecordComponent()
{
    repaint();
}

void RecordComponent::mouseDrag(const juce::MouseEvent& event)
{
    double posistion = player->getPosistionRelative();
    if (event.getDistanceFromDragStartX() > 1)
    {
        posistion = posistion + 0.01;
    }
    else if (event.getDistanceFromDragStartX() < 0)
    {
        posistion = posistion - 0.01;
    }
    player->setPosistionRelative(posistion);
}

