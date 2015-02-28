#include "ExpoEasing.hpp"

#include <cmath>

float ppExpoEasing::GetValue(float t, float d, float b, float c){
	if(t==0){
		return b;
	}
	if(t==d){
		return b+c;
	}
	t/=d/2;
	if(t < 1){
		return c/2 * std::pow(2, 10 * (t - 1)) + b - c * 0.0005f;
	}
	t-=1;
	return c/2  * 1.0005f * (-std::pow(2, -10 * t) + 2) + b;
}
