/*
  ==============================================================================

    PlaylistComponent.cpp
    Created: 16 Aug 2020 8:59:26pm
    Author:  Garrison

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PlaylistComponent.h"

//==============================================================================
PlaylistComponent::PlaylistComponent(DeckGUI* _deckGUI1, DeckGUI* _deckGUI2) : deckGUI1(_deckGUI1), deckGUI2(_deckGUI2)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.


    tableComponent.getHeader().addColumn("TrackTitle", 1, 250);
    tableComponent.getHeader().addColumn("SongLength", 2, 250);
    tableComponent.getHeader().addColumn("", 3, 50);
    tableComponent.getHeader().addColumn("", 4, 50);
    tableComponent.setMultipleSelectionEnabled(true);
    tableComponent.setModel(this);

    addAndMakeVisible(tableComponent);

   
    addAndMakeVisible(searchLabel);
    addAndMakeVisible(inputText);

    searchLabel.setText("Search:", juce::dontSendNotification);
    searchLabel.attachToComponent(&inputText, true);
    searchLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    searchLabel.setJustificationType(juce::Justification::right);

    inputText.setEditable(true);
    inputText.setColour(juce::Label::textColourId, juce::Colours::black);
    inputText.setColour(juce::Label::textWhenEditingColourId, juce::Colours::black);
    inputText.setColour(juce::Label::backgroundColourId, juce::Colours::lightgrey);
    inputText.setColour(juce::Label::outlineColourId, juce::Colours::black);
    inputText.setColour(juce::Label::backgroundWhenEditingColourId, juce::Colours::white);

    inputText.onTextChange = [this] {trackToDisplay = searchBox.linearSearch(inputText.getText()); updateBoxModel(); };
}

PlaylistComponent::~PlaylistComponent()
{
}

void PlaylistComponent::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText ("Please load a song file", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void PlaylistComponent::resized()
{
    tableComponent.setBounds(0, 0, getWidth(), getHeight());
    inputText.setBounds(getWidth() - 200, 2, 200, 20);
}

int PlaylistComponent::getNumRows()
{
    juce::XmlDocument list(juce::File("D:/masterPlaylist.xml"));
    
    if (auto playlist = list.getDocumentElement())
    {
        return playlist->getNumChildElements();
    }
    else
    {
        return 0;
    }
    
}

void PlaylistComponent::paintRowBackground(juce::Graphics& g,
                                           int rowNumber,
                                           int width,
                                           int height,
                                           bool rowIsSelected)
{
    if (rowIsSelected && rowNumber == selectedRowId1)
    {
        g.fillAll(juce::Colours::lightgoldenrodyellow);
    }
    else if (rowIsSelected && rowNumber == selectedRowId2)
    {
        g.fillAll(juce::Colours::cyan);
    }
    else
    {
        g.fillAll(juce::Colours::darkgrey);
    }
}

void PlaylistComponent::paintCell(juce::Graphics& g,
                                  int rowNumber,
                                  int columnId,
                                  int width,
                                  int height,
                                  bool rowIsSelected)
{
    
    if (getNumRows() == 0 )
    {
        
        
    }
    else
    {
        /**catches an array overload for the table box model*/
        if (rowNumber >= getNumRows())
        {
            return;
        }
        if (columnId == 1)
        {
            g.drawText(playlistLogic.loadPlaylist(rowNumber, 1, trackToDisplay), 1, 0, width - 4, height, juce::Justification::centredLeft, true);
        }
        if (columnId == 2)
        {
            g.drawText(playlistLogic.loadPlaylist(rowNumber, 2, trackToDisplay), 2, 0, width - 4, height, juce::Justification::centredLeft, true);
        }
        updateBoxModel();
    }
}

juce::Component* PlaylistComponent::refreshComponentForCell(int rowNumber,
                                                            int columnId,
                                                            bool isRowSelected,
                                                            Component* existingComponentToUpdate)
{
    
    if (columnId == 3)
    {
        if (existingComponentToUpdate == nullptr)
        {
            juce::TextButton* btn = new juce::TextButton{ "play" };
            juce::String id{ std::to_string(rowNumber) };
            btn->setComponentID(id);
            btn->setName("left");
            
            btn->addListener(this);
            existingComponentToUpdate = btn;
        }
    }
    if (columnId == 4)
    {
        if (existingComponentToUpdate == nullptr)
        {
            juce::TextButton* btn = new juce::TextButton{ "play" };
            juce::String id{ std::to_string(rowNumber) };
            btn->setComponentID(id);
            btn->setName("right");
            
            btn->addListener(this);
            existingComponentToUpdate = btn;
        }
    }
    
    
    return existingComponentToUpdate;

}

void PlaylistComponent::buttonClicked(juce::Button* button)
{
    int id = std::stoi(button->getComponentID().toStdString());

    if (button->getName() == "left")
    {
        if (selectedRowId1 != -1) tableComponent.deselectRow(selectedRowId1);
        tableComponent.selectRow(id,true,false);
        deckGUI1->playFromPlaylist(playlistLogic.loadPlaylist(id, 3, trackToDisplay));
        selectedRowId1 = id;
    }
    if (button->getName() == "right")
    {
        if(selectedRowId2 != -1) tableComponent.deselectRow(selectedRowId2);
        tableComponent.selectRow(id, true, false);
        deckGUI2->playFromPlaylist(playlistLogic.loadPlaylist(id, 4, trackToDisplay));
        selectedRowId2 = id;
    }
}

void PlaylistComponent::updateBoxModel()
{
    tableComponent.updateContent();
    tableComponent.repaint();
}



