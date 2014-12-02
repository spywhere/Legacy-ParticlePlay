#ifndef BOUNCEEASING_HEADER
#define BOUNCEEASING_HEADER

#include "Easing.hpp"

class ppBounceEasing : public ppEasing {
public:
	float GetValue(float time, float duration, float begin, float changes);
};

#endif
