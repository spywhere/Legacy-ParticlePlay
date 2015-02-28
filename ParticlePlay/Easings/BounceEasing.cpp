#include "BounceEasing.hpp"

#include "BounceInEasing.hpp"
#include "BounceOutEasing.hpp"

float ppBounceEasing::GetValue(float t, float d, float b, float c){
	if(t < d/2){
		return (new ppBounceInEasing())->GetValue(t*2, d, 0, c) * .5f + b;
	}else{
		return (new ppBounceOutEasing())->GetValue(t*2-d, d, 0, c) * .5f + c*.5f + b;
	}
}
