#include "SineInEasing.hpp"

#include <cmath>
const double PI = std::acos(-1);

float ppSineInEasing::GetValue(float t, float d, float b, float c){
	return -c * std::cos(t/d * (PI/2)) + c + b;
}
