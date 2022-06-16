/*
  ==============================================================================

    PlaylistComponent.h
    Created: 17 Mar 2021 12:34:49pm
    Author:  adilm

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <vector>
#include <string>
#include "DJAudioPlayer.h"

//==============================================================================
/*
*/
class PlaylistComponent  :	public juce::Component,
							public juce::TableListBoxModel,
							public juce::Button::Listener,
							public juce::FileDragAndDropTarget

							
{
public:
    PlaylistComponent(DJAudioPlayer* player, juce::AudioFormatManager & formatManagerToUse,
		juce::AudioThumbnailCache & cacheToUse);
    ~PlaylistComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

	int getNumRows() override;
	int getNumColumns();

	void paintRowBackground(juce::Graphics &g, 
									int rowNumber, 
									int width, 
									int height, 
									bool rowIsSelected) override;

	void paintCell(juce::Graphics &g, 
							int rowNumber, 
							int columnId, 
							int width, 
							int height, 
							bool rowIsSelected) override;

	juce::Component* refreshComponentForCell(int rowNumber,
		int columnId,
		bool isRowSelected,
		juce::Component *existingComponentToUpdate) override;

	void buttonClicked(juce::Button* button) override;

	bool isInterestedInFileDrag(const juce::StringArray &files)override;
	void filesDropped(const juce::StringArray &files, int x, int y)override;

	void cellClicked(int rowNumber,
					 int columnId,
					 bool mouseWasClicked);


private:

	juce::TableListBox tableComponent;
	std::vector<std::string> trackTitles;
	std::vector<std::string> trackButtons;
	juce::AudioFormatManager formatManager;
	DJAudioPlayer* player;




    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlaylistComponent)
};
