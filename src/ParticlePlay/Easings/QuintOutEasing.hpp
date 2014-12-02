#ifndef QUINTOUTEASING_HEADER
#define QUINTOUTEASING_HEADER

#include "Easing.hpp"

class ppQuintOutEasing : public ppEasing {
public:
	float GetValue(float time, float duration, float begin, float changes);
};

#endif
