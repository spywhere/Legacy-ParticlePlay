#ifndef SOUND_HEADER
#define SOUND_HEADER

#include "../GUI/Control.hpp"
#include "Format/Format.hpp"

class ppSound : public ppControl {
protected:
	int track;
	bool stop;
	bool pause;
	int bufferSize;
	ppFormat* audioFormat;
	ALuint sourceID;
	ALuint bufferSet[2];
public:
	ppSound(const char *name, ppFormat* audioFormat, int track);
	int GetCurrentPosition();
	int GetPositionLength();
	float GetCurrentTime();
	float GetTotalTime();
	int GetTrack();
	ppFormat *GetAudioFormat();

	void Preload();

	void Render(SDL_Renderer* renderer);
	void Update(ppInput* input);
	ppControlType GetType();
};

#endif
