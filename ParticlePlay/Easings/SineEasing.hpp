#ifndef SINEEASING_HEADER
#define SINEEASING_HEADER

#include <ParticlePlay/Easings/Easing.hpp>

class ppSineEasing : public ppEasing {
public:
	ppSineEasing(float begin, float changes) : ppEasing(begin, changes){};
	ppSineEasing() : ppEasing(){};
	float GetValue(float time, float duration, float begin, float changes);
};

#endif
