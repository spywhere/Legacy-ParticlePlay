#include "BounceInEasing.hpp"

#include "BounceOutEasing.hpp"

float ppBounceInEasing::GetValue(float t, float d, float b, float c){
	return c - (new ppBounceOutEasing())->GetValue(d-t, d, 0, c) + b;
}
