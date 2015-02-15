#include "TimeListener.hpp"

void ppTimeListenerCallback::OnBar(ppGenericSound* source){}

void ppTimeListenerCallback::OnBeat(ppGenericSound* source){}

void ppTimeListenerCallback::OnNextCue(ppGenericSound* source){}

void ppTimeListenerCallback::OnExitCue(ppGenericSound* source){}

ppTimeListener::ppTimeListener(ppGenericSound* source, ppTimeListenerCallback* callback){
	this->source = source;
	this->callback = callback;
	this->currentBeat = -1;
	this->currentBar = -1;
}

void ppTimeListener::Update(){
	if(this->source && this->callback){
		if(this->currentBar != this->source->GetCurrentBar()){
			this->currentBar = this->source->GetCurrentBar();
			this->callback->OnBar(this->source);
		}
		if(this->currentBeat != this->source->GetCurrentBeat()){
			this->currentBeat = this->source->GetCurrentBeat();
			this->callback->OnBeat(this->source);
		}
	}
}
