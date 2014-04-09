#include "Filter.h"

ALuint Filter::GetFilterID(){
	return this->filterID;
}

bool Filter::IsSupported(){
	this->InitFilter();
	return this->supported;
}
