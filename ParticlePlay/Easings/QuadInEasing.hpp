#ifndef QUADINEASING_HEADER
#define QUADINEASING_HEADER

#include <ParticlePlay/Easings/Easing.hpp>

class ppQuadInEasing : public ppEasing {
public:
	float GetValue(float time, float duration, float begin, float changes);
};

#endif