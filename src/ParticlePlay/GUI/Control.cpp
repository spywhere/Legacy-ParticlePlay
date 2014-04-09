#include "Control.h"

ppControl::ppControl(){
	this->parent = NULL;
	this->x = 0;
	this->y = 0;
	this->visible = true;
	this->gui = NULL;
	// Self-reference
	// ppControl::Control(0, 0);
}

ppControl::ppControl(int x, int y){
	this->parent = NULL;
	this->x = x;
	this->y = y;
	this->gui = NULL;
}

ppGUI* ppControl::GetGUI(){
	return this->gui;
}

void ppControl::SetGUI(ppGUI* gui){
	if(!this->gui){
		this->gui = gui;
	}
}

ppControl* ppControl::GetParent(){
	return this->parent;
}

void ppControl::SetParent(ppControl* parent){
	this->parent = parent;
}

int ppControl::GetX(){
	return this->x;
}

int ppControl::GetY(){
	return this->y;
}

void ppControl::SetX(int x){
	this->x = x;
}

void ppControl::SetY(int y){
	this->y = y;
}

bool ppControl::IsVisible(){
	return this->visible;
}

void ppControl::SetVisible(bool visible){
	this->visible = visible;
}

void ppControl::Render(SDL_Renderer* renderer){
	if(this->parent){
		this->parent->Render(renderer);
	}
	if(!this->visible){
		return;
	}
}

void ppControl::Update(ppInput* input){

}
