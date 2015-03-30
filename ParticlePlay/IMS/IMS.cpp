#include "IMS.hpp"

#ifdef PPDEBUG
	#include <iostream>
#endif

ppIMS::ppIMS(ppGame* game, ppRandomizer* randomizer) {
	this->randomizer = randomizer;
	this->preload = false;
}

ppRandomizer* ppIMS::GetRandomizer(){
	return this->randomizer;
}

int ppIMS::Init(){
	this->device = alcOpenDevice(NULL);
	if(!this->device){
		#ifdef PPDEBUG
			std::cout << "Cannot open sound card" << std::endl;
		#endif
		return 1;
	}
	this->context = alcCreateContext(this->device, NULL);
	if(!this->context){
		#ifdef PPDEBUG
			std::cout << "Cannot create context" << std::endl;
		#endif
		return 2;
	}
	alcMakeContextCurrent(this->context);
	return 0;
}

ppFormat* ppIMS::CreateEmptyFormat(Sint64 length, ppFormat* audioFormat, bool stereo){
	ppEmptyFormat *format = new ppEmptyFormat(this, length, audioFormat);
	if(format->Init("", stereo)){
		return NULL;
	}
	this->formats.push_back(format);
	return format;
}

ppFormat* ppIMS::CreateEmptyFormat(Sint64 length, ppFormat* audioFormat){
	return this->CreateEmptyFormat(length, audioFormat, true);
}

ppFormat* ppIMS::CreateFormat(ppAudioFormat audioFormat, const char *filename, bool stereo){
	if(filename && audioFormat == ppAudioFormat::WAVE){
		ppWaveFormat *format = new ppWaveFormat(this);
		if(format->Init(filename, stereo)){
			return NULL;
		}
		this->formats.push_back(format);
		return format;
	}
	return NULL;
}

ppFormat* ppIMS::CreateFormat(ppAudioFormat audioFormat, const char *filename){
	return this->CreateFormat(audioFormat, filename, true);
}

ppSound *ppIMS::CreateSound(const char *name, ppFormat* audioFormat, int track){
	if(!name || !audioFormat){
		return NULL;
	}
	ppSound* sound = new ppSound(name, audioFormat, track, this->randomizer);
	this->sounds[name] = sound;
	return sound;
}

ppSound *ppIMS::CreateSound(const char *name, ppFormat* audioFormat){
	return this->CreateSound(name, audioFormat, 1);
}

ppSegment *ppIMS::CreateSegment(const char *name){
	if(!name){
		return NULL;
	}
	ppSegment *segment = new ppSegment(name, this);
	this->sounds[name] = segment;
	return segment;
}

ppPlaylist* ppIMS::CreatePlaylist(const char *name){
	if(!name){
		return NULL;
	}
	ppPlaylist* playlist = new ppPlaylist(name, this->randomizer);
	this->sounds[name] = playlist;
	return playlist;
}

ppSwitch *ppIMS::CreateSwitch(const char *name){
	if(!name){
		return NULL;
	}
	ppSwitch *sw = new ppSwitch(name, this);
	this->switches[name] = sw;
	return sw;
}

ppFilter *ppIMS::CreateFilter(const char *name, ppFilterType filterType){
	if(!name){
		return NULL;
	}
	ppFilter *filter = NULL;
	if(filterType == ppFilterType::LOW_PASS){
		filter = new ppLowPassFilter(this, filterType);
	}else if(filterType == ppFilterType::BAND_PASS){
		filter = new ppBandPassFilter(this, filterType);
	}else if(filterType == ppFilterType::HIGH_PASS){
		filter = new ppHighPassFilter(this, filterType);
	}
	if(filter){
		filter->InitFilter();
		this->filters[name] = filter;
	}
	return filter;
}

ppRTPC* ppIMS::CreateRTPC(const char *name){
	if(!name){
		return NULL;
	}
	ppRTPC* rtpc = new ppRTPC(this);
	this->rtpcs[name] = rtpc;
	return rtpc;
}

ppGenericSound* ppIMS::GetSound(const char *name){
	if(!name){
		return NULL;
	}
	auto it = this->sounds.find(name);
	if (it != this->sounds.end()){
		return it->second;
	}
	return NULL;
}

ppSwitch* ppIMS::GetSwitch(const char *name){
	if(!name){
		return NULL;
	}
	auto it = this->switches.find(name);
	if (it != this->switches.end()){
		return it->second;
	}
	return NULL;
}

ppFilter* ppIMS::GetFilter(const char *name){
	if(!name){
		return NULL;
	}
	auto it = this->filters.find(name);
	if (it != this->filters.end()){
		return it->second;
	}
	return NULL;
}

ppRTPC* ppIMS::GetRTPC(const char *name){
	if(!name){
		return NULL;
	}
	auto it = this->rtpcs.find(name);
	if (it != this->rtpcs.end()){
		return it->second;
	}
	return NULL;
}

void ppIMS::RemoveSound(const char *name){
	ppGenericSound* sound = this->GetSound(name);
	if(sound){
		sound->Stop();
		this->sounds.erase(name);
		delete sound;
	}
}

void ppIMS::RemoveSwitch(const char *name){
	ppSwitch* sw = this->GetSwitch(name);
	if(sw){
		this->switches.erase(name);
		delete sw;
	}
}

void ppIMS::ClearSound(){
	for(auto sound : this->sounds){
		delete sound.second;
	}
	this->sounds.clear();
}

void ppIMS::ClearSwitch(){
	for(auto sw : this->switches){
		delete sw.second;
	}
	this->switches.clear();
}

void ppIMS::ClearFilter(){
	for(auto filter : this->filters){
		delete filter.second;
	}
	this->filters.clear();
}

void ppIMS::ClearRTPC(){
	for(auto rtpc : this->rtpcs){
		delete rtpc.second;
	}
	this->rtpcs.clear();
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
	this->ClearFilter();
	this->ClearSound();
	this->ClearSwitch();
	for(auto format : this->formats){
		delete format;
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
	for(auto sw : this->switches){
		sw.second->Update();
	}
}
