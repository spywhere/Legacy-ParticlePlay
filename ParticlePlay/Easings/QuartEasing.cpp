#include "QuartEasing.hpp"

float ppQuartEasing::GetValue(float t, float d, float b, float c){
	t/=d/2;
	if(t < 1){
		return c/2*t*t*t*t + b;
	}
	t-=2;
	return -c/2 * (t*t*t*t - 2) + b;
}
