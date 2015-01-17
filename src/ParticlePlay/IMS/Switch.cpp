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
	this->currentTransition->Trigger(this->lastPlay, this->ims->GetSound(stateName));
	this->stateName = stateName;

	this->readyForTransition = false;
}

void ppSwitch::Update(ppInput* input){
	ppControl::Update(input);
}

void ppSwitch::Update(){
	ppUpdatable::Update();
	if(this->currentTransition){
		this->currentTransition->Update();

		if(!this->currentTransition->IsTransitioning()){
			this->lastPlay = this->currentTransition->GetActualDestination();
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
		ppGenericSound* source = this->currentTransition->GetActualSource();
		ppGenericSound* dest = this->currentTransition->GetActualDestination();

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
			int offset = this->currentTransition->GetTransitionPosition() * (this->width - 2) / maxDuration / 1000;
			glVertex3f(this->x+offset, this->y+1, 0);
			glVertex3f(this->x+offset, this->y+this->height, 0);
		}
		glEnd();
	}
}

ppControlType ppSwitch::GetType(){
	return ppControlType::SWITCH_CONTROL;
}
