#include "ExpoOutEasing.hpp"

#include <cmath>

float ppExpoOutEasing::GetValue(float t, float d, float b, float c){
	return (t==d) ? b+c : c * (-std::pow(2, -10 * t/d) + 1) + b;
}
