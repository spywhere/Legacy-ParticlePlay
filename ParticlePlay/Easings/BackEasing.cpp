#include "BackEasing.hpp"

float ppBackEasing::GetValue(float t, float d, float b, float c){
	float s = 1.70158f;
	s*=1.525f;
	t/=d/2;
	if (t < 1) {
		return c/2*(t*t*((s+1)*t - s)) + b;
	}
	t-=2;
	return c/2*(t*t*((s+1)*t + s) + 2) + b;
}
