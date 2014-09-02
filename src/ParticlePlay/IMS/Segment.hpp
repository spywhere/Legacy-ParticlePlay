#ifndef SEGMENT_HEADER
#define SEGMENT_HEADER

#include "../Includes.hpp"
#include "Interfaces.hpp"
#include "Sound.hpp"
#include <list>

class ppSegment : public ppPlayable, public ppClippable, public ppOffsetable {
protected:
	std::list<ppPlayable *> sounds;
public:
	ppSegment();
	void AddSound(ppPlayable *sound);
	void ClearSound();
	void Play();
	void Pause();
	void Stop();
	void Update();
};

#endif
