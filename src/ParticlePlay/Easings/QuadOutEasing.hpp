#ifndef QUADOUTEASING_HEADER
#define QUADOUTEASING_HEADER

#include "Easing.hpp"

class ppQuadOutEasing : public ppEasing {
public:
	float GetValue(float time, float duration, float begin, float changes);
};

#endif
