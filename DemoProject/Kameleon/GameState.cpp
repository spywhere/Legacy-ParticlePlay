#include "GameState.hpp"

void GameState::OnInit(){
	this->physics = new ppPhysics(0, 10);
	this->player = new kPlayer(this->physics, 320, 240);
}

void GameState::OnRender(SDL_Renderer* renderer, int delta){
	this->player->Render(renderer);
}

void GameState::OnUpdate(ppInput* input, int delta){
	this->physics->Update(delta);
	this->player->Update(input);
}
