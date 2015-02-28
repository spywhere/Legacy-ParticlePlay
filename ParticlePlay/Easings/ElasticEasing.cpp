#include "ElasticEasing.hpp"

#include <cmath>
const double PI = std::acos(-1);

float ppElasticEasing::GetValue(float t, float d, float b, float c){
	if(t==0){
		return b;
	}
	t/=d/2;
	if(t==2){
		return b+c;
	}
	float p=d*(.3f*1.5f);
	float a=c;
	float s=p/4;
	if (t < 1) {
		t-=1;
		return -.5f*(a*pow(2,10*t)* sin( (t*d-s)*(2*PI)/p )) + b;
	}
	t-=1;
	return a*pow(2,-10*t) * sin( (t*d-s)*(2*PI)/p )*.5f + c + b;
}
