#include "LowPassFilter.hpp"

ppLowPassFilter::ppLowPassFilter() : ppFilter(){
	this->gain = 1.0f;
	this->gainhf = 1.0f;
}

void ppLowPassFilter::InitFilter(){
	if(this->init || alGetEnumValue("AL_FILTER_LOWPASS") == 0){
		return;
	}
	ppFilter::InitFilter();
	this->supported = true;
	alFilteri(this->filterID, AL_FILTER_TYPE, AL_FILTER_LOWPASS);
}

float ppLowPassFilter::GetGain(){
	return this->gain;
}

float ppLowPassFilter::GetGainHF(){
	return this->gainhf;
}

void ppLowPassFilter::SetGain(float gain){
	this->gain = gain;
	alFilterf(this->filterID, AL_LOWPASS_GAIN, this->gain);
}

void ppLowPassFilter::SetGainHF(float gainhf){
	this->gainhf = gainhf;
	alFilterf(this->filterID, AL_LOWPASS_GAINHF, this->gainhf);
}
