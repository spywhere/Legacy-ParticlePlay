#include "EmptyFormat.hpp"

ppEmptyFormat::ppEmptyFormat(ppIMS* ims, Sint64 length) : ppFormat(ims){
	this->length = length;
}

int ppEmptyFormat::Init(const char *filename, bool stereo){
	int status = ppFormat::Init(filename, stereo);
	if(status>0){
		return status;
	}
	this->audioChannels = (stereo?2:1);
	this->audioTracks = 1;
	this->sampleRate = 44100;
	this->bitPerSample = 16;
	this->audioFormat = (stereo?AL_FORMAT_STEREO16:AL_FORMAT_MONO16);
	return 0;
}

Sint64 ppEmptyFormat::Read(char *bufferData, Sint64 position, Sint64 size, int track){
	for(Sint64 i=0;i<size;i++){
		bufferData[i] = 0;
	}
	return size;
}

Sint64 ppEmptyFormat::ActualPosition(Sint64 relativePosition){
	return relativePosition*this->audioChannels/(this->stereo?2:1);
}

Sint64 ppEmptyFormat::RelativePosition(Sint64 actualPosition){
	return actualPosition/this->audioChannels*(this->stereo?2:1);
}

Sint64 ppEmptyFormat::GetPositionLength(){
	return this->length;
}

float ppEmptyFormat::PositionToTime(Sint64 position){
	float sampleLength = position * 8 / (this->audioChannels * this->bitPerSample);
	return sampleLength / this->sampleRate;
}

Sint64 ppEmptyFormat::TimeToPosition(float time){
	float sampleLength = time * this->sampleRate;
	return sampleLength * this->audioChannels * this->bitPerSample / 8;
}

int ppEmptyFormat::GetSampleRate(){
	return this->sampleRate;
}

ALuint ppEmptyFormat::GetFormat(){
	return this->audioFormat;
}

int ppEmptyFormat::GetTotalTrack(){
	return 1;
}
