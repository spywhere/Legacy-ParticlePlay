#ifndef CUBICINEASING_HEADER
#define CUBICINEASING_HEADER

#include <ParticlePlay/Easings/Easing.hpp>

class ppCubicInEasing : public ppEasing {
public:
	ppCubicInEasing(float begin, float changes) : ppEasing(begin, changes){};
	ppCubicInEasing() : ppEasing(){};
	float GetValue(float time, float duration, float begin, float changes);
};

#endif
