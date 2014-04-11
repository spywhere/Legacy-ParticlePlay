#include "GUI.h"

#include <iostream>

bool ppGUI::ppControlOrdering(ppControl* a, ppControl* b){
	return a->GetZ()<b->GetZ();
}

ppGUI::ppGUI(){
	this->defaultFont = NULL;
	if(!IMG_Load("monaco12.png")){
		std::cout << "Default GUI font is not found" << std::endl;
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Warning!", "Default GUI font is not found.", 0);
	}else{
		this->defaultFont = new ppBitmapFont(IMG_Load("monaco12.png"));
	}
}

void ppGUI::AddControl(ppControl* control){
	control->SetGUI(this);
	this->controls.push_back(control);
}

ppBitmapFont* ppGUI::GetDefaultFont(){
	return this->defaultFont;
}

ppControl* ppGUI::GetControl(const char* name){
	if(this->controls.empty()){
		return NULL;
	}
	for(auto control : this->controls){
		if(control->GetName()==std::string(name)){
			return control;
		}
	}
	return NULL;
}

void ppGUI::RemoveControl(const char* name){
	if(this->controls.empty()){
		return;
	}
	int i=0;
	for(auto control : this->controls){
		if(control->GetName()==std::string(name)){
			this->controls.erase(this->controls.begin()+i);
			return;
		}
		i++;
	}
}

void ppGUI::ClearControl(){
	this->controls.clear();
}

void ppGUI::Render(SDL_Renderer* renderer){
	std::sort(this->controls.begin(), this->controls.end(), ppGUI::ppControlOrdering);
	for(auto control : this->controls){
		control->Render(renderer);
	}
}

void ppGUI::Update(ppInput* input){
	std::sort(this->controls.begin(), this->controls.end(), ppGUI::ppControlOrdering);
	for(auto control : this->controls){
		control->Update(input);
	}
}