#ifndef SEGMENT_HEADER
#define SEGMENT_HEADER

#include "../Includes.hpp"
#include "IMS.hpp"
#include "Interfaces.hpp"
#include "Sound.hpp"
#include <list>

class ppSegment : public ppGenericSound {
protected:
	std::list<ppGenericSound *> sounds;
	ppIMS* ims;
	ppSound* emptySound;
public:
	ppSegment(const char *name, ppIMS* ims);
	~ppSegment();
	void AddSound(ppGenericSound *sound);
	void ClearSound();
	void Play();
	void Pause();
	void StopDecay(bool decay);
	void Update();
	void SetLoop(int loop);
	Sint64 GetCurrentPosition();
	Sint64 GetPositionLength();
	float GetCurrentTime();
	float GetTotalTime();
	bool IsLoop();
	bool IsPause();
	bool IsStop();
	bool IsPlaying();
	int GetLoop();
	int GetTotalSound();
	void Render(SDL_Renderer* renderer);
	void Update(ppInput* input);
	ppControlType GetType();
};

#endif
