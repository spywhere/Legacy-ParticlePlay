#ifndef IMS_HEADER
#define IMS_HEADER

#include <map>
#include "../Includes.h"
#include "Sound.h"
#include "Filter.h"

class ppSound;
class ppIMS {
private:
	//// InteractiveMusicSystem will inherit from SoundSystem class
	bool preload;
	ALCdevice* device;
	ALCcontext* context;
	std::map<std::string, ppSound*> sounds;
public:
	ppIMS();
	int Init();
	void Quit();
	ppSound* NewSound(const char *refname, const char *filename);
	ppSound* NewSound(const char *refname, const char *filename, int track);
	ppSound* NewSound(const char *refname, const char *filename, int track, bool stereo);
	ppSound* GetSound(const char *refname);
	void RemoveSound(const char *refname);
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
