#include "BandPassFilter.hpp"

ppBandPassFilter::ppBandPassFilter() : ppFilter(){
	this->gain = 1.0f;
	this->gainhf = 1.0f;
	this->gainlf = 1.0f;
}

void ppBandPassFilter::InitFilter(){
	if(this->init || alGetEnumValue("AL_FILTER_BANDPASS") == 0){
		return;
	}
	ppFilter::InitFilter();
	this->supported = true;
	alFilteri(this->filterID, AL_FILTER_TYPE, AL_FILTER_BANDPASS);
}

float ppBandPassFilter::GetGain(){
	return this->gain;
}

float ppBandPassFilter::GetGainLF(){
	return this->gainlf;
}

float ppBandPassFilter::GetGainHF(){
	return this->gainhf;
}

void ppBandPassFilter::SetGain(float gain){
	this->gain = gain;
	alFilterf(this->filterID, AL_BANDPASS_GAIN, this->gain);
}

void ppBandPassFilter::SetGainLF(float gainlf){
	this->gainlf = gainlf;
	alFilterf(this->filterID, AL_BANDPASS_GAINLF, this->gainlf);
}

void ppBandPassFilter::SetGainHF(float gainhf){
	this->gainhf = gainhf;
	alFilterf(this->filterID, AL_BANDPASS_GAINHF, this->gainhf);
}
