#ifndef QUINTEASING_HEADER
#define QUINTEASING_HEADER

#include "Easing.hpp"

class ppQuintEasing : public ppEasing {
public:
	float GetValue(float time, float duration, float begin, float changes);
};

#endif
