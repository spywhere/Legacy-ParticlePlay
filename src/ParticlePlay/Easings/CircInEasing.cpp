#include "CircInEasing.hpp"

#include <cmath>

float ppCircInEasing::GetValue(float t, float d, float b, float c){
	t/=d;
	return -c * (std::sqrt(1 - t*t) - 1) + b;
}
