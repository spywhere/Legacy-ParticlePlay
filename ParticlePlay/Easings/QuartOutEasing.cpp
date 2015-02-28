#include "QuartOutEasing.hpp"

float ppQuartOutEasing::GetValue(float t, float d, float b, float c){
	t=t/d-1;
	return -c * (t*t*t*t - 1) + b;
}
