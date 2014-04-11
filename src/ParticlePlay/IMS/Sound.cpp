#include "Sound.h"

ppSound::ppSound(ppIMS* ims){
	this->justLoop = false;
	this->preload = false;
	this->loop = false;
	this->speed = 1.0f;
	this->volumn = 1.0f;
	this->bufferProcessed=0;
	this->targetChannels=1;
	this->track = 0;
	this->filter = NULL;
	this->filePointer = NULL;
}

ppSound::~ppSound(){
    alDeleteBuffers(2, this->bufferSet);
	alDeleteSources(1, &this->sourceID);
}

void ppSound::GetWaveChunkInfo(SDL_RWops *filePointer, char *chunkName, int &chunkSize){
	char buffer[4];
	SDL_RWread(filePointer, chunkName, 4, 1);
	SDL_RWread(filePointer, buffer, 4, 1);
	chunkSize=ConvertToInt(buffer, 4);
}

void ppSound::Preload(){
	this->Preload(this->track, false);
}

void ppSound::Preload(int track){
	this->Preload(track, false);
}

void ppSound::Preload(int track, bool skip){
	this->track = track;
	if(skip){
		return;
	}
	ALint sourceState;
	alGetSourcei(this->sourceID, AL_SOURCE_STATE, &sourceState);
	if(!this->preload&&(sourceState==AL_STOPPED||sourceState==AL_INITIAL)){
		alSourceUnqueueBuffers(this->sourceID, 2, this->bufferSet);
		this->preload = true;
		char *dataBuffer = new char[this->bufferSize];
		this->filePointer = SDL_RWFromFile(this->filename.c_str(), "rb");

		SDL_RWseek(this->filePointer, this->dataReadPosition, RW_SEEK_SET);

		this->ReadData(this->filePointer, dataBuffer, this->bufferSize, this->bufferSet[0]);
		this->dataReadPosition=SDL_RWtell(this->filePointer);
		if(this->dataReadPosition<0||this->dataReadPosition-this->dataStartPosition>this->dataSize){
			//Reopen on eof
			this->dataReadPosition = this->dataStartPosition;
			SDL_RWclose(this->filePointer);
			this->filePointer = SDL_RWFromFile(this->filename.c_str(), "rb");
		}
		SDL_RWseek(this->filePointer, this->dataReadPosition, RW_SEEK_SET);

		this->ReadData(this->filePointer, dataBuffer, this->bufferSize, this->bufferSet[1]);

		this->dataReadPosition=SDL_RWtell(this->filePointer);
		SDL_RWclose(this->filePointer);
		delete[] dataBuffer;
		alSourceQueueBuffers(this->sourceID, 2, this->bufferSet);
	}
}

int ppSound::LoadWaveFile(const char *filename, bool stereo){
	this->filename = std::string(filename);
	this->filePointer = SDL_RWFromFile(this->filename.c_str(), "rb");
	if(!this->filePointer){
		return 1;
	}
	int valid = 0;
	char buffer[4];
	int chunkSize=0;
	while(!SDL_RWread(filePointer, buffer, 0, 1)&&valid<3){
		this->GetWaveChunkInfo(this->filePointer, buffer, chunkSize);
		// std::cout << "Reading... " << buffer << std::endl;
		if(strncmp(buffer, "RIFF", 4)==0){
			//chunkSize = Total chunk in this wave file
			chunkSize=0;
			SDL_RWread(filePointer, buffer, 4, 1);
			if(strncmp(buffer, "WAVE", 4)==0){
				valid++;
			}else{
				break;
			}
		}else if(strncmp(buffer, "fmt ", 4)==0){
			SDL_RWread(filePointer, buffer, 2, 1); //1 = PCM, other = compression
			this->audioFormat=ConvertToInt(buffer, 2);
			chunkSize-=2;
			SDL_RWread(filePointer, buffer, 2, 1);
			this->channels=ConvertToInt(buffer, 2);
			chunkSize-=2;
			SDL_RWread(filePointer, buffer, 4, 1);
			this->sampleRate=ConvertToInt(buffer, 4);
			chunkSize-=4;
			SDL_RWread(filePointer, buffer, 4, 1);
			this->byteRate=ConvertToInt(buffer, 4);
			chunkSize-=4;
			SDL_RWread(filePointer, buffer, 2, 1); //BlockAlign
			chunkSize-=2;
			SDL_RWread(filePointer, buffer, 2, 1);
			this->bitPerSample=ConvertToInt(buffer, 2);
			chunkSize-=2;
			valid++;
		}else if(strncmp(buffer, "data", 4)==0){
			this->dataSize=chunkSize;
			this->dataReadPosition = SDL_RWtell(this->filePointer);;
			this->dataStartPosition = this->dataReadPosition;
			this->dataPositionOffset = 0;
			chunkSize = 0;
			valid++;
		}
		if(chunkSize>0){
			// std::cout << "Skip " << buffer << " [" << chunkSize << "b]" << std::endl;
			//Skip any unread data
			SDL_RWseek(this->filePointer, chunkSize, RW_SEEK_CUR);
		}
	}
	SDL_RWclose(this->filePointer);
	if(valid<3){
		// std::cout << "Invalid Wave file" << std::endl;
		return 2;
	}
	if(stereo){
		this->targetChannels = 2;
	}
	this->totalTrack = this->channels / this->targetChannels;
	if(this->targetChannels==1){
		if(this->bitPerSample==8){
			this->format = AL_FORMAT_MONO8;
		}else{
			this->format = AL_FORMAT_MONO16;
		}
	}else{
		if(this->bitPerSample==8){
			this->format = AL_FORMAT_STEREO8;
		}else{
			this->format = AL_FORMAT_STEREO16;
		}
	}

	alDeleteSources(1, &this->sourceID);
	alDeleteBuffers(2, this->bufferSet);
	alGenBuffers(2, this->bufferSet);
	alGenSources(1, &this->sourceID);

	this->bufferSize = (this->byteRate+this->byteRate);

	return 0;
}

void ppSound::ApplyFilter(ppFilter* filter){
	this->filter = filter;
}

void ppSound::ReadData(SDL_RWops *filePointer, char *dataBuffer, int bufferSize, ALuint &bufferID){
	int x=0;
	for(x=0;x<bufferSize;){
		int bytePerSample = this->bitPerSample/8;
		char *buf = new char[this->channels * 2];
		if(!SDL_RWread(filePointer, buf, this->channels * 2, 1)){
			break;
		}
		for(int c=0;c<this->targetChannels;c++){
			for(int byte=0;byte<this->bitPerSample/8;byte++){
				dataBuffer[x++]=buf[this->track*(this->targetChannels*2)+(c*this->targetChannels+byte)];
			}
		}
		delete[] buf;
	}
	alBufferData(bufferID, this->format, dataBuffer, x, this->sampleRate);
}

void ppSound::Play(){
	this->Play(this->track);
}

void ppSound::Play(int track){
	ALint sourceState;
	alGetSourcei(this->sourceID, AL_SOURCE_STATE, &sourceState);
	if(sourceState==AL_PLAYING){
		if(this->track==track){
			return;
		}else{
			this->Stop();
		}
	}
	this->Preload(track);

	alSourcePlay(this->sourceID);
}

int ppSound::GetTotalBuffer(int dataSize, bool countCurrent){
	int totalBuffer = dataSize/(this->bufferSize*this->totalTrack);
	if(countCurrent&&dataSize%(this->bufferSize*this->totalTrack)>0){
		totalBuffer++;
	}
	return totalBuffer;
}

void ppSound::Update(){
	this->justLoop = false;
	//Stream more data when buffer finished
	ALint processedBuffer;
	alGetSourcei(this->sourceID, AL_BUFFERS_PROCESSED, &processedBuffer);

	char *buffer = new char[this->bufferSize];
	this->filePointer = SDL_RWFromFile(this->filename.c_str(), "rb");

	SDL_RWseek(this->filePointer, this->dataReadPosition, RW_SEEK_SET);

	while(processedBuffer--&&!SDL_RWread(filePointer, buffer, 0, 1)){
		this->bufferProcessed++;
		ALuint bufferID;
		alSourceUnqueueBuffers(this->sourceID, 1, &bufferID);
		this->ReadData(this->filePointer, buffer, this->bufferSize, bufferID);
		this->dataReadPosition=SDL_RWtell(this->filePointer);
		alSourceQueueBuffers(this->sourceID, 1, &bufferID);
	}
	delete[] buffer;
	SDL_RWclose(this->filePointer);
	if(this->filter&&this->filter->IsSupported()){
		alSourcei(this->sourceID, AL_DIRECT_FILTER, filter->GetFilterID());
	}else{
		alSourcei(this->sourceID, AL_DIRECT_FILTER, AL_FILTER_NULL);
	}

	if(this->dataReadPosition<0||this->dataReadPosition-this->dataStartPosition>=this->dataSize){
		this->dataReadPosition = this->dataStartPosition;
	}

	//Add totalBuffer as a new local variable (performance issue)
	if(this->bufferProcessed>=this->GetTotalBuffer(this->dataSize, true)){
		//Current position exceed the track
		//Reset all position
		if(!this->loop){
			this->Stop();
		}
		this->bufferProcessed = 0;
		this->dataPositionOffset = 0;
		this->justLoop = true;
	}
}

float ppSound::ByteToSecond(int byte){
	float sampleLength = byte * 8 / (this->channels * this->bitPerSample);
	return sampleLength / this->sampleRate;
}

int ppSound::SecondToByte(float sec){
	float sampleLength = sec * this->sampleRate;
	return sampleLength * this->channels * this->bitPerSample / 8;
}

void ppSound::Pause(){
	alSourcePause(this->sourceID);
}

void ppSound::Stop(){
	if(this->IsStop()){
		return;
	}
	alSourceStop(this->sourceID);
	alSourceUnqueueBuffers(this->sourceID, 2, this->bufferSet);
	this->preload = false;
	this->dataReadPosition = this->dataStartPosition;
	this->bufferProcessed = 0;
}

void ppSound::SeekPosition(int targetPosition){
	this->SeekPosition(targetPosition, this->track);
}

void ppSound::SeekTime(float targetTime){
	this->SeekTime(targetTime, this->track);
}

void ppSound::SeekPosition(int targetPosition, int track){
	bool isplaying = !this->IsStop();
	if(isplaying){
		this->Stop();
	}
	alSourceUnqueueBuffers(this->sourceID, 2, this->bufferSet);
	this->preload = false;
	this->dataReadPosition = this->dataStartPosition+targetPosition;
	this->bufferProcessed = this->GetTotalBuffer(targetPosition, false);
	this->dataPositionOffset = targetPosition-this->bufferProcessed*this->bufferSize*this->totalTrack;
	this->Preload(track);
	if(isplaying){
		this->Play();
	}
}

void ppSound::SeekTime(float targetTime, int track){
	this->SeekPosition(this->SecondToByte(targetTime), track);
}

void ppSound::SetSpeed(float speed){
	this->speed = speed;
	alSourcef(this->sourceID, AL_PITCH, this->speed);
}

void ppSound::SetVolumn(float vol){
	this->volumn = vol;
	alSourcef(this->sourceID, AL_GAIN, this->volumn);
}

void ppSound::SetLoop(bool loop){
	this->loop = loop;
}

bool ppSound::IsPause(){
	ALint sourceState;
	alGetSourcei(this->sourceID, AL_SOURCE_STATE, &sourceState);
	return sourceState==AL_PAUSED;
}

bool ppSound::IsStop(){
	ALint sourceState;
	alGetSourcei(this->sourceID, AL_SOURCE_STATE, &sourceState);
	return sourceState==AL_STOPPED||sourceState==AL_INITIAL;
}

bool ppSound::IsPlaying(){
	return this->GetCurrentPosition()<this->GetPositionLength();
}

bool ppSound::IsLoop(){
	return this->loop;
}

bool ppSound::IsJustLoop(){
	return this->justLoop;
}

float ppSound::GetCurrentTime(){
	return this->ByteToSecond(this->GetCurrentPosition());
}

float ppSound::GetTimeLength(){
	return this->ByteToSecond(this->GetPositionLength());
}

int ppSound::GetCurrentPosition(){
	int pos;
	alGetSourcei(this->sourceID, AL_BYTE_OFFSET, &pos);
	return (((this->bufferProcessed*this->bufferSize))+pos)*this->totalTrack+this->dataPositionOffset;
}

int ppSound::GetPositionLength(){
	return this->dataSize;
}

int ppSound::GetAudioFormat(){
	return this->audioFormat;
}

int ppSound::GetChannels(){
	return this->channels;
}

int ppSound::GetTargetChannels(){
	return this->targetChannels;
}

int ppSound::GetSampleRate(){
	return this->sampleRate;
}

int ppSound::GetByteRate(){
	return this->byteRate;
}

int ppSound::GetBitPerSample(){
	return this->bitPerSample;
}

int ppSound::GetCurrentTrack(){
	return this->track;
}

int ppSound::GetTotalTrack(){
	return this->totalTrack;
}

float ppSound::GetSpeed(){
	return this->speed;
}

float ppSound::GetVolumn(){
	return this->volumn;
}

std::string ppSound::GetFileName(){
	return this->filename;
}
