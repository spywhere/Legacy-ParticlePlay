#ifndef BOUNCEOUTEASING_HEADER
#define BOUNCEOUTEASING_HEADER

#include "Easing.hpp"

class ppBounceOutEasing : public ppEasing {
public:
	float GetValue(float time, float duration, float begin, float changes);
};

#endif
