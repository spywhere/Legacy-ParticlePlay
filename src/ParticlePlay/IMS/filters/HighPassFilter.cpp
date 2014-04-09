#include "HighPassFilter.h"

HighPassFilter::HighPassFilter(){
	this->supported = false;
	this->gain = 1.0f;
	this->gainlf = 1.0f;
}

void HighPassFilter::InitFilter(){
	if(this->supported||alGetEnumValue("AL_FILTER_HIGHPASS") == 0){
		return;
	}
	this->supported = true;
	alGenFilters(1, &this->filterID);
	alFilteri(this->filterID, AL_FILTER_TYPE, AL_FILTER_HIGHPASS);
}

void HighPassFilter::SetGain(float val){
	this->InitFilter();
	this->gain = val;
	alFilterf(this->filterID, AL_HIGHPASS_GAIN, this->gain);
}

void HighPassFilter::SetGainLF(float val){
	this->InitFilter();
	this->gainlf = val;
	alFilterf(this->filterID, AL_HIGHPASS_GAINLF, this->gainlf);
}

float HighPassFilter::GetGainLF(){
	return this->gainlf;
}
