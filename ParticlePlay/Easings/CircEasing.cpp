#include "CircEasing.hpp"

#include <cmath>

float ppCircEasing::GetValue(float t, float d, float b, float c){
	t/=d/2;
	if(t < 1){
		return -c/2 * (std::sqrt(1 - t*t) - 1) + b;
	}
	t-=2;
	return c/2 * (std::sqrt(1 - t*t) + 1) + b;
}
