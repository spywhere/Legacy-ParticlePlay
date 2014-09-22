#ifndef PLAYLIST_HEADER
#define PLAYLIST_HEADER

#include <list>
#include "Interfaces.hpp"

class ppPlaylist : public ppGenericSound {
protected:
	std::list<ppGenericSound*> sounds;
	std::list<ppGenericSound*> queue;
	ppGenericSound *current;
	ppGenericSound *next;
	Sint64 playDuration;
public:
	ppPlaylist(const char *name);
	void AddSound(ppGenericSound *sound);
	void ClearSound();

	void Play();
	void Stop();

	void Update();
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
