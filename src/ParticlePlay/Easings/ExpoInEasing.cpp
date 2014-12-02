#include "ExpoInEasing.hpp"

#include <cmath>

float ppExpoInEasing::GetValue(float t, float d, float b, float c){
	return (t==0) ? b : c * std::pow(2, 10 * (t/d - 1)) + b;
}
