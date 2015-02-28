#ifndef CUBICINEASING_HEADER
#define CUBICINEASING_HEADER

#include <ParticlePlay/Easings/Easing.hpp>

class ppCubicInEasing : public ppEasing {
public:
	float GetValue(float time, float duration, float begin, float changes);
};

#endif
