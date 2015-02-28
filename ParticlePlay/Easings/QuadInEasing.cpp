#include "QuadInEasing.hpp"

float ppQuadInEasing::GetValue(float t, float d, float b, float c){
	t/=d;
	return c*t*t + b;
}
