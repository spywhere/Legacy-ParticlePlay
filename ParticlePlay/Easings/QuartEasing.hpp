#ifndef QUARTEASING_HEADER
#define QUARTEASING_HEADER

#include <ParticlePlay/Easings/Easing.hpp>

class ppQuartEasing : public ppEasing {
public:
	float GetValue(float time, float duration, float begin, float changes);
};

#endif
