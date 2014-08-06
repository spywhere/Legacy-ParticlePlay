#include "Playlist.hpp"

ppPlaylist::ppPlaylist(const char *name){
	this->name = std::string(name);
}

ppSound* ppPlaylist::NewSound(const char *name, ppFormat* audioFormat, int track){
	ppSound* sound = this->GetSound(name);
	if(sound){
		return sound;
	}
	sound = new ppSound(name, audioFormat, track);
	this->sounds[std::string(name)] = sound;
	return sound;
}

ppSound* ppPlaylist::NewSound(const char *name, ppFormat* audioFormat){
	return this->NewSound(name, audioFormat, 1);
}

ppPlaylist* ppPlaylist::NewPlaylist(const char *name){
	ppPlaylist* playlist = this->GetPlaylist(name);
	if(playlist){
		return playlist;
	}
	playlist = new ppPlaylist(name);
	this->playlists[name] = playlist;
	return playlist;
}

ppSound* ppPlaylist::GetSound(const char *name){
	auto sound = this->sounds.find(name);
	if(sound != this->sounds.end()){
		return sound->second;
	}
	return NULL;
}

ppPlaylist* ppPlaylist::GetPlaylist(const char *name){
	auto playlist = this->playlists.find(name);
	if(playlist != this->playlists.end()){
		return playlist->second;
	}
	return NULL;
}

void ppPlaylist::RemoveSound(const char *name){
	if(this->GetSound(name)){
		this->sounds.erase(std::string(name));
	}
}

void ppPlaylist::RemovePlaylist(const char *name){
	if(this->GetPlaylist(name)){
		this->playlists.erase(std::string(name));
	}
}

void ppPlaylist::ClearSound(){
	for(auto sound : this->sounds){
		delete sound.second;
	}
	this->sounds.clear();
}

void ppPlaylist::ClearPlaylist(){
	for(auto playlist : this->playlists){
		delete playlist.second;
	}
	this->playlists.clear();
}

void ppPlaylist::Update(){
	for(auto playlist : this->playlists){
		playlist.second->Update();
	}
	for(auto sound : this->sounds){
		sound.second->Update();
	}
}
