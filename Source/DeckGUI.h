/*
  ==============================================================================

	DeckGUI.h
	Created: 22 Feb 2021 8:00:54pm
	Author:  adilm

  ==============================================================================
*/

#pragma once

//#include <JuceHeader.h>
#include "../JuceLibraryCode/JuceHeader.h"
#include "DJAudioPlayer.h"
#include "WaveformDisplay.h"
//#include "csv.cpp"

//==============================================================================
/*
*/
class DeckGUI : public juce::Component,
	public juce::Button::Listener,
	public juce::Slider::Listener,
	public juce::FileDragAndDropTarget,
	public juce::Timer 

{
public:
	DeckGUI(DJAudioPlayer* player, juce::AudioFormatManager & formatManagerToUse,
		juce::AudioThumbnailCache & cacheToUse);
	~DeckGUI() override;

	void paint(juce::Graphics&) override;
	void resized() override;

	void buttonClicked(juce::Button *)override;
	void sliderValueChanged(juce::Slider *slider)override;

	bool isInterestedInFileDrag(const juce::StringArray &files)override;
	void filesDropped(const juce::StringArray &files, int x, int y)override;

	void timerCallback()override;

	
	void mouseDown(const juce::MouseEvent& e) override;
	void mouseDrag(const juce::MouseEvent& e) override;
	void mouseUp(const juce::MouseEvent&) override;
	bool canMoveTransport() const noexcept;
	

private:

	juce::TextButton playButton{ "Play" };
	juce::TextButton stopButton{ "Stop" };
	juce::TextButton loadButton{ "Load" };
	juce::TextButton loopButton{ "Loop" };

	juce::Slider volSlider, speedSlider, progressSlider; // , crossFaderSlider;

	juce::Label VolumeL, SpeedL, PositionL, TimerL;
	juce::LookAndFeel_V4 speedLAF, progressLAF;

	DJAudioPlayer* player;
	WaveformDisplay waveformDisplay;

	float trackTime = 5;
	std::string test;
	

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DeckGUI)
};
