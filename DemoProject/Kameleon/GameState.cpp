#include "GameState.hpp"

#include <sstream>

GameState::GameState(ppGame* game){
	this->game = game;
}

void GameState::OnInit(){
	this->gui = new ppGUI();
	this->physics = new ppPhysics(0, 50);
	this->physics->SetPTM(10);
	this->level = new Level(this->physics);
	this->player = new kPlayer(this->game, this->physics, 0, 240);
	this->physics->SetPTM(15);
	this->tx = 0;
	this->ty = -350;
	this->debugView = 0;

	this->background = new ppImage("tmpres/Kameleon/Assets/Image 2306.jpg");
}

void GameState::OnRender(SDL_Renderer* renderer, int delta){
	this->background->Render(renderer, this->game->GetWidth()/2-369, this->game->GetHeight()/2-240, 738, 480);
	glPushMatrix();
	glTranslatef(this->tx+320, this->ty, 0);
	this->level->Render(renderer);
	this->player->Render(renderer);
	glPopMatrix();

	std::stringstream ss;
	ss << "Translate: " << this->tx << ", " << this->ty << "\n";
	ss << "Zoom Factor: " << this->physics->GetPTM() << "\n";
	ss << "Water Level: " << (int(this->player->GetWaterLevel()*1000)/1000.0f) << "\n";
	ss << "Player: " << this->player->GetX() << ", " << this->player->GetY();
	if(this->gui->GetDefaultFont()){
		glColor3f(1 ,1 ,1);
		this->gui->GetDefaultFont()->Render(10, 35, ss.str().c_str(), renderer);
	}
	this->gui->Render(renderer);
}

void GameState::OnUpdate(ppInput* input, int delta){
	this->gui->Update(input);
	this->physics->Update(delta);
	this->level->SetDebugView(this->debugView != 0);
	this->player->SetDebugView(this->debugView != 0);
	this->level->Update(input);
	this->player->Update(input, delta);

	if(this->debugView > 1){
		int scrolly = input->GetScrollY();
		if(scrolly!=0){
			this->physics->SetPTM(this->physics->GetPTM()+scrolly);
			if(this->physics->GetPTM()<1){
				this->physics->SetPTM(1);
			}
		}
		if(input->IsMouseDown(SDL_BUTTON_RIGHT)){
			this->tx += input->GetDeltaMouseX();
			this->ty += input->GetDeltaMouseY();
		}
	}else{
		this->physics->SetPTM(15);
		this->tx = -this->player->GetX();
		this->ty = -this->player->GetY() + 240;
	}

	if(this->game->GetInteractiveMusicSystem()){
		ppIMS* ims = this->game->GetInteractiveMusicSystem();
		if(ims->GetRTPC("water_rtpc")){
			ims->GetRTPC("water_rtpc")->SetOffset(this->player->GetWaterLevel());
		}
	}
}

void GameState::SetDebugView(int debugView){
	this->debugView = debugView;
}
