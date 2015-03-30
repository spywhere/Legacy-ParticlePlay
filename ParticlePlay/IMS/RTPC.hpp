#ifndef RTPC_HEADER
#define RTPC_HEADER

#include <ParticlePlay/Easings/Easing.hpp>

enum class ppRTPCEffect {
	PANNING, PITCH, GAIN, GAINHF, GAINLF
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

class ppIMS;
class ppRTPC {
protected:
	float offset;
public:
	ppRTPC(ppIMS* ims);
	void SetOffset(float offset);
	float GetOffset();
};

#endif
