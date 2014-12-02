#ifndef QUARTINEASING_HEADER
#define QUARTINEASING_HEADER

#include "Easing.hpp"

class ppQuartInEasing : public ppEasing {
public:
	float GetValue(float time, float duration, float begin, float changes);
};

#endif
