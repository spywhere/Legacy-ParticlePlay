#include "FarmState.hpp"

#include <iostream>
#include <sstream>
#include "AnimateTile.hpp"
#include "Chicken.hpp"
#include "Player.hpp"

void FarmState::OnInit(){
	this->gui = new ppGUI();
	this->spritesheet = new Spritesheet(new ppImage("tmpres/FarmGame/FarmGame.png"), 8, 8, 5.0f);
	this->grassTile = this->spritesheet->GetTile(0);
	this->dirtTile = this->spritesheet->GetTile(11, 30);
	this->waterTile = new AnimateTile(spritesheet, new int[3]{8, 9, 10}, new int[3]{30, 30, 30}, 3, 1000, 5.0f);
	this->player = new Player(this->spritesheet, this->GetGame()->GetWidth()/2, this->GetGame()->GetHeight()/2);
	this->chicken = new Chicken(this->spritesheet, this->GetGame()->GetWidth()/2, this->GetGame()->GetHeight()/8);
	this->timeSec = 0;
	this->gameTime = 360;
	this->timeSpeed = 10;
}

void FarmState::RenderNumber(SDL_Renderer* renderer, int x, int y, int number){
	this->spritesheet->GetTile(8+number, 31)->Render(renderer, x, y);
}

std::string FarmState::FormatNumber(int number){
	std::stringstream ss;
	ss << number;
	return ss.str();
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

void FarmState::RenderText(SDL_Renderer* renderer, int x, int y, const char *time){
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
	for(int y=-1;y<this->GetGame()->GetHeight()/this->spritesheet->GetHeight();y++){
		for(int x=-1;x<this->GetGame()->GetWidth()/this->spritesheet->GetWidth();x++){
			if(x >= 0 && x <= 3 && y >= 3 && y<= 8){
				this->waterTile->Render(renderer, x*this->waterTile->GetWidth(), y*this->waterTile->GetHeight());
			}else if((x >= 10 && x <= 12 && y >= 3 && y <= 5) || (x >= 14 && x <= 16 && y >= 3 && y <= 5) || (x >= 10 && x <= 12 && y >= 7 && y <= 9) || (x >= 14 && x <= 16 && y >= 7 && y <= 9)){
				this->dirtTile->Render(renderer, x*this->dirtTile->GetWidth(), y*this->dirtTile->GetHeight());
			}else{
				this->grassTile->Render(renderer, x*this->grassTile->GetWidth(), y*this->grassTile->GetHeight());
			}
		}
	}

	this->chicken->Render(renderer);
	this->player->Render(renderer);

	glEnable(GL_BLEND);
	glBlendFunc(GL_ZERO, GL_SRC_COLOR);
	glBegin(GL_QUADS);
		if(this->gameTime >= 420 && this->gameTime < 840){
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		}else if(this->gameTime >= 840 && this->gameTime < 1020){
			float gain = (this->gameTime-840)/180.0f;
			glColor4f(1.0f, 1.0f-gain*0.5f, 1.0f-gain, 1.0f);
		}else if(this->gameTime >= 1020){
			float gain = (this->gameTime-1020)/420.0f;
			glColor4f(1.0f-gain, 0.5f-gain*0.25f, gain*0.5f, 1.0f);
		}else if(this->gameTime < 300){
			glColor4f(0.0f, 0.25f, 0.5f, 1.0f);
		}else if(this->gameTime >= 300 && this->gameTime < 420){
			float gain = (this->gameTime-300)/120.0f;
			glColor4f(gain, 0.25f+gain*0.75f, 0.5f+gain*0.5f, 1.0f);
		}
		glVertex3f(0, 0, 0);
		glVertex3f(this->GetGame()->GetWidth(), 0, 0);
		glVertex3f(this->GetGame()->GetWidth(), this->GetGame()->GetHeight(), 0);
		glVertex3f(0, this->GetGame()->GetHeight(), 0);
	glEnd();
	glDisable(GL_BLEND);
	glColor3f(1 ,1 ,1);

	this->RenderText(renderer, 8, this->GetGame()->GetHeight()-this->spritesheet->GetHeight()-50, this->FormatNumber(this->timeSpeed).c_str());
	this->RenderText(renderer, 8, this->GetGame()->GetHeight()-this->spritesheet->GetHeight(), this->FormatTime(this->gameTime).c_str());

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
	this->waterTile->Update(input, delta);
	this->timeSec += delta*this->timeSpeed;
	if(this->timeSec > 1000){
		this->timeSec %= 1000;
		this->gameTime = (this->gameTime+1)%1440;
	}

	this->chicken->SetInWater(this->chicken->IsInside(0, (int)(2.5f*this->spritesheet->GetHeight()), 4*this->spritesheet->GetWidth(), (int)(5.8f*this->spritesheet->GetHeight())));
	this->player->SetInWater(this->player->IsInside(0, (int)(2.5f*this->spritesheet->GetHeight()), 4*this->spritesheet->GetWidth(), (int)(5.8f*this->spritesheet->GetHeight())));
	this->chicken->Update(input, delta);
	this->player->Update(input, delta);

	this->ims = this->GetGame()->GetInteractiveMusicSystem();
	if(this->ims){
		if(this->ims->GetSound("dawnTrack")){
			if(this->gameTime >= 360 && this->gameTime < 840 && this->ims->GetSound("dawnTrack")->IsStop()){
				std::cout << "Dawn Track" << std::endl;
				this->ims->GetSound("dawnTrack")->Play();
				this->ims->GetSound("nightTrack")->Stop();
				this->ims->GetSound("predawnTrack")->Stop();
			}else if(this->gameTime >= 840 && this->gameTime < 1320 && this->ims->GetSound("nightTrack")->IsStop()){
				std::cout << "Night Track" << std::endl;
				this->ims->GetSound("dawnTrack")->Stop();
				this->ims->GetSound("nightTrack")->Play();
				this->ims->GetSound("predawnTrack")->Stop();
			}else if((this->gameTime >= 1320 || this->gameTime < 360) && this->ims->GetSound("predawnTrack")->IsStop()){
				std::cout << "PreDawn Track" << std::endl;
				this->ims->GetSound("dawnTrack")->Stop();
				this->ims->GetSound("nightTrack")->Stop();
				this->ims->GetSound("predawnTrack")->Play();
			}
		}else{
			ppFormat* chickenFormat = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/FarmGame/Chicken.wav");
			this->ims->CreateSound("chickenSound", chickenFormat);
			this->chicken->SetSound("chickenSound");

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
		}
	}
	this->gui->Update(input);

	if(input->IsKeyDown(SDL_SCANCODE_R)){
		this->ims->ClearSound();
		this->ims->ClearSwitch();
		this->GetGame()->EnterState("ims");
	}

	if(input->IsKeyDown(SDL_SCANCODE_Q)){
		if(this->timeSpeed > 1){
			this->timeSpeed--;
		}
	}else if(input->IsKeyDown(SDL_SCANCODE_E)){
		this->timeSpeed++;
	}
}
