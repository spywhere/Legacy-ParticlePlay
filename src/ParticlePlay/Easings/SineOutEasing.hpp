#ifndef SINEOUTEASING_HEADER
#define SINEOUTEASING_HEADER

#include "Easing.hpp"

class ppSineOutEasing : public ppEasing {
public:
	float GetValue(float time, float duration, float begin, float changes);
};

#endif
