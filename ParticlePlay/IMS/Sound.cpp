#include "Sound.hpp"

#include <iostream>

ppSound::ppSound(const char *name, ppFormat* audioFormat, int track, ppRandomizer* randomizer) : ppGenericSound(name){
	this->randomizer = randomizer;
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
	ppGenericSound::~ppGenericSound();
	alDeleteSources(1, &this->sourceID);
    alDeleteBuffers(2, this->bufferSet);
}

void ppSound::SetTrack(int track){
	if(track<1){
		#ifdef PPDEBUG
			throw std::runtime_error("Track number must be 1 or greater. (" + audioFormat->GetFileName() + ")");
		#else
			std::cout << "Track number must be 1 or greater. (" << audioFormat->GetFileName() << ")" << std::endl;
		#endif
		return;
	}
	this->track = track-1;
	this->loadingTrack = this->track;
}

void ppSound::SetPlayOrder(ppSoundPlayOrder playOrder){
	this->playOrder = playOrder;
	this->trackList.clear();
	if(this->playOrder == ppSoundPlayOrder::LOOP || this->playOrder == ppSoundPlayOrder::RANDOM){
		this->trackList.push_back(this->track);
	}else if(this->playOrder == ppSoundPlayOrder::SHUFFLE){
		std::list<int> sequencelist;
		for(int i=0;i<this->audioFormat->GetTotalTrack();i++){
			sequencelist.push_back((this->track+i)%this->audioFormat->GetTotalTrack());
		}
		while(!sequencelist.empty()){
			auto numit = sequencelist.begin();
			advance(numit, this->randomizer->NextInt(sequencelist.size()));
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

ppSoundPlayOrder ppSound::GetPlayOrder(){
	return this->playOrder;
}

void ppSound::GetNextTrack(){
	if(this->track!=this->loadingTrack){
		return;
	}
	this->loadingTrack = this->trackList.front();
	this->trackList.pop_front();
	if(this->playOrder == ppSoundPlayOrder::RANDOM){
		this->loadingTrack = this->randomizer->NextInt(this->audioFormat->GetTotalTrack());
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

void ppSound::SetClipStart(Sint64 clipping){
	clipping = this->audioFormat->RelativePosition(clipping);
	ppClippable::SetClipStart(clipping);
	this->nextReadPosition = this->clipStart;
}

void ppSound::SetClipEnd(Sint64 clipping){
	clipping = this->audioFormat->RelativePosition(clipping);
	ppClippable::SetClipEnd(clipping);
}

void ppSound::Preload(){
	// this->GetNextTrack();
	this->Stop();
	alSourceUnqueueBuffers(this->sourceID, 2, this->bufferSet);

	char *bufferData = new char[this->bufferSize];
	int totalBuffer = 0;
	while(totalBuffer<2){
		Sint64 sizeLeft = this->audioFormat->RelativePosition(this->GetPositionLength())-this->nextReadPosition+this->clipStart;
		if(this->bufferSize < sizeLeft){
			sizeLeft = this->bufferSize;
		}
		Sint64 size = this->audioFormat->Read(bufferData, this->nextReadPosition, sizeLeft, this->loadingTrack);
		this->nextReadPosition += size;
		alBufferData(this->bufferSet[totalBuffer], this->audioFormat->GetFormat(), bufferData, size, this->audioFormat->GetSampleRate());
		totalBuffer++;
		if(size<this->bufferSize){
			this->GetNextTrack();
			this->nextReadPosition = this->clipStart;
		}
	}
	delete[] bufferData;

	alSourceQueueBuffers(this->sourceID, 2, this->bufferSet);

	this->preload = true;
}

void ppSound::Update(){
	ppGenericSound::Update();
	ALint processedBuffer;
	alGetSourcei(this->sourceID, AL_BUFFERS_PROCESSED, &processedBuffer);
	char *bufferData = new char[this->bufferSize];
	while(processedBuffer>0 && !this->IsStop()){
		processedBuffer--;
		this->totalBufferProcessed++;
		ALuint bufferID;
		alSourceUnqueueBuffers(this->sourceID, 1, &bufferID);

		Sint64 sizeLeft = this->audioFormat->RelativePosition(this->GetPositionLength())-this->nextReadPosition+this->clipStart;
		if(this->bufferSize < sizeLeft){
			sizeLeft = this->bufferSize;
		}
		Sint64 size = this->audioFormat->Read(bufferData, this->nextReadPosition, sizeLeft, this->loadingTrack);
		this->nextReadPosition += size;
		alBufferData(bufferID, this->audioFormat->GetFormat(), bufferData, size, this->audioFormat->GetSampleRate());
		alSourceQueueBuffers(this->sourceID, 1, &bufferID);
		if(size<this->bufferSize){
			this->GetNextTrack();
			if(!this->IsAutoLoop() || this->loop == 0){
				break;
			}
			this->nextReadPosition = this->clipStart;
		}
	}
	if(this->GetCurrentPosition()>=this->GetPositionLength()||this->totalBufferProcessed>=this->GetTotalBuffer(true)){
		this->track = this->loadingTrack;
		if(this->loop == 0){
			this->nextReadPosition = this->clipStart;
			this->Stop();
		}else if(loop > 0){
			this->loop--;
		}
		this->totalBufferProcessed = 0;
		this->startReadPosition = 0;
		if(!this->IsAutoLoop()){
			this->Stop();
		}
	}
	delete[] bufferData;
}

void ppSound::StopDecay(bool decay){
	if(!this->isPlaying){
		return;
	}
	ppGenericSound::StopDecay(decay);
	alSourceStop(this->sourceID);
	alSourceUnqueueBuffers(this->sourceID, 2, this->bufferSet);

	this->track = this->loadingTrack;
	this->nextReadPosition = this->clipStart;
	this->totalBufferProcessed = 0;
	this->startReadPosition = 0;
	this->preload = false;
}

void ppSound::Play(){
	ALint sourceState;
	alGetSourcei(this->sourceID, AL_SOURCE_STATE, &sourceState);
	if(sourceState==AL_PLAYING){
		return;
	}
	if(!this->IsPause() && !this->preload){
		this->Preload();
	}
	ppGenericSound::Play();
	alSourcePlay(this->sourceID);
}

void ppSound::Pause(){
	if(this->IsPause()){
		return;
	}
	ppGenericSound::Pause();
	alSourcePause(this->sourceID);
}

void ppSound::Seek(Sint64 position){
	this->startReadPosition = position;
	this->nextReadPosition = this->clipStart+position;
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
	return this->audioFormat->GetPositionLength()-this->audioFormat->ActualPosition(this->clipStart+this->clipEnd);
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

ALuint ppSound::GetSourceID(){
	return this->sourceID;
}

void ppSound::Render(ppGraphics* graphics){
	ppControl::Render(graphics);
	if(!this->visible){
		return;
	}
	//Border
	graphics->SetColor(new ppColor(1.0f, 1.0f, 1.0f));
	graphics->DrawRect(this->x, this->y, this->width, this->height);

	//Skipped position
	int skippedWidth = this->audioFormat->ActualPosition(this->startReadPosition)*(this->width-2)/this->GetPositionLength();
	graphics->SetColor(new ppColor(1.0f, 0.8f, 0.8f, 0.5f));
	graphics->FillRect(this->x, this->y+1, skippedWidth, this->height);

	//Total processed buffer
	int width = this->audioFormat->ActualPosition(this->totalBufferProcessed*this->bufferSize)*(this->width-2)/this->GetPositionLength();
	graphics->SetColor(new ppColor(0.8f, 0.8f, 1, 0.5f));
	graphics->FillRect(this->x+skippedWidth, this->y+1, width, this->height);

	//Playing Cursor
	int offset = this->GetCurrentTime()*(this->width-2)/this->GetTotalTime();
	graphics->SetColor(new ppColor(1.0f, 1.0f, 1.0f));
	graphics->DrawLine(this->x+offset, this->y+1, this->x+offset, this->y+this->height);

	//Next read position
	offset = this->audioFormat->ActualPosition(this->nextReadPosition-this->clipStart)*(this->width-2)/this->GetPositionLength();
	graphics->SetColor(new ppColor(1.0f, 1.0f, 1.0f));
	graphics->SetVertex(this->x+offset-3, this->y+4);
	graphics->SetVertex(this->x+offset, this->y+1);
	graphics->SetVertex(this->x+offset+3, this->y+4);
	graphics->DrawPolygon();
}

void ppSound::Update(ppInput* input){
	ppControl::Update(input);
}

ppControlType ppSound::GetType(){
	return ppControlType::SOUND_CONTROL;
}
