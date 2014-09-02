#include "IMS.hpp"

ppIMS::ppIMS(ppGame* game) {
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

ppFormat* ppIMS::CreateFormat(ppAudioFormat audioFormat, const char *filename){
	return this->CreateFormat(audioFormat, filename, true);
}

ppSound *ppIMS::CreateSound(const char *name, ppFormat* audioFormat, int track){
	ppSound* sound = new ppSound(name, audioFormat, track);
	this->sounds[name] = sound;
	return sound;
}

ppSound *ppIMS::CreateSound(const char *name, ppFormat* audioFormat){
	return this->CreateSound(name, audioFormat, 1);
}

ppSegment *ppIMS::CreateSegment(const char *name){
	ppSegment *segment = new ppSegment();
	this->sounds[name] = segment;
	return segment;
}

ppPlaylist* ppIMS::CreatePlaylist(const char *name){
	ppPlaylist* playlist = new ppPlaylist();
	this->sounds[name] = playlist;
	return playlist;
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
	for(auto sound : this->sounds){
		delete sound.second;
	}
	alcDestroyContext(this->context);
	alcCloseDevice(this->device);
}

void ppIMS::Update(){
	if(!this->device || !this->context){
		return;
	}
	for(auto sound : this->sounds){
		sound.second->Update();
	}
}
