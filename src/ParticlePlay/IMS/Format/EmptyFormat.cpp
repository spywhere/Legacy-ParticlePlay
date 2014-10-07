#include "EmptyFormat.hpp"

ppEmptyFormat::ppEmptyFormat(ppIMS* ims, Sint64 length, ppFormat* audioFormat) : ppFormat(ims){
	this->length = length;
	this->sourceAudioFormat = audioFormat;
}

int ppEmptyFormat::Init(const char *filename, bool stereo){
	int status = ppFormat::Init(filename, stereo);
	if(status>0){
		return status;
	}
	this->audioChannels = (stereo?2:1);
	this->audioTracks = 1;
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
	return this->sourceAudioFormat->ActualPosition(relativePosition);
	// return relativePosition*this->audioChannels/(this->stereo?2:1);
}

Sint64 ppEmptyFormat::RelativePosition(Sint64 actualPosition){
	return this->sourceAudioFormat->RelativePosition(actualPosition);
	// return actualPosition/this->audioChannels*(this->stereo?2:1);
}

Sint64 ppEmptyFormat::GetPositionLength(){
	return this->length;
}

float ppEmptyFormat::PositionToTime(Sint64 position){
	return this->sourceAudioFormat->PositionToTime(position);
	// float sampleLength = position * 8 / (this->audioChannels * this->bitPerSample);
	// return sampleLength / this->sourceAudioFormat->GetSampleRate();
}

Sint64 ppEmptyFormat::TimeToPosition(float time){
	return this->sourceAudioFormat->TimeToPosition(time);
	float sampleLength = time * this->sourceAudioFormat->GetSampleRate();
	return sampleLength * this->audioChannels * this->bitPerSample / 8;
}

int ppEmptyFormat::GetSampleRate(){
	return this->sourceAudioFormat->GetSampleRate();
}

ALuint ppEmptyFormat::GetFormat(){
	return this->audioFormat;
}

int ppEmptyFormat::GetTotalTrack(){
	return 1;
}
