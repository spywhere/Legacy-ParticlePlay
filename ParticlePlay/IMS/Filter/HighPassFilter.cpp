#include "HighPassFilter.hpp"

ppHighPassFilter::ppHighPassFilter() : ppFilter(){
	this->gain = 1.0f;
	this->gainlf = 1.0f;
}

void ppHighPassFilter::InitFilter(){
	if(this->init || alGetEnumValue("AL_FILTER_HIGHPASS") == 0){
		return;
	}
	ppFilter::InitFilter();
	this->supported = true;
	alFilteri(this->filterID, AL_FILTER_TYPE, AL_FILTER_HIGHPASS);
}

float ppHighPassFilter::GetGain(){
	return this->gain;
}

float ppHighPassFilter::GetGainLF(){
	return this->gainlf;
}

void ppHighPassFilter::SetGain(float gain){
	this->gain = gain;
	alFilterf(this->filterID, AL_HIGHPASS_GAIN, this->gain);
}

void ppHighPassFilter::SetGainLF(float gainlf){
	this->gainlf = gainlf;
	alFilterf(this->filterID, AL_HIGHPASS_GAINLF, this->gainlf);
}
