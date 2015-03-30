#ifndef SEGMENT_HEADER
#define SEGMENT_HEADER

#include <list>
#include <ParticlePlay/Includes.hpp>
#include <ParticlePlay/IMS/IMS.hpp>
#include <ParticlePlay/IMS/Interfaces.hpp>
#include <ParticlePlay/IMS/Sound.hpp>

class ppSegment : public ppGenericSound {
protected:
	std::list<ppGenericSound *> sounds;
	ppIMS* ims;
	ppSound* emptySound;
public:
	ppSegment(const char *name, ppIMS* ims);
	~ppSegment();
	void AddSound(ppGenericSound *sound);
	void ClearSound();
	void Play();
	void Pause();
	void StopDecay(bool decay);
	void Update();
	void Seek(float time);
	void SetVolume(float volume);
	void SetSpeed(float speed);
	void SetLoop(int loop);
	Sint64 GetCurrentPosition();
	Sint64 GetPositionLength();
	float GetCurrentTime();
	float GetTotalTime();
	bool IsLoop();
	bool IsPause();
	bool IsStop();
	bool IsPlaying();
	int GetLoop();
	int GetTotalSound();
	void Render(SDL_Renderer* renderer);
	void Update(ppInput* input);
	ppControlType GetType();
	ALuint GetSourceID();
	void AddRTPC(ppRTPC* rtpc, ppRTPCEffect effect, ppEasing* easing);
	void RemoveRTPC(ppRTPC* rtpc);
	void SetFilter(ppFilter* filter);
};

#endif
