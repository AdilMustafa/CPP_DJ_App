/*
==============================================================================

				This file was auto-generated!

==============================================================================
*/

#include "MainComponent.h"
#include "csv.h"

//----------------------------------------------------------------------------
MainComponent::MainComponent()
{
	formatManager.registerBasicFormats();
	setSize(800, 600);

	
	if (juce::RuntimePermissions::isRequired(juce::RuntimePermissions::recordAudio)
		&& !juce::RuntimePermissions::isGranted(juce::RuntimePermissions::recordAudio))
	{
		juce::RuntimePermissions::request(juce::RuntimePermissions::recordAudio,
			[&](bool granted) { if (granted)  setAudioChannels(2, 2); });
	}
	else
	{
		
		setAudioChannels(0, 2);
	}

	addAndMakeVisible(deckGUI1);
	addAndMakeVisible(deckGUI2);
	addAndMakeVisible(playlistComponent);

	addAndMakeVisible(crossFaderSlider);
	crossFaderSlider.addListener(this);
	crossFaderSlider.setRange(-1, 1);

	addAndMakeVisible(crossFaderLabel);
	crossFaderLabel.setText("Crossfader", juce::dontSendNotification);
	crossFaderLabel.setColour(juce::Label::textColourId, juce::Colours::white);
	crossFaderLabel.setJustificationType(juce::Justification::centred);
	crossFaderLabel.setFont(juce::Font(13.0f, juce::Font::underlined));

	//std::string filename{ "C:/Users/adilm/Desktop/juce-6.0.7-windows/JUCE/myModules/DJ_App_Lab2/Source/playlist.csv" };
	//std::vector<std::vector<std::string>> playlist =
	//CSVReader::readCSV(filename);
	
}

//----------------------------------------------------------------------------
MainComponent::~MainComponent()
{
	shutdownAudio();
}

//----------------------------------------------------------------------------
void MainComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{

	// I had to comment out both player1 and 2 as they cause errors once I implemented mixerSource  

	//player1.prepareToPlay(samplesPerBlockExpected, sampleRate);
	//player2.prepareToPlay(samplesPerBlockExpected, sampleRate);
	//player3.prepareToPlay(samplesPerBlockExpected, sampleRate);
	
	mixerSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
	mixerSource.addInputSource(&player1, false);
	mixerSource.addInputSource(&player2, false);
	mixerSource.addInputSource(&player3, false);

}

//----------------------------------------------------------------------------
void MainComponent::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
	mixerSource.getNextAudioBlock(bufferToFill);
}

//----------------------------------------------------------------------------
void MainComponent::releaseResources()
{

	player1.releaseResources();
	player2.releaseResources();
	player3.releaseResources();
	mixerSource.releaseResources();
}

//----------------------------------------------------------------------------
void MainComponent::paint(juce::Graphics& g)
{

	g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

}

//----------------------------------------------------------------------------
void MainComponent::resized()
{
	deckGUI1.setBounds(0,0,getWidth()/2, getHeight()/1.2);
	deckGUI2.setBounds(getWidth() / 2,0,getWidth()/2, getHeight()/1.2);

	playlistComponent.setBounds(0,getHeight()*0.85,getWidth(), getHeight()*0.15);

	double rowH = getHeight() / 5;
	crossFaderSlider.setBounds(0, rowH * 3.3, getWidth(), 25);	
	crossFaderLabel.setBounds(getWidth() / 4, rowH * 3.1, getWidth()/2, 24);

	
}

//----------------------------------------------------------------------------
void MainComponent::buttonClicked(juce::Button* button) 
{
	
}

//----------------------------------------------------------------------------
void MainComponent::sliderValueChanged(juce::Slider * slider) {
	
	if (slider == &crossFaderSlider)
	{
		DBG("crossFaderSlider Value = " << slider->getValue());
		if(slider->getValue() <= 0 )
		{
			player1.setGain(-slider->getValue());
		}

		if (slider->getValue() >= 0)
		{
			player2.setGain(slider->getValue());
		}
		
	}

}

