#ifndef IMS_HEADER
#define IMS_HEADER

#include <map>
#include <vector>
#include "../Includes.hpp"
#include "Format/AudioFormat.hpp"
#include "Format/WaveFormat.hpp"

//Pre-included
#include "Sound.hpp"

class ppGame;
class ppIMS {
protected:
	//// InteractiveMusicSystem will inherit from SoundSystem class
	bool preload;
	ALCdevice* device;
	ALCcontext* context;
public:
	ppIMS(ppGame* game);
	ppFormat *CreateFormat(ppAudioFormat audioFormat, const char *filename, bool stereo);
	int Init();
	int Reinit();
	void Quit();
	void Update();
};

#endif
