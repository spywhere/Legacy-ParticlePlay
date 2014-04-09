#include "BandPassFilter.h"

BandPassFilter::BandPassFilter(){
	this->supported = false;
	this->gain = 1.0f;
	this->gainlf = 1.0f;
	this->gainhf = 1.0f;
}

void BandPassFilter::InitFilter(){
	if(this->supported||alGetEnumValue("AL_FILTER_BANDPASS") == 0){
		return;
	}
	this->supported = true;
	alGenFilters(1, &this->filterID);
	alFilteri(this->filterID, AL_FILTER_TYPE, AL_FILTER_BANDPASS);
}

void BandPassFilter::SetGain(float val){
	this->InitFilter();
	this->gain = val;
	alFilterf(this->filterID, AL_BANDPASS_GAIN, this->gain);
}

void BandPassFilter::SetGainLF(float val){
	this->InitFilter();
	this->gainlf = val;
	alFilterf(this->filterID, AL_BANDPASS_GAINLF, this->gainlf);
}

void BandPassFilter::SetGainHF(float val){
	this->InitFilter();
	this->gainhf = val;
	alFilterf(this->filterID, AL_BANDPASS_GAINHF, this->gainhf);
}

float BandPassFilter::GetGainLF(){
	return this->gainlf;
}

float BandPassFilter::GetGainHF(){
	return this->gainhf;
}
