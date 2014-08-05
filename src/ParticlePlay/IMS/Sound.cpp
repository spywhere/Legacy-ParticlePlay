#include "Sound.hpp"

ppSound::ppSound(const char *name, ppFormat* audioFormat, int track) : ppControl(name, 0, 0) {
	if(track<1){
		throw std::runtime_error("Track number must be 1 or greater. (" + audioFormat->GetFileName() + ")");
	}
	this->track = track-1;
	this->audioFormat = audioFormat;
	this->bufferSize = audioFormat->GetSampleRate()*2;
}

void ppSound::Preload(){
	if(!this->stop){
		//this->Stop();
	}
	alDeleteSources(1, &this->sourceID);
	alDeleteBuffers(2, this->bufferSet);
	alGenBuffers(2, this->bufferSet);
	alGenSources(1, &this->sourceID);
}

int ppSound::GetCurrentPosition(){
	return 0;
}

int ppSound::GetPositionLength(){
	return this->audioFormat->GetPositionLength();
}

float ppSound::GetCurrentTime(){
	return this->audioFormat->PositionToTime(this->GetCurrentPosition());
}

float ppSound::GetTotalTime(){
	return this->audioFormat->PositionToTime(this->GetPositionLength());
}

int ppSound::GetTrack(){
	return this->track+1;
}

ppFormat *ppSound::GetAudioFormat(){
	return this->audioFormat;
}

void ppSound::Render(SDL_Renderer* renderer){
	ppControl::Render(renderer);
	if(!this->visible){
		return;
	}
	//Border
	glBegin(GL_LINE_LOOP);
		glColor3f(1, 1, 1);
		glVertex3f(this->x, this->y, 0);
		glVertex3f(this->x+this->width, this->y, 0);
		glVertex3f(this->x+this->width, this->y+this->height, 0);
		glVertex3f(this->x, this->y+this->height, 0);
	glEnd();
	//Playing Cursor
	glBegin(GL_LINES);
	// glBegin(GL_QUADS);
		glColor3f(0.7f, 0.7f, 1);
		int offset = this->GetCurrentTime()*(this->height-2)/this->GetTotalTime();
		glVertex3f(this->x+1+offset, this->y, 0);
		glVertex3f(this->x+1+offset, this->y+this->height, 0);
	glEnd();
}

void ppSound::Update(ppInput* input){
	ppControl::Update(input);
}

ppControlType ppSound::GetType(){
	return ppControlType::SOUND_VIEW;
}
