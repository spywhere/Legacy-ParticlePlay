#ifndef CUBICOUTEASING_HEADER
#define CUBICOUTEASING_HEADER

#include <ParticlePlay/Easings/Easing.hpp>

class ppCubicOutEasing : public ppEasing {
public:
	float GetValue(float time, float duration, float begin, float changes);
};

#endif
