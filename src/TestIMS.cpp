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
		// this->soundFormat = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Music Gameplay/Music_Gameplay.wav", true);
		// this->sound = this->ims->CreateSound("sound", this->soundFormat, 1);
		// this->sound->SetSize(300, 30);
		// this->sound->SetLocation(10, 100);
		// this->gui->AddControl(this->sound);

		this->soundFormat = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Music Gameplay/Music_Gameplay_Drum.wav");
		this->sound = this->ims->CreateSound("sound", this->soundFormat);

		ppFormat *criticalFormat = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Music Gameplay/Music_Gameplay_Critical.wav");
		ppSound *critical = this->ims->CreateSound("critical", criticalFormat);

		ppFormat *melodyFormat = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Music Gameplay/Music_Gameplay_Base.wav");
		ppSound *melody = this->ims->CreateSound("melody", melodyFormat);

		this->segment = this->ims->CreateSegment("Level1");
		this->segment->AddSound(melody);
		critical->SetOffset(criticalFormat->TimeToPosition(5));
		this->segment->AddSound(critical);
		this->segment->AddSound(sound);
		this->segment->SetLoop(-1);
		this->segment->SetSize(300, 30);
		this->segment->SetLocation(10, 100);
		this->gui->AddControl(this->segment);
	}
	if(this->segment){
		ppLabel* label = (ppLabel*)this->gui->GetControl("text");
		std::stringstream msg;
		// msg << this->soundFormat->GetFileName() << " Track " << this->sound->GetTrack() << "/" << this->soundFormat->GetTotalTrack() << " " << " " << this->sound->GetCurrentTime() << "/" << this->sound->GetTotalTime();
		msg << this->segment->GetCurrentTime() << "/" << this->segment->GetTotalTime();
		label->SetText(msg.str());
		if(this->segment->IsStop()&&!this->played){
			// if(!this->played){
			// 	this->sound->Seek(60.0f);
			// }
			// this->sound->SetSpeed(1.5f);
			// this->sound->SetTrack(3);
			// this->sound->SetPlayOrder(ppSoundPlayOrder::SHUFFLE);
			// this->sound->SetLoop(-1);
			// this->sound->Play();
			this->segment->Play();
			this->played = true;
		}
	}
	this->gui->Update(input);
}
