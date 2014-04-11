#include "BandPassFilter.h"

ppBandPassFilter::ppBandPassFilter(ppIMS* ims){
	this->supported = false;
	this->gain = 1.0f;
	this->gainlf = 1.0f;
	this->gainhf = 1.0f;
}

void ppBandPassFilter::InitFilter(){
	if(this->supported||alGetEnumValue("AL_FILTER_BANDPASS") == 0){
		return;
	}
	this->supported = true;
	alGenFilters(1, &this->filterID);
	alFilteri(this->filterID, AL_FILTER_TYPE, AL_FILTER_BANDPASS);
}

void ppBandPassFilter::SetGain(float val){
	this->InitFilter();
	this->gain = val;
	alFilterf(this->filterID, AL_BANDPASS_GAIN, this->gain);
}

void ppBandPassFilter::SetGainLF(float val){
	this->InitFilter();
	this->gainlf = val;
	alFilterf(this->filterID, AL_BANDPASS_GAINLF, this->gainlf);
}

void ppBandPassFilter::SetGainHF(float val){
	this->InitFilter();
	this->gainhf = val;
	alFilterf(this->filterID, AL_BANDPASS_GAINHF, this->gainhf);
}

float ppBandPassFilter::GetGainLF(){
	return this->gainlf;
}

float ppBandPassFilter::GetGainHF(){
	return this->gainhf;
}
