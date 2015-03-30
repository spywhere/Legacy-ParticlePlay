#include "Easing.hpp"

ppEasing::ppEasing(float begin, float changes){
	this->begin = begin;
	this->changes = changes;
}

float ppEasing::GetValue(float time, float duration){
	return this->GetValue(time, duration, this->begin, this->changes);
}

void ppEasing::SetBegin(float begin){
	this->begin = begin;
}

void ppEasing::SetChanges(float changes){
	this->changes = changes;
}

float ppEasing::GetBegin(){
	return this->begin;
}

float ppEasing::GetChanges(){
	return this->changes;
}
