#ifndef IMS_HEADER
#define IMS_HEADER

#include <map>
#include "Includes.h"
#include "Sound.h"
#include "Filter.h"

class Sound;
class IMS {
private:
	//// InteractiveMusicSystem will inherit from SoundSystem class
	bool preload;
	ALCdevice* device;
	ALCcontext* context;
	std::map<std::string, Sound*> sounds;
public:
	IMS();
	~IMS();
	Sound* NewSound(const char *refname, const char *filename);
	Sound* NewSound(const char *refname, const char *filename, int track);
	Sound* NewSound(const char *refname, const char *filename, int track, bool stereo);
	Sound* GetSound(const char *refname);
	void RemoveSound(const char *refname);
	//Sound-related actions
	void Preload();
	void ApplyFilter(Filter* filter);
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
