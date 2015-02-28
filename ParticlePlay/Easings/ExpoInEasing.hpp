#ifndef EXPOINEASING_HEADER
#define EXPOINEASING_HEADER

#include <ParticlePlay/Easings/Easing.hpp>

class ppExpoInEasing : public ppEasing {
public:
	float GetValue(float time, float duration, float begin, float changes);
};

#endif
