#ifndef LINEAREASING_HEADER
#define LINEAREASING_HEADER

#include <ParticlePlay/Easings/Easing.hpp>

class ppLinearEasing : public ppEasing {
public:
	ppLinearEasing(float begin, float changes) : ppEasing(begin, changes){};
	ppLinearEasing() : ppEasing(){};
	float GetValue(float time, float duration, float begin, float changes);
};

#endif
