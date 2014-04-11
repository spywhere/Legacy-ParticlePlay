#ifndef IMS_HEADER
#define IMS_HEADER

#include <map>
#include <vector>
#include "../Includes.h"
#include "Sound.h"
#include "Filters.h"

class ppGame;
class ppSound;
class ppIMS {
private:
	//// InteractiveMusicSystem will inherit from SoundSystem class
	bool preload;
	ALCdevice* device;
	ALCcontext* context;
	std::vector<ppFilter*> filters;
	std::map<std::string, ppSound*> sounds;
public:
	ppIMS(ppGame* game);
	int Init();
	int Reinit();
	void Quit();
	ppSound* NewSound(const char *refname, const char *filename);
	ppSound* NewSound(const char *refname, const char *filename, int track);
	ppSound* NewSound(const char *refname, const char *filename, int track, bool stereo);
	ppFilter* NewFilter(ppFilterType filterType);
	ppSound* GetSound(const char *refname);
	void RemoveSound(const char *refname);
	void ClearFilter();
	void ClearSound();
	//Sound-related actions
	void Preload();
	void ApplyFilter(ppFilter* filter);
	void Play();
	void Pause();
	void Stop();
	void SeekPosition(int targetPosition);
	void SeekTime(float targetTime);
	void SetSpeed(float speed);
	void SetVolumn(float vol);
	void SetLoop(bool loop);
	void Update();
};

#endif
