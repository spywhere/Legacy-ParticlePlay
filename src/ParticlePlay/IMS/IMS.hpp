#ifndef IMS_HEADER
#define IMS_HEADER

#include <map>
#include <vector>
#include "../Includes.hpp"

class ppGame;
class ppIMS {
protected:
	//// InteractiveMusicSystem will inherit from SoundSystem class
	bool preload;
	ALCdevice* device;
	ALCcontext* context;
public:
	ppIMS(ppGame* game);
	int Init();
	int Reinit();
	void Quit();
	void Update();
};

#endif
