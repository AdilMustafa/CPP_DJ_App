/*
  ==============================================================================

	DJAudioPlayer.cpp
	Created: 22 Feb 2021 4:32:59pm
	Author:  adilm

  ==============================================================================
*/

#include "DJAudioPlayer.h"
#include "csv.h"

//----------------------------------------------------------------------------------------
DJAudioPlayer::DJAudioPlayer(juce::AudioFormatManager& _formatManager)
	:
	formatManager(_formatManager)
{

};

//----------------------------------------------------------------------------------------
DJAudioPlayer::~DJAudioPlayer()
{

};

//----------------------------------------------------------------------------------------
void DJAudioPlayer::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
	//formatManager.registerBasicFormats();
	transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
	resampleSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
};


//----------------------------------------------------------------------------------------
void DJAudioPlayer::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{

	//transportSource.setLooping(true);
	//transportSource.isLooping();
	resampleSource.getNextAudioBlock(bufferToFill);


};


//----------------------------------------------------------------------------------------
void DJAudioPlayer::releaseResources()
{
	transportSource.releaseResources();
	resampleSource.releaseResources();
};


//----------------------------------------------------------------------------------------
void DJAudioPlayer::loadURL(juce::URL audioURL)
{
	auto* reader = formatManager.createReaderFor(audioURL.createInputStream(false));
	if (reader != nullptr) {
		std::unique_ptr<juce::AudioFormatReaderSource> newSource(new juce::AudioFormatReaderSource(reader, true));
		//newSource->setLooping(true);
		transportSource.setSource(newSource.get(), 0, nullptr, reader->sampleRate);
		readerSource.reset(newSource.release());
	};
};


//----------------------------------------------------------------------------------------
void DJAudioPlayer::setGain(double gain)
{
	if (gain < 0 || gain > 1.0)
	{
		DBG("DJAudioPlayer::setGain gain should be between 0 and 1");
	}
	else
	{
		transportSource.setGain(gain);
	}
};


//----------------------------------------------------------------------------------------
void DJAudioPlayer::setSpeed(double ratio)
{
	if (ratio < 0 || ratio > 100.0)
	{
		DBG("DJAudioPlayer::setSpeed ratio should be between 0 and 1");
	}
	else
	{
		resampleSource.setResamplingRatio(ratio);
	}
};


//----------------------------------------------------------------------------------------
void DJAudioPlayer::setPosition(double posInSecs)
{
	transportSource.setPosition(posInSecs);
};

//----------------------------------------------------------------------------------------
void DJAudioPlayer::setPositionRelative(double pos)
{
	if (pos < 0 || pos > 1.0)
	{
		DBG("DJAudioPlayer::setPositionRelative pos should be between 0 and 1");
	}
	else
	{
		double posInSecs = transportSource.getLengthInSeconds() * pos;
		setPosition(posInSecs);
	}
};


//----------------------------------------------------------------------------------------
void DJAudioPlayer::start()
{
	//transportSource.setLooping(true);
	//transportSource.isLooping();
	transportSource.start();
	/*
	transportSource.setLooping(true);
	if(transportSource.getCurrentPosition() >=  transportSource.getTotalLength())
	{
		transportSource.isLooping();
	}

	else
	{
		transportSource.start();

	}

	*/
};


//----------------------------------------------------------------------------------------
void DJAudioPlayer::stop()
{
	transportSource.stop();
};


double DJAudioPlayer::getPositionRelative()
{
	return transportSource.getCurrentPosition() / transportSource.getLengthInSeconds();
};

double DJAudioPlayer::trackTimer()
{
	double trackTimerInSeconds = transportSource.getCurrentPosition();

	return trackTimerInSeconds;



};

void DJAudioPlayer::csv_test()
{
	std::string filename{ "C:/Users/adilm/Desktop/juce-6.0.7-windows/JUCE/myModules/DJ_App_Lab2/Source/playlist.csv" };
	std::vector<std::vector<std::string>> playlist =
	CSVReader::readCSV(filename);
}