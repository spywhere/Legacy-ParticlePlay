#include "Transition.hpp"

#include <string>

ppTransition::ppTransition(ppSwitch* sw, int priority, ppGenericSound* sourceSound, ppGenericSound* destSound){
	this->priority = priority;
	this->sourceSound = sourceSound;
	this->destSound = destSound;
	this->transitioning = false;
	this->transitionTrack = NULL;
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

	this->triggerSync = false;
	this->transitioning = true;

	if(this->sourceSound){
		this->actualSource = this->sourceSound;
	}
	if(this->destSound){
		this->actualDest = this->destSound;
	}

	this->syncPoint = (Uint32)(this->GetSourceDuration()*1000);

	long minStartTime = this->GetSourceOffset()*1000;
	long destStartTime = this->GetDestinationOffset()*1000;
	if(destStartTime < minStartTime){
		minStartTime = destStartTime;
	}
	if(minStartTime < 0){
		this->syncPoint -= minStartTime;
	}
	this->triggerTime = SDL_GetTicks();
	if(this->sourcePosition == ppTransitionSourcePosition::NEXT_BAR){
		int bar = this->actualSource->GetCurrentBar(this->actualSource->GetCurrentTime()+this->GetSyncPoint());
		float difTime = this->actualSource->GetTimeForBar(bar+1) - this->GetSyncPoint() - this->actualSource->GetCurrentTime();
		this->triggerTime += (Uint32)(difTime*1000);
	}else if(this->sourcePosition == ppTransitionSourcePosition::NEXT_BEAT){
		int beat = this->actualSource->GetTotalBeat(this->actualSource->GetCurrentTime()+this->GetSyncPoint());
		float difTime = this->actualSource->GetTimeForBeat(beat+1) - this->GetSyncPoint() - this->actualSource->GetCurrentTime();
		this->triggerTime += (Uint32)(difTime*1000);
	}

	new ppTimeListener(this->actualSource, this);
	new ppTimeListener(this->actualDest, this);
}

void ppTransition::Update(){
	if(!this->transitioning || this->GetTransitionPosition() < 0){
		return;
	}
	ppGenericSound* source = this->sourceSound;
	ppEasing* sourceEasing = this->sourceEasing;
	ppGenericSound* dest = this->destSound;
	ppEasing* destEasing = this->destEasing;
	ppGenericSound* transition = this->transitionTrack;
	if(!source){
		source = this->actualSource;
	}
	// If its destination is to "any" track, use the target
	if(!dest){
		dest = this->actualDest;
	}
	long currentTime = this->GetTransitionPosition()*1000;

	long sourceStartTime = this->GetSourceOffset()*1000;
	long destStartTime = this->GetDestinationOffset()*1000;

	long minStartTime = sourceStartTime;
	if(destStartTime < minStartTime){
		minStartTime = destStartTime;
	}
	if(minStartTime < 0){
		sourceStartTime -= minStartTime;
		destStartTime -= minStartTime;
	}

	// Source time calculation
	long sourceEndTime = sourceStartTime+this->GetSourceDuration()*1000;

	// Transition time calculation
	long transitionEntryCue = 0;
	long transitionExitCue = 0;
	long transitionStartTime = 0;
	long transitionDuration = 0;
	long transitionEndTime = 0;
	if(transition){
		transitionEntryCue = transition->GetAudioFormat()->PositionToTime(transition->GetEntryCue())*1000;
		transitionExitCue = transition->GetAudioFormat()->PositionToTime(transition->GetNormalExitCue())*1000;
		transitionStartTime = this->syncPoint-transitionEntryCue;
		transitionDuration = transitionExitCue-transitionEntryCue;
		transitionEndTime = this->syncPoint+transitionDuration+((transition->GetTotalTime()*1000)-transitionExitCue);
		long destEntryCue = 0;
		if(dest){
			destEntryCue = dest->GetAudioFormat()->PositionToTime(dest->GetEntryCue())*1000;
		}
		destStartTime = this->syncPoint+transitionDuration-destEntryCue;
	}

	// Destination time calculation
	long destEndTime = destStartTime+this->GetDestinationDuration()*1000;

	if(transition && currentTime >= transitionStartTime && currentTime < transitionEndTime && !transition->IsPlaying()){
		transition->Play();
	}else if(transition && currentTime >= transitionEndTime && transition->IsPlaying()){
		transition->StopDecay(true);
	}

	if(source && currentTime >= sourceStartTime && currentTime < sourceEndTime && sourceEasing){
		if(!source->IsPlaying()){
			source->Play();
		}
		float v = sourceEasing->GetValue(sourceEndTime-currentTime, this->sourceDuration*1000, 0, 1);
		source->SetVolume(v);
	}else if(source && currentTime >= sourceEndTime && !sourceEasing){
		source->SetVolume(0);
	}
	if(dest && currentTime >= destStartTime && currentTime < destEndTime){
		if(!dest->IsPlaying()){
			if(this->destPosition == ppTransitionDestinationPosition::SAME_TIME){
				dest->Seek(source->GetCurrentTime());
			}
			dest->Play();
		}
		float v = 1;
		if(destEasing){
			v -= destEasing->GetValue(destEndTime-currentTime, this->destDuration*1000, 0, 1);
		}
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

ppGenericSound* ppTransition::GetTransitionTrack(){
	return this->transitionTrack;
}

ppGenericSound* ppTransition::GetActualDestination(){
	return this->actualDest;
}

float ppTransition::GetTransitionPosition(){
	// Convert unsigned to float then subtract it
	return (SDL_GetTicks()/1000.0f)-(this->triggerTime/1000.0f);
}

float ppTransition::GetSyncPoint(){
	return this->syncPoint/1000.0f;
}

void ppTransition::SetSourcePosition(ppTransitionSourcePosition sourcePosition){
	this->sourcePosition = sourcePosition;
}

void ppTransition::SetDestinationPosition(ppTransitionDestinationPosition destPosition){
	this->destPosition = destPosition;
}

void ppTransition::SetTransitionTrack(ppGenericSound* transitionTrack){
	this->transitionTrack = transitionTrack;
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
