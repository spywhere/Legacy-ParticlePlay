#include "Filter.h"

ALuint ppFilter::GetFilterID(){
	return this->filterID;
}

bool ppFilter::IsSupported(){
	this->InitFilter();
	return this->supported;
}
