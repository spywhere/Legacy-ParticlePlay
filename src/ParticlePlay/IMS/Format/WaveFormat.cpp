#include "WaveFormat.hpp"

ppWaveFormat::ppWaveFormat(ppIMS* ims) : ppFormat(ims){
}

void ppWaveFormat::GetWaveChunkInfo(SDL_RWops *filePointer, char *chunkName, int &chunkSize){
	char buffer[4];
	SDL_RWread(filePointer, chunkName, 4, 1);
	SDL_RWread(filePointer, buffer, 4, 1);
	chunkSize=ConvertToInt(buffer, 4);
}

int ppWaveFormat::Init(const char *filename, bool stereo){
	int status = ppFormat::Init(filename, stereo);
	if(status>0){
		return status;
	}
	int valid = 0;
	int chunkSize;
	char buffer[4];
	this->filePointer = SDL_RWFromFile(this->filename.c_str(), "rb");
	while(!SDL_RWread(this->filePointer, buffer, 0, 1)&&valid<3){
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
			SDL_RWread(filePointer, buffer, 2, 1); //AudioFormat 1 = PCM, other = compression
			chunkSize-=2;
			SDL_RWread(filePointer, buffer, 2, 1);
			this->audioChannels=ConvertToInt(buffer, 2);
			chunkSize-=2;
			SDL_RWread(filePointer, buffer, 4, 1);
			this->sampleRate=ConvertToInt(buffer, 4);
			chunkSize-=4;
			SDL_RWread(filePointer, buffer, 4, 1); //ByteRate
			chunkSize-=4;
			SDL_RWread(filePointer, buffer, 2, 1); //BlockAlign
			chunkSize-=2;
			SDL_RWread(filePointer, buffer, 2, 1);
			this->bitPerSample=ConvertToInt(buffer, 2);
			chunkSize-=2;
			valid++;
		}else if(strncmp(buffer, "data", 4)==0){
			this->audioDataSize=chunkSize;
			this->startReadPosition = SDL_RWtell(this->filePointer);
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
	this->audioTracks = this->audioChannels / (stereo?2:1);
	if(stereo){
		if(this->bitPerSample==8){
			this->audioFormat = AL_FORMAT_STEREO8;
		}else{
			this->audioFormat = AL_FORMAT_STEREO16;
		}
	}else{
		if(this->bitPerSample==8){
			this->audioFormat = AL_FORMAT_MONO8;
		}else{
			this->audioFormat = AL_FORMAT_MONO16;
		}
	}
	return 0;
}

Sint64 ppWaveFormat::Read(char *bufferData, Sint64 position, Sint64 size, int track){
	int bytePerSample = this->bitPerSample/8;
	Sint64 bufferOffset = 0;
	int outputChannels = (stereo?2:1);
	this->filePointer = SDL_RWFromFile(this->filename.c_str(), "rb");
	SDL_RWseek(this->filePointer, this->startReadPosition+(position*this->audioChannels/outputChannels), RW_SEEK_SET);

	while(bufferOffset < size){
		char *rawBufferData = new char[this->audioChannels * 2];
		if(!SDL_RWread(this->filePointer, rawBufferData, this->audioChannels * 2, 1)){
			delete[] rawBufferData;
			break;
		}
		for(int c=0;c<outputChannels;c++){
			for(int byte=0;byte<bytePerSample;byte++){
				bufferData[bufferOffset++]=rawBufferData[track*(outputChannels*2)+(c*outputChannels+byte)];
			}
		}
		delete[] rawBufferData;
	}
	SDL_RWclose(this->filePointer);
	return bufferOffset;
}

Sint64 ppWaveFormat::ActualPosition(Sint64 relativePosition){
	return relativePosition*this->audioChannels/(this->stereo?2:1);
}

Sint64 ppWaveFormat::GetPositionLength(){
	return this->audioDataSize;
}

float ppWaveFormat::PositionToTime(Sint64 position){
	float sampleLength = position * 8 / (this->audioChannels * this->bitPerSample);
	return sampleLength / this->sampleRate;
}

Sint64 ppWaveFormat::TimeToPosition(float time){
	float sampleLength = time * this->sampleRate;
	return sampleLength * this->audioChannels * this->bitPerSample / 8;
}

int ppWaveFormat::GetSampleRate(){
	return this->sampleRate;
}

ALuint ppWaveFormat::GetFormat(){
	return this->audioFormat;
}

int ppWaveFormat::GetTotalTrack(){
	return this->audioTracks;
}
