#ifndef QUINTINEASING_HEADER
#define QUINTINEASING_HEADER

#include <ParticlePlay/Easings/Easing.hpp>

class ppQuintInEasing : public ppEasing {
public:
	ppQuintInEasing(float begin, float changes) : ppEasing(begin, changes){};
	ppQuintInEasing() : ppEasing(){};
	float GetValue(float time, float duration, float begin, float changes);
};

#endif
