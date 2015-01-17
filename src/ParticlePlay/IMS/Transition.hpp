#ifndef TRANSITION_HEADER
#define TRANSITION_HEADER

#include "../Easings/Easing.hpp"
#include "Interfaces.hpp"
#include "Switch.hpp"

enum ppTransitionSourcePosition {
	IMMEDIATE, NEXT_BEAT, NEXT_BAR
};

enum ppTransitionDestinationPosition {
	ENTRY_CUE, SAME_TIME
};

class ppSwitch;
class ppTransition : public ppUpdatable {
protected:
	int priority;
	float sourceOffset;
	float sourceDuration;
	float destOffset;
	float destDuration;
	bool transitioning;
	Uint32 triggerTime;
	Uint32 syncPoint;
	ppEasing* sourceEasing;
	ppEasing* destEasing;
	ppGenericSound* actualSource;
	ppGenericSound* sourceSound;
	ppGenericSound* destSound;
	ppGenericSound* actualDest;
	ppTransitionSourcePosition sourcePosition;
	ppTransitionDestinationPosition destPosition;
public:
	ppTransition(ppSwitch* sw, int priority, ppGenericSound* sourceSound, ppGenericSound* destSound);
	virtual ~ppTransition();
	void Trigger(ppGenericSound* actualSource, ppGenericSound* actualDest);
	int GetPriority();
	bool IsTransitioning();
	bool IsSourceName(const char *name);
	bool IsDestinationName(const char *name);
	ppGenericSound* GetSource();
	ppGenericSound* GetDestination();
	ppGenericSound* GetActualSource();
	ppGenericSound* GetActualDestination();
	Uint32 GetTransitionPosition();
	Uint32 GetSyncPoint();
	void SetSourcePosition(ppTransitionSourcePosition sourcePosition);
	void SetDestinationPosition(ppTransitionDestinationPosition destPosition);

	void SetSourceOffset(float offset);
	void SetSourceDuration(float duration);
	void SetSourceCurve(ppEasing* easing);
	void SetDestinationOffset(float offset);
	void SetDestinationDuration(float duration);
	void SetDestinationCurve(ppEasing* easing);

	ppTransitionSourcePosition GetSourcePosition();
	float GetSourceOffset();
	float GetSourceDuration();
	ppEasing* GetSourceCurve();
	ppTransitionDestinationPosition GetDestinationPosition();
	float GetDestinationOffset();
	float GetDestinationDuration();
	ppEasing* GetDestinationCurve();

	void Update();
};

#endif
