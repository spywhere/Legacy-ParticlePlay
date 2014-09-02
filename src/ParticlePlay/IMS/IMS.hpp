#ifndef IMS_HEADER
#define IMS_HEADER

#include "../Includes.hpp"
#include <map>
#include "Format/AudioFormat.hpp"
#include "Format/Format.hpp"
#include "Format/WaveFormat.hpp"
#include "Playlist.hpp"
#include "Segment.hpp"
#include "Sound.hpp"

class ppGame;
class ppIMS {
protected:
	//// InteractiveMusicSystem will inherit from SoundSystem class
	bool preload;
	std::map<std::string, ppPlayable*> sounds;
	ALCdevice* device;
	ALCcontext* context;
public:
	ppIMS(ppGame* game);
	ppFormat *CreateFormat(ppAudioFormat audioFormat, const char *filename, bool stereo);
	ppFormat *CreateFormat(ppAudioFormat audioFormat, const char *filename);
	ppSound *CreateSound(const char *name, ppFormat* audioFormat, int track);
	ppSound *CreateSound(const char *name, ppFormat* audioFormat);
	ppSegment *CreateSegment(const char *name);
	ppPlaylist* CreatePlaylist(const char *name);
	int Init();
	int Reinit();
	void Quit();
	void Update();
};

#endif
