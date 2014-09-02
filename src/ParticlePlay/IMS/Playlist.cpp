#include "Playlist.hpp"

ppPlaylist::ppPlaylist() : ppPlayable(){
}

void ppPlaylist::AddSound(ppPlayable *sound){
	this->sounds.push_back(sound);
}

void ppPlaylist::ClearSound(){
	this->sounds.clear();
}

void ppPlaylist::Update(){
	for(auto sound : this->sounds){
		sound->Update();
	}
}
