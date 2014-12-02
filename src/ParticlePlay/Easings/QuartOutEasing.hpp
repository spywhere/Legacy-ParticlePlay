#ifndef QUARTOUTEASING_HEADER
#define QUARTOUTEASING_HEADER

#include "Easing.hpp"

class ppQuartOutEasing : public ppEasing {
public:
	float GetValue(float time, float duration, float begin, float changes);
};

#endif
