#include "QuadOutEasing.hpp"

float ppQuadOutEasing::GetValue(float t, float d, float b, float c){
	t/=d;
	return -c *t*(t-2) + b;
}
