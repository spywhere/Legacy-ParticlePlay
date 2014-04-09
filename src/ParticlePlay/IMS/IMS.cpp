#include "IMS.h"

#include <string>

ppIMS::ppIMS(){
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
	this->Quit();
	return this->Init();
}

void ppIMS::Quit(){
	this->ClearSound();
	alcDestroyContext(this->context);
	alcCloseDevice(this->device);
}

ppSound* ppIMS::NewSound(const char *refname, const char *filename){
	return this->NewSound(refname, filename, -1);
}

ppSound* ppIMS::NewSound(const char *refname, const char *filename, int track){
	return this->NewSound(refname, filename, track, true);
}

ppSound* ppIMS::NewSound(const char *refname, const char *filename, int track, bool stereo){
	ppSound* sound = this->GetSound(refname);
	if (sound){
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
	std::map<std::string, ppSound*>::iterator it = this->sounds.find(refname);
	if (it != this->sounds.end()){
		return it->second;
	}
	return NULL;
}

void ppIMS::RemoveSound(const char *refname){
	if (!this->GetSound(refname)){
		return;
	}
	this->sounds.erase(std::string(refname));
}

void ppIMS::ClearSound(){
	for (std::map<std::string, ppSound*>::iterator it = this->sounds.begin(); it != this->sounds.end(); ++it){
		delete it->second;
	}
	this->sounds.clear();
	this->preload = false;
}

/////////////////////////
// Sound-based Methods //
/////////////////////////

void ppIMS::Preload(){
	for (std::map<std::string, ppSound*>::iterator it = this->sounds.begin(); it != this->sounds.end(); ++it){
		it->second->Preload();
	}
	this->preload = true;
}

void ppIMS::ApplyFilter(ppFilter* filter){
	for (std::map<std::string, ppSound*>::iterator it = this->sounds.begin(); it != this->sounds.end(); ++it){
		it->second->ApplyFilter(filter);
	}
}

void ppIMS::Play(){
	if(!this->preload){
		this->Preload();
	}
	for (std::map<std::string, ppSound*>::iterator it = this->sounds.begin(); it != this->sounds.end(); ++it){
		it->second->Play();
	}
}

void ppIMS::Pause(){
	for (std::map<std::string, ppSound*>::iterator it = this->sounds.begin(); it != this->sounds.end(); ++it){
		it->second->Pause();
	}
}

void ppIMS::Stop(){
	for (std::map<std::string, ppSound*>::iterator it = this->sounds.begin(); it != this->sounds.end(); ++it){
		it->second->Stop();
	}
	this->preload = false;
}

void ppIMS::SeekPosition(int targetPosition){
	// bool isplaying = this->IsPlaying();
	// if(isplaying){
	// 	this->Stop();
	// }
	for (std::map<std::string, ppSound*>::iterator it = this->sounds.begin(); it != this->sounds.end(); ++it){
		it->second->SeekPosition(targetPosition);
	}
	this->preload = true;
	// if(isplaying){
	// 	this->Play();
	// }
}

void ppIMS::SeekTime(float targetTime){
	// bool isplaying = this->IsPlaying();
	// if(isplaying){
	// 	this->Stop();
	// }
	for (std::map<std::string, ppSound*>::iterator it = this->sounds.begin(); it != this->sounds.end(); ++it){
		it->second->SeekTime(targetTime);
	}
	this->preload = true;
	// if(isplaying){
	// 	this->Play();
	// }
}

void ppIMS::SetSpeed(float speed){
	for (std::map<std::string, ppSound*>::iterator it = this->sounds.begin(); it != this->sounds.end(); ++it){
		it->second->SetSpeed(speed);
	}
}

void ppIMS::SetVolumn(float vol){
	for (std::map<std::string, ppSound*>::iterator it = this->sounds.begin(); it != this->sounds.end(); ++it){
		it->second->SetVolumn(vol);
	}
}

void ppIMS::SetLoop(bool loop){
	for (std::map<std::string, ppSound*>::iterator it = this->sounds.begin(); it != this->sounds.end(); ++it){
		it->second->SetLoop(loop);
	}
}

void ppIMS::Update(){
	for (std::map<std::string, ppSound*>::iterator it = this->sounds.begin(); it != this->sounds.end(); ++it){
		it->second->Update();
	}
}
