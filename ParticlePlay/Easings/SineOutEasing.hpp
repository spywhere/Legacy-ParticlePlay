#ifndef SINEOUTEASING_HEADER
#define SINEOUTEASING_HEADER

#include <ParticlePlay/Easings/Easing.hpp>

class ppSineOutEasing : public ppEasing {
public:
	ppSineOutEasing(float begin, float changes) : ppEasing(begin, changes){};
	ppSineOutEasing() : ppEasing(){};
	float GetValue(float time, float duration, float begin, float changes);
};

#endif
