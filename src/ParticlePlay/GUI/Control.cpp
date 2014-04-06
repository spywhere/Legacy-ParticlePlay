#include "Control.h"

ppControl::ppControl(){
	this->parent = NULL;
	this->x = 0;
	this->y = 0;
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

void ppControl::Render(SDL_Renderer* renderer){

}

void ppControl::Update(ppInput* input){

}
