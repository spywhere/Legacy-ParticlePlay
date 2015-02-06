#ifndef INTERFACES_HEADER
#define INTERFACES_HEADER

#include "../Includes.hpp"
#include "../GUI/Control.hpp"
#include "Format/Format.hpp"

class ppUpdatable {
public:
	virtual void Update();
};

class ppPlayable : public ppUpdatable {
protected:
	bool isPlaying;
	bool isPause;
	Sint64 entryCue;
	Sint64 exitCue;
	ppPlayable();
public:
	virtual ~ppPlayable();
	virtual void Play();
	virtual void Pause();
	virtual void StopDecay(bool decay);
	virtual void Stop();
	virtual bool IsPause();
	virtual bool IsStop();
	virtual bool IsPlaying();
	virtual void SetEntryCue(Sint64 entryCue);
	virtual void SetExitCue(Sint64 exitCue);
	virtual Sint64 GetNormalExitCue();
	virtual Sint64 GetEntryCue();
	virtual Sint64 GetExitCue();
	virtual Sint64 GetCurrentPosition()=0;
	virtual Sint64 GetPositionLength()=0;
	virtual float GetCurrentTime()=0;
	virtual float GetTotalTime()=0;
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

class ppRhythmic {
protected:
	int rhythm;
public:
	ppRhythmic();
	void SetTimeSignature(int beats, int noteValue);
	void SetTempo(int bpm);
	virtual int GetTotalBeat(float time);
	virtual int GetCurrentBeat(float time);
	virtual int GetCurrentBar(float time);
	float GetTimeForBeat(int beat);
	float GetTimeForBar(int bar);
	float GetTimePerBeat();
	virtual int GetTotalBeat()=0;
	virtual int GetCurrentBeat()=0;
	virtual int GetCurrentBar()=0;
	int GetTempo();
	int GetBeatPerBar();
	int GetNoteValue();
};

class ppGenericSound : public ppRhythmic, public ppPlayable, public ppClippable, public ppOffsetable, public ppControl {
protected:
	bool preload;
	bool autoloop;
	int loop;
	float volume;
	float speed;
	ppFormat* audioFormat;
	ppGenericSound(const char *name);
public:
	virtual ~ppGenericSound();
	virtual int GetTotalBeat(float time);
	virtual int GetCurrentBeat(float time);
	virtual int GetCurrentBar(float time);
	virtual int GetTotalBeat();
	virtual int GetCurrentBeat();
	virtual int GetCurrentBar();
	virtual void Seek(Sint64 position);
	virtual void Seek(float time);
	virtual void SetLoop(int loop);
	virtual void SetAutoLoop(bool autoloop);
	virtual void SetVolume(float volume);
	virtual void SetSpeed(float speed);
	virtual float GetVolume();
	virtual float GetSpeed();
	virtual ppFormat *GetAudioFormat();
	virtual int GetLoop();
	virtual bool IsLoop();
	virtual bool IsAutoLoop();
	virtual bool IsReady();
	virtual void Update();
	virtual void Render(SDL_Renderer* renderer);
	virtual void Update(ppInput* input);
	virtual ppControlType GetType();
};

#endif
