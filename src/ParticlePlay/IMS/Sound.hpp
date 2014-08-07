#ifndef SOUND_HEADER
#define SOUND_HEADER

#include "../GUI/Control.hpp"
#include "Format/Format.hpp"

class ppSound : public ppControl {
protected:
	int track;
	bool preload;
	bool stop;
	bool pause;
	bool loop;
	int bufferSize;
	int totalBufferProcessed;
	float volume, speed;
	Sint64 nextReadPosition;
	Sint64 startReadPosition;
	ppFormat* audioFormat;
	ALuint sourceID;
	ALuint bufferSet[2];
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
	void SetLoop(bool loop);
	void SetVolume(float volume);
	void SetSpeed(float speed);
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
