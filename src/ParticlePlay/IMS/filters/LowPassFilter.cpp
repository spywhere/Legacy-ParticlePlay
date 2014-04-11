#include "LowPassFilter.h"

ppLowPassFilter::ppLowPassFilter(ppIMS* ims){
	this->supported = false;
	this->gain = 1.0f;
	this->gainhf = 1.0f;
}

void ppLowPassFilter::InitFilter(){
	if(this->supported||alGetEnumValue("AL_FILTER_LOWPASS") == 0){
		return;
	}
	this->supported = true;
	alGenFilters(1, &this->filterID);
	alFilteri(this->filterID, AL_FILTER_TYPE, AL_FILTER_LOWPASS);
}

void ppLowPassFilter::SetGain(float val){
	this->InitFilter();
	this->gain = val;
	alFilterf(this->filterID, AL_LOWPASS_GAIN, this->gain);
}

void ppLowPassFilter::SetGainHF(float val){
	this->InitFilter();
	this->gainhf = val;
	alFilterf(this->filterID, AL_LOWPASS_GAINHF, this->gainhf);
}

float ppLowPassFilter::GetGainHF(){
	return this->gainhf;
}
