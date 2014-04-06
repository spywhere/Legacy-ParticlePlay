#include "GUI.h"

#include <iostream>

ppGUI::ppGUI(){
	this->defaultFont = NULL;
	if(!IMG_Load("monaco12.png")){
		std::cout << "Default GUI font is not found" << std::endl;
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Warning!", "Default GUI font is not found.", 0);
	}else{
		this->defaultFont = new ppBitmapFont(IMG_Load("monaco12.png"));
	}
}

void ppGUI::AddControl(const char *name, ppControl* control){
	if(!this->GetDefaultFont()){
		return;
	}
	control->SetGUI(this);
	this->controls.insert(std::pair<const char*, ppControl*>(name, control));
}

ppBitmapFont* ppGUI::GetDefaultFont(){
	return this->defaultFont;
}

ppControl* ppGUI::GetControl(const char* name){
	if(!this->GetDefaultFont() || this->controls.empty()){
		return NULL;
	}
	std::map<const char*, ppControl*>::iterator it;
	it = this->controls.find(name);
	if(it != this->controls.end()){
		return it->second;
	}
	return NULL;
}

void ppGUI::RemoveControl(const char* name){
	if(!this->GetDefaultFont() || this->controls.empty()){
		return;
	}
	std::map<const char*, ppControl*>::iterator it;
	it = this->controls.find(name);
	if(it != this->controls.end()){
		this->controls.erase(it);
	}
}

void ppGUI::ClearControl(){
	if(!this->GetDefaultFont()){
		return;
	}
	this->controls.clear();
}

void ppGUI::Render(SDL_Renderer* renderer){
	if(!this->GetDefaultFont()){
		return;
	}
	std::map<const char*, ppControl*>::iterator it = this->controls.begin();
	while(it!=this->controls.end()){
		it->second->Render(renderer);
		it++;
	}
}

void ppGUI::Update(ppInput* input){
	if(!this->GetDefaultFont()){
		return;
	}
	std::map<const char*, ppControl*>::iterator it = this->controls.begin();
	while(it!=this->controls.end()){
		it->second->Update(input);
		it++;
	}
}