#include "HighPassFilter.h"

ppHighPassFilter::ppHighPassFilter(ppIMS* ims){
	this->supported = false;
	this->gain = 1.0f;
	this->gainlf = 1.0f;
}

void ppHighPassFilter::InitFilter(){
	if(this->supported||alGetEnumValue("AL_FILTER_HIGHPASS") == 0){
		return;
	}
	this->supported = true;
	alGenFilters(1, &this->filterID);
	alFilteri(this->filterID, AL_FILTER_TYPE, AL_FILTER_HIGHPASS);
}

void ppHighPassFilter::SetGain(float val){
	this->InitFilter();
	this->gain = val;
	alFilterf(this->filterID, AL_HIGHPASS_GAIN, this->gain);
}

void ppHighPassFilter::SetGainLF(float val){
	this->InitFilter();
	this->gainlf = val;
	alFilterf(this->filterID, AL_HIGHPASS_GAINLF, this->gainlf);
}

float ppHighPassFilter::GetGainLF(){
	return this->gainlf;
}
