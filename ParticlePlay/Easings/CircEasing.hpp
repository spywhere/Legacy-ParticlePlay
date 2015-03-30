#ifndef CIRCEASING_HEADER
#define CIRCEASING_HEADER

#include <ParticlePlay/Easings/Easing.hpp>

class ppCircEasing : public ppEasing {
public:
	ppCircEasing(float begin, float changes) : ppEasing(begin, changes){};
	ppCircEasing() : ppEasing(){};
	float GetValue(float time, float duration, float begin, float changes);
};

#endif
