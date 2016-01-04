#include "BaseFarmState.hpp"

#include <sstream>
#include "AnimateTile.hpp"

void BaseFarmState::OnInit(){
	this->gui = new ppGUI();
	this->spritesheet = new Spritesheet(new ppImage("tmpres/FarmGame/FarmGame.png"), 8, 8, 5.0f);
	this->grassTile = this->spritesheet->GetTile(0);
	this->dirtTile = this->spritesheet->GetTile(11, 30);
	this->waterTile = new AnimateTile(spritesheet, new int[3]{8, 9, 10}, new int[3]{30, 30, 30}, 3, 1000, 5.0f);
	this->InitEntities();
	this->timeSec = 0;
	this->gameTime = 360;
	this->timeSpeed = 10;
}

void BaseFarmState::RenderNumber(ppGraphics* graphics, int x, int y, int number){
	this->spritesheet->GetTile(8+number, 31)->Render(graphics, x, y);
}

std::string BaseFarmState::FormatNumber(int number){
	std::stringstream ss;
	ss << number;
	return ss.str();
}

std::string BaseFarmState::FormatTime(int time){
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

void BaseFarmState::RenderText(ppGraphics* graphics, int x, int y, const char *time){
	int ox = x;
	int i=0;
	while(time[i]!='\0'){
		if(time[i]=='.'){
			this->RenderNumber(graphics, ox, y, 10);
		}else if(time[i]==','){
			this->RenderNumber(graphics, ox, y, 11);
		}else if(time[i]==':'){
			this->RenderNumber(graphics, ox, y, 12);
		}else if(time[i]=='o'){
			this->RenderNumber(graphics, ox, y, 13);
		}else if(time[i]=='O'){
			this->RenderNumber(graphics, ox, y, 14);
		}else if(time[i]!=' '){
			this->RenderNumber(graphics, ox, y, time[i]-'0');
		}
		ox += this->spritesheet->GetWidth();
		i++;
	}
}

void BaseFarmState::Render(ppGraphics* graphics, int delta){}

void BaseFarmState::OnRender(ppGraphics* graphics, int delta){
	for(int y=-1;y<this->GetGame()->GetHeight()/this->spritesheet->GetHeight();y++){
		for(int x=-1;x<this->GetGame()->GetWidth()/this->spritesheet->GetWidth();x++){
			if(x >= 0 && x <= 3 && y >= 3 && y<= 8){
				this->waterTile->Render(graphics, x*this->waterTile->GetWidth(), y*this->waterTile->GetHeight());
			}else if((x >= 10 && x <= 12 && y >= 3 && y <= 5) || (x >= 14 && x <= 16 && y >= 3 && y <= 5) || (x >= 10 && x <= 12 && y >= 7 && y <= 9) || (x >= 14 && x <= 16 && y >= 7 && y <= 9)){
				this->dirtTile->Render(graphics, x*this->dirtTile->GetWidth(), y*this->dirtTile->GetHeight());
			}else{
				this->grassTile->Render(graphics, x*this->grassTile->GetWidth(), y*this->grassTile->GetHeight());
			}
		}
	}

	this->RenderEntities(graphics, delta);

	if(this->gameTime >= 420 && this->gameTime < 840){
		graphics->SetColor(new ppColor(1.0f, 1.0f, 1.0f));
	}else if(this->gameTime >= 840 && this->gameTime < 1020){
		float gain = (this->gameTime-840)/180.0f;
		graphics->SetColor(new ppColor(1.0f, 1.0f-gain*0.5f, 1.0f-gain));
	}else if(this->gameTime >= 1020){
		float gain = (this->gameTime-1020)/420.0f;
		graphics->SetColor(new ppColor(1.0f-gain, 0.5f-gain*0.25f, gain*0.5f));
	}else if(this->gameTime < 300){
		graphics->SetColor(new ppColor(0.0f, 0.25f, 0.5f));
	}else if(this->gameTime >= 300 && this->gameTime < 420){
		float gain = (this->gameTime-300)/120.0f;
		graphics->SetColor(new ppColor(gain, 0.25f+gain*0.75f, 0.5f+gain*0.5f));
	}

	SDL_BlendMode blendMode = graphics->GetBlendMode();
	graphics->SetBlendMode(SDL_BLENDMODE_MOD);
	graphics->FillRect(0, 0, this->GetGame()->GetWidth(), this->GetGame()->GetHeight());
	graphics->SetColor(new ppColor(1.0f, 1.0f, 1.0f));
	graphics->SetBlendMode(blendMode);

	this->Render(graphics, delta);
	this->RenderText(graphics, 8, this->GetGame()->GetHeight()-this->spritesheet->GetHeight()-50, this->FormatNumber(this->timeSpeed).c_str());
	this->RenderText(graphics, 8, this->GetGame()->GetHeight()-this->spritesheet->GetHeight(), this->FormatTime(this->gameTime).c_str());

	std::stringstream ss;
	ss << "FPS: " << this->GetGame()->GetFPS() << " [" << this->GetGame()->GetAvgRenderTime() << "ms]\n";
	ss << "UPS: " << this->GetGame()->GetUPS() << " [" << this->GetGame()->GetAvgUpdateTime() << "ms]\n";
	if(this->gui->GetDefaultFont()){
		graphics->SetColor(new ppColor(1.0f, 1.0f, 1.0f));
		this->gui->GetDefaultFont()->Render(10, 10, ss.str().c_str(), graphics);
	}
	this->gui->Render(graphics);
}

void BaseFarmState::OnUpdate(ppInput* input, int delta){
	this->waterTile->Update(input, delta);
	this->timeSec += delta*this->timeSpeed;
	if(this->timeSec > 1000){
		this->timeSec %= 1000;
		this->gameTime = (this->gameTime+1)%1440;
	}

	this->UpdateEntities(input, delta);

	this->ims = this->GetGame()->GetInteractiveMusicSystem();
	if(this->ims){
		if(this->ims->GetSound("dawnTrack")){
			this->Update(input, delta);
		}else{
			this->InitSounds();
			this->InitMusic();
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
