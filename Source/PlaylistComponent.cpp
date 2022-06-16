/*
  ==============================================================================

    PlaylistComponent.cpp
    Created: 17 Mar 2021 12:34:49pm
    Author:  adilm

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "PlaylistComponent.h"
#include "csv.h"


//==============================================================================
PlaylistComponent::PlaylistComponent(DJAudioPlayer* _player,
	juce::AudioFormatManager & formatManagerToUse,
	juce::AudioThumbnailCache & cacheToUse)
	: player(_player)
{
	trackTitles.push_back("Track 1");
	trackTitles.push_back("Track 2");
	trackTitles.push_back("Track 3");
	trackTitles.push_back("Track 4");

	trackButtons.push_back("Play");
	trackButtons.push_back("Stop");

	tableComponent.getHeader().addColumn("Track Title", 1, 400);
	tableComponent.getHeader().addColumn("Play", 2, 75);
	tableComponent.getHeader().addColumn("Stop/UpdateCSV", 3, 150);


	tableComponent.setModel(this);
	
	addAndMakeVisible(tableComponent);

	std::string filename{ "C:/Users/adilm/Desktop/juce-6.0.7-windows/JUCE/myModules/DJ_App_Lab2/Source/playlist.csv" };
	std::vector<std::vector<std::string>> playlist =
	CSVReader::readCSV(filename);

}

PlaylistComponent::~PlaylistComponent()
{
	//shutdownAudio();
}

void PlaylistComponent::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText ("PlaylistComponent", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void PlaylistComponent::resized()
{
	tableComponent.setBounds(0,0,getWidth(),getHeight());

}


int PlaylistComponent::getNumRows()
{
	return trackTitles.size();

}

int PlaylistComponent::getNumColumns()
{
	return trackButtons.size() + 1;

}

void PlaylistComponent::paintRowBackground(juce::Graphics &g, 
						int rowNumber,
						int width, 
						int height,
						bool rowIsSelected)
{
	if(rowIsSelected)
	{
		g.fillAll(juce::Colours::purple);
	}

	else
	{
		g.fillAll(juce::Colours::lightgrey);
	}
}


void PlaylistComponent::paintCell(juce::Graphics &g, 
						int rowNumber, 
						int columnId, 
						int width, 
						int height, 
						bool rowIsSelected)
{
	g.drawText(trackTitles[rowNumber],
		2, 0,
		width - 4, height,
		juce::Justification::centredLeft,
		true);



};

juce::Component* PlaylistComponent::refreshComponentForCell(
				 int rowNumber,
				 int columnId,
				 bool isRowSelected,
				 juce::Component *existingComponentToUpdate) 
{

	if(columnId == 2)
	{
		if(existingComponentToUpdate == nullptr)
		{
			juce::TextButton* btn = new juce::TextButton{ "Play" }; 
			juce::String id{ std::to_string(rowNumber) };
			btn->setComponentID(id);
			btn->addListener(this);
			
		
		
			existingComponentToUpdate = btn;

			
				
			


		}
	}
	
	//stop
	if (columnId == 3)
	{
		if (existingComponentToUpdate == nullptr)
		{
			/*
			juce::TextButton* btn = new juce::TextButton{ "Stop" };
			juce::String id{ std::to_string(rowNumber) };
			btn->setComponentID(id);
			btn->addListener(this);
			player->stop();
			existingComponentToUpdate = btn;

			*/
			player->stop();
			std::string filename{ "C:/Users/adilm/Desktop/juce-6.0.7-windows/JUCE/myModules/DJ_App_Lab2/Source/playlist.csv" };
			std::vector<std::vector<std::string>> playlist =
			CSVReader::readCSV(filename);

		}
	}




	
	
	return existingComponentToUpdate;
};

void PlaylistComponent::buttonClicked(juce::Button* button)
{
	int id = std::stoi(button->getComponentID().toStdString());

	DBG("playlist button id = " << trackTitles[id]);
	juce::String id2 = (button->getComponentID().toStdString());




	if(id2 == "0")
	{
		player->start();
	}

	if(id2 == "1")
	{
		
		player->loadURL( juce::URL { "file:///C:/Users/adilm/Music/track1.WAV" } );
		player->start();
	}
	
	
	if(id2 == "2")
	{
		
		player->loadURL(juce::URL{ "file:///C:/Users/adilm/Music/track2.WAV" });
		player->start();
	}
	
	
	if(id2 == "3")
	{
		player->loadURL(juce::URL{ "file:///C:/Users/adilm/Music/track5.WAV" });
		player->start();
	}
	
}


/*
void PlaylistComponent::cellClicked(int rowNumber,
									int columnId,
									bool mouseWasClicked)
{
	if(rowNumber == 1 && columnId == 6 && mouseWasClicked == true)
	{
		DBG("true");		
		std::string filename{ "C:/Users/adilm/Desktop/juce-6.0.7-windows/JUCE/myModules/DJ_App_Lab2/Source/playlist.csv" };
		std::vector<std::vector<std::string>> playlist =
		CSVReader::readCSV(filename);

	}
}

*/

bool PlaylistComponent::isInterestedInFileDrag(const juce::StringArray &files)
{
	DBG("isInterestedInFileDrag");
	return true;
}


void PlaylistComponent::filesDropped(const juce::StringArray &files, int x, int y)
{
	DBG("filesDropped");

		player->loadURL(juce::URL{ juce::File{files[0]} });
	
}
