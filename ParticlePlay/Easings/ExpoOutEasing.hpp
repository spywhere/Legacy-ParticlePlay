#ifndef EXPOOUTEASING_HEADER
#define EXPOOUTEASING_HEADER

#include <ParticlePlay/Easings/Easing.hpp>

class ppExpoOutEasing : public ppEasing {
public:
	float GetValue(float time, float duration, float begin, float changes);
};

#endif
