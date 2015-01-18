#include "Transition.hpp"

#include <string>

ppTransition::ppTransition(ppSwitch* sw, int priority, ppGenericSound* sourceSound, ppGenericSound* destSound){
	this->priority = priority;
	this->sourceSound = sourceSound;
	this->destSound = destSound;
	this->transitioning = false;
	this->SetSourcePosition(ppTransitionSourcePosition::IMMEDIATE);
	this->SetSourceOffset(0);
	this->SetSourceDuration(5);
	this->SetSourceCurve(new ppLinearEasing());
	this->SetDestinationPosition(ppTransitionDestinationPosition::ENTRY_CUE);
	this->SetDestinationOffset(0);
	this->SetDestinationDuration(5);
	this->SetDestinationCurve(new ppLinearEasing());
}

ppTransition::~ppTransition(){}

void ppTransition::Trigger(ppGenericSound* actualSource, ppGenericSound* actualDest){
	if(this->transitioning){
		return;
	}
	this->actualSource = actualSource;
	this->actualDest = actualDest;

	this->triggerTime = SDL_GetTicks();

	this->triggerSync = false;
	this->transitioning = true;

	if(this->sourceSound){
		this->actualSource = this->sourceSound;
	}
	if(this->destSound){
		this->actualDest = this->destSound;
	}

	new ppTimeListener(this->actualSource, this);
	new ppTimeListener(this->actualDest, this);
}

void ppTransition::Update(){
	if(!this->transitioning){
		return;
	}
	ppGenericSound* source = this->sourceSound;
	ppEasing* sourceEasing = this->sourceEasing;
	ppGenericSound* dest = this->destSound;
	ppEasing* destEasing = this->destEasing;
	if(!source){
		source = this->actualSource;
	}
	// If its destination is to "any" track, use the target
	if(!dest){
		dest = this->actualDest;
	}
	Uint32 currentTime = this->GetTransitionPosition();
	this->syncPoint = (Uint32)(this->GetSourceDuration()*1000);

	int sourceStartTime = this->GetSourceOffset()*1000;
	int destStartTime = this->GetDestinationOffset()*1000;

	int minStartTime = sourceStartTime;
	if(destStartTime < minStartTime){
		minStartTime = destStartTime;
	}
	if(minStartTime < 0){
		sourceStartTime -= minStartTime;
		destStartTime -= minStartTime;
		this->syncPoint -= minStartTime;
	}

	int sourceEndTime = sourceStartTime+this->GetSourceDuration()*1000;
	int destEndTime = destStartTime+this->GetDestinationDuration()*1000;

	if(source && currentTime >= sourceStartTime && currentTime < sourceEndTime){
		if(!source->IsPlaying()){
			source->Play();
		}
		float v = sourceEasing->GetValue(sourceEndTime-currentTime, this->sourceDuration*1000, 0, 1);
		source->SetVolume(v);
	}
	if(dest && currentTime >= destStartTime && currentTime < destEndTime){
		if(!dest->IsPlaying()){
			if(this->destPosition == ppTransitionDestinationPosition::SAME_TIME){
				dest->Seek(source->GetCurrentTime());
			}
			dest->Play();
		}
		float v = 1-destEasing->GetValue(destEndTime-currentTime, this->destDuration*1000, 0, 1);
		dest->SetVolume(v);
	}
	if(source && currentTime > sourceEndTime){
		source->StopDecay(true);
	}
	if(dest && currentTime > destEndTime){
		dest->SetVolume(1);
	}
	if(currentTime > this->syncPoint && !this->triggerSync){
		// TODO: Trigger seeking here
		this->triggerSync = true;
	}
	if(currentTime > sourceEndTime && currentTime > destEndTime && this->triggerSync){
		this->transitioning = false;
	}
}

bool ppTransition::IsTransitioning(){
	return this->transitioning;
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

ppGenericSound* ppTransition::GetActualSource(){
	return this->actualSource;
}

ppGenericSound* ppTransition::GetActualDestination(){
	return this->actualDest;
}

Uint32 ppTransition::GetTransitionPosition(){
	return SDL_GetTicks()-this->triggerTime;
}

Uint32 ppTransition::GetSyncPoint(){
	return this->syncPoint;
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
