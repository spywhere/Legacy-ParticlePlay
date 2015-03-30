#ifndef ELASTICINEASING_HEADER
#define ELASTICINEASING_HEADER

#include <ParticlePlay/Easings/Easing.hpp>

class ppElasticInEasing : public ppEasing {
public:
	ppElasticInEasing(float begin, float changes) : ppEasing(begin, changes){};
	ppElasticInEasing() : ppEasing(){};
	float GetValue(float time, float duration, float begin, float changes);
};

#endif
