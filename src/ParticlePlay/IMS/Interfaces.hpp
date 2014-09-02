#ifndef INTERFACES_HEADER
#define INTERFACES_HEADER

#include "../Includes.hpp"

class ppUpdatable {
public:
	virtual void Update();
};

class ppPlayable : public ppUpdatable {
protected:
	bool isPlaying;
	bool isPause;
	ppPlayable();
public:
	virtual ~ppPlayable();
	virtual void Play();
	virtual void Pause();
	virtual void Stop();
	virtual bool IsPause();
	virtual bool IsStop();
	virtual bool IsPlaying();
};

class ppClippable {
protected:
	Sint64 clipStart;
	Sint64 clipEnd;
	ppClippable();
public:
	void SetClipStart(Sint64 clipping);
	void SetClipEnd(Sint64 clipping);
	Sint64 GetClipStart();
	Sint64 GetClipEnd();
};

class ppOffsetable {
protected:
	Sint64 offset;
	ppOffsetable();
public:
	void SetOffset(Sint64 offset);
	Sint64 GetOffset();
};

class ppGenericSound : public ppPlayable, public ppClippable, public ppOffsetable {
protected:
	bool preload;
	int loop;
	float volume;
	float speed;
	ppGenericSound();
public:
	virtual ~ppGenericSound();
	virtual void Seek(Sint64 position)=0;
	virtual void Seek(float time)=0;
	virtual void SetLoop(int loop);
	virtual void SetVolume(float volume);
	virtual void SetSpeed(float speed);
	virtual Sint64 GetCurrentPosition()=0;
	virtual Sint64 GetPositionLength()=0;
	virtual float GetCurrentTime()=0;
	virtual float GetTotalTime()=0;
	virtual float GetVolume();
	virtual float GetSpeed();
	virtual bool IsLoop();
	virtual bool IsReady();
};

#endif
