#include "GameState.hpp"

#include <sstream>

void GameState::OnInit(){
	this->gui = new ppGUI();
	this->physics = new ppPhysics(0, 50);
	this->physics->SetPTM(10);
	this->level = new Level(this->physics);
	this->player = new kPlayer(this->physics, 0, 240);
	this->physics->SetPTM(5);
	this->tx = 0;
	this->ty = 150;
}

void GameState::OnRender(SDL_Renderer* renderer, int delta){
	std::stringstream ss;
	ss << "Translate: " << this->tx << ", " << this->ty << "\n";
	ss << "Zoom Factor: " << this->physics->GetPTM();
	if(this->gui->GetDefaultFont()){
		glColor3f(1 ,1 ,1);
		this->gui->GetDefaultFont()->Render(10, 35, ss.str().c_str(), renderer);
	}
	this->gui->Render(renderer);

	glPushMatrix();
	glTranslatef(this->tx+320, this->ty, 0);
	this->level->Render(renderer);
	this->player->Render(renderer);
	glPopMatrix();
}

void GameState::OnUpdate(ppInput* input, int delta){
	this->gui->Update(input);
	this->physics->Update(delta);
	this->level->Update(input);
	this->player->Update(input);

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
}
