#ifndef CIRCOUTEASING_HEADER
#define CIRCOUTEASING_HEADER

#include <ParticlePlay/Easings/Easing.hpp>

class ppCircOutEasing : public ppEasing {
public:
	float GetValue(float time, float duration, float begin, float changes);
};

#endif
