#include "Interfaces.hpp"

void ppUpdatable::Update(){}

ppPlayable::ppPlayable(){
	this->Stop();
	this->entryCue = 0;
	this->exitCue = -1;
}

ppPlayable::~ppPlayable(){}

void ppPlayable::Play(){
	if(this->isPlaying){
		this->isPause = false;
	}else{
		this->isPlaying = true;
	}
}

void ppPlayable::Pause(){
	this->isPause = true;
}

void ppPlayable::Stop(){
	this->isPlaying = false;
	this->isPause = false;
}

Sint64 ppPlayable::GetEntryCue(){
	return this->entryCue;
}

Sint64 ppPlayable::GetExitCue(){
	return this->exitCue;
}

void ppPlayable::SetEntryCue(Sint64 entryCue){
	this->entryCue = entryCue;
}

void ppPlayable::SetExitCue(Sint64 exitCue){
	this->exitCue = exitCue;
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
	this->clipEnd = 0;
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

ppGenericSound::ppGenericSound(const char *name) : ppControl(name, 0, 0) {
	this->preload = false;
	this->volume = 1;
	this->speed = 1;
	this->autoloop = true;
	this->loop = 0;
	this->audioFormat = NULL;
}

ppGenericSound::~ppGenericSound(){}

void ppGenericSound::Seek(Sint64 position){}

void ppGenericSound::Seek(float time){}

void ppGenericSound::SetLoop(int loop){
	this->loop = loop;
}

void ppGenericSound::SetAutoLoop(bool autoloop){
	this->autoloop = autoloop;
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

ppFormat* ppGenericSound::GetAudioFormat(){
	return this->audioFormat;
}

int ppGenericSound::GetLoop(){
	return this->loop;
}

bool ppGenericSound::IsLoop(){
	return this->loop != 0;
}

bool ppGenericSound::IsAutoLoop(){
	return this->autoloop;
}

bool ppGenericSound::IsReady(){
	return this->preload && this->IsStop();
}

void ppGenericSound::Update(){
	ppUpdatable::Update();
}

void ppGenericSound::Render(SDL_Renderer* renderer){
	ppControl::Render(renderer);
}

void ppGenericSound::Update(ppInput* input){
	ppControl::Update(input);
}

ppControlType ppGenericSound::GetType(){
	return ppControlType::GENERIC_SOUND_CONTROL;
}
