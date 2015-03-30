#ifndef QUARTINEASING_HEADER
#define QUARTINEASING_HEADER

#include <ParticlePlay/Easings/Easing.hpp>

class ppQuartInEasing : public ppEasing {
public:
	ppQuartInEasing(float begin, float changes) : ppEasing(begin, changes){};
	ppQuartInEasing() : ppEasing(){};
	float GetValue(float time, float duration, float begin, float changes);
};

#endif
