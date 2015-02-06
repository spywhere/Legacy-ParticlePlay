#ifndef PLAYLIST_HEADER
#define PLAYLIST_HEADER

#include <list>
#include "Interfaces.hpp"
#include "../Randomizer.hpp"

enum ppPlaylistPlayOrder {
	SEQUENCE_CONTINUOUS, SHUFFLE_CONTINUOUS, SEQUENCE_STEP, SHUFFLE_STEP
};

class ppPlaylist : public ppGenericSound {
protected:
	std::list<ppGenericSound*> sounds;
	std::list<ppGenericSound*> soundOrder;
	std::list<ppGenericSound*> queue;
	ppGenericSound *current;
	ppGenericSound *next;
	Sint64 playDuration;
	ppPlaylistPlayOrder playOrder;
	ppRandomizer* randomizer;
	void SoftStop(bool decay, bool reset);
public:
	ppPlaylist(const char *name, ppRandomizer* randomizer);
	void AddSound(ppGenericSound *sound);
	void ClearSound();
	void SetPlayOrder(ppPlaylistPlayOrder playOrder);
	ppPlaylistPlayOrder GetPlayOrder();

	ppGenericSound* GetPlayingSound();
	ppGenericSound* GetSoundAtIndex(int index);
	int GetTotalSound();

	void Play();
	void Pause();
	void StopDecay(bool decay);

	void Update();
	void SetVolume(float volume);
	void SetSpeed(float speed);
	void SetTempo(int bpm);
	Sint64 GetEntryCue();
	Sint64 GetExitCue();
	Sint64 GetCurrentPosition();
	Sint64 GetPositionLength();
	float GetCurrentTime();
	float GetTotalTime();

	//Control
	void Render(SDL_Renderer* renderer);
	void Update(ppInput* input);
	ppControlType GetType();
};

#endif
