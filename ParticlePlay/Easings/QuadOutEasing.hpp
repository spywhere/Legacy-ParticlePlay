#ifndef QUADOUTEASING_HEADER
#define QUADOUTEASING_HEADER

#include <ParticlePlay/Easings/Easing.hpp>

class ppQuadOutEasing : public ppEasing {
public:
	ppQuadOutEasing(float begin, float changes) : ppEasing(begin, changes){};
	ppQuadOutEasing() : ppEasing(){};
	float GetValue(float time, float duration, float begin, float changes);
};

#endif
