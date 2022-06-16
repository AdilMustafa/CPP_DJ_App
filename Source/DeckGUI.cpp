/*
  ==============================================================================

	DeckGUI.cpp
	Created: 22 Feb 2021 8:00:54pm
	Author:  adilm

  ==============================================================================
*/

//#include <JuceHeader.h>
#include "../JuceLibraryCode/JuceHeader.h"
#include "DeckGUI.h"


//==============================================================================
DeckGUI::DeckGUI(DJAudioPlayer* _player,
	juce::AudioFormatManager & formatManagerToUse,
	juce::AudioThumbnailCache & cacheToUse)
	: player(_player),
	waveformDisplay(formatManagerToUse, cacheToUse)
{
	//---------------------------------- Waveform Display ---------------------------------\\
		
	addAndMakeVisible(waveformDisplay);

	//---------------------------------- Buttons ---------------------------------\\

	addAndMakeVisible(playButton);
	addAndMakeVisible(stopButton);
	addAndMakeVisible(loadButton);
	addAndMakeVisible(loopButton);

	playButton.addListener(this);
	stopButton.addListener(this);
	loadButton.addListener(this);
	loopButton.addListener(this);

	//---------------------------------- Sliders ---------------------------------\\

	addAndMakeVisible(volSlider);
	volSlider.addListener(this);
	volSlider.setRange(0, 1);
	volSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
	volSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 80, 20);

	addAndMakeVisible(speedSlider);
	speedSlider.addListener(this);
	speedSlider.setRange(0.0001, 3);
	speedSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
	speedSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 80, 20);

	addAndMakeVisible(progressSlider);
	progressSlider.addListener(this);
	progressSlider.setRange(0, 1);
	progressLAF.setColour(juce::Slider::thumbColourId, juce::Colours::white);
	progressLAF.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::black);
	progressSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 0, 0);
	progressSlider.setLookAndFeel(&progressLAF);

	/*
	addAndMakeVisible(crossFaderSlider);
	crossFaderSlider.addListener(this);
	crossFaderSlider.setRange(-1, 1);
	*/

	//---------------------------------- Labels ---------------------------------\\

	addAndMakeVisible(VolumeL);
	VolumeL.setText("Volume", juce::dontSendNotification);
	VolumeL.setColour(juce::Label::textColourId, juce::Colours::white);
	VolumeL.setJustificationType(juce::Justification::centred);
	VolumeL.setFont(juce::Font(12.0f, juce::Font::underlined));
	getLookAndFeel().setColour(juce::Slider::thumbColourId, juce::Colours::black);
	getLookAndFeel().setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::white);


	addAndMakeVisible(SpeedL);
	SpeedL.setText("Speed", juce::dontSendNotification);
	SpeedL.setColour(juce::Label::textColourId, juce::Colours::white);
	SpeedL.setJustificationType(juce::Justification::centred);
	SpeedL.setFont(juce::Font(12.0f, juce::Font::underlined));

	//addAndMakeVisible(PositionL);
	PositionL.setText("Position", juce::dontSendNotification);
	PositionL.setColour(juce::Label::textColourId, juce::Colours::white);
	PositionL.setJustificationType(juce::Justification::centred);
	PositionL.setFont(juce::Font(12.0f, juce::Font::underlined));

	addAndMakeVisible(TimerL);
	TimerL.setText(" ", juce::dontSendNotification);
	TimerL.setColour(juce::Label::textColourId, juce::Colours::white);
	TimerL.setJustificationType(juce::Justification::centred);
	TimerL.setFont(juce::Font(16.0f, juce::Font::underlined));

	speedLAF.setColour(juce::Slider::thumbColourId, juce::Colours::grey);
	speedLAF.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::black);
	speedSlider.setLookAndFeel(&speedLAF);

	startTimer(30);




}

DeckGUI::~DeckGUI()
{
	stopTimer();
}

void DeckGUI::paint(juce::Graphics& g)
{
	g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));   // clear the background

	g.setColour(juce::Colours::black);
	g.setFont(16.0f);
	//g.drawText(player->trackTimer(), getLocalBounds(),juce::Justification::centred, true);


	juce::String timecode(player->trackTimer());

	//g.drawText(timecode, getWidth() / 2, getHeight() / 2, 200, 200, juce::Justification::centred, true);
	g.drawText("Time: " + timecode ,getLocalBounds(), juce::Justification::centred, true);
	repaint(getWidth()/2 - 100, getHeight()/2 - 100,200,200);
}

void DeckGUI::resized()
{
	double rowH = getHeight() / 8;
	double rowH2 = getHeight() / 8.35;
	double wid = getWidth() / 2;

	//buttons
	playButton.setBounds(0, 0, getWidth(), rowH2);
	stopButton.setBounds(0, rowH2, getWidth(), rowH2);
	loadButton.setBounds(0, rowH2 * 7.35, getWidth(), rowH2);
	loopButton.setBounds(wid - 24, rowH * 2.1, 50, 25);

	//sliders
	volSlider.setBounds(wid / 4, rowH * 2, 100, rowH*1.5);
	speedSlider.setBounds(wid + wid / 4, rowH * 2, 100, rowH*1.5);
	progressSlider.setBounds(0, rowH2 * 3.3, getWidth(), rowH2*2.5);
	//crossFaderSlider.setBounds(0, rowH * 3.2, getWidth(), rowH);

	//labels
	VolumeL.setBounds(0, rowH * 2.275, wid, 24);
	SpeedL.setBounds(0, rowH * 2.275, getWidth() + wid, 24);
	PositionL.setBounds(getWidth() / 4, rowH2 * 4, wid, 24);
	TimerL.setBounds(-30, rowH2 * 3.2, getWidth(), 80);

	waveformDisplay.setBounds(5, rowH * 4.5, getWidth() - 5, rowH*1.2);

}


void DeckGUI::buttonClicked(juce::Button* button)
{

	if (button == &playButton)
	{
		DBG("PlayButton Clicked");
		//dphase = volSlider.getValue()*0.01;

		//player->csv_test();
		player->start();

		

		
	}

	if (button == &stopButton)
	{
		DBG("StopButton Clicked");
		//dphase = 0;
		player->stop();
	}

	if (button == &loopButton)
	{
		DBG("LoopButton Clicked");
		//transportSource.start();
		//player->setLooping(true);
		//player->isLooping();

	}

	if (button == &loadButton)
	{
		DBG("LoadButton Clicked");

		juce::FileChooser chooser{ "Select a File.." };
		if (chooser.browseForFileToOpen()) {
			player->loadURL(juce::URL{ chooser.getResult() });
			waveformDisplay.loadURL(juce::URL{ chooser.getResult() });

		}

	};

}

//----------------------------------------------------------------------------
void DeckGUI::sliderValueChanged(juce::Slider *slider) {


	if (slider == &volSlider)
	{
		DBG("volSlider Value = " << slider->getValue());
		player->setGain(slider->getValue());
	}

	if (slider == &progressSlider)
	{
		DBG("ProgressSlider Value = " << slider->getValue());
		player->setPositionRelative(slider->getValue());
	}

	if (slider == &speedSlider)
	{
		DBG("speedSlider Value = " << slider->getValue());
		player->setSpeed(slider->getValue());
	}

}



bool DeckGUI::isInterestedInFileDrag(const juce::StringArray &files)
{
	DBG("isInterestedInFileDrag");
	return true;
}


void DeckGUI::filesDropped(const juce::StringArray &files, int x, int y)
{
	DBG("filesDropped");

	player->loadURL(juce::URL{ juce::File{files[0]} });
}

void DeckGUI::timerCallback()
{
	//DBG(player->trackTimer());
	//juce::String timecode(player->trackTimer());
	waveformDisplay.setPositionRelative(player->getPositionRelative());
	//repaint();
}


void DeckGUI::mouseDown(const juce::MouseEvent& e)
{
	mouseDrag(e);
}

void DeckGUI::mouseDrag(const juce::MouseEvent& e)
{
		player->setPositionRelative(e.getMouseDownX());
}

void DeckGUI::mouseUp(const juce::MouseEvent&)
{
	player->start();
}
/*
bool DeckGUI::canMoveTransport()const noexcept
{
	return !(isFollowingTransport && transportSource.isPlaying());
}
*/
