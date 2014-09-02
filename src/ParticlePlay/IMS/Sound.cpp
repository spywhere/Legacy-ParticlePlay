#include "Sound.hpp"

#include <iostream>

ppSound::ppSound(const char *name, ppFormat* audioFormat, int track) : ppGenericSound(), ppControl(name, 0, 0){
	this->SetTrack(track);
	this->audioFormat = audioFormat;
	this->bufferSize = audioFormat->GetSampleRate()*2;
	this->nextReadPosition = 0;
	this->startReadPosition = 0;
	this->totalBufferProcessed = 0;
	alGenBuffers(2, this->bufferSet);
	alGenSources(1, &this->sourceID);
	this->SetPlayOrder(ppSoundPlayOrder::LOOP);
}

ppSound::~ppSound(){
	ppPlayable::~ppPlayable();
	alDeleteSources(1, &this->sourceID);
    alDeleteBuffers(2, this->bufferSet);
}

void ppSound::SetTrack(int track){
	if(track<1){
		throw std::runtime_error("Track number must be 1 or greater. (" + audioFormat->GetFileName() + ")");
	}
	this->track = track-1;
	this->loadingTrack = this->track;
}

void ppSound::SetPlayOrder(ppSoundPlayOrder playOrder){
	this->playOrder = playOrder;
	this->trackList.clear();
	std::srand(unsigned(std::time(0)));
	if(this->playOrder == ppSoundPlayOrder::LOOP || this->playOrder == ppSoundPlayOrder::RANDOM){
		this->trackList.push_back(this->track);
	}else if(this->playOrder == ppSoundPlayOrder::SHUFFLE){
		std::list<int> sequencelist;
		for(int i=0;i<this->audioFormat->GetTotalTrack();i++){
			sequencelist.push_back((this->track+i)%this->audioFormat->GetTotalTrack());
		}
		while(!sequencelist.empty()){
			auto numit = sequencelist.begin();
			advance(numit, std::rand()%sequencelist.size());
			this->trackList.push_back((this->track+(*numit))%this->audioFormat->GetTotalTrack());
			sequencelist.erase(numit);
		}
	}else if(this->playOrder == ppSoundPlayOrder::SEQUENCE){
		for(int i=0;i<this->audioFormat->GetTotalTrack();i++){
			this->trackList.push_back((this->track+i)%this->audioFormat->GetTotalTrack());
		}
	}
	this->GetNextTrack();
	this->track = this->loadingTrack;
}

void ppSound::GetNextTrack(){
	if(this->track!=this->loadingTrack){
		return;
	}
	this->loadingTrack = this->trackList.front();
	this->trackList.pop_front();
	if(this->playOrder == ppSoundPlayOrder::RANDOM){
		this->loadingTrack = std::rand()%this->audioFormat->GetTotalTrack();
	}
	this->trackList.push_back(this->loadingTrack);
}

int ppSound::GetTotalBuffer(bool countCurrent){
	int bufferSize = this->bufferSize*this->audioFormat->GetTotalTrack();
	int totalBuffer = this->GetPositionLength()/bufferSize;
	if(countCurrent && this->GetPositionLength()%bufferSize > 0){
		totalBuffer++;
	}
	return totalBuffer;
}

void ppSound::Preload(){
	this->Stop();
	alSourceUnqueueBuffers(this->sourceID, 2, this->bufferSet);

	char *bufferData = new char[this->bufferSize];
	int totalBuffer = 0;
	while(totalBuffer<2){
		Sint64 size = this->audioFormat->Read(bufferData, this->nextReadPosition, this->bufferSize, this->loadingTrack);
		this->nextReadPosition += size;
		alBufferData(this->bufferSet[totalBuffer], this->audioFormat->GetFormat(), bufferData, size, this->audioFormat->GetSampleRate());
		totalBuffer++;
		if(size<this->bufferSize){
			this->GetNextTrack();
			this->nextReadPosition = 0;
		}
	}
	delete[] bufferData;

	alSourceQueueBuffers(this->sourceID, 2, this->bufferSet);

	this->preload = true;
}

void ppSound::Update(){
	ALint processedBuffer;
	alGetSourcei(this->sourceID, AL_BUFFERS_PROCESSED, &processedBuffer);
	char *bufferData = new char[this->bufferSize];
	while(processedBuffer>0 && !this->IsStop()){
		processedBuffer--;
		this->totalBufferProcessed++;
		ALuint bufferID;
		alSourceUnqueueBuffers(this->sourceID, 1, &bufferID);
		Sint64 size = this->audioFormat->Read(bufferData, this->nextReadPosition, this->bufferSize, this->loadingTrack);
		this->nextReadPosition += size;
		alBufferData(bufferID, this->audioFormat->GetFormat(), bufferData, size, this->audioFormat->GetSampleRate());
		alSourceQueueBuffers(this->sourceID, 1, &bufferID);
		if(size<this->bufferSize){
			this->GetNextTrack();
			this->nextReadPosition = 0;
		}
	}
	if(this->GetCurrentPosition()>=this->GetPositionLength()||this->totalBufferProcessed>=this->GetTotalBuffer(true)){
		this->track = this->loadingTrack;
		if(this->loop == 0){
			this->nextReadPosition = 0;
			this->Stop();
		}else if(loop > 0){
			this->loop--;
		}
		this->totalBufferProcessed = 0;
		this->startReadPosition = 0;
	}
	delete[] bufferData;
}

void ppSound::Stop(){
	if(!this->isPlaying){
		return;
	}
	ppPlayable::Stop();
	alSourceStop(this->sourceID);
	this->preload = false;
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
	ppPlayable::Play();
	alSourcePlay(this->sourceID);
}

void ppSound::Seek(Sint64 position){
	this->startReadPosition = position;
	this->nextReadPosition = position;
	this->totalBufferProcessed = 0;
	this->Preload();
}

void ppSound::Seek(float time){
	this->Seek(this->audioFormat->RelativePosition(this->audioFormat->TimeToPosition(time)));
}

void ppSound::SetVolume(float volume){
	ppGenericSound::SetVolume(volume);
	alSourcef(this->sourceID, AL_GAIN, this->volume);
}

void ppSound::SetSpeed(float speed){
	ppGenericSound::SetSpeed(speed);
	alSourcef(this->sourceID, AL_PITCH, this->speed);
}

Sint64 ppSound::GetCurrentPosition(){
	int pos;
	alGetSourcei(this->sourceID, AL_BYTE_OFFSET, &pos);
	return this->audioFormat->ActualPosition(((this->totalBufferProcessed*this->bufferSize))+pos+this->startReadPosition);
}

Sint64 ppSound::GetPositionLength(){
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
	//Skipped position
	int skippedWidth = this->audioFormat->ActualPosition(this->startReadPosition)*(this->width-2)/this->GetPositionLength();
	glBegin(GL_QUADS);
	{
		glColor4f(1, 0.8f, 0.8f, 0.5f);
		glVertex3f(this->x, this->y+1, 0);
		glVertex3f(this->x+skippedWidth, this->y+1, 0);
		glVertex3f(this->x+skippedWidth, this->y+this->height, 0);
		glVertex3f(this->x, this->y+this->height, 0);
	}
	glEnd();
	//Total processed buffer
	glBegin(GL_QUADS);
	{
		glColor4f(0.8f, 0.8f, 1, 0.5f);
		int width = this->audioFormat->ActualPosition(this->totalBufferProcessed*this->bufferSize)*(this->width-2)/this->GetPositionLength();
		glVertex3f(this->x+skippedWidth, this->y+1, 0);
		glVertex3f(this->x+skippedWidth+width, this->y+1, 0);
		glVertex3f(this->x+skippedWidth+width, this->y+this->height, 0);
		glVertex3f(this->x+skippedWidth, this->y+this->height, 0);
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
