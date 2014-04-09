#include "Scene.h"

ppScene::ppScene(){
	this->game = NULL;
	this->name = "";
	this->needInit = false;
}

bool ppScene::IsNeedInit(){
	return this->needInit;
}

void ppScene::SetNeedInit(bool needInit){
	this->needInit = needInit;
}

const char* ppScene::GetName(){
	return this->name;
}

void ppScene::SetName(const char* name){
	this->name = name;
}

ppGame* ppScene::GetGame(){
	return this->game;
}

void ppScene::SetGame(ppGame* game){
	this->game = game;
}

void ppScene::OnRestart(){
	// Pure virtual
	// Will run when game require to restart
}

void ppScene::OnRestore(){
	// Pure virtual
	// Will run after game has been restarted
}

bool ppScene::OnEvent(SDL_Event* event){
	// Pure virtual
	// Will run on important event only
	return false;
}

ppScene::~ppScene(){
	// Pure virtual
	// Will run on destroy only
}