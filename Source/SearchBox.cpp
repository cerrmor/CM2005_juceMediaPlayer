/*
  ==============================================================================

    SearchBox.cpp
    Created: 7 Sep 2020 3:25:31pm
    Author:  Garrison

  ==============================================================================
*/

#include <JuceHeader.h>
#include "SearchBox.h"

//==============================================================================
SearchBox::SearchBox()
{   
}

SearchBox::~SearchBox()
{
}

void SearchBox::paint (juce::Graphics& g)
{

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText ("SearchBox", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void SearchBox::resized()
{

}

juce::String SearchBox::linearSearch(juce::String item)
{
    juce::XmlDocument list(juce::File("D:/masterPlaylist.xml"));

    if (auto playlist = list.getDocumentElement())
    {
        for (int i = 1; i <= playlist->getNumChildElements(); ++i)
        {
            juce::String index = std::to_string(i);
            juce::String compare = playlist->getChildByName("track" + index)->getChildByName("name")->getAllSubText();
            
            tokeniser(compare);
            
            for (int j = 0; j < token.size(); ++j)
            {
                if (item == compare || item == token[j])
                {
                    DBG("track" + index);
                    return juce::String("track" + index);
                }
            }
            token.clear();
        }
    }
    DBG("did not find the item");
    return juce::String();
}

void SearchBox::tokeniser(juce::String item)
{
    juce::StringArray tokens;
    tokens.addTokens(item, "_"".", ".");

    for (int i = 0; i < tokens.size(); i++)
    {
        token.add(tokens[i]); // holds next token
    }
}
