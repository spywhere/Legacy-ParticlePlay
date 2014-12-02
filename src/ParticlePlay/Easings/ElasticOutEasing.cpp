#include "ElasticOutEasing.hpp"

#include <cmath>
const double PI = std::acos(-1);

float ppElasticOutEasing::GetValue(float t, float d, float b, float c){
	if(t==0){
		return b;
	}
	t/=d;
	if(t==1){
		return b+c;
	}
	float p=d*.3f;
	float a=c;
	float s=p/4;
	return (a*std::pow(2,-10*t) * std::sin( (t*d-s)*(2*PI)/p ) + c + b);
}
