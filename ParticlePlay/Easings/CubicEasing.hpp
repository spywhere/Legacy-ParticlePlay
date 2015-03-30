#ifndef CUBICEASING_HEADER
#define CUBICEASING_HEADER

#include <ParticlePlay/Easings/Easing.hpp>

class ppCubicEasing : public ppEasing {
public:
	ppCubicEasing(float begin, float changes) : ppEasing(begin, changes){};
	ppCubicEasing() : ppEasing(){};
	float GetValue(float time, float duration, float begin, float changes);
};

#endif
