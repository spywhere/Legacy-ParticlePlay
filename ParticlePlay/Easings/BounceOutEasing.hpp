#ifndef BOUNCEOUTEASING_HEADER
#define BOUNCEOUTEASING_HEADER

#include <ParticlePlay/Easings/Easing.hpp>

class ppBounceOutEasing : public ppEasing {
public:
	ppBounceOutEasing(float begin, float changes) : ppEasing(begin, changes){};
	ppBounceOutEasing() : ppEasing(){};
	float GetValue(float time, float duration, float begin, float changes);
};

#endif
