#include "State.h"

ppState::ppState(){
	this->game = NULL;
	this->name = "";
	this->needInit = false;
}

bool ppState::IsNeedInit(){
	return this->needInit;
}

void ppState::SetNeedInit(bool needInit){
	this->needInit = needInit;
}

const char* ppState::GetName(){
	return this->name;
}

void ppState::SetName(const char* name){
	this->name = name;
}

ppGame* ppState::GetGame(){
	return this->game;
}

void ppState::SetGame(ppGame* game){
	this->game = game;
}

void ppState::OnRestart(){
	// Pure virtual
	// Will run when game require to restart
}

void ppState::OnRestore(){
	// Pure virtual
	// Will run after game has been restarted
}

bool ppState::OnEvent(SDL_Event* event){
	// Pure virtual
	// Will run on important event only
	return false;
}

ppState::~ppState(){
	// Pure virtual
	// Will run on destroy only
}