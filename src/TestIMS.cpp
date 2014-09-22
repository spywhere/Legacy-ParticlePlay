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
	ppPlaylist* l4a1 = NULL;
	if(this->ims && !this->sound){
		ppFormat* seg1format = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/kameleon/l4_a1-01.wav");
		ppFormat* seg2format = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/kameleon/l4_a1-02.wav");
		ppFormat* seg3format = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/kameleon/l4_a1-03.wav");
		ppFormat* seg4format = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/kameleon/l4_a1-04.wav");
		ppFormat* seg5format = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/kameleon/l4_a1-05.wav");
		ppFormat* seg6format = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/kameleon/l4_a1-06.wav");
		ppFormat* seg7format = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/kameleon/l4_a1-07.wav");
		ppFormat* seg8format = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/kameleon/l4_a1-08.wav");
		ppFormat* seg9format = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/kameleon/l4_a1-09.wav");
		ppFormat* seg10format = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/kameleon/l4_a1-10.wav");
		ppFormat* seg11format = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/kameleon/l4_a1-11.wav");
		ppFormat* seg12format = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/kameleon/l4_a1-12.wav");

		ppSound* seg1sound = this->ims->CreateSound("seg1sound", seg1format);
		this->sound = seg1sound;
		ppSound* seg2sound = this->ims->CreateSound("seg2sound", seg2format);
		ppSound* seg3sound = this->ims->CreateSound("seg3sound", seg3format);
		ppSound* seg4sound = this->ims->CreateSound("seg4sound", seg4format);
		ppSound* seg5sound = this->ims->CreateSound("seg5sound", seg5format);
		ppSound* seg6sound = this->ims->CreateSound("seg6sound", seg6format);
		ppSound* seg7sound = this->ims->CreateSound("seg7sound", seg7format);
		ppSound* seg8sound = this->ims->CreateSound("seg8sound", seg8format);
		ppSound* seg9sound = this->ims->CreateSound("seg9sound", seg9format);
		ppSound* seg10sound = this->ims->CreateSound("seg10sound", seg10format);
		ppSound* seg11sound = this->ims->CreateSound("seg11sound", seg11format);
		ppSound* seg12sound = this->ims->CreateSound("seg12sound", seg12format);

		ppSegment* seg1 = this->ims->CreateSegment("seg1");
		seg1->SetEntryCue(seg1format->TimeToPosition(1.5f));
		seg1->SetExitCue(seg1format->TimeToPosition(4.5f));
		ppSegment* seg2 = this->ims->CreateSegment("seg2");
		seg2->SetEntryCue(seg1format->TimeToPosition(1.125f));
		seg2->SetExitCue(seg1format->TimeToPosition(4.5f));
		ppSegment* seg3 = this->ims->CreateSegment("seg3");
		seg3->SetEntryCue(seg1format->TimeToPosition(1.5f));
		seg3->SetExitCue(seg1format->TimeToPosition(4.5f));
		ppSegment* seg4 = this->ims->CreateSegment("seg4");
		seg4->SetEntryCue(seg1format->TimeToPosition(1.125f));
		seg4->SetExitCue(seg1format->TimeToPosition(4.5f));
		ppSegment* seg5 = this->ims->CreateSegment("seg5");
		seg5->SetEntryCue(seg1format->TimeToPosition(1.5f));
		seg5->SetExitCue(seg1format->TimeToPosition(4.5f));
		ppSegment* seg6 = this->ims->CreateSegment("seg6");
		seg6->SetEntryCue(seg1format->TimeToPosition(1.125f));
		seg6->SetExitCue(seg1format->TimeToPosition(4.5f));
		ppSegment* seg7 = this->ims->CreateSegment("seg7");
		seg7->SetEntryCue(seg1format->TimeToPosition(1.125f));
		seg7->SetExitCue(seg1format->TimeToPosition(4.5f));
		ppSegment* seg8 = this->ims->CreateSegment("seg8");
		seg8->SetEntryCue(seg1format->TimeToPosition(1.125f));
		seg8->SetExitCue(seg1format->TimeToPosition(4.5f));
		ppSegment* seg9 = this->ims->CreateSegment("seg9");
		seg9->SetEntryCue(seg1format->TimeToPosition(1.875f));
		seg9->SetExitCue(seg1format->TimeToPosition(4.5f));
		ppSegment* seg10 = this->ims->CreateSegment("seg10");
		seg10->SetEntryCue(seg1format->TimeToPosition(1.5f));
		seg10->SetExitCue(seg1format->TimeToPosition(4.5f));
		ppSegment* seg11 = this->ims->CreateSegment("seg11");
		seg11->SetEntryCue(seg1format->TimeToPosition(1.125f));
		seg11->SetExitCue(seg1format->TimeToPosition(5.625f));
		ppSegment* seg12 = this->ims->CreateSegment("seg12");
		seg12->SetEntryCue(seg1format->TimeToPosition(2.625f));
		seg12->SetExitCue(seg1format->TimeToPosition(4.5f));

		seg1->AddSound(seg1sound);
		seg2->AddSound(seg2sound);
		seg3->AddSound(seg3sound);
		seg4->AddSound(seg4sound);
		seg5->AddSound(seg5sound);
		seg6->AddSound(seg6sound);
		seg7->AddSound(seg7sound);
		seg8->AddSound(seg8sound);
		seg9->AddSound(seg9sound);
		seg10->AddSound(seg10sound);
		seg11->AddSound(seg11sound);
		seg12->AddSound(seg12sound);

		l4a1 = this->ims->CreatePlaylist("l4a1");
		l4a1->AddSound(seg1);
		l4a1->AddSound(seg2);
		l4a1->AddSound(seg3);
		l4a1->AddSound(seg4);
		l4a1->AddSound(seg5);
		l4a1->AddSound(seg6);
		l4a1->AddSound(seg7);
		l4a1->AddSound(seg8);
		l4a1->AddSound(seg9);
		l4a1->AddSound(seg10);
		l4a1->AddSound(seg11);
		l4a1->AddSound(seg12);

		l4a1->SetSize(300, 250);
		l4a1->SetLocation(10, 100);
		this->gui->AddControl(l4a1);


		// this->soundFormat = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/MusicGameplay/Music_Gameplay.wav");
		// this->sound = this->ims->CreateSound("sound", this->soundFormat, 1);
		// this->sound->SetSize(300, 30);
		// this->sound->SetLocation(10, 100);
		// this->gui->AddControl(this->sound);

		// this->soundFormat = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/MusicGameplay/Music_Gameplay_Drum.wav");
		// this->sound = this->ims->CreateSound("sound", this->soundFormat);

		// ppFormat *criticalFormat = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/MusicGameplay/Music_Gameplay_Critical.wav");
		// ppSound *critical = this->ims->CreateSound("critical", criticalFormat);

		// ppFormat *melodyFormat = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/MusicGameplay/Music_Gameplay_Base.wav");
		// ppSound *melody = this->ims->CreateSound("melody", melodyFormat);

		// this->segment = this->ims->CreateSegment("Level1");
		// this->segment->AddSound(melody);
		// critical->SetOffset(criticalFormat->TimeToPosition(5));
		// this->segment->AddSound(critical);
		// this->segment->AddSound(sound);
		// this->segment->SetLoop(-1);
		// this->segment->SetSize(300, 30);
		// this->segment->SetLocation(10, 100);
		// this->gui->AddControl(this->segment);
	}
	if(l4a1){
			ppLabel* label = (ppLabel*)this->gui->GetControl("text");
			std::stringstream msg;
			// msg << l4a1->GetCurrentTime() << "/" << l4a1->GetTotalTime();
			label->SetText(msg.str());
			if(!this->played && l4a1->IsStop()){
				l4a1->Play();
				this->played = true;
				// seg1->Play();
				// l4a1->Play();
			}
	}

	// if(this->sound){
	// if(this->segment){
		// ppLabel* label = (ppLabel*)this->gui->GetControl("text");
		// std::stringstream msg;
		// msg << this->soundFormat->GetFileName() << " Track " << this->sound->GetTrack() << "/" << this->soundFormat->GetTotalTrack() << " " << " " << this->sound->GetCurrentTime() << "/" << this->sound->GetTotalTime();
		// msg << this->segment->GetCurrentTime() << "/" << this->segment->GetTotalTime();
		// label->SetText(msg.str());
		// if(this->sound->IsStop()&&!this->played){
		// if(this->segment->IsStop()&&!this->played){
			// if(!this->played){
			// 	this->sound->Seek(60.0f);
			// }
			// this->sound->SetSpeed(1.5f);
			// this->sound->SetTrack(3);
			// this->sound->SetClipStart(this->soundFormat->TimeToPosition(5));
			// this->sound->SetClipEnd(this->soundFormat->TimeToPosition(5));
			// this->sound->SetPlayOrder(ppSoundPlayOrder::SHUFFLE);
			// this->sound->SetLoop(-1);
			// this->sound->Play();
			// this->segment->Play();
			// this->played = true;
		// }
	// }
	this->gui->Update(input);
}
