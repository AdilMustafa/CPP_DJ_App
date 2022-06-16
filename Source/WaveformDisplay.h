/*
  ==============================================================================

    WaveformDisplay.h
    Created: 3 Mar 2021 1:41:24pm
    Author:  adilm

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class WaveformDisplay  : public juce::Component, 
						 public juce::ChangeListener
{
public:
    WaveformDisplay(juce::AudioFormatManager & formatManagerToUse,
					juce::AudioThumbnailCache & cacheToUse);
    ~WaveformDisplay() override;

    void paint (juce::Graphics&) override;
    void resized() override;
	void loadURL(juce::URL audioURL);
	void changeListenerCallback(juce::ChangeBroadcaster *source) override;
	void setPositionRelative(double pos);

	/*
	void mouseDown(const juce::MouseEvent& e) override;
	void mouseDrag(const juce::MouseEvent& e) override;
	void mouseUp(const juce::MouseEvent&) override;
	*/



private:

	bool fileLoaded;
	juce::AudioThumbnail audioThumbnail;
	double position;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveformDisplay)
};
