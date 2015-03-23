#include "TimeListener.hpp"

void ppTimeListenerCallback::OnBar(ppGenericSound* source){}

void ppTimeListenerCallback::OnBeat(ppGenericSound* source){}

void ppTimeListenerCallback::OnEntryCue(ppGenericSound* source){}

void ppTimeListenerCallback::OnExitCue(ppGenericSound* source){}

ppTimeListener::ppTimeListener(ppGenericSound* source, ppTimeListenerCallback* callback){
	this->offset = 0;
	this->source = source;
	this->callback = callback;
	this->currentBeat = -1;
	this->currentBar = -1;
	this->entryCooldown = 0;
	this->exitCooldown = 0;
}

void ppTimeListener::SetOffset(float offset){
	this->offset = offset;
}

void ppTimeListener::Update(){
	if(this->source && this->callback){
		if(this->currentBar != this->source->GetCurrentBar(this->source->GetCurrentTime()+this->offset)){
			this->currentBar = this->source->GetCurrentBar(this->source->GetCurrentTime()+this->offset);
			this->callback->OnBar(this->source);
		}
		if(this->currentBeat != this->source->GetCurrentBeat(this->source->GetCurrentTime()+this->offset)){
			this->currentBeat = this->source->GetCurrentBeat(this->source->GetCurrentTime()+this->offset);
			this->callback->OnBeat(this->source);
		}
		if(this->entryCooldown == 0 && this->source->GetCurrentTime() >= this->source->GetAudioFormat()->PositionToTime(this->source->GetEntryCue())-this->offset && this->source->GetCurrentTime() <= this->source->GetAudioFormat()->PositionToTime(this->source->GetEntryCue())+0.01f-this->offset){
			this->entryCooldown = 50;
			this->callback->OnEntryCue(this->source);
		}else if(this->entryCooldown > 0){
			this->entryCooldown--;
		}
		if(this->exitCooldown == 0 && this->source->GetCurrentTime() >= this->source->GetAudioFormat()->PositionToTime(this->source->GetNormalExitCue())-this->offset && this->source->GetCurrentTime() <= this->source->GetAudioFormat()->PositionToTime(this->source->GetNormalExitCue())+0.01f-this->offset){
			this->exitCooldown = 50;
			this->callback->OnExitCue(this->source);
		}else if(this->exitCooldown > 0){
			this->exitCooldown--;
		}
	}
}
