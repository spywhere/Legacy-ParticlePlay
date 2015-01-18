#ifndef TIMELISTENER_HEADER
#define TIMELISTENER_HEADER

#include "Interfaces.hpp"

class ppTimeListenerCallback {
public:
	virtual void OnBar(ppGenericSound* source);
	virtual void OnBeat(ppGenericSound* source);
	virtual void OnNextCue(ppGenericSound* source);
	virtual void OnExitCue(ppGenericSound* source);
};

class ppTimeListener : public ppUpdatable {
protected:
	int currentBeat;
	int currentBar;
	ppGenericSound* source;
	ppTimeListenerCallback* callback;
public:
	ppTimeListener(ppGenericSound* source, ppTimeListenerCallback* callback);
	void Update();
};

#endif
