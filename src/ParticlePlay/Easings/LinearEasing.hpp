#ifndef LINEAREASING_HEADER
#define LINEAREASING_HEADER

#include "Easing.hpp"

class ppLinearEasing : public ppEasing {
public:
	float GetValue(float time, float duration, float begin, float changes);
};

#endif
