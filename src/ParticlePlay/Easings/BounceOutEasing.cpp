#include "BounceOutEasing.hpp"

float ppBounceOutEasing::GetValue(float t, float d, float b, float c){
	t/=d;
	if(t < (1/2.75f)){
		return c*(7.5625f*t*t) + b;
	}else if(t < (2/2.75f)){
		t-=(1.5f/2.75f);
		return c*(7.5625f*t*t + .75f) + b;
	}else if(t < (2.5/2.75)){
		t-=(2.25f/2.75f);
		return c*(7.5625f*t*t + .9375f) + b;
	}else{
		t-=(2.625f/2.75f);
		return c*(7.5625f*t*t + .984375f) + b;
	}
}
