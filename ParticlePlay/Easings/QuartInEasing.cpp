#include "QuartInEasing.hpp"

float ppQuartInEasing::GetValue(float t, float d, float b, float c){
	t/=d;
	return c*t*t*t*t + b;
}
