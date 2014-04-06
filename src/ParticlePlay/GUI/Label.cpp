#include "Label.h"

#include <sstream>
#include "GUIType.h"

ppLabel::ppLabel(){
	this->text = "Label";
}
ppLabel::ppLabel(int x, int y) : ppControl(x, y){
	this->text = "Label";
}

const char* ppLabel::GetText(){
	return this->text;
}

void ppLabel::SetText(const char *text){
	this->text = text;
}

void ppLabel::Render(SDL_Renderer* renderer){
	this->GetGUI()->GetDefaultFont()->Render(this->GetX(), this->GetY(), this->text, renderer);
}

ppGUIType ppLabel::GetType(){
	return GUI_LABEL;
}