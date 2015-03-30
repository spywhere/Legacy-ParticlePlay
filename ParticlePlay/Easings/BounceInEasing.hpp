#ifndef BOUNCEINEASING_HEADER
#define BOUNCEINEASING_HEADER

#include <ParticlePlay/Easings/Easing.hpp>

class ppBounceInEasing : public ppEasing {
public:
	ppBounceInEasing(float begin, float changes) : ppEasing(begin, changes){};
	ppBounceInEasing() : ppEasing(){};
	float GetValue(float time, float duration, float begin, float changes);
};

#endif
