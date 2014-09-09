#include "Playlist.hpp"

ppPlaylist::ppPlaylist() : ppGenericSound(){
}

void ppPlaylist::AddSound(ppGenericSound *sound){
	this->sounds.push_back(sound);
}

void ppPlaylist::ClearSound(){
	this->sounds.clear();
}

Sint64 ppPlaylist::GetCurrentPosition(){
	return 0;
}

Sint64 ppPlaylist::GetPositionLength(){
	return 0;
}

float ppPlaylist::GetCurrentTime(){
	return 0;
}

float ppPlaylist::GetTotalTime(){
	return 0;
}

void ppPlaylist::Update(){
	for(auto sound : this->sounds){
		sound->Update();
	}
}
