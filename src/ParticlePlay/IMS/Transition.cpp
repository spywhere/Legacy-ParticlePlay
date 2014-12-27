#include "Transition.hpp"

#include <string>

ppTransition::ppTransition(ppSwitch* sw, int priority, ppGenericSound* sourceSound, ppGenericSound* destSound){
	this->priority = priority;
	this->sourceSound = sourceSound;
	this->destSound = destSound;
	this->SetSourcePosition(ppTransitionSourcePosition::IMMEDIATE);
	this->SetSourceOffset(0);
	this->SetSourceDuration(5);
	this->SetSourceCurve(new ppLinearEasing());
	this->SetDestinationPosition(ppTransitionDestinationPosition::ENTRY_CUE);
	this->SetDestinationOffset(0);
	this->SetDestinationDuration(5);
	this->SetDestinationCurve(new ppLinearEasing());
}

void ppTransition::SetSourceStartTime(ppSwitch* sw, Uint32 sourceStartTime){
	this->sourceStartTime = sourceStartTime;
}

Uint32 ppTransition::GetSourceStartTime(ppSwitch* sw){
	return this->sourceStartTime;
}

void ppTransition::SetDestinationStartTime(ppSwitch* sw, Uint32 destStartTime){
	this->destStartTime = destStartTime;
}

Uint32 ppTransition::GetDestinationStartTime(ppSwitch* sw){
	return this->destStartTime;
}

void ppTransition::SetSourceEndTime(ppSwitch* sw, Uint32 sourceEndTime){
	this->sourceEndTime = sourceEndTime;
}

Uint32 ppTransition::GetSourceEndTime(ppSwitch* sw){
	return this->sourceEndTime;
}

void ppTransition::SetDestinationEndTime(ppSwitch* sw, Uint32 destEndTime){
	this->destEndTime = destEndTime;
}

Uint32 ppTransition::GetDestinationEndTime(ppSwitch* sw){
	return this->destEndTime;
}

bool ppTransition::IsSourceName(const char *name){
	return !this->GetSource() || this->GetSource()->GetName() == std::string(name);
}

bool ppTransition::IsDestinationName(const char *name){
	return !this->GetDestination() || this->GetDestination()->GetName() == std::string(name);
}

ppGenericSound* ppTransition::GetSource(){
	return this->sourceSound;
}

ppGenericSound* ppTransition::GetDestination(){
	return this->destSound;
}

void ppTransition::SetSourcePosition(ppTransitionSourcePosition sourcePosition){
	this->sourcePosition = sourcePosition;
}

void ppTransition::SetDestinationPosition(ppTransitionDestinationPosition destPosition){
	this->destPosition = destPosition;
}

int ppTransition::GetPriority(){
	return this->priority;
}

void ppTransition::SetSourceOffset(float offset){
	this->sourceOffset = offset;
}

void ppTransition::SetSourceDuration(float duration){
	this->sourceDuration = duration;
}

void ppTransition::SetSourceCurve(ppEasing* easing){
	this->sourceEasing = easing;
}

void ppTransition::SetDestinationOffset(float offset){
	this->destOffset = offset;
}

void ppTransition::SetDestinationDuration(float duration){
	this->destDuration = duration;
}

void ppTransition::SetDestinationCurve(ppEasing* easing){
	this->destEasing = easing;
}

ppTransitionSourcePosition ppTransition::GetSourcePosition(){
	return this->sourcePosition;
}

float ppTransition::GetSourceOffset(){
	return this->sourceOffset;
}

float ppTransition::GetSourceDuration(){
	return this->sourceDuration;
}

ppEasing* ppTransition::GetSourceCurve(){
	return this->sourceEasing;
}

ppTransitionDestinationPosition ppTransition::GetDestinationPosition(){
	return this->destPosition;
}

float ppTransition::GetDestinationOffset(){
	return this->destOffset;
}

float ppTransition::GetDestinationDuration(){
	return this->destDuration;
}

ppEasing* ppTransition::GetDestinationCurve(){
	return this->destEasing;
}
