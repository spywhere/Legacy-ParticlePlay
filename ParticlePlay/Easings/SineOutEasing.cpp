#include "SineOutEasing.hpp"

#include <cmath>
const double PI = std::acos(-1);

float ppSineOutEasing::GetValue(float t, float d, float b, float c){
	return c * std::sin(t/d * (PI/2)) + b;
}
