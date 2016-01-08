#include "Segment.hpp"

#include <sstream>

ppSegment::ppSegment(const char *name, ppIMS* ims) : ppGenericSound(name){
	this->ims = ims;
	this->emptySound = NULL;
}

ppSegment::~ppSegment(){
	ppGenericSound::~ppGenericSound();
	if(this->emptySound){
		delete this->emptySound;
	}
}

void ppSegment::AddSound(ppGenericSound *sound){
	sound->SetAutoLoop(false);
	this->sounds.push_back(sound);

	if(this->emptySound){
		delete this->emptySound;
	}
	Sint64 maxtime = 0;
	for(auto sound : this->sounds){
		if(maxtime<sound->GetOffset()+sound->GetPositionLength()){
			maxtime = sound->GetOffset()+sound->GetPositionLength();
		}
	}
	this->audioFormat = sound->GetAudioFormat();
	this->emptySound = new ppSound("_empty", ims->CreateEmptyFormat(maxtime, sound->GetAudioFormat()), 1, ims->GetRandomizer());
}

void ppSegment::ClearSound(){
	this->sounds.clear();
}

int ppSegment::GetTotalSound(){
	return this->sounds.size();
}

Sint64 ppSegment::GetCurrentPosition(){
	return this->emptySound->GetCurrentPosition();
}

Sint64 ppSegment::GetPositionLength(){
	return this->emptySound->GetPositionLength();
}

float ppSegment::GetCurrentTime(){
	return this->emptySound->GetCurrentTime();
}

float ppSegment::GetTotalTime(){
	return this->emptySound->GetTotalTime();
}

ALuint ppSegment::GetSourceID(){
	return 0; // Override Add/Remove RTPCs instead
}

void ppSegment::AddRTPC(ppRTPC* rtpc, ppRTPCEffect effect, ppEasing* easing){
	for(auto sound : this->sounds){
		sound->AddRTPC(rtpc, effect, easing);
	}
}

void ppSegment::RemoveRTPC(ppRTPC* rtpc){
	for(auto sound : this->sounds){
		sound->RemoveRTPC(rtpc);
	}
}

void ppSegment::SetFilter(ppFilter* filter){
	for(auto sound : this->sounds){
		sound->SetFilter(filter);
	}
}

void ppSegment::SetLoop(int loop){
	this->emptySound->SetLoop(loop);
}

bool ppSegment::IsLoop(){
	return this->emptySound->IsLoop();
}

bool ppSegment::IsPause(){
	return this->emptySound->IsPause();
}

bool ppSegment::IsStop(){
	return this->emptySound->IsStop();
}

bool ppSegment::IsPlaying(){
	return this->emptySound->IsPlaying();
}

int ppSegment::GetLoop(){
	return this->emptySound->GetLoop();
}

void ppSegment::Play(){
	ppGenericSound::Play();
	this->emptySound->Play();
}

void ppSegment::Pause(){
	ppGenericSound::Pause();
	this->emptySound->Pause();
	for(auto sound : this->sounds){
		if(sound->IsPlaying()){
			sound->Pause();
		}
	}
}

void ppSegment::StopDecay(bool decay){
	ppGenericSound::StopDecay(decay);
	this->emptySound->StopDecay(decay);
	for(auto sound : this->sounds){
		sound->StopDecay(decay);
	}
}

void ppSegment::Seek(float time){
	ppGenericSound::Seek(time);
	this->emptySound->Seek(time);
	for(auto sound : this->sounds){
		sound->Seek(time);
	}
}

void ppSegment::SetVolume(float volume){
	ppGenericSound::SetVolume(volume);
	for(auto sound : this->sounds){
		sound->SetVolume(volume);
	}
}

void ppSegment::SetSpeed(float speed){
	ppGenericSound::SetSpeed(speed);
	for(auto sound : this->sounds){
		sound->SetSpeed(speed);
	}
}

void ppSegment::Update(){
	ppGenericSound::Update();
	this->emptySound->Update();
	for(auto sound : this->sounds){
		if(sound->GetOffset()<this->GetCurrentPosition() && sound->IsStop() && this->GetCurrentPosition() < sound->GetPositionLength()){
			sound->Play();
		}
		if(!this->IsPause() && sound->IsPause()){
			sound->Play();
		}
		sound->Update();
	}
}

void ppSegment::Render(ppGraphics* graphics){
	ppControl::Render(graphics);
	if(!this->visible){
		return;
	}
	//Border
	graphics->SetColor(new ppColor(1.0f, 1.0f, 1.0f));
	graphics->DrawRect(this->x, this->y, this->width, this->height);

	int index=1;
	int height=this->height/(this->sounds.size()+1);
	int width = this->GetCurrentPosition()*(this->width-2)/this->GetPositionLength();
	graphics->SetColor(new ppColor(0.8f, 0.5f, 0.5f));
	graphics->FillRect(this->x, this->y+1, width, height);

	std::stringstream ss;
	ss << this->GetName();
	if(this->GetGUI()->GetDefaultFont()){
		graphics->SetColor(new ppColor(1.0f, 1.0f, 1.0f));
		this->GetGUI()->GetDefaultFont()->Render(this->x+5, this->y+(height/2)-5, ss.str().c_str(), graphics);
	}

	for(auto sound : this->sounds){
		int offset_width = sound->GetOffset()*(this->width-2)/this->GetPositionLength();
		int width = sound->GetCurrentPosition()*(this->width-2)/this->GetPositionLength();
		int max_width = sound->GetPositionLength()*(this->width-2)/this->GetPositionLength();
		//Total playing time
		graphics->SetColor(new ppColor(0.3f+(0.2f*(index%2)), 0.3f+(0.2f*(index%2)), 0.3f+(0.2f*(index%2))));
		graphics->FillRect(this->x+offset_width+width, this->y+(index*height)+1, max_width - width, height);

		//Current playing time
		graphics->SetColor(new ppColor(0.5f, 0.5f+(0.3f*(index%2)), 0.5f+(0.3f*((index+1)%2))));
		graphics->FillRect(this->x+offset_width, this->y+(index*height)+1, width, height);

		std::stringstream ss;
		ss << sound->GetName();
		if(this->GetGUI()->GetDefaultFont()){
			graphics->SetColor(new ppColor(1.0f, 1.0f, 1.0f));
			this->GetGUI()->GetDefaultFont()->Render(this->x+5, this->y+(index*height)+(height/2)-5, ss.str().c_str(), graphics);
		}
		index++;
	}

	//Playing Cursor
	graphics->SetColor(new ppColor(1.0f, 1.0f, 1.0f));
	int offset = this->GetCurrentTime()*(this->width-2)/this->GetTotalTime();
	graphics->DrawLine(this->x+offset, this->y+1, this->x+offset, this->y+this->height);
}

void ppSegment::Update(ppInput* input){
	ppControl::Update(input);
}

ppControlType ppSegment::GetType(){
	return ppControlType::SEGMENT_CONTROL;
}
