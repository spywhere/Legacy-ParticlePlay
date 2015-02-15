#ifndef SOUND_HEADER
#define SOUND_HEADER

#include <list>
#include "Interfaces.hpp"
#include "../Randomizer.hpp"

enum class ppSoundPlayOrder {
	LOOP, SEQUENCE, RANDOM, SHUFFLE
};

class ppSound : public ppGenericSound {
protected:
	std::list<int> trackList;
	int track;
	int loadingTrack;
	int bufferSize;
	int totalBufferProcessed;
	Sint64 nextReadPosition;
	Sint64 startReadPosition;
	ALuint sourceID;
	ALuint bufferSet[2];
	ppSoundPlayOrder playOrder;
	ppRandomizer* randomizer;
	void GetNextTrack();
	int GetTotalBuffer(bool countCurrent);
public:
	ppSound(const char *name, ppFormat* audioFormat, int track, ppRandomizer* randomizer);
	~ppSound();
	int GetTrack();
	void SetPlayOrder(ppSoundPlayOrder playOrder);
	void SetTrack(int track);
	void Preload();
	ppSoundPlayOrder GetPlayOrder();

	//Playable
	void Play();
	void Pause();
	void StopDecay(bool decay);
	void Update();

	//Clippable
	void SetClipStart(Sint64 clipping);
	void SetClipEnd(Sint64 clipping);

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
