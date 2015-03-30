#ifndef QUADEASING_HEADER
#define QUADEASING_HEADER

#include <ParticlePlay/Easings/Easing.hpp>

class ppQuadEasing : public ppEasing {
public:
	ppQuadEasing(float begin, float changes) : ppEasing(begin, changes){};
	ppQuadEasing() : ppEasing(){};
	float GetValue(float time, float duration, float begin, float changes);
};

#endif
