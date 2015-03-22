#include "KameleonState.hpp"

#include <iostream>
#include <sstream>

void KameleonState::OnInit(){
	this->gui = new ppGUI();
}

void KameleonState::OnRender(SDL_Renderer* renderer, int delta){
	std::stringstream ss;
	ss << "FPS: " << this->GetGame()->GetFPS() << " [" << this->GetGame()->GetAvgRenderTime() << "ms]\n";
	ss << "UPS: " << this->GetGame()->GetUPS() << " [" << this->GetGame()->GetAvgUpdateTime() << "ms]\n";
	if(this->gui->GetDefaultFont()){
		glColor3f(1 ,1 ,1);
		this->gui->GetDefaultFont()->Render(10, 10, ss.str().c_str(), renderer);
	}
	this->gui->Render(renderer);
}

void KameleonState::OnUpdate(ppInput* input, int delta){


	this->ims = this->GetGame()->GetInteractiveMusicSystem();
	if(this->ims){
		if(this->ims->GetSwitch("level")){

		}else{
			///////////////////
			// Sound Effects //
			///////////////////
			this->ims->CreateSound("bee", this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Kameleon/SFX/bee.wav"))->SetLoop(-1);
			this->ims->CreateSound("heal", this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Kameleon/SFX/heal.wav"))->SetLoop(-1);
			this->ims->CreateSound("jump", this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Kameleon/SFX/jump.wav"));
			this->ims->CreateSound("ouch", this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Kameleon/SFX/ouch.wav"));
			this->ims->CreateSound("splash", this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Kameleon/SFX/splash.wav"));

			//////////////////
			// Bridge Track //
			//////////////////
			ppFormat* b1f = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Kameleon/Music/l4_s3-01.wav");
			ppSound* b1s = this->ims->CreateSound("bridge_sound1", b1f);
			ppSegment* b1seg = this->ims->CreateSegment("bridge_seg1");
			b1seg->AddSound(b1s);
			// b1seg->SetEntryCue(b1f->TimeToPosition(0.0f));
			// b1seg->SetExitCue(b1f->TimeToPosition(0.0f));
			ppFormat* b2f = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Kameleon/Music/l4_s3-02.wav");
			ppSound* b2s = this->ims->CreateSound("bridge_sound2", b2f);
			ppSegment* b2seg = this->ims->CreateSegment("bridge_seg2");
			b2seg->AddSound(b2s);
			// b2seg->SetEntryCue(b2f->TimeToPosition(0.0f));
			// b2seg->SetExitCue(b2f->TimeToPosition(0.0f));
			ppFormat* b3f = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Kameleon/Music/l4_s3-03.wav");
			ppSound* b3s = this->ims->CreateSound("bridge_sound3", b3f);
			ppSegment* b3seg = this->ims->CreateSegment("bridge_seg3");
			b3seg->AddSound(b3s);
			// b3seg->SetEntryCue(b3f->TimeToPosition(0.0f));
			// b3seg->SetExitCue(b3f->TimeToPosition(0.0f));
			ppFormat* b4f = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Kameleon/Music/l4_s3-04.wav");
			ppSound* b4s = this->ims->CreateSound("bridge_sound4", b4f);
			ppSegment* b4seg = this->ims->CreateSegment("bridge_seg4");
			b4seg->AddSound(b4s);
			// b4seg->SetEntryCue(b4f->TimeToPosition(0.0f));
			// b4seg->SetExitCue(b4f->TimeToPosition(0.0f));
			ppFormat* b5f = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Kameleon/Music/l4_s3-05.wav");
			ppSound* b5s = this->ims->CreateSound("bridge_sound5", b5f);
			ppSegment* b5seg = this->ims->CreateSegment("bridge_seg5");
			b5seg->AddSound(b5s);
			// b5seg->SetEntryCue(b5f->TimeToPosition(0.0f));
			// b5seg->SetExitCue(b5f->TimeToPosition(0.0f));
			ppFormat* b6f = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Kameleon/Music/l4_s3-06.wav");
			ppSound* b6s = this->ims->CreateSound("bridge_sound6", b6f);
			ppSegment* b6seg = this->ims->CreateSegment("bridge_seg6");
			b6seg->AddSound(b6s);
			// b6seg->SetEntryCue(b6f->TimeToPosition(0.0f));
			// b6seg->SetExitCue(b6f->TimeToPosition(0.0f));
			ppFormat* b7f = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Kameleon/Music/l4_s3-07.wav");
			ppSound* b7s = this->ims->CreateSound("bridge_sound7", b7f);
			ppSegment* b7seg = this->ims->CreateSegment("bridge_seg7");
			b7seg->AddSound(b7s);
			// b7seg->SetEntryCue(b7f->TimeToPosition(0.0f));
			// b7seg->SetExitCue(b7f->TimeToPosition(0.0f));
			ppFormat* b8f = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Kameleon/Music/l4_s3-08.wav");
			ppSound* b8s = this->ims->CreateSound("bridge_sound8", b8f);
			ppSegment* b8seg = this->ims->CreateSegment("bridge_seg8");
			b8seg->AddSound(b8s);
			// b8seg->SetEntryCue(b8f->TimeToPosition(0.0f));
			// b8seg->SetExitCue(b8f->TimeToPosition(0.0f));
			ppFormat* b9f = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Kameleon/Music/l4_s3-09.wav");
			ppSound* b9s = this->ims->CreateSound("bridge_sound9", b9f);
			ppSegment* b9seg = this->ims->CreateSegment("bridge_seg9");
			b9seg->AddSound(b9s);
			// b9seg->SetEntryCue(b9f->TimeToPosition(0.0f));
			// b9seg->SetExitCue(b9f->TimeToPosition(0.0f));
			ppFormat* b10f = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Kameleon/Music/l4_s3-10.wav");
			ppSound* b10s = this->ims->CreateSound("bridge_sound10", b10f);
			ppSegment* b10seg = this->ims->CreateSegment("bridge_seg10");
			b10seg->AddSound(b10s);
			// b10seg->SetEntryCue(b10f->TimeToPosition(0.0f));
			// b10seg->SetExitCue(b10f->TimeToPosition(0.0f));
			ppFormat* b11f = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Kameleon/Music/l4_s3-11.wav");
			ppSound* b11s = this->ims->CreateSound("bridge_sound11", b11f);
			ppSegment* b11seg = this->ims->CreateSegment("bridge_seg11");
			b11seg->AddSound(b11s);
			// b11seg->SetEntryCue(b11f->TimeToPosition(0.0f));
			// b11seg->SetExitCue(b11f->TimeToPosition(0.0f));
			ppFormat* b12f = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Kameleon/Music/l4_s3-12.wav");
			ppSound* b12s = this->ims->CreateSound("bridge_sound12", b12f);
			ppSegment* b12seg = this->ims->CreateSegment("bridge_seg12");
			b12seg->AddSound(b12s);
			// b12seg->SetEntryCue(b12f->TimeToPosition(0.0f));
			// b12seg->SetExitCue(b12f->TimeToPosition(0.0f));

			ppPlaylist* bridgePlaylist = this->ims->CreatePlaylist("bridge");
			bridgePlaylist->AddSound(b1seg);
			bridgePlaylist->AddSound(b2seg);
			bridgePlaylist->AddSound(b3seg);
			bridgePlaylist->AddSound(b4seg);
			bridgePlaylist->AddSound(b5seg);
			bridgePlaylist->AddSound(b6seg);
			bridgePlaylist->AddSound(b7seg);
			bridgePlaylist->AddSound(b8seg);
			bridgePlaylist->AddSound(b9seg);
			bridgePlaylist->AddSound(b10seg);
			bridgePlaylist->AddSound(b11seg);
			bridgePlaylist->AddSound(b12seg);

			/////////////////////////////
			// Bridge->Main Transition //
			/////////////////////////////
			ppFormat* b2m_f = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Kameleon/Music/l4_s3--l4_a2.wav");
			ppSound* b2m_s = this->ims->CreateSound("bridge2main_sound", b2m_f);
			ppSegment* b2m_seg = this->ims->CreateSegment("bridge2main_seg");
			b2m_seg->AddSound(b2m_s);
			// b2m_seg->SetExitCue();

			////////////////////////////////
			// Main Track Sounds (normal) //
			////////////////////////////////
			ppFormat* mn1f = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Kameleon/Music/l4_a2-01.wav");
			ppSound* mn1s = this->ims->CreateSound("main_normal_sound1", mn1f);

			ppFormat* mn2f = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Kameleon/Music/l4_a2-02.wav");
			ppSound* mn2s = this->ims->CreateSound("main_normal_sound2", mn2f);

			ppFormat* mn3f = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Kameleon/Music/l4_a2-03.wav");
			ppSound* mn3s = this->ims->CreateSound("main_normal_sound3", mn3f);

			ppFormat* mn4f = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Kameleon/Music/l4_a2-04.wav");
			ppSound* mn4s = this->ims->CreateSound("main_normal_sound4", mn4f);

			ppFormat* mn5f = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Kameleon/Music/l4_a2-05.wav");
			ppSound* mn5s = this->ims->CreateSound("main_normal_sound5", mn5f);

			ppFormat* mn6f = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Kameleon/Music/l4_a2-06.wav");
			ppSound* mn6s = this->ims->CreateSound("main_normal_sound6", mn6f);

			ppFormat* mn7f = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Kameleon/Music/l4_a2-07.wav");
			ppSound* mn7s = this->ims->CreateSound("main_normal_sound7", mn7f);

			ppFormat* mn8f = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Kameleon/Music/l4_a2-08.wav");
			ppSound* mn8s = this->ims->CreateSound("main_normal_sound8", mn8f);

			ppFormat* mn9f = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Kameleon/Music/l4_a2-09.wav");
			ppSound* mn9s = this->ims->CreateSound("main_normal_sound9", mn9f);

			ppFormat* mn10f = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Kameleon/Music/l4_a2-10.wav");
			ppSound* mn10s = this->ims->CreateSound("main_normal_sound10", mn10f);

			ppFormat* mn11f = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Kameleon/Music/l4_a2-11.wav");
			ppSound* mn11s = this->ims->CreateSound("main_normal_sound11", mn11f);

			ppFormat* mn12f = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Kameleon/Music/l4_a2-12.wav");
			ppSound* mn12s = this->ims->CreateSound("main_normal_sound12", mn12f);

			ppFormat* mn13f = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Kameleon/Music/l4_a2-13.wav");
			ppSound* mn13s = this->ims->CreateSound("main_normal_sound13", mn13f);

			////////////////////////////////////
			// Main Track Sounds (low health) //
			////////////////////////////////////
			ppFormat* ml1f = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Kameleon/Music/l4_a4-01.wav");
			ppSound* ml1s = this->ims->CreateSound("main_low_sound1", ml1f);

			ppFormat* ml2f = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Kameleon/Music/l4_a4-02.wav");
			ppSound* ml2s = this->ims->CreateSound("main_low_sound2", ml2f);

			ppFormat* ml3f = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Kameleon/Music/l4_a4-03.wav");
			ppSound* ml3s = this->ims->CreateSound("main_low_sound3", ml3f);

			ppFormat* ml4f = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Kameleon/Music/l4_a4-04.wav");
			ppSound* ml4s = this->ims->CreateSound("main_low_sound4", ml4f);

			ppFormat* ml5f = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Kameleon/Music/l4_a4-05.wav");
			ppSound* ml5s = this->ims->CreateSound("main_low_sound5", ml5f);

			ppFormat* ml6f = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Kameleon/Music/l4_a4-06.wav");
			ppSound* ml6s = this->ims->CreateSound("main_low_sound6", ml6f);

			ppFormat* ml7f = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Kameleon/Music/l4_a4-07.wav");
			ppSound* ml7s = this->ims->CreateSound("main_low_sound7", ml7f);

			ppFormat* ml8f = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Kameleon/Music/l4_a4-08.wav");
			ppSound* ml8s = this->ims->CreateSound("main_low_sound8", ml8f);

			ppFormat* ml9f = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Kameleon/Music/l4_a4-09.wav");
			ppSound* ml9s = this->ims->CreateSound("main_low_sound9", ml9f);

			ppFormat* ml10f = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Kameleon/Music/l4_a4-10.wav");
			ppSound* ml10s = this->ims->CreateSound("main_low_sound10", ml10f);

			ppFormat* ml11f = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Kameleon/Music/l4_a4-11.wav");
			ppSound* ml11s = this->ims->CreateSound("main_low_sound11", ml11f);

			ppFormat* ml12f = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Kameleon/Music/l4_a4-12.wav");
			ppSound* ml12s = this->ims->CreateSound("main_low_sound12", ml12f);

			ppFormat* ml13f = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Kameleon/Music/l4_a4-13.wav");
			ppSound* ml13s = this->ims->CreateSound("main_low_sound13", ml13f);

			////////////////
			// Main Track //
			////////////////
			ppSegment* m1s = this->ims->CreateSegment("main_seg1");
			m1s->AddSound(mn1s);
			m1s->AddSound(ml1s);
			// ppFormat* m1f = m1s->GetAudioFormat();
			// m1s->SetEntryCue(m1f->TimeToPosition(0.0f));
			// m1s->SetExitCue(m1f->TimeToPosition(0.0f));
			ppSegment* m2s = this->ims->CreateSegment("main_seg2");
			m2s->AddSound(mn2s);
			m2s->AddSound(ml2s);
			// ppFormat* m2f = m2s->GetAudioFormat();
			// m2s->SetEntryCue(m2f->TimeToPosition(0.0f));
			// m2s->SetExitCue(m2f->TimeToPosition(0.0f));
			ppSegment* m3s = this->ims->CreateSegment("main_seg3");
			m3s->AddSound(mn3s);
			m3s->AddSound(ml3s);
			// ppFormat* m3f = m3s->GetAudioFormat();
			// m3s->SetEntryCue(m3f->TimeToPosition(0.0f));
			// m3s->SetExitCue(m3f->TimeToPosition(0.0f));
			ppSegment* m4s = this->ims->CreateSegment("main_seg4");
			m4s->AddSound(mn4s);
			m4s->AddSound(ml4s);
			// ppFormat* m4f = m4s->GetAudioFormat();
			// m4s->SetEntryCue(m4f->TimeToPosition(0.0f));
			// m4s->SetExitCue(m4f->TimeToPosition(0.0f));
			ppSegment* m5s = this->ims->CreateSegment("main_seg5");
			m5s->AddSound(mn5s);
			m5s->AddSound(ml5s);
			// ppFormat* m5f = m5s->GetAudioFormat();
			// m5s->SetEntryCue(m5f->TimeToPosition(0.0f));
			// m5s->SetExitCue(m5f->TimeToPosition(0.0f));
			ppSegment* m6s = this->ims->CreateSegment("main_seg6");
			m6s->AddSound(mn6s);
			m6s->AddSound(ml6s);
			// ppFormat* m6f = m6s->GetAudioFormat();
			// m6s->SetEntryCue(m6f->TimeToPosition(0.0f));
			// m6s->SetExitCue(m6f->TimeToPosition(0.0f));
			ppSegment* m7s = this->ims->CreateSegment("main_seg7");
			m7s->AddSound(mn7s);
			m7s->AddSound(ml7s);
			// ppFormat* m7f = m7s->GetAudioFormat();
			// m7s->SetEntryCue(m7f->TimeToPosition(0.0f));
			// m7s->SetExitCue(m7f->TimeToPosition(0.0f));
			ppSegment* m8s = this->ims->CreateSegment("main_seg8");
			m8s->AddSound(mn8s);
			m8s->AddSound(ml8s);
			// ppFormat* m8f = m8s->GetAudioFormat();
			// m8s->SetEntryCue(m8f->TimeToPosition(0.0f));
			// m8s->SetExitCue(m8f->TimeToPosition(0.0f));
			ppSegment* m9s = this->ims->CreateSegment("main_seg9");
			m9s->AddSound(mn9s);
			m9s->AddSound(ml9s);
			// ppFormat* m9f = m9s->GetAudioFormat();
			// m9s->SetEntryCue(m9f->TimeToPosition(0.0f));
			// m9s->SetExitCue(m9f->TimeToPosition(0.0f));
			ppSegment* m10s = this->ims->CreateSegment("main_seg10");
			m10s->AddSound(mn10s);
			m10s->AddSound(ml10s);
			// ppFormat* m10f = m10s->GetAudioFormat();
			// m10s->SetEntryCue(m10f->TimeToPosition(0.0f));
			// m10s->SetExitCue(m10f->TimeToPosition(0.0f));
			ppSegment* m11s = this->ims->CreateSegment("main_seg11");
			m11s->AddSound(mn11s);
			m11s->AddSound(ml11s);
			// ppFormat* m11f = m11s->GetAudioFormat();
			// m11s->SetEntryCue(m11f->TimeToPosition(0.0f));
			// m11s->SetExitCue(m11f->TimeToPosition(0.0f));
			ppSegment* m12s = this->ims->CreateSegment("main_seg12");
			m12s->AddSound(mn12s);
			m12s->AddSound(ml12s);
			// ppFormat* m12f = m12s->GetAudioFormat();
			// m12s->SetEntryCue(m12f->TimeToPosition(0.0f));
			// m12s->SetExitCue(m12f->TimeToPosition(0.0f));
			ppSegment* m13s = this->ims->CreateSegment("main_seg13");
			m13s->AddSound(mn13s);
			m13s->AddSound(ml13s);
			// ppFormat* m13f = m13s->GetAudioFormat();
			// m13s->SetEntryCue(m13f->TimeToPosition(0.0f));
			// m13s->SetExitCue(m13f->TimeToPosition(0.0f));

			ppPlaylist* mainPlaylist = this->ims->CreatePlaylist("main");
			mainPlaylist->AddSound(m1s);
			mainPlaylist->AddSound(m2s);
			mainPlaylist->AddSound(m3s);
			mainPlaylist->AddSound(m4s);
			mainPlaylist->AddSound(m5s);
			mainPlaylist->AddSound(m6s);
			mainPlaylist->AddSound(m7s);
			mainPlaylist->AddSound(m8s);
			mainPlaylist->AddSound(m9s);
			mainPlaylist->AddSound(m10s);
			mainPlaylist->AddSound(m11s);
			mainPlaylist->AddSound(m12s);
			mainPlaylist->AddSound(m13s);

			//////////////////////////
			// Main->End Transition //
			//////////////////////////
			ppFormat* m2e_f = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Kameleon/Music/l4_a2--l4_am1.wav");
			ppSound* m2e_s = this->ims->CreateSound("main2end_sound", m2e_f);
			ppSegment* m2e_seg = this->ims->CreateSegment("main2end_seg");
			m2e_seg->AddSound(m2e_s);
			// m2e_seg->SetExitCue();

			////////////////////
			// Heroic Stinger //
			////////////////////
			ppFormat* h1f = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Kameleon/Music/l4_a3-14.wav");
			ppSound* h1s = this->ims->CreateSound("heroic_sound1", h1f);
			ppSegment* h1seg = this->ims->CreateSegment("heroic_seg1");
			h1seg->AddSound(h1s);
			// h1seg->SetEntryCue(h1f->TimeToPosition(0.0f));
			// h1seg->SetExitCue(h1f->TimeToPosition(0.0f));
			ppFormat* h2f = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Kameleon/Music/l4_a3-15.wav");
			ppSound* h2s = this->ims->CreateSound("heroic_sound2", h2f);
			ppSegment* h2seg = this->ims->CreateSegment("heroic_seg2");
			h2seg->AddSound(h2s);
			// h2seg->SetEntryCue(h2f->TimeToPosition(0.0f));
			// h2seg->SetExitCue(h2f->TimeToPosition(0.0f));
			ppFormat* h3f = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Kameleon/Music/l4_a3-16.wav");
			ppSound* h3s = this->ims->CreateSound("heroic_sound3", h3f);
			ppSegment* h3seg = this->ims->CreateSegment("heroic_seg3");
			h3seg->AddSound(h3s);
			// h3seg->SetEntryCue(h3f->TimeToPosition(0.0f));
			// h3seg->SetExitCue(h3f->TimeToPosition(0.0f));
			ppFormat* h4f = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Kameleon/Music/l4_a3-17.wav");
			ppSound* h4s = this->ims->CreateSound("heroic_sound4", h4f);
			ppSegment* h4seg = this->ims->CreateSegment("heroic_seg4");
			h4seg->AddSound(h4s);
			// h4seg->SetEntryCue(h4f->TimeToPosition(0.0f));
			// h4seg->SetExitCue(h4f->TimeToPosition(0.0f));

			ppPlaylist* heroicPlaylist = this->ims->CreatePlaylist("heroic");
			heroicPlaylist->AddSound(h1seg);
			heroicPlaylist->AddSound(h2seg);
			heroicPlaylist->AddSound(h3seg);
			heroicPlaylist->AddSound(h4seg);

			////////////////////
			// ppSwitch* sw =
			this->ims->CreateSwitch("level");
		}
	}

	if(input->IsKeyDown(SDL_SCANCODE_R)){
		this->ims->ClearSound();
		this->ims->ClearSwitch();
		this->GetGame()->EnterState("ims");
	}
}
