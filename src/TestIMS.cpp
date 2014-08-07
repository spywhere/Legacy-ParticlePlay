#include "TestIMS.hpp"

#include <iostream>
#include <cmath>
#include <sstream>

void TestIMS::OnInit(){
	this->gui = new ppGUI();
	this->gui->AddControl(new ppLabel("text", 10, 50));
	this->played = false;
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
	this->ims = this->GetGame()->GetInteractiveMusicSystem();
	if(this->ims && !this->sound){
		this->soundFormat = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/FalkDemo.wav", true);
		this->sound = this->ims->NewSound("sound", this->soundFormat, 1);
		this->sound->SetSize(300, 30);
		this->sound->SetLocation(10, 100);
		this->gui->AddControl(this->sound);
	}
	if(this->sound){
		ppLabel* label = (ppLabel*)this->gui->GetControl("text");
		std::stringstream msg;
		msg << this->soundFormat->GetFileName() << " Track " << this->sound->GetTrack() << "/" << this->soundFormat->GetTotalTrack() << " " << " " << this->sound->GetCurrentTime() << "/" << this->sound->GetTotalTime();
		label->SetText(msg.str());
		if(this->sound->IsStop()){
			if(!this->played){
				this->sound->Seek(218.0f);
			}
			// this->sound->SetSpeed(1.5f);
			this->sound->Play();
			this->sound->SetLoop(true);
			this->played = true;
		}
	}
	this->gui->Update(input);
}
