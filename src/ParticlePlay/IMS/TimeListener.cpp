#include "TimeListener.hpp"

void ppTimeListenerCallback::OnBar(ppGenericSound* source){}

void ppTimeListenerCallback::OnBeat(ppGenericSound* source){}

void ppTimeListenerCallback::OnNextCue(ppGenericSound* source){}

void ppTimeListenerCallback::OnExitCue(ppGenericSound* source){}

ppTimeListener::ppTimeListener(ppGenericSound* source, ppTimeListenerCallback* callback){
	this->source = source;
	this->callback = callback;
}

void ppTimeListener::Update(){

}
