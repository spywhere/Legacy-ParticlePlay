#include "Sound.h"

Sound::Sound(IMS* ims){
	this->justLoop = false;
	this->preload = false;
	this->loop = false;
	this->speed = 1.0f;
	this->volumn = 1.0f;
	this->bufferProcessed=0;
	this->targetChannels=1;
	this->track = 0;
	this->filter = NULL;
}

Sound::~Sound(){
    alDeleteBuffers(2, this->bufferSet);
	alDeleteSources(1, &this->sourceID);
}

void Sound::GetWaveChunkInfo(std::ifstream &filePointer, char *chunkName, int &chunkSize){
	char buffer[4];
	filePointer.read(chunkName, 4);
	filePointer.read(buffer, 4);
	chunkSize=ConvertToInt(buffer, 4);
}

void Sound::Preload(){
	this->Preload(this->track, false);
}

void Sound::Preload(int track){
	this->Preload(track, false);
}

void Sound::Preload(int track, bool skip){
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
		this->filePointer.open(this->filename.c_str(), std::ios::binary);
		this->filePointer.seekg(this->dataReadPosition);

		this->ReadData(this->filePointer, dataBuffer, this->bufferSize, this->bufferSet[0]);
		this->dataReadPosition=this->filePointer.tellg();
		if(this->dataReadPosition<0||this->dataReadPosition-this->dataStartPosition>this->dataSize){
			//Reopen on eof
			this->dataReadPosition = this->dataStartPosition;
			this->filePointer.close();
			this->filePointer.open(this->filename.c_str(), std::ios::binary);
		}
		this->filePointer.seekg(this->dataReadPosition);

		this->ReadData(this->filePointer, dataBuffer, this->bufferSize, this->bufferSet[1]);

		this->dataReadPosition=this->filePointer.tellg();
		this->filePointer.close();
		delete[] dataBuffer;
		alSourceQueueBuffers(this->sourceID, 2, this->bufferSet);
	}
}

int Sound::LoadWaveFile(const char *filename, bool stereo){
	this->filename = std::string(filename);
	this->filePointer.open(this->filename.c_str(), std::ios::binary);
	if(!this->filePointer){
		return 1;
	}
	int valid = 0;
	char buffer[4];
	int chunkSize=0;
	while(!this->filePointer.eof()&&valid<3){
		this->GetWaveChunkInfo(this->filePointer, buffer, chunkSize);
		// std::cout << "Reading... " << buffer << std::endl;
		if(strncmp(buffer, "RIFF", 4)==0){
			//chunkSize = Total chunk in this wave file
			chunkSize=0;
			this->filePointer.read(buffer, 4);
			if(strncmp(buffer, "WAVE", 4)==0){
				valid++;
			}else{
				break;
			}
		}else if(strncmp(buffer, "fmt ", 4)==0){
			this->filePointer.read(buffer, 2); //1 = PCM, other = compression
			this->audioFormat=ConvertToInt(buffer, 2);
			chunkSize-=2;
			this->filePointer.read(buffer, 2);
			this->channels=ConvertToInt(buffer, 2);
			chunkSize-=2;
			this->filePointer.read(buffer, 4);
			this->sampleRate=ConvertToInt(buffer, 4);
			chunkSize-=4;
			this->filePointer.read(buffer, 4);
			this->byteRate=ConvertToInt(buffer, 4);
			chunkSize-=4;
			this->filePointer.read(buffer, 2); //BlockAlign
			chunkSize-=2;
			this->filePointer.read(buffer, 2);
			this->bitPerSample=ConvertToInt(buffer, 2);
			chunkSize-=2;
			valid++;
		}else if(strncmp(buffer, "data", 4)==0){
			this->dataSize=chunkSize;
			this->dataReadPosition = this->filePointer.tellg();;
			this->dataStartPosition = this->dataReadPosition;
			this->dataPositionOffset = 0;
			chunkSize = 0;
			valid++;
		}
		if(chunkSize>0){
			// std::cout << "Skip " << buffer << " [" << chunkSize << "b]" << std::endl;
			//Skip any unread data
			this->filePointer.seekg(chunkSize, std::ios_base::cur);
		}
	}
	this->filePointer.close();
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

	alDeleteBuffers(2, this->bufferSet);
	alGenBuffers(2, this->bufferSet);
	alGenSources(1, &this->sourceID);

	this->bufferSize = (this->byteRate+this->byteRate);

	return 0;
}

void Sound::ApplyFilter(Filter* filter){
	this->filter = filter;
}

void Sound::ReadData(std::ifstream &filePointer, char *dataBuffer, int bufferSize, ALuint &bufferID){
	int x=0;
	for(x=0;x<bufferSize;){
		if(filePointer.eof()){
			break;
		}
		int bytePerSample = this->bitPerSample/8;
		char *buf = new char[this->channels * 2];
		filePointer.read(buf, this->channels * 2);
		for(int c=0;c<this->targetChannels;c++){
			for(int byte=0;byte<this->bitPerSample/8;byte++){
				dataBuffer[x++]=buf[this->track*(this->targetChannels*2)+(c*this->targetChannels+byte)];
			}
		}
		delete[] buf;
	}
	alBufferData(bufferID, this->format, dataBuffer, x, this->sampleRate);
}

void Sound::Play(){
	this->Play(this->track);
}

void Sound::Play(int track){
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

int Sound::GetTotalBuffer(int dataSize, bool countCurrent){
	int totalBuffer = dataSize/(this->bufferSize*this->totalTrack);
	if(countCurrent&&dataSize%(this->bufferSize*this->totalTrack)>0){
		totalBuffer++;
	}
	return totalBuffer;
}

void Sound::Update(){
	this->justLoop = false;
	//Stream more data when buffer finished
	ALint processedBuffer;
	alGetSourcei(this->sourceID, AL_BUFFERS_PROCESSED, &processedBuffer);

	char *buffer = new char[this->bufferSize];
	this->filePointer.open(this->filename.c_str(), std::ios::binary);

	this->filePointer.seekg(this->dataReadPosition);

	while(processedBuffer--&&!this->filePointer.eof()){
		this->bufferProcessed++;
		ALuint bufferID;
		alSourceUnqueueBuffers(this->sourceID, 1, &bufferID);
		this->ReadData(this->filePointer, buffer, this->bufferSize, bufferID);
		this->dataReadPosition=this->filePointer.tellg();
		alSourceQueueBuffers(this->sourceID, 1, &bufferID);
	}
	delete[] buffer;
	this->filePointer.close();
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

float Sound::ByteToSecond(int byte){
	float sampleLength = byte * 8 / (this->channels * this->bitPerSample);
	return sampleLength / this->sampleRate;
}

int Sound::SecondToByte(float sec){
	float sampleLength = sec * this->sampleRate;
	return sampleLength * this->channels * this->bitPerSample / 8;
}

void Sound::Pause(){
	alSourcePause(this->sourceID);
}

void Sound::Stop(){
	if(this->IsStop()){
		return;
	}
	alSourceStop(this->sourceID);
	alSourceUnqueueBuffers(this->sourceID, 2, this->bufferSet);
	this->preload = false;
	this->dataReadPosition = this->dataStartPosition;
	this->bufferProcessed = 0;
}

void Sound::SeekPosition(int targetPosition){
	this->SeekPosition(targetPosition, this->track);
}

void Sound::SeekTime(float targetTime){
	this->SeekTime(targetTime, this->track);
}

void Sound::SeekPosition(int targetPosition, int track){
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

void Sound::SeekTime(float targetTime, int track){
	this->SeekPosition(this->SecondToByte(targetTime), track);
}

void Sound::SetSpeed(float speed){
	this->speed = speed;
	alSourcef(this->sourceID, AL_PITCH, this->speed);
}

void Sound::SetVolumn(float vol){
	this->volumn = vol;
	alSourcef(this->sourceID, AL_GAIN, this->volumn);
}

void Sound::SetLoop(bool loop){
	this->loop = loop;
}

bool Sound::IsPause(){
	ALint sourceState;
	alGetSourcei(this->sourceID, AL_SOURCE_STATE, &sourceState);
	return sourceState==AL_PAUSED;
}

bool Sound::IsStop(){
	ALint sourceState;
	alGetSourcei(this->sourceID, AL_SOURCE_STATE, &sourceState);
	return sourceState==AL_STOPPED||sourceState==AL_INITIAL;
}

bool Sound::IsPlaying(){
	return this->GetCurrentPosition()<this->GetPositionLength();
}

bool Sound::IsLoop(){
	return this->loop;
}

bool Sound::IsJustLoop(){
	return this->justLoop;
}

float Sound::GetCurrentTime(){
	return this->ByteToSecond(this->GetCurrentPosition());
}

float Sound::GetTimeLength(){
	return this->ByteToSecond(this->GetPositionLength());
}

int Sound::GetCurrentPosition(){
	int pos;
	alGetSourcei(this->sourceID, AL_BYTE_OFFSET, &pos);
	return (((this->bufferProcessed*this->bufferSize))+pos)*this->totalTrack+this->dataPositionOffset;
}

int Sound::GetPositionLength(){
	return this->dataSize;
}

int Sound::GetAudioFormat(){
	return this->audioFormat;
}

int Sound::GetChannels(){
	return this->channels;
}

int Sound::GetTargetChannels(){
	return this->targetChannels;
}

int Sound::GetSampleRate(){
	return this->sampleRate;
}

int Sound::GetByteRate(){
	return this->byteRate;
}

int Sound::GetBitPerSample(){
	return this->bitPerSample;
}

int Sound::GetCurrentTrack(){
	return this->track;
}

int Sound::GetTotalTrack(){
	return this->totalTrack;
}

float Sound::GetSpeed(){
	return this->speed;
}

float Sound::GetVolumn(){
	return this->volumn;
}

std::string Sound::GetFileName(){
	return this->filename;
}
