#include "Filter.h"

ppFilter::~ppFilter(){
	if(this->supported){
		alDeleteFilters(1, &this->filterID);
	}
}

ALuint ppFilter::GetFilterID(){
	return this->filterID;
}

bool ppFilter::IsSupported(){
	this->InitFilter();
	return this->supported;
}
