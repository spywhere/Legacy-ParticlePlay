#include "LinearEasing.hpp"

float ppLinearEasing::GetValue(float t, float d, float b, float c){
	return c*t/d + b;
}
