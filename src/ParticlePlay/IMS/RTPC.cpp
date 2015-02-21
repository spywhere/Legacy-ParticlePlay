#include "RTPC.hpp"

ppGraphCurve::ppGraphCurve(float offset, ppEasing* easing){
	this->offset = offset;
	this->easing = easing;
}

ppEasing* ppGraphCurve::GetCurve(){
	return this->easing;
}

float ppGraphCurve::GetOffset(){
	return this->offset;
}

bool ppRTPC::GraphCurveSorter(ppGraphCurve* curve1, ppGraphCurve* curve2){
	return curve1->GetOffset() < curve2->GetOffset();
}

ppEffectInfo::ppEffectInfo(float value, ppRTPCEffect effect){
	this->value = value;
	this->effect = effect;
}

float ppEffectInfo::GetValue(){
	return this->value;
}

ppRTPCEffect ppEffectInfo::GetEffect(){
	return this->effect;
}

ppRTPC::ppRTPC(){
	this->offset = 0;
}

void ppRTPC::AddMidPoint(float offset, ppEasing* easing){
	this->curves.push_back(new ppGraphCurve(offset, easing));
	this->curves.sort(ppRTPC::GraphCurveSorter);
}

void ppRTPC::AddSound(ppGenericSound* sound, ppRTPCEffect effect){
	this->effects[sound] = effect;
}

void ppRTPC::RemoveSound(ppGenericSound* sound){
	auto it = this->effects.find(sound);
	if (it != this->effects.end()){
		this->effects.erase(sound);
	}
}

ppEffectInfo* ppRTPC::GetEffectInfo(ppGenericSound* sound){
	// TOOD:
	// Need to rework since the graph curve must be 2D not 1D
	auto it = this->effects.find(sound);
	ppRTPCEffect effect = ppRTPCEffect::VOLUME;
	if (it != this->effects.end()){
		effect = it->second;
	}else{
		return NULL;
	}
	float nextOffset = 0;
	ppGraphCurve* curve = NULL;
	for(auto cv : this->curves){
		if(cv->GetOffset() > this->offset){
			nextOffset = cv->GetOffset();
			break;
		}
		curve = cv;
	}
	if(curve){
		ppEasing* easing = curve->GetCurve();
		return new ppEffectInfo(easing->GetValue(this->offset-curve->GetOffset(), nextOffset-curve->GetOffset(), 0, 1), effect);
	}
	return NULL;
}

void ppRTPC::SetOffset(float offset){
	this->offset = offset;
}

float ppRTPC::GetOffset(){
	return this->offset;
}
