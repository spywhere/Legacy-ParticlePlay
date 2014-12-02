#include "CubicInEasing.hpp"

float ppCubicInEasing::GetValue(float t, float d, float b, float c){
	t/=d;
	return c*t*t*t + b;
}
