#ifndef PLAYLIST_HEADER
#define PLAYLIST_HEADER

#include <map>
#include <string>
#include "Format/Format.hpp"
#include "Sound.hpp"

class ppPlaylist {
protected:
	std::string name;
	std::map<std::string, ppSound*> sounds;
	std::map<std::string, ppPlaylist*> playlists;
public:
	ppPlaylist(const char *name);
	virtual ppSound* NewSound(const char *name, ppFormat* audioFormat, int track);
	virtual ppSound* NewSound(const char *name, ppFormat* audioFormat);
	virtual ppPlaylist* NewPlaylist(const char *name);
	virtual ppSound* GetSound(const char *name);
	virtual ppPlaylist* GetPlaylist(const char *name);
	virtual void RemoveSound(const char *name);
	virtual void RemovePlaylist(const char *name);
	virtual void ClearSound();
	virtual void ClearPlaylist();
	virtual void Update();
};

#endif
