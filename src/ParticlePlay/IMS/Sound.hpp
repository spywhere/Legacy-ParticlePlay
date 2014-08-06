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
	int bufferSize;
	int totalBufferProcessed;
	Sint64 nextReadPosition;
	ppFormat* audioFormat;
	ALuint sourceID;
	ALuint bufferSet[2];
public:
	ppSound(const char *name, ppFormat* audioFormat, int track);
	~ppSound();
	Sint64 GetCurrentPosition();
	int GetPositionLength();
	float GetCurrentTime();
	float GetTotalTime();
	int GetTrack();
	ppFormat *GetAudioFormat();

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
