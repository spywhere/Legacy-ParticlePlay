#include "QuadEasing.hpp"

float ppQuadEasing::GetValue(float t, float d, float b, float c){
	t/=d/2;
	if(t < 1){
		return ((c/2)*(t*t)) + b;
	}
	t-=1;
	return -c/2 * (((t-2)*t) - 1) + b;
}
