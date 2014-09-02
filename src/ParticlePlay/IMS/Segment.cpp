#include "Segment.hpp"

ppSegment::ppSegment() : ppPlayable(), ppClippable(), ppOffsetable(){

}

void ppSegment::AddSound(ppPlayable *sound){
	this->sounds.push_back(sound);
}

void ppSegment::ClearSound(){
	this->sounds.clear();
}

void ppSegment::Play(){
	for(auto sound : this->sounds){
		sound->Play();
	}
}

void ppSegment::Pause(){
	for(auto sound : this->sounds){
		sound->Pause();
	}
}

void ppSegment::Stop(){
	for(auto sound : this->sounds){
		sound->Play();
	}
}

void ppSegment::Update(){
	for(auto sound : this->sounds){
		sound->Update();
	}
}
