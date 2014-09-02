#include "Interfaces.hpp"

void ppUpdatable::Update(){}

ppPlayable::ppPlayable(){
	this->Stop();
}

ppPlayable::~ppPlayable(){}

void ppPlayable::Play(){
	this->isPlaying = true;
}

void ppPlayable::Pause(){
	this->isPause = true;
}

void ppPlayable::Stop(){
	this->isPlaying = false;
	this->isPause = false;
}

bool ppPlayable::IsPause(){
	return this->isPause;
}

bool ppPlayable::IsPlaying(){
	return this->isPlaying && !this->isPause;
}

bool ppPlayable::IsStop(){
	return !this->isPlaying;
}

ppClippable::ppClippable(){
	this->clipStart = 0;
	this->clipEnd = -1;
}

void ppClippable::SetClipStart(Sint64 clipping) {
	this->clipStart = clipping;
}

void ppClippable::SetClipEnd(Sint64 clipping) {
	this->clipEnd = clipping;
}

Sint64 ppClippable::GetClipStart(){
	return this->clipStart;
}

Sint64 ppClippable::GetClipEnd(){
	return this->clipEnd;
}

ppOffsetable::ppOffsetable(){
	this->offset = 0;
}

void ppOffsetable::SetOffset(Sint64 offset){
	this->offset = offset;
}

Sint64 ppOffsetable::GetOffset(){
	return this->offset;
}

ppGenericSound::ppGenericSound(){
	this->preload = false;
	this->volume = 1;
	this->speed = 1;
	this->loop = 0;
}

ppGenericSound::~ppGenericSound(){}

void ppGenericSound::SetLoop(int loop){
	this->loop = loop;
}

void ppGenericSound::SetVolume(float volume){
	this->volume = volume;
}

void ppGenericSound::SetSpeed(float speed){
	this->speed = speed;
}

float ppGenericSound::GetVolume(){
	return this->volume;
}

float ppGenericSound::GetSpeed(){
	return this->speed;
}

bool ppGenericSound::IsLoop(){
	return this->loop != 0;
}

bool ppGenericSound::IsReady(){
	return this->preload && this->IsStop();
}
