#ifndef STINGER_HEADER
#define STINGER_HEADER

#include <ParticlePlay/IMS/Interfaces.hpp>

enum class ppStingerTriggerPosition {
	IMMEDIATE, NEXT_BEAT, NEXT_BAR
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
	void Trigger();
	bool IsPreparing();
	bool IsTriggering();
	ppStingerTriggerPosition GetTriggerPosition();
	void Update();
};

#endif
