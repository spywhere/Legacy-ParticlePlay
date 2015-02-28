#ifndef BACKINEASING_HEADER
#define BACKINEASING_HEADER

#include <ParticlePlay/Easings/Easing.hpp>

class ppBackInEasing : public ppEasing {
public:
	float GetValue(float time, float duration, float begin, float changes);
};

#endif
