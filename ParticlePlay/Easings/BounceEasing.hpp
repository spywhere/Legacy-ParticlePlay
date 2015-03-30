#ifndef BOUNCEEASING_HEADER
#define BOUNCEEASING_HEADER

#include <ParticlePlay/Easings/Easing.hpp>

class ppBounceEasing : public ppEasing {
public:
	ppBounceEasing(float begin, float changes) : ppEasing(begin, changes){};
	ppBounceEasing() : ppEasing(){};
	float GetValue(float time, float duration, float begin, float changes);
};

#endif
