#ifndef BACKEASING_HEADER
#define BACKEASING_HEADER

#include <ParticlePlay/Easings/Easing.hpp>

class ppBackEasing : public ppEasing {
public:
	float GetValue(float time, float duration, float begin, float changes);
};

#endif