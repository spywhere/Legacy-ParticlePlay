#ifndef IMS_HEADER
#define IMS_HEADER

#include "../Includes.hpp"
#include "Format/AudioFormat.hpp"
#include "Format/WaveFormat.hpp"
#include "Playlist.hpp"

class ppGame;
class ppIMS : public ppPlaylist {
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
