#include "Stinger.hpp"

#include <iostream>

ppStinger::ppStinger(ppGenericSound* sound, ppStingerTriggerPosition position){
	this->prepare = false;
	this->trigger = false;
	this->sound = sound;
	this->position = position;
}

void ppStinger::Reset(){
	this->prepare = false;
	this->trigger = false;
	this->sound->Stop();
}

void ppStinger::PrepareTrigger(){
	if(this->prepare){
		return;
	}
	this->prepare = true;
	this->sound->Stop();
}

void ppStinger::Trigger(){
	if(!this->prepare || this->trigger){
		return;
	}
	this->trigger = true;
	this->sound->Play();
}

bool ppStinger::IsPreparing(){
	return this->prepare;
}

bool ppStinger::IsTriggering(){
	return this->trigger;
}

float ppStinger::GetEntryCue(){
	return this->sound->GetAudioFormat()->PositionToTime(this->sound->GetEntryCue());
}

ppStingerTriggerPosition ppStinger::GetTriggerPosition(){
	return this->position;
}

void ppStinger::Update(){
	if(this->prepare && this->trigger && this->sound->IsStop()){
		this->Reset();
	}
}
