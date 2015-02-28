#ifndef CIRCINEASING_HEADER
#define CIRCINEASING_HEADER

#include <ParticlePlay/Easings/Easing.hpp>

class ppCircInEasing : public ppEasing {
public:
	float GetValue(float time, float duration, float begin, float changes);
};

#endif
