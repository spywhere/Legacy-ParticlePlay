#include "CubicOutEasing.hpp"

float ppCubicOutEasing::GetValue(float t, float d, float b, float c){
	t=t/d-1;
	return c*(t*t*t + 1) + b;
}
