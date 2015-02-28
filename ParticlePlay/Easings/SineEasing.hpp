#ifndef SINEEASING_HEADER
#define SINEEASING_HEADER

#include <ParticlePlay/Easings/Easing.hpp>

class ppSineEasing : public ppEasing {
public:
	float GetValue(float time, float duration, float begin, float changes);
};

#endif
