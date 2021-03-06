#include "Switch.hpp"

#include <iostream>

bool ppSwitch::ppTransitionOrdering(ppTransition* a, ppTransition* b){
	return a->GetPriority()<b->GetPriority();
}

ppSwitch::ppSwitch(const char *name, ppIMS* ims) : ppControl(name, 0, 0) {
	this->ims = ims;
	this->lastPlay = NULL;
	this->stateName = std::string("");
	this->defaultTransition = new ppTransition(this, 0, NULL, NULL);
	this->currentTransition = NULL;
	this->readyForTransition = true;
	this->isPause = false;
	this->isPlaying = false;
	this->timeListener = NULL;
}

ppSwitch::~ppSwitch(){
	for(auto transition : this->transitions){
		delete transition;
	}
}

std::string ppSwitch::GetCurrentState(){
	return this->stateName;
}

ppTransition* ppSwitch::GetDefaultTransition(){
	return this->defaultTransition;
}

ppTransition* ppSwitch::CreateTransition(int priority, ppGenericSound* sourceSound, ppGenericSound* destSound){
	ppTransition* transition = new ppTransition(this, priority, sourceSound, destSound);
	this->transitions.push_back(transition);
	std::sort(this->transitions.begin(), this->transitions.end(), ppSwitch::ppTransitionOrdering);
	return transition;
}

ppStinger* ppSwitch::CreateStinger(const char *stingerName, ppGenericSound* sound, ppStingerTriggerPosition position){
	ppStinger* stinger = new ppStinger(sound, position);
	this->stingers[stingerName] = stinger;
	return stinger;
}

ppTransition* ppSwitch::FindTransition(const char *sourceName, const char *destName){
	for(auto transition : this->transitions){
		if(transition->IsSourceName(sourceName) && transition->IsDestinationName(destName)){
			return transition;
		}
	}
	return this->GetDefaultTransition();
}

void ppSwitch::SwitchState(const char *stateName){
	if(!this->readyForTransition){
		return;
	}
	if(this->currentTransition && this->currentTransition->IsTransitioning()){
		return;
	}
	this->currentTransition = this->FindTransition(this->stateName.c_str(), stateName);
	ppGenericSound* target = this->ims->GetSound(stateName);
	this->timeListener = new ppTimeListener(target, this);
	this->currentTransition->Trigger(this->lastPlay, target);
	this->stateName = std::string(stateName);

	this->readyForTransition = false;
}

void ppSwitch::TriggerStinger(const char *stingerName){
	if(!this->readyForTransition){
		return;
	}
	if(this->currentTransition && this->currentTransition->IsTransitioning()){
		return;
	}
	ppStinger* stinger=this->GetStinger(stingerName);
	if(stinger && !stinger->IsPreparing()){
		stinger->PrepareTrigger();
		if(!stinger->IsTriggering() && stinger->GetTriggerPosition() == ppStingerTriggerPosition::IMMEDIATE){
			stinger->Trigger();
		}else{
			this->timeListener->SetOffset(stinger->GetEntryCue());
		}
	}
}

ppStinger* ppSwitch::GetStinger(const char *stingerName){
	auto it = this->stingers.find(stingerName);
	if (it != this->stingers.end()){
		return it->second;
	}
	return NULL;
}

void ppSwitch::OnBar(ppGenericSound* source){
	for(auto stingerKey : this->stingers){
		ppStinger* stinger = stingerKey.second;
		if(!stinger->IsTriggering() && stinger->GetTriggerPosition() == ppStingerTriggerPosition::NEXT_BAR){
			stinger->Trigger();
		}
	}
}

void ppSwitch::OnBeat(ppGenericSound* source){
	for(auto stingerKey : this->stingers){
		ppStinger* stinger = stingerKey.second;
		if(!stinger->IsTriggering() && stinger->GetTriggerPosition() == ppStingerTriggerPosition::NEXT_BEAT){
			stinger->Trigger();
		}
	}
}

void ppSwitch::OnEntryCue(ppGenericSound* source){
	for(auto stingerKey : this->stingers){
		ppStinger* stinger = stingerKey.second;
		if(!stinger->IsTriggering() && stinger->GetTriggerPosition() == ppStingerTriggerPosition::ENTRY_CUE){
			stinger->Trigger();
		}
	}
}

void ppSwitch::OnExitCue(ppGenericSound* source){
	for(auto stingerKey : this->stingers){
		ppStinger* stinger = stingerKey.second;
		if(!stinger->IsTriggering() && stinger->GetTriggerPosition() == ppStingerTriggerPosition::EXIT_CUE){
			stinger->Trigger();
		}
	}
}

void ppSwitch::Play(){
	if(!this->IsStop() || this->IsPlaying()){
		return;
	}
	// TODO
	// Play/Resume sound and transition
}

void ppSwitch::Pause(){
	if(this->IsStop() || this->IsPause()){
		return;
	}
	// TODO
	// Pause sound and transition
}

void ppSwitch::Stop(){
	if(this->IsStop()){
		return;
	}
	// TODO
	// Stop sound and transition
}

bool ppSwitch::IsPlaying(){
	return this->isPlaying && !this->isPause;
}

bool ppSwitch::IsPause(){
	return this->isPlaying && this->isPause;
}

bool ppSwitch::IsStop(){
	return !this->isPlaying;
}

bool ppSwitch::IsStingerTrigger(const char *stingerName){
	ppStinger* stinger = this->GetStinger(stingerName);
	return stinger && stinger->IsPreparing();
}

bool ppSwitch::IsTransitioning(){
	return this->currentTransition && this->currentTransition->IsTransitioning();
}

void ppSwitch::Update(ppInput* input){
	ppControl::Update(input);
}

void ppSwitch::Update(){
	ppUpdatable::Update();
	if(this->timeListener){
		this->timeListener->Update();
	}
	for(auto stinger : this->stingers){
		stinger.second->Update();
	}
	if(this->currentTransition){
		this->currentTransition->Update();
		if(!this->currentTransition->IsTransitioning()){
			this->lastPlay = this->currentTransition->GetActualDestination();
			this->currentTransition = NULL;
			this->readyForTransition = true;
			for(auto stinger : this->stingers){
				stinger.second->Reset();
			}
		}
	}
}

void ppSwitch::Render(ppGraphics* graphics){
	ppControl::Render(graphics);
	if(!this->visible){
		return;
	}

	if(this->currentTransition){
		ppGenericSound* source = this->currentTransition->GetActualSource();
		ppGenericSound* dest = this->currentTransition->GetActualDestination();
		float minimumStartTime = this->currentTransition->GetSourceOffset();
		float maximumStartTime = this->currentTransition->GetDestinationOffset();
		if(this->currentTransition->GetDestinationOffset() < minimumStartTime){
			minimumStartTime = this->currentTransition->GetDestinationOffset();
			maximumStartTime = this->currentTransition->GetSourceOffset();
		}
		float maximumEndTime = this->currentTransition->GetSourceDuration();
		if(this->currentTransition->GetDestinationDuration() > maximumEndTime){
			maximumEndTime = this->currentTransition->GetDestinationDuration();
		}

		float maxWidth = maximumEndTime;
		if(maximumStartTime > 0){
			maxWidth += maximumStartTime;
		}
		if(minimumStartTime < 0){
			maxWidth -= minimumStartTime;
		}

		//Border
		graphics->SetColor(new ppColor(1.0f, 1.0f, 1.0f));
		graphics->DrawRect(this->x, this->y, this->width, this->height);

		//Source
		int sourceOffset = this->currentTransition->GetSourceOffset() * this->width / maxWidth;
		if(minimumStartTime < 0){
			sourceOffset = (this->currentTransition->GetSourceOffset() - minimumStartTime) * this->width / maxWidth;
		}
		int sourceLength = this->currentTransition->GetSourceDuration() * this->width / maxWidth;
		if(source){
			graphics->SetColor(new ppColor(1, 0.7f, 0.7f));
		}else{
			graphics->SetColor(new ppColor(0.4f, 0.3f, 0.3f));
		}
		graphics->FillRect(this->x+sourceOffset, this->y, sourceLength, this->height/2);

		//Source Transition
		sourceOffset = this->currentTransition->GetSourceOffset() * this->width / maxWidth;
		if(minimumStartTime < 0){
			sourceOffset = (this->currentTransition->GetSourceOffset() - minimumStartTime) * this->width / maxWidth;
		}
		graphics->SetColor(new ppColor(0.7f, 0.0f, 0.0f));

		graphics->SetVertex(this->x, this->y+1);
		graphics->SetVertex(this->x+sourceOffset, this->y+1);
		if(this->currentTransition->GetSourceCurve()){
			int transitionEnd = this->currentTransition->GetSourceDuration() * this->width / maxWidth;
			for(int x=sourceOffset;x<sourceOffset+transitionEnd;x++){
				graphics->SetVertex(this->x+x, this->y+1+this->currentTransition->GetSourceCurve()->GetValue(x-sourceOffset, transitionEnd, 0, this->height/2));
			}
		}else{
			graphics->SetVertex(this->x+x, this->y+1);
		}
		graphics->DrawStrip();

		//Destination
		int destOffset = this->currentTransition->GetDestinationOffset() * this->width / maxWidth;
		if(minimumStartTime < 0){
			destOffset = (this->currentTransition->GetDestinationOffset() - minimumStartTime) * this->width / maxWidth;
		}
		int destLength = this->currentTransition->GetDestinationDuration() * this->width / maxWidth;
		if(dest){
			graphics->SetColor(new ppColor(0.7f, 1, 0.7f));
		}else{
			graphics->SetColor(new ppColor(0.3f, 0.4f, 0.3f));
		}
		graphics->FillRect(this->x+destOffset, this->y+this->height/2, destLength, this->height/2);

		//Destination Transition
		destOffset = this->currentTransition->GetDestinationOffset() * this->width / maxWidth;
		if(minimumStartTime < 0){
			destOffset = (this->currentTransition->GetDestinationOffset() - minimumStartTime) * this->width / maxWidth;
		}
		graphics->SetColor(new ppColor(0.0f, 0.7f, 0.0f));

		graphics->SetVertex(this->x, this->y+this->height/2+1);
		graphics->SetVertex(this->x+destOffset, this->y+this->height/2+1);
		int transitionEnd = this->currentTransition->GetDestinationDuration() * this->width / maxWidth;
		if(this->currentTransition->GetDestinationCurve()){
			for(int x=destOffset;x<destOffset+transitionEnd;x++){
				graphics->SetVertex(this->x+x, this->y+this->height+1-this->currentTransition->GetDestinationCurve()->GetValue(x-destOffset, transitionEnd, 0, this->height/2));
			}
		}else{
			graphics->SetVertex(this->x+x, this->y+this->height/2+1);
		}

		graphics->DrawStrip();

		//SyncPoint
		int offset = this->currentTransition->GetSyncPoint() * (this->width - 2) / maxWidth;
		graphics->SetColor(new ppColor(1.0f, 1.0f, 1.0f));
		graphics->DrawLine(this->x+offset, this->y+1, this->x+offset, this->y+this->height);

		//Playing Cursor
		offset = this->currentTransition->GetTransitionPosition() * (this->width - 2) / maxWidth;
		if(this->currentTransition->GetTransitionPosition() < 0){
			offset = -this->currentTransition->GetTransitionPosition() * (this->width - 2) / maxWidth;
		}
		graphics->SetColor(new ppColor(0.5f, 0.5f, 1.0f));
		graphics->DrawLine(this->x+offset, this->y+1, this->x+offset, this->y+this->height);
	}
}

ppControlType ppSwitch::GetType(){
	return ppControlType::SWITCH_CONTROL;
}
