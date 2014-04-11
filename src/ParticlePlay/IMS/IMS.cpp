#include "IMS.h"

#include <string>

ppIMS::ppIMS(ppGame* game){
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
		return 1;
	}
	alcMakeContextCurrent(this->context);
	return 0;
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
	this->ClearFilter();
	alcDestroyContext(this->context);
	alcCloseDevice(this->device);
}

ppFilter* ppIMS::NewFilter(ppFilterType filterType){
	if(!this->device || !this->context){
		return NULL;
	}
	if(filterType == ppFilterType::BAND_PASS){
		ppFilter* filter = new ppBandPassFilter(this);
		this->filters.push_back(filter);
		return filter;
	}else if(filterType == ppFilterType::HIGH_PASS){
		ppFilter* filter = new ppHighPassFilter(this);
		this->filters.push_back(filter);
		return filter;
	}else if(filterType == ppFilterType::LOW_PASS){
		ppFilter* filter = new ppLowPassFilter(this);
		this->filters.push_back(filter);
		return filter;
	}
	return NULL;
}

ppSound* ppIMS::NewSound(const char *refname, const char *filename){
	return this->NewSound(refname, filename, -1);
}

ppSound* ppIMS::NewSound(const char *refname, const char *filename, int track){
	return this->NewSound(refname, filename, track, true);
}

ppSound* ppIMS::NewSound(const char *refname, const char *filename, int track, bool stereo){
	if(!this->device || !this->context){
		return NULL;
	}
	ppSound* sound = this->GetSound(refname);
	if(sound){
		return sound;
	}
	sound = new ppSound(this);
	if(sound->LoadWaveFile(filename, stereo)==0){
		if(track>=0){
			sound->Preload(track, true);
		}
		this->sounds[std::string(refname)] = sound;
		return sound;
	}
	return NULL;
}

ppSound* ppIMS::GetSound(const char *refname){
	if(!this->device || !this->context){
		return NULL;
	}
	auto sound = this->sounds.find(refname);
	if(sound != this->sounds.end()){
		return sound->second;
	}
	return NULL;
}

void ppIMS::RemoveSound(const char *refname){
	if(!this->device || !this->context){
		return;
	}
	if(!this->GetSound(refname)){
		return;
	}
	this->sounds.erase(std::string(refname));
}

void ppIMS::ClearFilter(){
	if(!this->device || !this->context){
		return;
	}
	for(auto filter : this->filters){
		delete filter;
	}
	this->filters.clear();
}

void ppIMS::ClearSound(){
	if(!this->device || !this->context){
		return;
	}
	for(auto sound : this->sounds){
		delete sound.second;
	}
	this->sounds.clear();
	this->preload = false;
}

/////////////////////////
// Sound-based Methods //
/////////////////////////

void ppIMS::Preload(){
	if(!this->device || !this->context){
		return;
	}
	for(auto sound : this->sounds){
		sound.second->Preload();
	}
	this->preload = true;
}

void ppIMS::ApplyFilter(ppFilter* filter){
	if(!this->device || !this->context){
		return;
	}
	for(auto sound : this->sounds){
		sound.second->ApplyFilter(filter);
	}
}

void ppIMS::Play(){
	if(!this->device || !this->context){
		return;
	}
	if(!this->preload){
		this->Preload();
	}
	for(auto sound : this->sounds){
		sound.second->Play();
	}
}

void ppIMS::Pause(){
	if(!this->device || !this->context){
		return;
	}
	for(auto sound : this->sounds){
		sound.second->Pause();
	}
}

void ppIMS::Stop(){
	if(!this->device || !this->context){
		return;
	}
	for(auto sound : this->sounds){
		sound.second->Stop();
	}
	this->preload = false;
}

void ppIMS::SeekPosition(int targetPosition){
	if(!this->device || !this->context){
		return;
	}
	// bool isplaying = this->IsPlaying();
	// if(isplaying){
	// 	this->Stop();
	// }
	for(auto sound : this->sounds){
		sound.second->SeekPosition(targetPosition);
	}
	this->preload = true;
	// if(isplaying){
	// 	this->Play();
	// }
}

void ppIMS::SeekTime(float targetTime){
	if(!this->device || !this->context){
		return;
	}
	// bool isplaying = this->IsPlaying();
	// if(isplaying){
	// 	this->Stop();
	// }
	for(auto sound : this->sounds){
		sound.second->SeekTime(targetTime);
	}
	this->preload = true;
	// if(isplaying){
	// 	this->Play();
	// }
}

void ppIMS::SetSpeed(float speed){
	if(!this->device || !this->context){
		return;
	}
	for(auto sound : this->sounds){
		sound.second->SetSpeed(speed);
	}
}

void ppIMS::SetVolumn(float vol){
	if(!this->device || !this->context){
		return;
	}
	for(auto sound : this->sounds){
		sound.second->SetVolumn(vol);
	}
}

void ppIMS::SetLoop(bool loop){
	if(!this->device || !this->context){
		return;
	}
	for(auto sound : this->sounds){
		sound.second->SetLoop(loop);
	}
}

void ppIMS::Update(){
	if(!this->device || !this->context){
		return;
	}
	for(auto sound : this->sounds){
		sound.second->Update();
	}
}
