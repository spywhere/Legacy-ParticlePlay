#ifndef ELASTICEASING_HEADER
#define ELASTICEASING_HEADER

#include "Easing.hpp"

class ppElasticEasing : public ppEasing {
public:
	float GetValue(float time, float duration, float begin, float changes);
};

#endif
