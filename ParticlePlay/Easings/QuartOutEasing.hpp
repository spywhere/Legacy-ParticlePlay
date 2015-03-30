#ifndef QUARTOUTEASING_HEADER
#define QUARTOUTEASING_HEADER

#include <ParticlePlay/Easings/Easing.hpp>

class ppQuartOutEasing : public ppEasing {
public:
	ppQuartOutEasing(float begin, float changes) : ppEasing(begin, changes){};
	ppQuartOutEasing() : ppEasing(){};
	float GetValue(float time, float duration, float begin, float changes);
};

#endif
