#ifndef SINEINEASING_HEADER
#define SINEINEASING_HEADER

#include "Easing.hpp"

class ppSineInEasing : public ppEasing {
public:
	float GetValue(float time, float duration, float begin, float changes);
};

#endif
