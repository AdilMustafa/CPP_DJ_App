/*
  ==============================================================================

    DJAudioPlayer.h
    Created: 22 Feb 2021 4:32:59pm
    Author:  adilm

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"


class DJAudioPlayer : public juce::AudioSource
{
public:
	DJAudioPlayer(juce::AudioFormatManager& _formatManager);
	~DJAudioPlayer();

	void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
	void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
	void releaseResources() override;

	void loadURL(juce::URL audioURL);
	void setGain(double gain);
	void setSpeed(double ratio);
	void setPosition(double posInSecs);
	void setPositionRelative(double pos);

	void start();
	void stop();
	void csv_test();
	
	double trackTimer();

	double getPositionRelative();
	/*
	void mouseDown(const juce::MouseEvent& e);
	void mouseDrag(const juce::MouseEvent& e);
	void mouseUp(const juce::MouseEvent&);
	bool canMoveTransport() const noexcept;
	*/

private:
	
	juce::AudioFormatManager& formatManager;
	std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
	juce::AudioTransportSource transportSource;
	juce::ResamplingAudioSource resampleSource{ &transportSource, false, 2 };
	//bool isFollowingTransport = false;

};
