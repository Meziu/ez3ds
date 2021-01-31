// Meziu here
// this code below is from my Lord and Saviour "MyLegGuy", who saved my soul from agony during difficult times
// thanks to him I got my hands on some *nice audio code*

// thank you MyLegGuy, very cool!


#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <3ds.h>
#include <ogg.h>
#include <codec.h>
#include <vorbisfile.h>


#define BYTESPERSAMPLE 2

#define MAXBUFFERSIZE 200000
#define SINGLEOGGREAD 4096
#define STUPIDSOUNDLOADINGMAXBUFFER 20

#define MUSICTYPE_NONE 0
#define MUSICTYPE_OGG 1
#define MUSICTYPE_MP3 2

typedef struct{
	void* _musicMainStruct; // Made with malloc, remember to free.
	char* _musicMusicBuffer[STUPIDSOUNDLOADINGMAXBUFFER]; // Only 2 used normally. Up STUPIDSOUNDLOADINGMAXBUFFER for single buffer sound effects
	ndspWaveBuf _musicWaveBuffer[STUPIDSOUNDLOADINGMAXBUFFER];
	char _musicIsTwoBuffers; // For sound effects, this is the number of buffers.
	unsigned char _musicChannel;
	unsigned char _musicShoudLoop;
	unsigned char _musicType;
	char _musicIsDone;
}NathanMusic;

char nathanInit3dsSound();

signed char decoreMoreOGG(OggVorbis_File* _passedOggFile, char* _passedAudioBuffer, char _passedShouldLoop, u64* _soundBufferWriteOffset);
int nathanGetMusicNumberOfChannels(NathanMusic* _passedMusic);
signed char nathannathanUpdateAudioBufferNathanMusic(NathanMusic* _passedMusic, int _passedBufferNumber);
long nathanGetMusicRate(NathanMusic* _passedMusic);
unsigned char getMusicType(char* _filename);

void nathanLoadMusic(NathanMusic* _passedMusic, char* _filename, unsigned char _passedShouldLoop);
void nathanLoadSoundEffect(NathanMusic* _passedMusic, char* _filename);

void nathanQueueMusic3ds(ndspWaveBuf* _musicToPlay, int _channelNumber);

void nathanMakeChannelMono(int _channelNumber);
void nathanMakeChannelStereo(int _channelNumber);
char nathanSetChannelFormat(int _channelNumber, int _numberOfChannels);
void nathanSetChannelVolume(int _channelNumber, float _volume);
void nathanInit3dsChannel(int _channelNumber);
void nathanSetChannelForMusic(int _channelNumber, NathanMusic* _passedMusic);
void stopChannel(int _channelNumber);

void nathanPlayMusic(NathanMusic* _passedMusic, unsigned char _channelNumber);
void nathanPlaySound(NathanMusic* _passedMusic, unsigned char _channelNumber);

void nathanUpdateMusicIfNeeded(NathanMusic* _passedMusic);

void nathanFreeMusic(NathanMusic* _passedMusic);
void nathanFreeSound(NathanMusic* _passedMusic);
