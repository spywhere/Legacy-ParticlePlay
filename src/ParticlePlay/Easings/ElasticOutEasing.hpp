#ifndef ELASTICOUTEASING_HEADER
#define ELASTICOUTEASING_HEADER

#include "Easing.hpp"

class ppElasticOutEasing : public ppEasing {
public:
	float GetValue(float time, float duration, float begin, float changes);
};

#endif
