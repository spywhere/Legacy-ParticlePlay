#include "BackOutEasing.hpp"

float ppBackOutEasing::GetValue(float t, float d, float b, float c){
	float s = 1.70158f;
	t=t/d-1;
	return c*(t*t*((s+1)*t + s) + 1) + b;
}
