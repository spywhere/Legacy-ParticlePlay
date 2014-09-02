#ifndef PLAYLIST_HEADER
#define PLAYLIST_HEADER

#include <list>
#include "Interfaces.hpp"

class ppPlaylist : public ppPlayable {
protected:
	std::list<ppPlayable*> sounds;
public:
	ppPlaylist();
	void AddSound(ppPlayable *sound);
	void ClearSound();
	void Update();
};

#endif
