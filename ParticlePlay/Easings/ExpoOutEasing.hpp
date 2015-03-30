#ifndef EXPOOUTEASING_HEADER
#define EXPOOUTEASING_HEADER

#include <ParticlePlay/Easings/Easing.hpp>

class ppExpoOutEasing : public ppEasing {
public:
	ppExpoOutEasing(float begin, float changes) : ppEasing(begin, changes){};
	ppExpoOutEasing() : ppEasing(){};
	float GetValue(float time, float duration, float begin, float changes);
};

#endif
