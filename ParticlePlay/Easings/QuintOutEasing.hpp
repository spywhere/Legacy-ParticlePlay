#ifndef QUINTOUTEASING_HEADER
#define QUINTOUTEASING_HEADER

#include <ParticlePlay/Easings/Easing.hpp>

class ppQuintOutEasing : public ppEasing {
public:
	ppQuintOutEasing(float begin, float changes) : ppEasing(begin, changes){};
	ppQuintOutEasing() : ppEasing(){};
	float GetValue(float time, float duration, float begin, float changes);
};

#endif
