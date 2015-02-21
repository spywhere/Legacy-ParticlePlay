#ifndef RTPC_HEADER
#define RTPC_HEADER

#include <map>
#include <list>
#include "../Easings/Easing.hpp"
#include "Interfaces.hpp"

class ppGenericSound;
class ppGraphCurve {
protected:
	ppEasing* easing;
	float offset;
public:
	ppGraphCurve(float offset, ppEasing* easing);
	ppEasing* GetCurve();
	float GetOffset();
};

enum class ppRTPCEffect {
	PANNING, VOLUME, PITCH
};

class ppEffectInfo {
protected:
	float value;
	ppRTPCEffect effect;
public:
	ppEffectInfo(float value, ppRTPCEffect effect);
	float GetValue();
	ppRTPCEffect GetEffect();
};

class ppRTPC {
protected:
	float offset;
	std::map<ppGenericSound*, ppRTPCEffect> effects;
	std::list<ppGraphCurve*> curves;
	static bool GraphCurveSorter(ppGraphCurve* curve1, ppGraphCurve* curve2);
public:
	ppRTPC();
	void AddMidPoint(float offset, ppEasing* easing);
	void AddSound(ppGenericSound* sound, ppRTPCEffect effect);
	void RemoveSound(ppGenericSound* sound);
	void SetOffset(float offset);
	ppEffectInfo* GetEffectInfo(ppGenericSound* sound);
	float GetOffset();
};

#endif
