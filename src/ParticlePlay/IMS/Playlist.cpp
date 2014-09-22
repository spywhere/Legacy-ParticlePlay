#include "Playlist.hpp"

ppPlaylist::ppPlaylist(const char *name) : ppGenericSound(name){
	this->current = NULL;
	this->next = NULL;
	this->playDuration = 0;
}

void ppPlaylist::AddSound(ppGenericSound *sound){
	sound->SetAutoLoop(false);
	this->sounds.push_back(sound);
	this->queue.push_back(sound);
}

void ppPlaylist::ClearSound(){
	this->sounds.clear();
}

void ppPlaylist::Play(){
	this->current = this->queue.front();
	this->queue.pop_front();
	this->queue.push_back(current);
	this->next = this->queue.front();
	this->current->Play();
}

void ppPlaylist::Stop(){
	this->current = NULL;
	this->next = NULL;
	this->queue.clear();
	for(auto sound : this->sounds){
		this->queue.push_back(sound);
	}
}

Sint64 ppPlaylist::GetCurrentPosition(){
	return this->playDuration;
}

Sint64 ppPlaylist::GetPositionLength(){
	return this->playDuration;
}

float ppPlaylist::GetCurrentTime(){
	// if(this->current!=NULL){
	// 	return this->current->GetAudioFormat()->PositionToTime(this->playDuration);
	// }
	return 0;
}

float ppPlaylist::GetTotalTime(){
	// if(this->current!=NULL){
	// 	return this->current->GetAudioFormat()->PositionToTime(this->playDuration);
	// }
	return 0;
}

void ppPlaylist::Update(){
	if(this->current!=NULL){
		Sint64 length = this->current->GetEntryCue() + this->current->GetExitCue() - this->next->GetEntryCue();
		if(this->current->GetExitCue() < 0){
			length = this->current->GetPositionLength() + this->current->GetExitCue() - this->next->GetEntryCue();
		}
		if(this->current->GetCurrentPosition() >= length){
			this->current = this->queue.front();
			this->queue.pop_front();
			this->queue.push_back(current);
			this->next = this->queue.front();
			this->current->Play();
		}
	}
	for(auto sound : this->sounds){
		sound->Update();
	}
}

void ppPlaylist::Render(SDL_Renderer* renderer){
	int index=1;
	int height=this->height/(this->sounds.size()+1);
	for(auto sound : this->sounds){
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
			Sint64 length = sound->GetEntryCue() + sound->GetExitCue();
			if(sound->GetExitCue() < 0){
				length = sound->GetPositionLength() + sound->GetExitCue();
			}
			glColor3f(1, 1, 1);
			int offset = length*(this->width-2)/sound->GetPositionLength();
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
