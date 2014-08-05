#include "TestIMS.hpp"

#include <iostream>
#include <cmath>
#include <sstream>

void TestIMS::OnInit(){
	this->gui = new ppGUI();
	this->gui->AddControl(new ppLabel("text", 10, 50));
	this->ims = new ppIMS(this->GetGame());
	this->soundFormat = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/FalkDemo.wav", true);
	this->sound = new ppSound("sound", this->soundFormat, 1);
	this->sound->SetSize(300, 30);
	this->sound->SetLocation(10, 100);
	this->gui->AddControl(this->sound);
}

void TestIMS::OnRender(SDL_Renderer* renderer, int delta){
	std::stringstream ss;
	ss << "FPS: " << this->GetGame()->GetFPS() << " [" << this->GetGame()->GetAvgRenderTime() << "ms]\n";
	ss << "UPS: " << this->GetGame()->GetUPS() << " [" << this->GetGame()->GetAvgUpdateTime() << "ms]\n";
	if(this->gui->GetDefaultFont()){
		glColor3f(1 ,1 ,1);
		this->gui->GetDefaultFont()->Render(10, 10, ss.str().c_str(), renderer);
	}
	this->gui->Render(renderer);
}

void TestIMS::OnUpdate(ppInput* input, int delta){
	this->gui->Update(input);
	ppLabel* label = (ppLabel*)this->gui->GetControl("text");
	std::stringstream msg;
	msg << this->soundFormat->GetFileName() << " Track " << this->sound->GetTrack() << "/" << this->soundFormat->GetTotalTrack() << " " << " " << this->sound->GetCurrentTime() << "/" << this->sound->GetTotalTime();
	label->SetText(msg.str());
}
