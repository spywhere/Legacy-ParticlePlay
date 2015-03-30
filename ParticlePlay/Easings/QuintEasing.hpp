#ifndef QUINTEASING_HEADER
#define QUINTEASING_HEADER

#include <ParticlePlay/Easings/Easing.hpp>

class ppQuintEasing : public ppEasing {
public:
	ppQuintEasing(float begin, float changes) : ppEasing(begin, changes){};
	ppQuintEasing() : ppEasing(){};
	float GetValue(float time, float duration, float begin, float changes);
};

#endif
