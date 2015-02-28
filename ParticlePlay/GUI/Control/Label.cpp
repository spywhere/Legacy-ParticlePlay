#include "Label.hpp"

ppLabel::ppLabel(const char *name, int x, int y) : ppControl(name, x, y){
	this->text = "Label";
}

std::string ppLabel::GetText(){
	return this->text;
}

void ppLabel::SetText(std::string text){
	this->text = text;
}

void ppLabel::Render(SDL_Renderer* renderer){
	ppControl::Render(renderer);
	if(!this->visible){
		return;
	}
	if(this->GetGUI()->GetDefaultFont()){
		this->GetGUI()->GetDefaultFont()->Render(this->GetX(), this->GetY(), this->text.c_str(), renderer);
	}
}

ppControlType ppLabel::GetType(){
	return ppControlType::LABEL;
}
