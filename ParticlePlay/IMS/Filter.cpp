#include "Filter.hpp"

ppFilter::ppFilter(ppIMS* ims, ppFilterType type){
	this->init = false;
	this->supported = false;
	this->gain = 1.0f;
	this->type = type;
	alGenFilters(1, &this->filterID);
}

ppFilter::~ppFilter(){
	alDeleteFilters(1, &this->filterID);
}

void ppFilter::InitFilter(){
	if(!this->init){
		this->init = true;
	}
}

bool ppFilter::IsSupported(){
	return this->supported;
}

ppFilterType ppFilter::GetFilterType(){
	return this->type;
}

ALuint ppFilter::GetFilterID(){
	return this->filterID;
}

void ppFilter::AddRTPC(ppRTPC* rtpc, ppRTPCEffect effect, ppEasing* easing){
	this->rtpcs[rtpc] = new ppEffectInfo(effect, easing);
}

void ppFilter::RemoveRTPC(ppRTPC* rtpc){
	auto it = this->rtpcs.find(rtpc);
	if (it != this->rtpcs.end()){
		this->rtpcs.erase(rtpc);
	}
}

std::map<ppRTPC*, ppEffectInfo*> ppFilter::GetRTPCs(){
	return this->rtpcs;
}

void ppFilter::SetGain(float gain){
	this->gain = gain;
}

float ppFilter::GetGain(){
	return this->gain;
}
