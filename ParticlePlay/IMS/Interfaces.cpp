#include "Interfaces.hpp"

void ppUpdatable::Update(){}

ppPlayable::ppPlayable(){
	this->Stop();
	this->entryCue = 0;
	this->exitCue = -1;
}

ppPlayable::~ppPlayable(){}

void ppPlayable::Play(){
	if(this->isPlaying){
		this->isPause = false;
	}else{
		this->isPlaying = true;
	}
}

void ppPlayable::Pause(){
	this->isPause = true;
}

void ppPlayable::StopDecay(bool decay){
	this->isPlaying = false;
	this->isPause = false;
}

void ppPlayable::Stop(){
	this->StopDecay(false);
}

Sint64 ppPlayable::GetNormalExitCue(){
	if(this->GetExitCue() < 0){
		return this->GetPositionLength()+this->GetExitCue()-this->GetEntryCue();
	}
	return this->GetExitCue();
}

Sint64 ppPlayable::GetEntryCue(){
	return this->entryCue;
}

Sint64 ppPlayable::GetExitCue(){
	return this->exitCue;
}

void ppPlayable::SetEntryCue(Sint64 entryCue){
	this->entryCue = entryCue;
}

void ppPlayable::SetExitCue(Sint64 exitCue){
	this->exitCue = exitCue;
}

bool ppPlayable::IsPause(){
	return this->isPause;
}

bool ppPlayable::IsPlaying(){
	return this->isPlaying && !this->isPause;
}

bool ppPlayable::IsStop(){
	return !this->isPlaying;
}

ppClippable::ppClippable(){
	this->clipStart = 0;
	this->clipEnd = 0;
}

void ppClippable::SetClipStart(Sint64 clipping) {
	this->clipStart = clipping;
}

void ppClippable::SetClipEnd(Sint64 clipping) {
	this->clipEnd = clipping;
}

Sint64 ppClippable::GetClipStart(){
	return this->clipStart;
}

Sint64 ppClippable::GetClipEnd(){
	return this->clipEnd;
}

ppOffsetable::ppOffsetable(){
	this->offset = 0;
}

void ppOffsetable::SetOffset(Sint64 offset){
	this->offset = offset;
}

Sint64 ppOffsetable::GetOffset(){
	return this->offset;
}

ppRhythmic::ppRhythmic(){
	this->rhythm = 0; //Tempo, Beat, NoteValue
	this->SetTimeSignature(4, 4);
	this->SetTempo(120);
}

void ppRhythmic::SetTimeSignature(int beats, int noteValue){
	this->rhythm &= (~0xffff);
	this->rhythm |= (beats & 0xff) << 8;
	this->rhythm |= noteValue & 0xff;
}

void ppRhythmic::SetTempo(int bpm){
	this->rhythm &= 0xffff;
	this->rhythm |= bpm << 16;
}

int ppRhythmic::GetTotalBeat(float time){
	return time/this->GetTimePerBeat();
}

int ppRhythmic::GetCurrentBeat(float time){
	return (this->GetTotalBeat(time) % this->GetBeatPerBar());
}

int ppRhythmic::GetCurrentBar(float time){
	return (this->GetTotalBeat(time) / this->GetBeatPerBar());
}

float ppRhythmic::GetTimeForBeat(int beat){
	return beat*this->GetTimePerBeat();
}

float ppRhythmic::GetTimeForBar(int bar){
	return this->GetTimeForBeat(bar*this->GetBeatPerBar());
}

float ppRhythmic::GetTimePerBeat(){
	return 60.0f/this->GetTempo();
}

int ppRhythmic::GetTempo(){
	return this->rhythm >> 16;
}

int ppRhythmic::GetBeatPerBar(){
	return (this->rhythm >> 8) & 0xf;
}

int ppRhythmic::GetNoteValue(){
	return this->rhythm & 0xf;
}

ppGenericSound::ppGenericSound(const char *name) : ppRhythmic(), ppPlayable(), ppClippable(), ppOffsetable(), ppControl(name, 0, 0) {
	this->preload = false;
	this->volume = 1;
	this->speed = 1;
	this->autoloop = true;
	this->loop = 0;
	this->audioFormat = NULL;
}

ppGenericSound::~ppGenericSound(){}

void ppGenericSound::AddRTPC(ppRTPC* rtpc){
	for(auto it : this->rtpcs){
		if(it == rtpc){
			return;
		}
	}
	this->rtpcs.push_back(rtpc);
}

void ppGenericSound::RemoveRTPC(ppRTPC* rtpc){
	for (auto it = this->rtpcs.begin(); it != this->rtpcs.end(); ++it){
		if(*it == rtpc){
			this->rtpcs.erase(it);
			return;
		}
	}
}

int ppGenericSound::GetTotalBeat(float time){
	return ppRhythmic::GetTotalBeat(time);
}

int ppGenericSound::GetCurrentBeat(float time){
	return ppRhythmic::GetCurrentBeat(time);
}

int ppGenericSound::GetCurrentBar(float time){
	return ppRhythmic::GetCurrentBar(time);
}

int ppGenericSound::GetTotalBeat(){
	return ppRhythmic::GetTotalBeat(this->GetCurrentTime());
}

int ppGenericSound::GetCurrentBeat(){
	return ppRhythmic::GetCurrentBeat(this->GetCurrentTime());
}

int ppGenericSound::GetCurrentBar(){
	return ppRhythmic::GetCurrentBar(this->GetCurrentTime());
}

void ppGenericSound::Seek(Sint64 position){}

void ppGenericSound::Seek(float time){}

void ppGenericSound::SetLoop(int loop){
	this->loop = loop;
}

void ppGenericSound::SetAutoLoop(bool autoloop){
	this->autoloop = autoloop;
}

void ppGenericSound::SetVolume(float volume){
	this->volume = volume;
}

void ppGenericSound::SetSpeed(float speed){
	this->speed = speed;
}

float ppGenericSound::GetVolume(){
	return this->volume;
}

float ppGenericSound::GetSpeed(){
	return this->speed;
}

ppFormat* ppGenericSound::GetAudioFormat(){
	return this->audioFormat;
}

int ppGenericSound::GetLoop(){
	return this->loop;
}

bool ppGenericSound::IsLoop(){
	return this->loop != 0;
}

bool ppGenericSound::IsAutoLoop(){
	return this->autoloop;
}

bool ppGenericSound::IsReady(){
	return this->preload && this->IsStop();
}

void ppGenericSound::Update(){
	ppUpdatable::Update();
	for(auto rtpc : this->rtpcs){
		ppEffectInfo* effect = rtpc->GetEffectInfo(this);
		if(!effect){
			continue;
		}
		float value = effect->GetCurve()->GetValue(rtpc->GetOffset(), 1, 0, 1);
		ALuint sourceID = this->GetSourceID();
		if(effect->GetEffect() == ppRTPCEffect::VOLUME){
			alSourcef(sourceID, AL_GAIN, value);
		}else if(effect->GetEffect() == ppRTPCEffect::PITCH){
			alSourcef(sourceID, AL_PITCH, value);
		}else if(effect->GetEffect() == ppRTPCEffect::PANNING){
			alSource3f(sourceID, AL_POSITION, (value-0.5f)*2.0f, 0, 0);
		}
	}
}

void ppGenericSound::Render(SDL_Renderer* renderer){
	ppControl::Render(renderer);
}

void ppGenericSound::Update(ppInput* input){
	ppControl::Update(input);
}

ppControlType ppGenericSound::GetType(){
	return ppControlType::GENERIC_SOUND_CONTROL;
}
