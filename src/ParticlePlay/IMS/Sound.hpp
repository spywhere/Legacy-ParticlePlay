#ifndef SOUND_HEADER
#define SOUND_HEADER

#include "../GUI/Control.hpp"
#include "Format/Format.hpp"
#include "Interfaces.hpp"
#include <list>
#include <ctime>
#include <cstdlib>

enum class ppSoundPlayOrder {
	LOOP, SEQUENCE, RANDOM, SHUFFLE
};

class ppSound : public ppGenericSound, public ppControl {
protected:
	std::list<int> trackList;
	int track;
	int loadingTrack;
	int bufferSize;
	int totalBufferProcessed;
	Sint64 nextReadPosition;
	Sint64 startReadPosition;
	ppFormat* audioFormat;
	ALuint sourceID;
	ALuint bufferSet[2];
	ppSoundPlayOrder playOrder;
	void GetNextTrack();
	int GetTotalBuffer(bool countCurrent);
public:
	ppSound(const char *name, ppFormat* audioFormat, int track);
	~ppSound();
	int GetTrack();
	ppFormat *GetAudioFormat();
	void SetPlayOrder(ppSoundPlayOrder playOrder);
	void SetTrack(int track);
	void Preload();

	//Playable
	void Play();
	void Stop();
	void Update();

	//GenericSound
	void Seek(Sint64 position);
	void Seek(float time);
	void SetVolume(float volume);
	void SetSpeed(float speed);
	Sint64 GetCurrentPosition();
	Sint64 GetPositionLength();
	float GetCurrentTime();
	float GetTotalTime();

	//Control
	void Render(SDL_Renderer* renderer);
	void Update(ppInput* input);
	ppControlType GetType();
};

#endif
