#ifndef BACKOUTEASING_HEADER
#define BACKOUTEASING_HEADER

#include <ParticlePlay/Easings/Easing.hpp>

class ppBackOutEasing : public ppEasing {
public:
	float GetValue(float time, float duration, float begin, float changes);
};

#endif
