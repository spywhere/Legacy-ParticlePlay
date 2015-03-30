#ifndef IMS_HEADER
#define IMS_HEADER

#include <map>
#include <list>
#include <ParticlePlay/Includes.hpp>
#include <ParticlePlay/Core/Randomizer.hpp>
#include <ParticlePlay/IMS/Format/AudioFormat.hpp>
#include <ParticlePlay/IMS/Format/Format.hpp>
#include <ParticlePlay/IMS/Format/EmptyFormat.hpp>
#include <ParticlePlay/IMS/Format/WaveFormat.hpp>
#include <ParticlePlay/IMS/Playlist.hpp>
#include <ParticlePlay/IMS/Segment.hpp>
#include <ParticlePlay/IMS/Sound.hpp>
#include <ParticlePlay/IMS/Switch.hpp>
#include <ParticlePlay/IMS/RTPC.hpp>
#include <ParticlePlay/IMS/Filter.hpp>
#include <ParticlePlay/IMS/Filter/Filters.hpp>

class ppSegment;
class ppSwitch;
class ppGame;
class ppIMS {
protected:
	//// InteractiveMusicSystem will inherit from SoundSystem class
	bool preload;
	std::map<std::string, ppGenericSound*> sounds;
	std::map<std::string, ppSwitch*> switches;
	std::map<std::string, ppFilter*> filters;
	std::map<std::string, ppRTPC*> rtpcs;
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
	ppFilter* CreateFilter(const char *name, ppFilterType filterType);
	ppRTPC* CreateRTPC(const char *name);
	ppPlaylist* CreatePlaylist(const char *name);
	ppGenericSound* GetSound(const char *name);
	ppSwitch* GetSwitch(const char *name);
	ppFilter* GetFilter(const char *name);
	ppRTPC* GetRTPC(const char *name);
	void RemoveSound(const char *name);
	void RemoveSwitch(const char *name);
	void ClearSound();
	void ClearSwitch();
	void ClearFilter();
	void ClearRTPC();
	int Init();
	int Reinit();
	void Quit();
	void Update();
};

#endif
