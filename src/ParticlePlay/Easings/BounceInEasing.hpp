#ifndef BOUNCEINEASING_HEADER
#define BOUNCEINEASING_HEADER

#include "Easing.hpp"

class ppBounceInEasing : public ppEasing {
public:
	float GetValue(float time, float duration, float begin, float changes);
};

#endif
