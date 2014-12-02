#ifndef ELASTICINEASING_HEADER
#define ELASTICINEASING_HEADER

#include "Easing.hpp"

class ppElasticInEasing : public ppEasing {
public:
	float GetValue(float time, float duration, float begin, float changes);
};

#endif
