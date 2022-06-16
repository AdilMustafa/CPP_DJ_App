/*
  ==============================================================================

    WaveformDisplay.cpp
    Created: 3 Mar 2021 1:41:24pm
    Author:  adilm

  ==============================================================================
*/

#include <JuceHeader.h>
#include "WaveformDisplay.h"

//==============================================================================
WaveformDisplay::WaveformDisplay(juce::AudioFormatManager & formatManagerToUse,
								 juce::AudioThumbnailCache & cacheToUse) 
								 : audioThumbnail(1000, formatManagerToUse, cacheToUse),
								 fileLoaded(false),
								 position(0)

{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
	audioThumbnail.addChangeListener(this);
}

WaveformDisplay::~WaveformDisplay()
{
}

void WaveformDisplay::paint (juce::Graphics& g)
{
 
	g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));   // clear the background
	g.setColour(juce::Colours::black);
	g.drawRect(getLocalBounds(), 1);   // draw an outline around the component
	//g.drawText("pos", getWidth()/2, -20, 200, 40, juce::Justification::centred, true);
	if (fileLoaded)
	{
		g.setColour(juce::Colours::purple);
		audioThumbnail.drawChannel(g, getLocalBounds(), 
								   0, 
								   audioThumbnail.getTotalLength(),
								   0, 
								   1.0f);
		g.setColour(juce::Colours::white);
		g.drawRect(position * getWidth(), 0, getWidth() / 20, getHeight()); 



	}
	
	else
	{
		g.setColour(juce::Colours::black);
		g.setFont(16.0f);
		g.drawText("File not loaded yet...", getLocalBounds(),
			juce::Justification::centred, true);   // draw some placeholder text
	}
}

void WaveformDisplay::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}


void WaveformDisplay::loadURL(juce::URL audioURL)
{
	DBG("wfd: loadURL");
	audioThumbnail.clear();
	fileLoaded = audioThumbnail.setSource(new juce::URLInputSource(audioURL));

	if(fileLoaded)
	{
		DBG("wfd: loaded!");
		repaint();
	}

	else
	{
		DBG("wfd: not loaded!");
	}
}

void WaveformDisplay::changeListenerCallback(juce::ChangeBroadcaster *source)
{

	DBG("wfd: change recieved!");
	repaint();
};

void WaveformDisplay:: setPositionRelative(double pos)
{
	if (pos != position) 
	{
		position = pos - 0.01;
		repaint();
	}

}