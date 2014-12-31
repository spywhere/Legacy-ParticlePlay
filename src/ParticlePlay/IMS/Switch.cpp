#include "Switch.hpp"

bool ppSwitch::ppTransitionOrdering(ppTransition* a, ppTransition* b){
	return a->GetPriority()<b->GetPriority();
}

ppSwitch::ppSwitch(const char *name, ppIMS* ims) : ppControl(name, 0, 0) {
	this->ims = ims;
	this->lastPlay = NULL;
	this->stateName = "";
	this->defaultTransition = new ppTransition(this, 0, NULL, NULL);
	this->currentTransition = NULL;
	this->readyForTransition = true;
	this->switchTime = 0;
}

ppSwitch::~ppSwitch(){
	for(auto transition : this->transitions){
		delete transition;
	}
}

const char *ppSwitch::GetCurrentState(){
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

	this->currentTransition = this->FindTransition(this->stateName, stateName);
	this->switchTime = SDL_GetTicks();
	this->currentTransition->SetSourceStartTime(this, this->switchTime+(Uint32)(this->currentTransition->GetSourceOffset()*1000));
	this->currentTransition->SetSourceEndTime(this, this->switchTime+(Uint32)(this->currentTransition->GetSourceOffset()*1000)+(Uint32)(this->currentTransition->GetSourceDuration()*1000));
	this->currentTransition->SetDestinationStartTime(this, this->switchTime+(Uint32)(this->currentTransition->GetDestinationOffset()*1000));
	this->currentTransition->SetDestinationEndTime(this, this->switchTime+(Uint32)(this->currentTransition->GetDestinationOffset()*1000)+(Uint32)(this->currentTransition->GetDestinationDuration()*1000));
	this->stateName = stateName;
	this->readyForTransition = false;
}

void ppSwitch::Update(ppInput* input){
	ppControl::Update(input);
}

void ppSwitch::Update(){
	ppUpdatable::Update();
	if(this->currentTransition){
		ppGenericSound* source = this->currentTransition->GetSource();
		ppEasing* sourceEasing = this->currentTransition->GetSourceCurve();
		ppGenericSound* dest = this->currentTransition->GetDestination();
		ppEasing* destEasing = this->currentTransition->GetDestinationCurve();
		if(!source && this->lastPlay){
			source = this->lastPlay;
		}
		// If it's to any track, search it
		if(!dest){
			dest = this->ims->GetSound(this->stateName);
		}
		Uint32 currentTime = SDL_GetTicks();
		if(source && currentTime >= this->currentTransition->GetSourceStartTime(this) && currentTime < this->currentTransition->GetSourceEndTime(this)){
			if(!source->IsPlaying()){
				source->Play();
			}
			float v = sourceEasing->GetValue(this->currentTransition->GetSourceEndTime(this)-currentTime, this->currentTransition->GetSourceDuration()*1000, 0, 1);
			source->SetVolume(v);
		}
		if(dest && currentTime >= this->currentTransition->GetDestinationStartTime(this) && currentTime < this->currentTransition->GetDestinationEndTime(this)){
			if(!dest->IsPlaying()){
				if(this->currentTransition->GetDestinationPosition() == ppTransitionDestinationPosition::SAME_TIME){
					dest->Seek(source->GetCurrentTime());
				}
				dest->Play();
			}
			float v = 1-destEasing->GetValue(this->currentTransition->GetDestinationEndTime(this)-currentTime, this->currentTransition->GetDestinationDuration()*1000, 0, 1);
			dest->SetVolume(v);
		}
		if(source && currentTime > this->currentTransition->GetSourceEndTime(this)){
			source->StopDecay(true);
		}
		if(dest && currentTime > this->currentTransition->GetDestinationEndTime(this)){
			dest->SetVolume(1);
		}
		if(currentTime > this->currentTransition->GetSourceEndTime(this) && currentTime > this->currentTransition->GetDestinationEndTime(this)){
			this->lastPlay = dest;
			this->currentTransition = NULL;
			this->readyForTransition = true;
		}
	}
}

void ppSwitch::Render(SDL_Renderer* renderer){
	ppControl::Render(renderer);
	if(!this->visible){
		return;
	}


	if(this->currentTransition){
		float maxOffset = this->currentTransition->GetSourceOffset();
		if(this->currentTransition->GetDestinationOffset() > maxOffset){
			maxOffset = this->currentTransition->GetDestinationOffset();
		}
		float maxDuration = this->currentTransition->GetSourceDuration();
		if(this->currentTransition->GetDestinationDuration() > maxDuration){
			maxDuration = this->currentTransition->GetDestinationDuration();
		}
		float maxWidth = maxOffset+maxDuration;
		ppGenericSound* source = this->currentTransition->GetSource();
		ppGenericSound* dest = this->currentTransition->GetDestination();
		Uint32 currentTime = SDL_GetTicks();
		if(!source && this->lastPlay){
			source = this->lastPlay;
		}
		if(!dest){
			dest = this->ims->GetSound(this->stateName);
		}

		//Border
		glBegin(GL_LINE_LOOP);
		{
			glColor3f(1, 1, 1);
			glVertex3f(this->x, this->y, 0);
			glVertex3f(this->x+this->width, this->y, 0);
			glVertex3f(this->x+this->width, this->y+this->height, 0);
			glVertex3f(this->x, this->y+this->height, 0);
		}
		glEnd();

		//Source
		glBegin(GL_QUADS);
		{
			int sourceOffset = this->currentTransition->GetSourceOffset() * this->width / maxWidth;
			int sourceLength = this->currentTransition->GetSourceDuration() * this->width / maxWidth;
			if(source){
				glColor3f(1, 0.7f, 0.7f);
			}else{
				glColor3f(0.4f, 0.3f, 0.3f);
			}
			glVertex3f(this->x+sourceOffset, this->y, 0);
			glVertex3f(this->x+sourceOffset+sourceLength, this->y, 0);
			glVertex3f(this->x+sourceOffset+sourceLength, this->y+this->height/2, 0);
			glVertex3f(this->x+sourceOffset, this->y+this->height/2, 0);
		}
		glEnd();

		//Source Transition
		glBegin(GL_LINE_STRIP);
		{
			int sourceOffset = this->currentTransition->GetSourceOffset() * this->width / maxWidth;
			glColor3f(0.7f, 0, 0);
			glVertex3f(this->x, this->y+1, 0);
			glVertex3f(this->x+sourceOffset, this->y+1, 0);
			for(int x=sourceOffset;x<this->width;x++){
				glVertex3f(this->x+x, this->y+1+this->currentTransition->GetSourceCurve()->GetValue(x-sourceOffset, this->width-sourceOffset, 0, this->height/2), 0);
			}
		}
		glEnd();

		//Destination
		glBegin(GL_QUADS);
		{
			int destOffset = this->currentTransition->GetDestinationOffset() * this->width / maxWidth;
			int destLength = this->currentTransition->GetDestinationDuration() * this->width / maxWidth;
			if(dest){
				glColor3f(0.7f, 1, 0.7f);
			}else{
				glColor3f(0.3f, 0.4f, 0.3f);
			}
			glVertex3f(this->x+destOffset, this->y+this->height/2, 0);
			glVertex3f(this->x+destOffset+destLength, this->y+this->height/2, 0);
			glVertex3f(this->x+destOffset+destLength, this->y+this->height, 0);
			glVertex3f(this->x+destOffset, this->y+this->height, 0);
		}
		glEnd();

		//Destination Transition
		glBegin(GL_LINE_STRIP);
		{
			int destOffset = this->currentTransition->GetDestinationOffset() * this->width / maxWidth;
			glColor3f(0, 0.7f, 0);
			glVertex3f(this->x, this->y+this->height/2+1, 0);
			glVertex3f(this->x+destOffset, this->y+this->height/2+1, 0);
			for(int x=destOffset;x<this->width;x++){
				glVertex3f(this->x+x, this->y+this->height+1-this->currentTransition->GetDestinationCurve()->GetValue(x-destOffset, this->width-destOffset, 0, this->height/2), 0);
			}
		}
		glEnd();

		//Playing Cursor
		glBegin(GL_LINES);
		{
			glColor3f(0.5f, 0.5f, 1);
			int offset = (currentTime-this->switchTime)*(this->width-2)/maxDuration/1000;
			glVertex3f(this->x+offset, this->y+1, 0);
			glVertex3f(this->x+offset, this->y+this->height, 0);
		}
		glEnd();
	}
}

ppControlType ppSwitch::GetType(){
	return ppControlType::SWITCH_CONTROL;
}
