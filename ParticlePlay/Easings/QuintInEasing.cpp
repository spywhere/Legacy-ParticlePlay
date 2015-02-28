#include "QuintInEasing.hpp"

float ppQuintInEasing::GetValue(float t, float d, float b, float c){
	t/=d;
	return c*t*t*t*t*t + b;
}
