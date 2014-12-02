#ifndef CUBICEASING_HEADER
#define CUBICEASING_HEADER

#include "Easing.hpp"

class ppCubicEasing : public ppEasing {
public:
	float GetValue(float time, float duration, float begin, float changes);
};

#endif
