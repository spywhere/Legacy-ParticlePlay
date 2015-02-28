#ifndef QUADOUTEASING_HEADER
#define QUADOUTEASING_HEADER

#include <ParticlePlay/Easings/Easing.hpp>

class ppQuadOutEasing : public ppEasing {
public:
	float GetValue(float time, float duration, float begin, float changes);
};

#endif
