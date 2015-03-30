#ifndef CUBICOUTEASING_HEADER
#define CUBICOUTEASING_HEADER

#include <ParticlePlay/Easings/Easing.hpp>

class ppCubicOutEasing : public ppEasing {
public:
	ppCubicOutEasing(float begin, float changes) : ppEasing(begin, changes){};
	ppCubicOutEasing() : ppEasing(){};
	float GetValue(float time, float duration, float begin, float changes);
};

#endif
