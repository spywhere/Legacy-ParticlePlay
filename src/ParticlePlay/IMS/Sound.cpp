#include "Sound.hpp"

#include <iostream>

ppSound::ppSound(const char *name, ppFormat* audioFormat, int track) : ppControl(name, 0, 0) {
	if(track<1){
		throw std::runtime_error("Track number must be 1 or greater. (" + audioFormat->GetFileName() + ")");
	}
	this->track = track-1;
	this->audioFormat = audioFormat;
	this->bufferSize = audioFormat->GetSampleRate()*2;
	this->preload = false;
	this->stop = true;
	this->pause = false;
	this->nextReadPosition = 0;
	this->totalBufferProcessed = 0;
}

ppSound::~ppSound(){
    alDeleteBuffers(2, this->bufferSet);
	alDeleteSources(1, &this->sourceID);
}

void ppSound::Preload(){
	this->Stop();
	alSourceUnqueueBuffers(this->sourceID, 2, this->bufferSet);
	alDeleteSources(1, &this->sourceID);
	alDeleteBuffers(2, this->bufferSet);
	alGenBuffers(2, this->bufferSet);
	alGenSources(1, &this->sourceID);

	char *bufferData = new char[this->bufferSize];
	this->nextReadPosition += this->audioFormat->Read(bufferData, this->nextReadPosition, this->bufferSize, this->track);
	alBufferData(this->bufferSet[0], this->audioFormat->GetFormat(), bufferData, this->bufferSize, this->audioFormat->GetSampleRate());
	this->nextReadPosition += this->audioFormat->Read(bufferData, this->nextReadPosition, this->bufferSize, this->track);
	alBufferData(this->bufferSet[1], this->audioFormat->GetFormat(), bufferData, this->bufferSize, this->audioFormat->GetSampleRate());
	delete[] bufferData;

	alSourceQueueBuffers(this->sourceID, 2, this->bufferSet);

	this->preload = true;
}

void ppSound::Update(){
	ALint processedBuffer;
	alGetSourcei(this->sourceID, AL_BUFFERS_PROCESSED, &processedBuffer);
	char *bufferData = new char[this->bufferSize];
	while(processedBuffer--){
		this->totalBufferProcessed++;
		ALuint bufferID;
		alSourceUnqueueBuffers(this->sourceID, 1, &bufferID);
		this->nextReadPosition += this->audioFormat->Read(bufferData, this->nextReadPosition, this->bufferSize, this->track);
		alBufferData(bufferID, this->audioFormat->GetFormat(), bufferData, this->bufferSize, this->audioFormat->GetSampleRate());
		alSourceQueueBuffers(this->sourceID, 1, &bufferID);
	}
	delete[] bufferData;
}

void ppSound::Stop(){
	if(this->stop){
		return;
	}
	alSourceStop(this->sourceID);
	this->stop = true;
}

void ppSound::Play(){
	ALint sourceState;
	alGetSourcei(this->sourceID, AL_SOURCE_STATE, &sourceState);
	if(sourceState==AL_PLAYING){
		return;
	}
	if(!this->preload){
		this->Preload();
	}
	this->stop = false;
	alSourcePlay(this->sourceID);
}

bool ppSound::IsReady(){
	return this->preload && this->IsStop();
}

bool ppSound::IsStop(){
	return this->stop;
}

Sint64 ppSound::GetCurrentPosition(){
	int pos;
	alGetSourcei(this->sourceID, AL_BYTE_OFFSET, &pos);
	return this->audioFormat->ActualPosition(((this->totalBufferProcessed*this->bufferSize))+pos);
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
	//Total processed buffer
	glBegin(GL_QUADS);
	{
		glColor4f(0.9f, 0.9f, 1, 0.5f);
		int width = this->audioFormat->ActualPosition(this->totalBufferProcessed*this->bufferSize)*(this->width-2)/this->GetPositionLength();
		glVertex3f(this->x, this->y+1, 0);
		glVertex3f(this->x+width, this->y+1, 0);
		glVertex3f(this->x+width, this->y+this->height, 0);
		glVertex3f(this->x, this->y+this->height, 0);
	}
	glEnd();
	//Next read position
	glBegin(GL_LINE_STRIP);
	{
		glColor3f(1, 1, 1);
		int offset = this->audioFormat->ActualPosition(this->nextReadPosition)*(this->width-2)/this->GetPositionLength();
		glVertex3f(this->x+offset-3, this->y+4, 0);
		glVertex3f(this->x+offset, this->y+1, 0);
		glVertex3f(this->x+offset+3, this->y+4, 0);
	}
	glEnd();
}

void ppSound::Update(ppInput* input){
	ppControl::Update(input);
}

ppControlType ppSound::GetType(){
	return ppControlType::SOUND_VIEW;
}
