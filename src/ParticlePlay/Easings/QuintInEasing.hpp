#ifndef QUINTINEASING_HEADER
#define QUINTINEASING_HEADER

#include "Easing.hpp"

class ppQuintInEasing : public ppEasing {
public:
	float GetValue(float time, float duration, float begin, float changes);
};

#endif
