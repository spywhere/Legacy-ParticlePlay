#include "Button.hpp"

#include <iostream>

ppButton::ppButton(const char *name, int x, int y, int w, int h) : ppControl(name, x, y, w, h){
	this->text = "Button";
	this->listener = NULL;
	this->backgroundColor = 0x888888;
	this->highlightColor = 0xaaaaaa;
	this->foregroundColor = 0xffffff;
	this->highlight = false;
}

std::string ppButton::GetText(){
	return this->text;
}

bool ppButton::IsHighlight(){
	return this->highlight;
}

void ppButton::SetText(std::string text){
	this->text = text;
}

void ppButton::SetListener(ppButtonListener* listener){
	this->listener = listener;
}

void ppButton::SetBackgroundColor(int color){
	this->backgroundColor = color;
}

void ppButton::SetHighlightColor(int color){
	this->highlightColor = color;
}

void ppButton::SetForegroundColor(int color){
	this->foregroundColor = color;
}

void ppButton::Render(ppGraphics* graphics){
	ppControl::Render(graphics);
	if(!this->visible){
		return;
	}
	if(this->highlight){
		graphics->SetColor(new ppColor((this->highlightColor >> 16 & 0xff) / 255.0f, (this->highlightColor >> 8 & 0xff) / 255.0f, (this->highlightColor & 0xff) / 255.0f));
	}else{
		graphics->SetColor(new ppColor((this->backgroundColor >> 16 & 0xff) / 255.0f, (this->backgroundColor >> 8 & 0xff) / 255.0f, (this->backgroundColor & 0xff) / 255.0f));
	}
	graphics->FillRect(this->GetX(), this->GetY(), this->GetWidth(), this->GetHeight());
	graphics->SetColor(new ppColor((this->foregroundColor >> 16 & 0xff) / 255.0f, (this->foregroundColor >> 8 & 0xff) / 255.0f, (this->foregroundColor & 0xff) / 255.0f));
	if(this->GetGUI()->GetDefaultFont()){
		this->GetGUI()->GetDefaultFont()->Render(this->GetX(), this->GetY(), this->text.c_str(), graphics);
	}
}

void ppButton::Update(ppInput* input){
	ppControl::Update(input);
	if(!this->visible){
		return;
	}
	this->highlight = this->IsInside(input->GetMouseX(), input->GetMouseY());
	if(this->highlight && this->listener){
		this->listener->OnMouseOver(this);
		if(input->IsMouseDown(1, 10)){
			this->listener->OnClick(this);
		}
	}
}

ppControlType ppButton::GetType(){
	return ppControlType::BUTTON;
}
