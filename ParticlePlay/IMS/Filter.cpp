#include "Filter.hpp"

ppFilter::ppFilter(){
	this->init = false;
	this->supported = false;
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

ALuint ppFilter::GetFilterID(){
	return this->filterID;
}
