#ifndef BACKOUTEASING_HEADER
#define BACKOUTEASING_HEADER

#include <ParticlePlay/Easings/Easing.hpp>

class ppBackOutEasing : public ppEasing {
public:
	ppBackOutEasing(float begin, float changes) : ppEasing(begin, changes){};
	ppBackOutEasing() : ppEasing(){};
	float GetValue(float time, float duration, float begin, float changes);
};

#endif
