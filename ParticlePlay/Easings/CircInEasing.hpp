#ifndef CIRCINEASING_HEADER
#define CIRCINEASING_HEADER

#include <ParticlePlay/Easings/Easing.hpp>

class ppCircInEasing : public ppEasing {
public:
	ppCircInEasing(float begin, float changes) : ppEasing(begin, changes){};
	ppCircInEasing() : ppEasing(){};
	float GetValue(float time, float duration, float begin, float changes);
};

#endif
