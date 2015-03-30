#ifndef EXPOEASING_HEADER
#define EXPOEASING_HEADER

#include <ParticlePlay/Easings/Easing.hpp>

class ppExpoEasing : public ppEasing {
public:
	ppExpoEasing(float begin, float changes) : ppEasing(begin, changes){};
	ppExpoEasing() : ppEasing(){};
	float GetValue(float time, float duration, float begin, float changes);
};

#endif
