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

ppRTPC::ppRTPC(){
	this->offset = 0;
}

void ppRTPC::AddSound(ppGenericSound* sound, ppRTPCEffect effect, ppEasing* easing){
	this->effects[sound] = new ppEffectInfo(effect, easing);
}

void ppRTPC::RemoveSound(ppGenericSound* sound){
	auto it = this->effects.find(sound);
	if (it != this->effects.end()){
		this->effects.erase(sound);
	}
}

ppEffectInfo* ppRTPC::GetEffectInfo(ppGenericSound* sound){
	auto it = this->effects.find(sound);
	if (it != this->effects.end()){
		return it->second;
	}else{
		return NULL;
	}
}

void ppRTPC::SetOffset(float offset){
	this->offset = offset;
}

float ppRTPC::GetOffset(){
	return this->offset;
}
