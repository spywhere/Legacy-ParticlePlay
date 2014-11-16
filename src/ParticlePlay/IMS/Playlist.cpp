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
			if(this->playOrder == ppPlaylistPlayOrder::SHUFFLE_STEP){
				break;
			}
		}
	}else if(this->playOrder == ppPlaylistPlayOrder::SEQUENCE_CONTINUOUS || this->playOrder == ppPlaylistPlayOrder::SEQUENCE_STEP){
		for(auto sound : this->sounds){
			this->soundOrder.push_back(sound);
			this->queue.push_back(sound);
			if(this->playOrder == ppPlaylistPlayOrder::SEQUENCE_STEP){
				break;
			}
		}
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

void ppPlaylist::Stop(){
	if(this->IsStop()){
		return;
	}
	ppGenericSound::Stop();
	for(auto sound : this->sounds){
		if(!sound->IsStop()){
			sound->Stop();
		}
	}
	this->playDuration = 0;
	this->current = NULL;
	this->next = NULL;
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

	Sint64 exitCue = this->soundOrder.back()->GetExitCue();
	if(exitCue >= 0){
		exitCue = this->GetPositionLength()-this->GetEntryCue()-(this->soundOrder.back()->GetPositionLength()-this->soundOrder.back()->GetExitCue()-this->soundOrder.back()->GetEntryCue());
	}
	return exitCue;
}

Sint64 ppPlaylist::GetCurrentPosition(){
	if(!this->current){
		return 0;
	}
	if(playDuration == 0){
		return this->current->GetCurrentPosition();
	}else{
		return this->current->GetCurrentPosition()-this->current->GetEntryCue()+this->playDuration;
	}
}

Sint64 ppPlaylist::GetPositionLength(){
	Sint64 totalLength = 0;
	for(auto sound : this->soundOrder){
		if(sound->GetExitCue() < 0){
			totalLength += sound->GetPositionLength()-sound->GetEntryCue()+sound->GetExitCue();
		}else{
			totalLength += sound->GetExitCue();
		}
	}
	if(this->soundOrder.size()>0){
		totalLength += this->soundOrder.front()->GetEntryCue();
		if(this->soundOrder.back()->GetExitCue() < 0){
			totalLength -= this->soundOrder.back()->GetExitCue();
		}else{
			totalLength += this->soundOrder.back()->GetPositionLength()-this->soundOrder.back()->GetExitCue()-this->soundOrder.back()->GetEntryCue();
		}
	}
	return totalLength;
}

float ppPlaylist::GetCurrentTime(){
	if(!this->current){
		if(this->soundOrder.size()<=0){
			return 0;
		}else{
			return this->soundOrder.front()->GetCurrentTime();
		}
	}
	return this->current->GetCurrentTime();
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

void ppPlaylist::Update(){
	if(this->current!=NULL){
		Sint64 length = this->current->GetExitCue();
		Sint64 triggerLength = this->current->GetEntryCue() + this->current->GetExitCue() - this->next->GetEntryCue();
		if(this->current->GetExitCue() < 0){
			length = this->current->GetPositionLength() + this->current->GetExitCue() - this->current->GetEntryCue();
			triggerLength = this->current->GetPositionLength() + this->current->GetExitCue() - this->next->GetEntryCue();
		}
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
				this->current = this->queue.front();
				this->queue.pop_front();
				this->queue.push_back(current);
				this->next = this->queue.front();
				this->current->Play();
			}
		}
		if(this->queue.back() == this->soundOrder.back() && this->queue.back()->IsStop()){
			if(!this->IsAutoLoop() || this->loop == 0){
				this->Stop();
			}
		}
		if(!this->IsAutoLoop() && this->current == this->soundOrder.back() && this->current->IsStop()){
			this->playDuration = 0;
			this->SetPlayOrder(this->GetPlayOrder());
		}
	}
	for(auto sound : this->sounds){
		sound->Update();
	}
}

void ppPlaylist::Render(SDL_Renderer* renderer){
	ppControl::Render(renderer);
	if(!this->visible){
		return;
	}
	int index=0;
	int height=this->height/(this->soundOrder.size()+1);
	for(auto sound : this->soundOrder){
		int width = sound->GetCurrentPosition()*(this->width-2)/sound->GetPositionLength();
		int max_width = sound->GetPositionLength()*(this->width-2)/sound->GetPositionLength();
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
			Sint64 exitCue = sound->GetEntryCue() + sound->GetExitCue();
			if(sound->GetExitCue() < 0){
				exitCue = sound->GetPositionLength() + sound->GetExitCue();
			}
			glColor3f(1, 1, 1);
			int offset = exitCue*(this->width-2)/sound->GetPositionLength();
			glVertex3f(this->x+offset, this->y+(index*height)+1, 0);
			glVertex3f(this->x+offset, this->y+(index*height)+height, 0);
		}
		glEnd();

		std::stringstream ss;
		ss << sound->GetName();
		if(this->GetGUI()->GetDefaultFont()){
			glColor3f(1 ,1 ,1);
			this->GetGUI()->GetDefaultFont()->Render(this->x+5, this->y+(index*height)+(height/2)-5, ss.str().c_str(), renderer);
		}

		index++;
	}
}

void ppPlaylist::Update(ppInput* input){
	ppControl::Update(input);
}

ppControlType ppPlaylist::GetType(){
	return ppControlType::PLAYLIST_CONTROL;
}
