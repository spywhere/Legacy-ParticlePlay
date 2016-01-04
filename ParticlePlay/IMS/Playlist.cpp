#include "Playlist.hpp"

#include <iterator>
#include <sstream>

ppPlaylist::ppPlaylist(const char *name, ppRandomizer* randomizer) : ppGenericSound(name){
	this->randomizer = randomizer;
	this->current = NULL;
	this->next = NULL;
	this->playDuration = 0;
	this->SetPlayOrder(ppPlaylistPlayOrder::SEQUENCE_CONTINUOUS);
}

void ppPlaylist::AddSound(ppGenericSound *sound){
	sound->SetAutoLoop(false);
	this->sounds.push_back(sound);
	this->SetPlayOrder(this->GetPlayOrder());
}

void ppPlaylist::ClearSound(){
	this->sounds.clear();
}

void ppPlaylist::SetPlayOrder(ppPlaylistPlayOrder playOrder){
	this->playOrder = playOrder;
	this->queue.clear();
	this->soundOrder.clear();
	if(this->playOrder == ppPlaylistPlayOrder::SHUFFLE_CONTINUOUS || this->playOrder == ppPlaylistPlayOrder::SHUFFLE_STEP){
		std::list<ppGenericSound*> sequencelist;
		for(auto sound : this->sounds){
			sequencelist.push_back(sound);
		}
		while(!sequencelist.empty()){
			auto numit = sequencelist.begin();
			int x = this->randomizer->NextInt(sequencelist.size());
			advance(numit, x);
			this->soundOrder.push_back(*numit);
			this->queue.push_back(*numit);
			sequencelist.erase(numit);
		}
	}else if(this->playOrder == ppPlaylistPlayOrder::SEQUENCE_CONTINUOUS || this->playOrder == ppPlaylistPlayOrder::SEQUENCE_STEP){
		for(auto sound : this->sounds){
			this->soundOrder.push_back(sound);
			this->queue.push_back(sound);
		}
	}
	if(this->soundOrder.size() > 0){
		this->audioFormat = this->soundOrder.front()->GetAudioFormat();
	}
}

ppPlaylistPlayOrder ppPlaylist::GetPlayOrder(){
	return this->playOrder;
}

void ppPlaylist::Play(){
	ppGenericSound::Play();
	if(!this->current || !this->current->IsPause()){
		this->current = this->queue.front();
		this->queue.pop_front();
		this->queue.push_back(current);
		this->next = this->queue.front();
		this->current->Play();
	}else{
		for(auto sound : this->sounds){
			if(sound->IsPause()){
				sound->Play();
			}
		}
	}
}

void ppPlaylist::Pause(){
	ppGenericSound::Pause();
	for(auto sound : this->sounds){
		if(sound->IsPlaying()){
			sound->Pause();
		}
	}
}

void ppPlaylist::SoftStop(bool decay, bool reset){
	if(this->IsStop()){
		return;
	}
	ppGenericSound::StopDecay(decay);
	if(!decay){
		for(auto sound : this->sounds){
			if(!sound->IsStop()){
				sound->StopDecay(decay);
			}
		}
	}
	if(reset){
		this->queue.clear();
		for(auto sound : this->soundOrder){
			this->queue.push_back(sound);
		}
	}
	this->playDuration = 0;
	this->current = NULL;
	this->next = NULL;
}

void ppPlaylist::StopDecay(bool decay){
	this->SoftStop(decay, true);
}

ppGenericSound *ppPlaylist::GetPlayingSound(){
	return this->current;
}

ppGenericSound *ppPlaylist::GetSoundAtIndex(int index){
	if(index < this->soundOrder.size()){
		return *std::next(this->soundOrder.begin(), index);
	}
	return NULL;
}

int ppPlaylist::GetTotalSound(){
	if(this->playOrder == ppPlaylistPlayOrder::SHUFFLE_STEP || this->playOrder == ppPlaylistPlayOrder::SEQUENCE_STEP){
		return this->soundOrder.size() > 0 ? 1 : 0;
	}
	return this->sounds.size();
}

Sint64 ppPlaylist::GetEntryCue(){
	if(this->soundOrder.size()<=0){
		return 0;
	}
	return this->soundOrder.front()->GetEntryCue();
}

Sint64 ppPlaylist::GetExitCue(){
	if(this->soundOrder.size()<=0){
		return 0;
	}

	ppGenericSound* sound = this->soundOrder.back();
	if(this->playOrder == ppPlaylistPlayOrder::SHUFFLE_STEP || this->playOrder == ppPlaylistPlayOrder::SEQUENCE_STEP){
		sound = this->soundOrder.front();
	}
	return this->GetPositionLength()-this->GetEntryCue()-(sound->GetPositionLength()-sound->GetNormalExitCue()-sound->GetEntryCue());
}

Sint64 ppPlaylist::GetCurrentPosition(){
	if(!this->current){
		return 0;
	}
	if(this->playDuration == 0 || this->playOrder == ppPlaylistPlayOrder::SHUFFLE_STEP || this->playOrder == ppPlaylistPlayOrder::SEQUENCE_STEP){
		return this->current->GetCurrentPosition();
	}else{
		return this->current->GetCurrentPosition()-this->current->GetEntryCue()+this->playDuration;
	}
}

Sint64 ppPlaylist::GetPositionLength(){
	Sint64 totalLength = 0;
	for(auto sound : this->soundOrder){
		totalLength += sound->GetExitCue();
		if(this->playOrder == ppPlaylistPlayOrder::SHUFFLE_STEP || this->playOrder == ppPlaylistPlayOrder::SEQUENCE_STEP){
			break;
		}
	}
	if(this->soundOrder.size()>0){
		totalLength += this->soundOrder.front()->GetEntryCue();
		ppGenericSound* sound = this->soundOrder.back();
		if(this->playOrder == ppPlaylistPlayOrder::SHUFFLE_STEP || this->playOrder == ppPlaylistPlayOrder::SEQUENCE_STEP){
			sound = this->soundOrder.front();
		}
		totalLength += sound->GetPositionLength()-sound->GetExitCue()-sound->GetEntryCue();
	}
	return totalLength;
}

float ppPlaylist::GetCurrentTime(){
	float time = 0;
	for(auto sound : this->soundOrder){
		if(sound == this->current){
			break;
		}
		if(time == 0){
			time += sound->GetAudioFormat()->PositionToTime(sound->GetEntryCue());
		}
		time += sound->GetAudioFormat()->PositionToTime(sound->GetNormalExitCue()-sound->GetEntryCue());
	}
	if(!this->current){
		if(this->soundOrder.size()<=0){
			return 0;
		}else{
			return time+this->soundOrder.front()->GetCurrentTime();
		}
	}
	return time+this->current->GetCurrentTime();
}

float ppPlaylist::GetTotalTime(){
	if(!this->current){
		if(this->soundOrder.size()<=0){
			return 0;
		}else{
			return this->soundOrder.front()->GetTotalTime();
		}
	}
	return this->current->GetTotalTime();
}

ALuint ppPlaylist::GetSourceID(){
	return 0; // Override Add/Remove RTPCs instead
}

void ppPlaylist::AddRTPC(ppRTPC* rtpc, ppRTPCEffect effect, ppEasing* easing){
	for(auto sound : this->sounds){
		sound->AddRTPC(rtpc, effect, easing);
	}
}

void ppPlaylist::RemoveRTPC(ppRTPC* rtpc){
	for(auto sound : this->sounds){
		sound->RemoveRTPC(rtpc);
	}
}

void ppPlaylist::SetFilter(ppFilter* filter){
	for(auto sound : this->sounds){
		sound->SetFilter(filter);
	}
}

void ppPlaylist::SetVolume(float volume){
	ppGenericSound::SetVolume(volume);
	for(auto sound : this->sounds){
		sound->SetVolume(volume);
	}
}

void ppPlaylist::SetSpeed(float speed){
	ppGenericSound::SetSpeed(speed);
	for(auto sound : this->sounds){
		sound->SetSpeed(speed);
	}
}

void ppPlaylist::SetTempo(int bpm){
	ppRhythmic::SetTempo(bpm);
	for(auto sound : this->sounds){
		sound->SetTempo(bpm);
	}
}

void ppPlaylist::Update(){
	ppGenericSound::Update();
	if(this->current!=NULL){
		Sint64 length = this->current->GetNormalExitCue();
		Sint64 triggerLength = this->current->GetEntryCue() + this->current->GetNormalExitCue() - this->next->GetEntryCue();
		if(this->current->GetCurrentPosition() >= triggerLength){
			if(this->playDuration == 0){
				this->playDuration += this->current->GetEntryCue();
			}
			if(this->current != this->soundOrder.back()){
				this->playDuration += length;
			}
			bool willPlay = false;
			if(this->IsAutoLoop() || this->queue.front() != this->soundOrder.front()){
				if(this->IsAutoLoop() && this->queue.front() == this->soundOrder.front()){
					willPlay = loop != 0;
					if(loop > 0){
						this->loop--;
					}
				}else{
					willPlay = true;
				}
			}
			if(willPlay){
				if(this->playOrder == ppPlaylistPlayOrder::SHUFFLE_CONTINUOUS || this->playOrder == ppPlaylistPlayOrder::SEQUENCE_CONTINUOUS){
					this->current = this->queue.front();
					this->queue.pop_front();
					this->queue.push_back(current);
					this->next = this->queue.front();
					this->current->Play();
				}
			}
		}
		if(!this->IsAutoLoop() || this->loop == 0){
			if(this->playOrder == ppPlaylistPlayOrder::SHUFFLE_CONTINUOUS || this->playOrder == ppPlaylistPlayOrder::SEQUENCE_CONTINUOUS){
				if(this->queue.back() == this->soundOrder.back() && this->queue.back()->IsStop()){
					this->Stop();
				}
			}else{
				if(this->queue.back() == this->soundOrder.front() && this->queue.back()->IsStop()){
					this->soundOrder.push_back(this->soundOrder.front());
					this->soundOrder.front()->Seek(0.0f);
					this->soundOrder.pop_front();
					this->SoftStop(true, false);
				}
			}
		}
	}
	for(auto sound : this->sounds){
		sound->Update();
	}
}

void ppPlaylist::Seek(float time){
	int index = 0;
	for(auto sound : this->sounds){
		float duration = sound->GetAudioFormat()->PositionToTime(sound->GetNormalExitCue());
		if(index != 0){
			duration -= sound->GetAudioFormat()->PositionToTime(sound->GetEntryCue());
		}
		if(time < duration){
			sound->Seek(time);
			break;
		}else{
			time -= duration;
		}
		index++;
	}
	while(index-- > 0){
		this->queue.push_back(this->queue.front());
		this->queue.pop_front();
	}
}

void ppPlaylist::Render(ppGraphics* graphics){
	ppControl::Render(graphics);
	if(!this->visible){
		return;
	}
	int index=0;
	int height=this->height/(this->GetTotalSound()+1);
	for(auto sound : this->soundOrder){
		int width = sound->GetCurrentPosition()*(this->width-2)/sound->GetPositionLength();
		int max_width = this->width-2;
		//Total playing time
		glBegin(GL_QUADS);
		{
			glColor4f(0.3f+(0.2f*(index%2)), 0.3f+(0.2f*(index%2)), 0.3f+(0.2f*(index%2)), 1);
			glVertex3f(this->x+width, this->y+(index*height)+1, 0);
			glVertex3f(this->x+max_width, this->y+(index*height)+1, 0);
			glVertex3f(this->x+max_width, this->y+(index*height)+height, 0);
			glVertex3f(this->x+width, this->y+(index*height)+height, 0);
		}
		glEnd();
		//Current playing time
		glBegin(GL_QUADS);
		{
			glColor4f(0.5f, 0.5f+(0.3f*(index%2)), 0.5f+(0.3f*((index+1)%2)), 1);
			glVertex3f(this->x, this->y+(index*height)+1, 0);
			glVertex3f(this->x+width, this->y+(index*height)+1, 0);
			glVertex3f(this->x+width, this->y+(index*height)+height, 0);
			glVertex3f(this->x, this->y+(index*height)+height, 0);
		}
		glEnd();
		//Entry Cue
		glBegin(GL_LINES);
		{
			glColor3f(1, 1, 1);
			int offset = sound->GetEntryCue()*(this->width-2)/sound->GetPositionLength();
			glVertex3f(this->x+offset, this->y+(index*height)+1, 0);
			glVertex3f(this->x+offset, this->y+(index*height)+height, 0);
		}
		glEnd();
		//Exit Cue
		glBegin(GL_LINES);
		{
			Sint64 exitCue = sound->GetEntryCue()+sound->GetNormalExitCue();
			glColor3f(1, 1, 1);
			int offset = exitCue*(this->width-2)/sound->GetPositionLength();
			glVertex3f(this->x+offset, this->y+(index*height)+1, 0);
			glVertex3f(this->x+offset, this->y+(index*height)+height, 0);
		}
		glEnd();
		//Beat line
		glBegin(GL_LINES);
		{
			glColor4f(1, 1, 1, 0.25f);
			float beatTime = sound->GetTimePerBeat();
			while(sound->GetEntryCue()+sound->GetAudioFormat()->TimeToPosition(beatTime) < sound->GetPositionLength()){
				int offset = (int)((sound->GetEntryCue()+sound->GetAudioFormat()->TimeToPosition(beatTime))*(this->width-2)/sound->GetPositionLength());
				glVertex3f(this->x+offset, this->y+(index*height)+1, 0);
				glVertex3f(this->x+offset, this->y+(index*height)+(height/8), 0);
				beatTime += sound->GetTimePerBeat();
			}
		}
		//Bar line
		glBegin(GL_LINES);
		{
			glColor4f(1, 1, 1, 0.5f);
			float barTime = sound->GetTimePerBeat()*sound->GetBeatPerBar();
			while(sound->GetEntryCue()+sound->GetAudioFormat()->TimeToPosition(barTime) < sound->GetPositionLength()){
				int offset = (int)((sound->GetEntryCue()+sound->GetAudioFormat()->TimeToPosition(barTime))*(this->width-2)/sound->GetPositionLength());
				glVertex3f(this->x+offset, this->y+(index*height)+1, 0);
				glVertex3f(this->x+offset, this->y+(index*height)+(height/4), 0);
				barTime += sound->GetTimePerBeat()*sound->GetBeatPerBar();
			}
		}
		glEnd();

		std::stringstream ss;
		ss << sound->GetName();
		if(this->GetGUI()->GetDefaultFont()){
			glColor3f(1 ,1 ,1);
			this->GetGUI()->GetDefaultFont()->Render(this->x+5, this->y+(index*height)+(height/2)-5, ss.str().c_str(), graphics);
		}

		index++;
		if(this->playOrder == ppPlaylistPlayOrder::SHUFFLE_STEP || this->playOrder == ppPlaylistPlayOrder::SEQUENCE_STEP){
			break;
		}
	}
}

void ppPlaylist::Update(ppInput* input){
	ppControl::Update(input);
}

ppControlType ppPlaylist::GetType(){
	return ppControlType::PLAYLIST_CONTROL;
}
