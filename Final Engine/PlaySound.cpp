#include "PlaySound.h"
#include <iostream>

using namespace std;

//Loads the sound files
HSAMPLE Sound::loadSample(const char* filename, HSAMPLE sample)
{
	//Initialize default output device
	if (!BASS_Init(-1, 44100, 0, 0, NULL))
		cout << "Can't initialize device";

	HSAMPLE sam;
	if (sam = BASS_SampleLoad(FALSE, filename, 0, 0, 3, sample))
		cout << "sample " << filename << " loaded!" << endl;
	else
	{
		cout << "Can't load sample";
		exit(0);
	}
	return sam;
}

void Sound::playSample(HSAMPLE sample)
{
	HCHANNEL ch = BASS_SampleGetChannel(sample, FALSE); //chosing song
	BASS_ChannelSetAttribute(ch, BASS_ATTRIB_FREQ, 0);
	BASS_ChannelSetAttribute(ch, BASS_ATTRIB_VOL, 0.5);
	BASS_ChannelSetAttribute(ch, BASS_ATTRIB_PAN, -1);
	if (!BASS_ChannelPlay(ch, FALSE))
		cout << "Can't play sample" << endl;
}