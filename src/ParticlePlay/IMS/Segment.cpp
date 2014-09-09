#include "Segment.hpp"

ppSegment::ppSegment(const char *name, ppIMS* ims) : ppGenericSound(), ppControl(name, 0, 0){
	this->ims = ims;
	this->emptySound = NULL;
}

ppSegment::~ppSegment(){
	ppGenericSound::~ppGenericSound();
	if(this->emptySound){
		delete this->emptySound;
	}
}

void ppSegment::AddSound(ppGenericSound *sound){
	this->sounds.push_back(sound);

	if(this->emptySound){
		delete this->emptySound;
	}
	Sint64 maxtime = 0;
	for(auto sound : this->sounds){
		if(maxtime<sound->GetOffset()+sound->GetPositionLength()){
			maxtime = sound->GetOffset()+sound->GetPositionLength();
		}
	}
	this->emptySound = new ppSound("_empty", ims->CreateEmptyFormat(maxtime), 1);
}

void ppSegment::ClearSound(){
	this->sounds.clear();
}

Sint64 ppSegment::GetCurrentPosition(){
	return this->emptySound->GetCurrentPosition();
}

Sint64 ppSegment::GetPositionLength(){
	return this->emptySound->GetPositionLength();
}

float ppSegment::GetCurrentTime(){
	return this->emptySound->GetCurrentTime();
}

float ppSegment::GetTotalTime(){
	return this->emptySound->GetTotalTime();
}

void ppSegment::SetLoop(int loop){
	this->emptySound->SetLoop(loop);
}

void ppSegment::Play(){
	this->emptySound->Play();
}

void ppSegment::Pause(){
	this->emptySound->Pause();
	for(auto sound : this->sounds){
		sound->Pause();
	}
}

void ppSegment::Stop(){
	this->emptySound->Stop();
	for(auto sound : this->sounds){
		sound->Stop();
	}
}

void ppSegment::Update(){
	this->emptySound->Update();
	for(auto sound : this->sounds){
		if(sound->GetOffset()<this->GetCurrentPosition() && sound->IsStop() && this->GetCurrentPosition() < sound->GetPositionLength()){
			sound->Play();
		}else if(!sound->IsStop()){
			sound->Stop();
		}
		sound->Update();
	}
}

void ppSegment::Render(SDL_Renderer* renderer){
	ppControl::Render(renderer);
	if(!this->visible){
		return;
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
	//Playing Cursor
	glBegin(GL_LINES);
	{
		glColor3f(0.7f, 0.7f, 1);
		int offset = this->GetCurrentTime()*(this->width-2)/this->GetTotalTime();
		glVertex3f(this->x+offset, this->y+1, 0);
		glVertex3f(this->x+offset, this->y+this->height, 0);
	}
	glEnd();
	int index=1;
	int height=this->height/(this->sounds.size()+1);
	glBegin(GL_QUADS);
	{
		glColor4f(0.8f, 0.5f, 0.5f, 1);
		// int width = this->audioFormat->ActualPosition(this->totalBufferProcessed*this->bufferSize)*(this->width-2)/this->GetPositionLength();
		int width = this->GetCurrentPosition()*(this->width-2)/this->GetPositionLength();
		glVertex3f(this->x, this->y+1, 0);
		glVertex3f(this->x+width, this->y+1, 0);
		glVertex3f(this->x+width, this->y+height, 0);
		glVertex3f(this->x, this->y+height, 0);
	}
	glEnd();
	for(auto sound : this->sounds){
		int offset_width = sound->GetOffset()*(this->width-2)/this->GetPositionLength();
		int width = sound->GetCurrentPosition()*(this->width-2)/this->GetPositionLength();
		int max_width = sound->GetPositionLength()*(this->width-2)/this->GetPositionLength();
		//Total playing time
		glBegin(GL_QUADS);
		{
			glColor4f(0.3f+(0.2f*(index%2)), 0.3f+(0.2f*(index%2)), 0.3f+(0.2f*(index%2)), 1);
			glVertex3f(this->x+offset_width+width, this->y+(index*height)+1, 0);
			glVertex3f(this->x+offset_width+max_width, this->y+(index*height)+1, 0);
			glVertex3f(this->x+offset_width+max_width, this->y+(index*height)+height, 0);
			glVertex3f(this->x+offset_width+width, this->y+(index*height)+height, 0);
		}
		glEnd();
		//Current playing time
		glBegin(GL_QUADS);
		{
			glColor4f(0.5f, 0.5f+(0.3f*(index%2)), 0.5f+(0.3f*((index+1)%2)), 1);
			glVertex3f(this->x+offset_width, this->y+(index*height)+1, 0);
			glVertex3f(this->x+offset_width+width, this->y+(index*height)+1, 0);
			glVertex3f(this->x+offset_width+width, this->y+(index*height)+height, 0);
			glVertex3f(this->x+offset_width, this->y+(index*height)+height, 0);
		}
		glEnd();
		index++;
	}
}

void ppSegment::Update(ppInput* input){
	ppControl::Update(input);
}

ppControlType ppSegment::GetType(){
	return ppControlType::SEGMENT_CONTROL;
}