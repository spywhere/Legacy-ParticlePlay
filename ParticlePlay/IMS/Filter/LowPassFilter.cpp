#include "LowPassFilter.hpp"

ppLowPassFilter::ppLowPassFilter(ppIMS* ims, ppFilterType type) : ppFilter(ims, type){
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

float ppLowPassFilter::GetGainHF(){
	return this->gainhf;
}

void ppLowPassFilter::SetGain(float gain){
	ppFilter::SetGain(gain);
	alFilterf(this->filterID, AL_LOWPASS_GAIN, this->gain);
}

void ppLowPassFilter::SetGainHF(float gainhf){
	this->gainhf = gainhf;
	alFilterf(this->filterID, AL_LOWPASS_GAINHF, this->gainhf);
}
