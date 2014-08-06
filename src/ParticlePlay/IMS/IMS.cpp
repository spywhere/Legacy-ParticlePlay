#include "IMS.hpp"

ppIMS::ppIMS(ppGame* game) : ppPlaylist("global") {
	this->preload = false;
}

int ppIMS::Init(){
	this->device = alcOpenDevice(NULL);
	if(!this->device){
		// std::cout << "Cannot open sound card" << std::endl;
		return 1;
	}
	this->context = alcCreateContext(this->device, NULL);
	if(!this->context){
		// std::cout << "Cannot create context" << std::endl;
		return 2;
	}
	alcMakeContextCurrent(this->context);
	return 0;
}

ppFormat* ppIMS::CreateFormat(ppAudioFormat audioFormat, const char *filename, bool stereo){
	if(audioFormat == ppAudioFormat::WAVE){
		ppWaveFormat *format = new ppWaveFormat(this);
		format->Init(filename, stereo);
		return format;
	}
	return NULL;
}

int ppIMS::Reinit(){
	if(!this->device || !this->context){
		return 1;
	}
	this->Quit();
	return this->Init();
}

void ppIMS::Quit(){
	if(!this->device || !this->context){
		return;
	}
	this->ClearSound();
	this->ClearPlaylist();
	alcDestroyContext(this->context);
	alcCloseDevice(this->device);
}

void ppIMS::Update(){
	if(!this->device || !this->context){
		return;
	}
	ppPlaylist::Update();
}
