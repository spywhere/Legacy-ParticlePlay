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
class ppTransition {
protected:
	int priority;
	float sourceOffset;
	float sourceDuration;
	float destOffset;
	float destDuration;
	Uint32 sourceStartTime, sourceEndTime;
	Uint32 destStartTime, destEndTime;
	ppEasing* sourceEasing;
	ppEasing* destEasing;
	ppGenericSound* sourceSound;
	ppGenericSound* destSound;
	ppTransitionSourcePosition sourcePosition;
	ppTransitionDestinationPosition destPosition;
public:
	ppTransition(ppSwitch* sw, int priority, ppGenericSound* sourceSound, ppGenericSound* destSound);
	void SetSourceStartTime(ppSwitch* sw, Uint32 sourceStartTime);
	void SetDestinationStartTime(ppSwitch* sw, Uint32 destStartTime);
	void SetSourceEndTime(ppSwitch* sw, Uint32 sourceEndTime);
	void SetDestinationEndTime(ppSwitch* sw, Uint32 destEndTime);
	Uint32 GetSourceStartTime(ppSwitch* sw);
	Uint32 GetDestinationStartTime(ppSwitch* sw);
	Uint32 GetSourceEndTime(ppSwitch* sw);
	Uint32 GetDestinationEndTime(ppSwitch* sw);

	int GetPriority();
	bool IsSourceName(const char *name);
	bool IsDestinationName(const char *name);
	ppGenericSound* GetSource();
	ppGenericSound* GetDestination();
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
};

#endif
