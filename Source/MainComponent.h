/*
  ==============================================================================

	This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "DJAudioPlayer.h"
#include "DeckGUI.h"
#include "PlaylistComponent.h"


//==============================================================================
/*
	This component lives inside our window, and this is where you should put all
	your controls and content.
*/
class MainComponent : public juce::AudioAppComponent,
					  public juce::Button::Listener,
					  public juce::Slider::Listener


{
public:
	//==============================================================================
	MainComponent();
	~MainComponent();

	void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
	void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
	void releaseResources() override;
	void paint(juce::Graphics& g) override;
	void resized() override;
	void buttonClicked(juce::Button *)override;
	void sliderValueChanged(juce::Slider *slider)override;

private:
	//==============================================================================
	// Your private member variables go here...

	juce::AudioFormatManager formatManager;
	juce::AudioThumbnailCache thumbnailCache{ 100 };

	DJAudioPlayer player1{formatManager};
	DeckGUI deckGUI1{&player1,  formatManager, thumbnailCache };
	
	DJAudioPlayer player2{formatManager};
	DeckGUI deckGUI2{&player2,  formatManager, thumbnailCache };

	juce::MixerAudioSource mixerSource;

	juce::Slider crossFaderSlider;
	juce::Label crossFaderLabel;

	DJAudioPlayer player3{ formatManager };
	PlaylistComponent playlistComponent{ &player3,  formatManager, thumbnailCache };




	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};