#include "CircOutEasing.hpp"

#include <cmath>

float ppCircOutEasing::GetValue(float t, float d, float b, float c){
	t=t/d-1;
	return c * std::sqrt(1 - t*t) + b;
}
