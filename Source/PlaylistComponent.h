/*
  ==============================================================================

    PlaylistComponent.h
    Created: 16 Aug 2020 8:59:26pm
    Author:  Garrison

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <vector>
#include "DeckGUI.h"
#include "PlaylistLogic.h"
#include "SearchBox.h"

//==============================================================================
/*
*/
class PlaylistComponent  : public juce::Component,
                           public juce::TableListBoxModel,
                           public juce::Button::Listener
{
public:
    /**playlist component constructor takes in a pointer to the deckGUI 1 and 2*/
    PlaylistComponent(DeckGUI* deckGUI1, DeckGUI* deckGUI2);
    ~PlaylistComponent() override;
    /**The paint() method gets called when a region of a component needs redrawing,
    either because the component's repaint() method has been called, or because something
    has happened on the screen that means a section of a window needs to be redrawn.*/
    void paint (juce::Graphics&) override;
    /**Called when this component's size has been changed.*/
    void resized() override;
    /**returns an integer that represents the number of tracks in the playlist*/
    int getNumRows() override;
    /**This must draw the background behind one of the rows in the table.
    The graphics context has its origin at the row's top-left, and your method 
    should fill the area specified by the width and height parameters.*/
    void paintRowBackground(juce::Graphics&,
                            int rowNumber, 
                            int width, 
                            int height, 
                            bool rowIsSelected) override;
    /**This must draw one of the cells.
    The graphics context's origin will already be set to the top-left of the cell,
    whose size is specified by (width, height).*/
    void paintCell(juce::Graphics&, 
                   int rowNumber, 
                   int columnId, 
                   int width, 
                   int height, 
                   bool rowIsSelected) override;
    /**This is used to create or update a custom component to go in a cell.
    This method will be called whenever a custom component might need to be updated 
    - e.g. when the table is changed, or TableListBox::updateContent() is called.*/
    Component* refreshComponentForCell(int rowNumber, 
                                       int columnId, 
                                       bool isRowSelected, 
                                       Component* existingComponentToUpdate) override;
    /**Called when the button is clicked
    requires a button listener to be registered*/
    void buttonClicked(juce::Button* button) override;
    /**gets called when a change has happened and the model needs to be repainted.
    outputs void*/
    void updateBoxModel();

private:

    DeckGUI* deckGUI1;
    DeckGUI* deckGUI2;
    PlaylistLogic playlistLogic;
    SearchBox searchBox;

    juce::Label searchLabel;
    juce::Label inputText;
    juce::String trackToDisplay;
    juce::TableListBox tableComponent;
    int selectedRowId1 = -1;
    int selectedRowId2 = -1;
    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlaylistComponent)
};
