#ifndef TIMELISTENER_HEADER
#define TIMELISTENER_HEADER

#include <ParticlePlay/IMS/Interfaces.hpp>

class ppTimeListenerCallback {
public:
	virtual void OnBar(ppGenericSound* source);
	virtual void OnBeat(ppGenericSound* source);
	virtual void OnEntryCue(ppGenericSound* source);
	virtual void OnExitCue(ppGenericSound* source);
};

class ppTimeListener : public ppUpdatable {
protected:
	float offset;
	int currentBeat;
	int currentBar;
	int entryCooldown;
	int exitCooldown;
	ppGenericSound* source;
	ppTimeListenerCallback* callback;
public:
	ppTimeListener(ppGenericSound* source, ppTimeListenerCallback* callback);
	void SetOffset(float offset);
	void Update();
};

#endif
