#ifndef PLAYLIST_HEADER
#define PLAYLIST_HEADER

#include <list>
#include "Interfaces.hpp"

class ppPlaylist : public ppGenericSound {
protected:
	std::list<ppGenericSound*> sounds;
public:
	ppPlaylist();
	void AddSound(ppGenericSound *sound);
	void ClearSound();
	void Update();
	Sint64 GetCurrentPosition();
	Sint64 GetPositionLength();
	float GetCurrentTime();
	float GetTotalTime();
};

#endif
