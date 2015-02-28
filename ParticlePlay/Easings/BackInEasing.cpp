#include "BackInEasing.hpp"

float ppBackInEasing::GetValue(float t, float d, float b, float c){
	float s = 1.70158f;
	t/=d;
	return c*t*t*((s+1)*t - s) + b;
}
