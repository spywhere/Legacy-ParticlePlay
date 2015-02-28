#include "SineEasing.hpp"

#include <cmath>
const double PI = std::acos(-1);

float ppSineEasing::GetValue(float t, float d, float b, float c){
	return -c/2 * (std::cos(PI*t/d) - 1) + b;
}
