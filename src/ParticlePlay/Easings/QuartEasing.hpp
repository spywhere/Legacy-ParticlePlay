#ifndef QUARTEASING_HEADER
#define QUARTEASING_HEADER

#include "Easing.hpp"

class ppQuartEasing : public ppEasing {
public:
	float GetValue(float time, float duration, float begin, float changes);
};

#endif
