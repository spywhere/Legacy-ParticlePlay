#ifndef STINGER_HEADER
#define STINGER_HEADER

#include <ParticlePlay/IMS/Interfaces.hpp>

enum class ppStingerTriggerPosition {
	IMMEDIATE, NEXT_BEAT, NEXT_BAR, ENTRY_CUE, EXIT_CUE
};

class ppStinger {
protected:
	bool prepare;
	bool trigger;
	ppGenericSound* sound;
	ppStingerTriggerPosition position;
public:
	ppStinger(ppGenericSound* sound, ppStingerTriggerPosition position);
	void PrepareTrigger();
	void Reset();
	void Trigger();
	bool IsPreparing();
	bool IsTriggering();
	float GetEntryCue();
	ppStingerTriggerPosition GetTriggerPosition();
	void Update();
};

#endif
