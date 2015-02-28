#ifndef QUADEASING_HEADER
#define QUADEASING_HEADER

#include <ParticlePlay/Easings/Easing.hpp>

class ppQuadEasing : public ppEasing {
public:
	float GetValue(float time, float duration, float begin, float changes);
};

#endif
