#ifndef ELASTICEASING_HEADER
#define ELASTICEASING_HEADER

#include <ParticlePlay/Easings/Easing.hpp>

class ppElasticEasing : public ppEasing {
public:
	ppElasticEasing(float begin, float changes) : ppEasing(begin, changes){};
	ppElasticEasing() : ppEasing(){};
	float GetValue(float time, float duration, float begin, float changes);
};

#endif
