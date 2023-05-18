/*
  ==============================================================================

    PlaylistLogic.cpp
    Created: 6 Sep 2020 11:55:57am
    Author:  Garrison

  ==============================================================================
*/

#include "PlaylistLogic.h"

PlaylistLogic::PlaylistLogic()
{
}

PlaylistLogic::~PlaylistLogic()
{
}

void PlaylistLogic::addToPlaylist(juce::URL audioURL, juce::String time)
{
    /**creates the first instance of the xml file if one does not exsist at the address indicated*/
    if (!juce::File("D:/masterPlaylist.xml").existsAsFile())
    {
        juce::XmlElement masterPlaylist("songs");
        juce::XmlElement* newElement = masterPlaylist.createNewChildElement("track1");
        masterPlaylist.getChildByName("track1")->createNewChildElement("name");
        masterPlaylist.getChildByName("track1")->getChildByName("name")->addTextElement(audioURL.getFileName());
        masterPlaylist.getChildByName("track1")->createNewChildElement("url");
        masterPlaylist.getChildByName("track1")->getChildByName("url")->addTextElement(audioURL.toString(false));
        masterPlaylist.getChildByName("track1")->createNewChildElement("length");
        masterPlaylist.getChildByName("track1")->getChildByName("length")->addTextElement(time);
        masterPlaylist.writeToFile(juce::File("D:/masterPlaylist.xml"), juce::String());
    }
    else
    {
        /**Appends new entries to the masterplaylist if there is an xml file at the location*/
        juce::XmlDocument list(juce::File("D:/masterPlaylist.xml"));

        if (auto playlist = list.getDocumentElement())
        {
            count = std::to_string(playlist->getNumChildElements() + 1);
            juce::XmlElement* newElement = playlist->createNewChildElement("track" + count);
            playlist->getChildByName("track" + count)->createNewChildElement("name");
            playlist->getChildByName("track" + count)->getChildByName("name")->addTextElement(audioURL.getFileName());
            playlist->getChildByName("track" + count)->createNewChildElement("url");
            playlist->getChildByName("track" + count)->getChildByName("url")->addTextElement(audioURL.toString(false));
            playlist->getChildByName("track" + count)->createNewChildElement("length");
            playlist->getChildByName("track" + count)->getChildByName("length")->addTextElement(time);
            playlist->writeToFile(juce::File("D:/masterPlaylist.xml"), juce::String());

        }
    }
}

juce::String PlaylistLogic::loadPlaylist(int num, int columnID, juce::String string)
{
    trackNum = std::to_string(num + 1);
    juce::XmlDocument list(juce::File("D:/masterPlaylist.xml"));
    juce::String track;
    if (string == "")
    {
        track = "track" + trackNum;
    }
    else
    {
        track = string;
    }
    if (auto playlist = list.getDocumentElement())
    {
        if (columnID == 1)
        {
            return playlist->getChildByName(track)->getChildByName("name")->getAllSubText();
        }
        if (columnID == 2)
        {
            return playlist->getChildByName(track)->getChildByName("length")->getAllSubText();
        }
        if (columnID == 3)
        {
            return playlist->getChildByName(track)->getChildByName("url")->getAllSubText();
        }
        if (columnID == 4)
        {
            return playlist->getChildByName(track)->getChildByName("url")->getAllSubText();
        }
    }
}


