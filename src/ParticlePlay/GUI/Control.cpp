#include "Control.hpp"

ppControl::ppControl(const char *name, int x, int y, int width, int height){
	this->name = std::string(name);
	this->parent = NULL;
	this->x = x;
	this->y = y;
	this->z = 0;
	this->width = width;
	this->height = height;
	this->visible = true;
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

std::string ppControl::GetName(){
	return this->name;
}

int ppControl::GetX(){
	return this->x;
}

int ppControl::GetY(){
	return this->y;
}

int ppControl::GetZ(){
	return this->z;
}

int ppControl::GetWidth(){
	return this->width;
}

int ppControl::GetHeight(){
	return this->height;
}

void ppControl::SetLocation(int x, int y){
	this->x = x;
	this->y = y;
}

void ppControl::SetSize(int width, int height){
	this->width = width;
	this->height = height;
}

void ppControl::SetName(const char *name){
	this->name = std::string(name);
}

void ppControl::SetX(int x){
	this->x = x;
}

void ppControl::SetY(int y){
	this->y = y;
}

void ppControl::SetZ(int z){
	this->z = z;
}

void ppControl::SetWidth(int width){
	this->width = width;
}

void ppControl::SetHeight(int height){
	this->height = height;
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
