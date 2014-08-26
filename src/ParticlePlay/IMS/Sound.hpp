#ifndef SOUND_HEADER
#define SOUND_HEADER

#include "../GUI/Control.hpp"
#include "Format/Format.hpp"
#include <list>
#include <ctime>
#include <cstdlib>

enum class ppSoundPlayOrder{
	LOOP, SEQUENCE, RANDOM, SHUFFLE
};

class ppSound : public ppControl {
protected:
	std::list<int> trackList;
	int track;
	int loadingTrack;
	bool preload;
	bool stop;
	bool pause;
	int loop;
	int bufferSize;
	int totalBufferProcessed;
	float volume, speed;
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
	Sint64 GetCurrentPosition();
	Sint64 GetPositionLength();
	float GetCurrentTime();
	float GetTotalTime();
	int GetTrack();
	ppFormat *GetAudioFormat();
	float GetVolume();
	float GetSpeed();

	void Seek(Sint64 position);
	void Seek(float time);
	void SetLoop(int loop);
	void SetVolume(float volume);
	void SetSpeed(float speed);
	void SetPlayOrder(ppSoundPlayOrder playOrder);
	void SetTrack(int track);
	bool IsLoop();
	bool IsReady();
	bool IsStop();
	void Preload();
	void Stop();
	void Play();
	void Update();

	void Render(SDL_Renderer* renderer);
	void Update(ppInput* input);
	ppControlType GetType();
};

#endif
