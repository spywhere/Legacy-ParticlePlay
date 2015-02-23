#ifndef RTPC_HEADER
#define RTPC_HEADER

#include <map>
#include <list>
#include "../Easings/Easing.hpp"
#include "Interfaces.hpp"

class ppGenericSound;
enum class ppRTPCEffect {
	PANNING, VOLUME, PITCH
};

class ppEffectInfo {
protected:
	ppEasing* easing;
	ppRTPCEffect effect;
public:
	ppEffectInfo(ppRTPCEffect effect, ppEasing* easing);
	ppEasing* GetCurve();
	ppRTPCEffect GetEffect();
};

class ppRTPC {
protected:
	float offset;
	std::map<ppGenericSound*, ppEffectInfo*> effects;
public:
	ppRTPC();
	void AddSound(ppGenericSound* sound, ppRTPCEffect effect, ppEasing* easing);
	void RemoveSound(ppGenericSound* sound);
	void SetOffset(float offset);
	ppEffectInfo* GetEffectInfo(ppGenericSound* sound);
	float GetOffset();
};

#endif
