#include "IMS.h"

#include <string>

IMS::IMS(){
	this->preload = false;
	this->device = alcOpenDevice(NULL);
	if(!device){
		// std::cout << "Cannot open sound card" << std::endl;
		return;
	}
	this->context = alcCreateContext(this->device, NULL);
	if(!this->context){
		// std::cout << "Cannot create context" << std::endl;
		return;
	}
	alcMakeContextCurrent(this->context);
}

IMS::~IMS(){
	alcDestroyContext(this->context);
	alcCloseDevice(this->device);
}

Sound* IMS::NewSound(const char *refname, const char *filename){
	return this->NewSound(refname, filename, -1);
}

Sound* IMS::NewSound(const char *refname, const char *filename, int track){
	return this->NewSound(refname, filename, track, true);
}

Sound* IMS::NewSound(const char *refname, const char *filename, int track, bool stereo){
	Sound* sound = this->GetSound(refname);
	if (sound){
		return sound;
	}
	sound = new Sound(this);
	if(sound->LoadWaveFile(filename, stereo)==0){
		if(track>=0){
			sound->Preload(track, true);
		}
		this->sounds[std::string(refname)] = sound;
		return sound;
	}
	return NULL;
}

Sound* IMS::GetSound(const char *refname){
	std::map<std::string, Sound*>::iterator it = this->sounds.find(refname);
	if (it != this->sounds.end()){
		return it->second;
	}
	return NULL;
}

void IMS::RemoveSound(const char *refname){
	if (!this->GetSound(refname)){
		return;
	}
	this->sounds.erase(std::string(refname));
}

/////////////////////////
// Sound-based Methods //
/////////////////////////

void IMS::Preload(){
	for (std::map<std::string, Sound*>::iterator it = this->sounds.begin(); it != this->sounds.end(); ++it){
		it->second->Preload();
	}
	this->preload = true;
}

void IMS::ApplyFilter(Filter* filter){
	for (std::map<std::string, Sound*>::iterator it = this->sounds.begin(); it != this->sounds.end(); ++it){
		it->second->ApplyFilter(filter);
	}
}

void IMS::Play(){
	if(!this->preload){
		this->Preload();
	}
	for (std::map<std::string, Sound*>::iterator it = this->sounds.begin(); it != this->sounds.end(); ++it){
		it->second->Play();
	}
}

void IMS::Pause(){
	for (std::map<std::string, Sound*>::iterator it = this->sounds.begin(); it != this->sounds.end(); ++it){
		it->second->Pause();
	}
}

void IMS::Stop(){
	for (std::map<std::string, Sound*>::iterator it = this->sounds.begin(); it != this->sounds.end(); ++it){
		it->second->Stop();
	}
}

void IMS::SeekPosition(int targetPosition){
	// bool isplaying = this->IsPlaying();
	// if(isplaying){
	// 	this->Stop();
	// }
	for (std::map<std::string, Sound*>::iterator it = this->sounds.begin(); it != this->sounds.end(); ++it){
		it->second->SeekPosition(targetPosition);
	}
	this->preload = true;
	// if(isplaying){
	// 	this->Play();
	// }
}

void IMS::SeekTime(float targetTime){
	// bool isplaying = this->IsPlaying();
	// if(isplaying){
	// 	this->Stop();
	// }
	for (std::map<std::string, Sound*>::iterator it = this->sounds.begin(); it != this->sounds.end(); ++it){
		it->second->SeekTime(targetTime);
	}
	this->preload = true;
	// if(isplaying){
	// 	this->Play();
	// }
}

void IMS::SetSpeed(float speed){
	for (std::map<std::string, Sound*>::iterator it = this->sounds.begin(); it != this->sounds.end(); ++it){
		it->second->SetSpeed(speed);
	}
}

void IMS::SetVolumn(float vol){
	for (std::map<std::string, Sound*>::iterator it = this->sounds.begin(); it != this->sounds.end(); ++it){
		it->second->SetVolumn(vol);
	}
}

void IMS::SetLoop(bool loop){
	for (std::map<std::string, Sound*>::iterator it = this->sounds.begin(); it != this->sounds.end(); ++it){
		it->second->SetLoop(loop);
	}
}

void IMS::Update(){
	for (std::map<std::string, Sound*>::iterator it = this->sounds.begin(); it != this->sounds.end(); ++it){
		it->second->Update();
	}
}
