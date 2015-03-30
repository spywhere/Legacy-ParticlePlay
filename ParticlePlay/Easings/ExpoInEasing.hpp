#ifndef EXPOINEASING_HEADER
#define EXPOINEASING_HEADER

#include <ParticlePlay/Easings/Easing.hpp>

class ppExpoInEasing : public ppEasing {
public:
	ppExpoInEasing(float begin, float changes) : ppEasing(begin, changes){};
	ppExpoInEasing() : ppEasing(){};
	float GetValue(float time, float duration, float begin, float changes);
};

#endif
