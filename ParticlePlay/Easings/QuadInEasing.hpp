#ifndef QUADINEASING_HEADER
#define QUADINEASING_HEADER

#include <ParticlePlay/Easings/Easing.hpp>

class ppQuadInEasing : public ppEasing {
public:
	ppQuadInEasing(float begin, float changes) : ppEasing(begin, changes){};
	ppQuadInEasing() : ppEasing(){};
	float GetValue(float time, float duration, float begin, float changes);
};

#endif
