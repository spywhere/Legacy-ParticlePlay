#include "FarmState.hpp"

#include <sstream>

void FarmState::OnInit(){
	this->gui = new ppGUI();
	this->spritesheet = new Spritesheet(new ppImage("tmpres/FarmGame/FarmGame.png"), 8, 8, 5.0f);
	this->tile = this->spritesheet->GetTile(0);
	this->player = new Player(this->spritesheet, this->GetGame()->GetWidth()/2, this->GetGame()->GetHeight()/2);
	this->timeSec = 0;
	this->gameTime = 360;
}

void FarmState::RenderNumber(SDL_Renderer* renderer, int x, int y, int number){
	this->spritesheet->GetTile(8+number, 31)->Render(renderer, x, y);
}

std::string FarmState::FormatTime(int time){
	std::stringstream ss;
	int hour = time/60;
	int minute = time%60;
	if(hour < 10){
		ss << "0";
	}
	ss << hour << ":";
	if(minute < 10){
		ss << "0";
	}
	ss << minute;
	return ss.str();
}

void FarmState::RenderTime(SDL_Renderer* renderer, int x, int y, const char *time){
	int ox = x;
	int i=0;
	while(time[i]!='\0'){
		if(time[i]=='.'){
			this->RenderNumber(renderer, ox, y, 10);
		}else if(time[i]==','){
			this->RenderNumber(renderer, ox, y, 11);
		}else if(time[i]==':'){
			this->RenderNumber(renderer, ox, y, 12);
		}else{
			this->RenderNumber(renderer, ox, y, time[i]-'0');
		}
		ox += this->spritesheet->GetWidth();
		i++;
	}
}

void FarmState::OnRender(SDL_Renderer* renderer, int delta){
	for(int y=-1;y<this->GetGame()->GetHeight()/this->tile->GetHeight();y++){
		for(int x=-1;x<this->GetGame()->GetWidth()/this->tile->GetWidth();x++){
			this->tile->Render(renderer, x*this->tile->GetWidth(), y*this->tile->GetHeight());
		}
	}

	this->player->Render(renderer);

	this->RenderTime(renderer, 8, this->GetGame()->GetHeight()-this->spritesheet->GetHeight(), this->FormatTime(this->gameTime).c_str());

	std::stringstream ss;
	ss << "FPS: " << this->GetGame()->GetFPS() << " [" << this->GetGame()->GetAvgRenderTime() << "ms]\n";
	ss << "UPS: " << this->GetGame()->GetUPS() << " [" << this->GetGame()->GetAvgUpdateTime() << "ms]\n";
	if(this->gui->GetDefaultFont()){
		glColor3f(1 ,1 ,1);
		this->gui->GetDefaultFont()->Render(10, 10, ss.str().c_str(), renderer);
	}
	this->gui->Render(renderer);
}

void FarmState::OnUpdate(ppInput* input, int delta){
	this->timeSec += delta;
	if(this->timeSec > 1000){
		this->timeSec %= 1000;
		this->gameTime = (this->gameTime+1)%1440;
	}
	this->ims = this->GetGame()->GetInteractiveMusicSystem();
	if(this->ims){
		if(!this->ims->GetSound("dawnTrack")){
			ppFormat* dawnFormat = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/FarmGame/Dawn.wav");
			ppFormat* nightFormat = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/FarmGame/Night.wav");
			ppFormat* predawnFormat = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/FarmGame/PreDawn.wav");

			ppSound* dawnSound = this->ims->CreateSound("dawnSound", dawnFormat);
			ppSound* dawnSound2 = this->ims->CreateSound("dawnSound2", dawnFormat);
			ppSound* nightSound = this->ims->CreateSound("nightSound", nightFormat);
			ppSound* nightSound2 = this->ims->CreateSound("nightSound2", nightFormat);
			ppSound* predawnSound = this->ims->CreateSound("predawnSound", predawnFormat);
			ppSound* predawnSound2 = this->ims->CreateSound("predawnSound2", predawnFormat);

			ppSegment* dawnSegment = this->ims->CreateSegment("dawnSeg1");
			ppSegment* dawnSegment2 = this->ims->CreateSegment("dawnSeg2");
			ppSegment* nightSegment = this->ims->CreateSegment("nightSeg1");
			ppSegment* nightSegment2 = this->ims->CreateSegment("nightSeg2");
			ppSegment* predawnSegment = this->ims->CreateSegment("predawnSeg1");
			ppSegment* predawnSegment2 = this->ims->CreateSegment("predawnSeg2");

			dawnSegment->AddSound(dawnSound);
			dawnSegment2->AddSound(dawnSound2);
			nightSegment->AddSound(nightSound);
			nightSegment2->AddSound(nightSound2);
			predawnSegment->AddSound(predawnSound);
			predawnSegment2->AddSound(predawnSound2);

			dawnSegment->SetExitCue(dawnFormat->TimeToPosition(22.75f));
			dawnSegment2->SetExitCue(dawnFormat->TimeToPosition(22.75f));
			nightSegment->SetExitCue(nightFormat->TimeToPosition(22.75f));
			nightSegment2->SetExitCue(nightFormat->TimeToPosition(22.75f));
			predawnSegment->SetExitCue(predawnFormat->TimeToPosition(22.75f));
			predawnSegment2->SetExitCue(predawnFormat->TimeToPosition(22.75f));

			ppPlaylist* dawnPlaylist = this->ims->CreatePlaylist("dawnTrack");
			dawnPlaylist->AddSound(dawnSegment);
			dawnPlaylist->AddSound(dawnSegment2);
			dawnPlaylist->SetLoop(-1);
			ppPlaylist* nightPlaylist = this->ims->CreatePlaylist("nightTrack");
			nightPlaylist->AddSound(nightSegment);
			nightPlaylist->AddSound(nightSegment2);
			nightPlaylist->SetLoop(-1);
			ppPlaylist* predawnPlaylist = this->ims->CreatePlaylist("predawnTrack");
			predawnPlaylist->AddSound(predawnSegment);
			predawnPlaylist->AddSound(predawnSegment2);
			predawnPlaylist->SetLoop(-1);

			dawnPlaylist->Play();
		}
	}
	this->gui->Update(input);

	if(input->IsKeyDown(SDL_SCANCODE_W) || input->IsKeyDown(SDL_SCANCODE_UP)){
		this->player->MoveY(-2);
	}else if(input->IsKeyDown(SDL_SCANCODE_S) || input->IsKeyDown(SDL_SCANCODE_DOWN)){
		this->player->MoveY(2);
	}else{
		this->player->MoveY(0);
	}
	if(input->IsKeyDown(SDL_SCANCODE_A) || input->IsKeyDown(SDL_SCANCODE_LEFT)){
		this->player->MoveX(-2);
	}else if(input->IsKeyDown(SDL_SCANCODE_D) || input->IsKeyDown(SDL_SCANCODE_RIGHT)){
		this->player->MoveX(2);
	}else{
		this->player->MoveX(0);
	}
	this->player->Update();
}
