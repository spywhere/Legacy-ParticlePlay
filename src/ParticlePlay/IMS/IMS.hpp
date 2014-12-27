#ifndef IMS_HEADER
#define IMS_HEADER

#include "../Includes.hpp"
#include "../Randomizer.hpp"
#include <map>
#include <list>
#include "Format/AudioFormat.hpp"
#include "Format/Format.hpp"
#include "Format/EmptyFormat.hpp"
#include "Format/WaveFormat.hpp"
#include "Playlist.hpp"
#include "Segment.hpp"
#include "Sound.hpp"
#include "Switch.hpp"

class ppSegment;
class ppSwitch;
class ppGame;
class ppIMS {
protected:
	//// InteractiveMusicSystem will inherit from SoundSystem class
	bool preload;
	std::map<std::string, ppGenericSound*> sounds;
	std::map<std::string, ppSwitch*> switches;
	std::list<ppFormat*> formats;
	ALCdevice* device;
	ALCcontext* context;
	ppRandomizer* randomizer;
public:
	ppIMS(ppGame* game, ppRandomizer* randomizer);
	ppRandomizer* GetRandomizer();
	ppFormat* CreateEmptyFormat(Sint64 length, ppFormat* audioFormat, bool stereo);
	ppFormat* CreateEmptyFormat(Sint64 length, ppFormat* audioFormat);
	ppFormat* CreateFormat(ppAudioFormat audioFormat, const char *filename, bool stereo);
	ppFormat* CreateFormat(ppAudioFormat audioFormat, const char *filename);
	ppSound* CreateSound(const char *name, ppFormat* audioFormat, int track);
	ppSound* CreateSound(const char *name, ppFormat* audioFormat);
	ppSegment* CreateSegment(const char *name);
	ppSwitch* CreateSwitch(const char *name);
	ppPlaylist* CreatePlaylist(const char *name);
	ppGenericSound* GetSound(const char *name);
	ppSwitch* GetSwitch(const char *name);
	void RemoveSound(const char *name);
	void RemoveSwitch(const char *name);
	void ClearSound();
	void ClearSwitch();
	int Init();
	int Reinit();
	void Quit();
	void Update();
};

#endif
