#include "RTPC.hpp"

ppEffectInfo::ppEffectInfo(ppRTPCEffect effect, ppEasing* easing){
	this->effect = effect;
	this->easing = easing;
}

ppRTPCEffect ppEffectInfo::GetEffect(){
	return this->effect;
}

ppEasing* ppEffectInfo::GetCurve(){
	return this->easing;
}

ppRTPC::ppRTPC(ppIMS* ims){
	this->offset = 0;
}

void ppRTPC::SetOffset(float offset){
	this->offset = offset;
}

float ppRTPC::GetOffset(){
	return this->offset;
}
