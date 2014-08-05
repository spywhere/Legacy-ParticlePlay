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

int ppWaveFormat::GetPositionLength(){
	return this->audioDataSize;
}

float ppWaveFormat::PositionToTime(int position){
	float sampleLength = position * 8 / (this->audioChannels * this->bitPerSample);
	return sampleLength / this->sampleRate;
}

int ppWaveFormat::TimeToPosition(float time){
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
