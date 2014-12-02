#ifndef EXPOEASING_HEADER
#define EXPOEASING_HEADER

#include "Easing.hpp"

class ppExpoEasing : public ppEasing {
public:
	float GetValue(float time, float duration, float begin, float changes);
};

#endif
