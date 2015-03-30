#ifndef CIRCOUTEASING_HEADER
#define CIRCOUTEASING_HEADER

#include <ParticlePlay/Easings/Easing.hpp>

class ppCircOutEasing : public ppEasing {
public:
	ppCircOutEasing(float begin, float changes) : ppEasing(begin, changes){};
	ppCircOutEasing() : ppEasing(){};
	float GetValue(float time, float duration, float begin, float changes);
};

#endif
