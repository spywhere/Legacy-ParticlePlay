#include "KameleonState.hpp"

#include <sstream>

class DebugButtonListener : public ppButtonListener {
	protected:
		KameleonState* state;
	public:
		DebugButtonListener(KameleonState* state) : ppButtonListener(){
			this->state = state;
		};

		void OnClick(ppButton* button){
			ppIMS* ims = this->state->GetGame()->GetInteractiveMusicSystem();
			if(button->GetName() == "debugbtn"){
				this->state->debugView = (this->state->debugView+1)%4;
			}else if(button->GetName() == "bridgebtn"){
				ppGenericSound* sound = ims->GetSound("bridge");
				if(sound->IsPlaying()){
					sound->Stop();
				}else{
					sound->SetVolume(1);
					sound->Play();
				}
			}else if(button->GetName() == "mainnormalbtn"){
				ppGenericSound* sound = ims->GetSound("main_normal");
				if(sound->IsPlaying()){
					sound->Stop();
				}else{
					sound->SetVolume(1);
					sound->Play();
				}
			}else if(button->GetName() == "mainlowbtn"){
				ppGenericSound* sound = ims->GetSound("main_low");
				if(sound->IsPlaying()){
					sound->Stop();
				}else{
					sound->SetVolume(1);
					sound->Play();
				}
			}else if(button->GetName() == "heroicbtn"){
				ppGenericSound* sound = ims->GetSound("heroic");
				if(sound->IsPlaying()){
					sound->Stop();
				}else{
					sound->SetVolume(1);
					sound->Play();
				}
			}else if(button->GetName() == "stopsw"){
				ppSwitch* sw = ims->GetSwitch("level");
				if(sw->GetCurrentState() != ""){
					sw->SwitchState("");
				}
			}else if(button->GetName() == "bridgesw"){
				ppSwitch* sw = ims->GetSwitch("level");
				if(sw->GetCurrentState() != "bridge"){
					sw->SwitchState("bridge");
				}
			}else if(button->GetName() == "mainnormalsw"){
				ppSwitch* sw = ims->GetSwitch("level");
				if(sw->GetCurrentState() != "main_normal"){
					sw->SwitchState("main_normal");
				}
			}else if(button->GetName() == "mainlowsw"){
				ppSwitch* sw = ims->GetSwitch("level");
				if(sw->GetCurrentState() != "main_low"){
					sw->SwitchState("main_low");
				}
			}else if(button->GetName() == "heroicsw"){
				ppSwitch* sw = ims->GetSwitch("level");
				if(sw->GetCurrentState() != ""){
					sw->TriggerStinger("heroic");
				}
			}
		}
};

void KameleonState::OnInit(){
	this->gameStart = false;
	this->gui = new ppGUI();
	this->debugView = 0;
	this->gameState = new GameState(this->GetGame());
	this->gameState->OnInit();
}

void KameleonState::OnRender(SDL_Renderer* renderer, int delta){
	this->gameState->OnRender(renderer, delta);
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
	this->gameState->SetDebugView(this->debugView);
	ppIMS* ims = this->GetGame()->GetInteractiveMusicSystem();
	if(ims){
		if(ims->GetSwitch("level")){
			if(!this->gameStart){
				ims->GetSwitch("level")->SwitchState("bridge");
				this->gameStart = true;
			}
			this->gui->GetControl("bridge")->SetVisible(this->debugView==3);
			ppButton* bridgeButton = (ppButton*)this->gui->GetControl("bridgebtn");
			bridgeButton->SetText((ims->GetSound("bridge")->IsPlaying())?"Stop":"Play");
			bridgeButton->SetVisible(this->debugView==3);
			this->gui->GetControl("main_normal")->SetVisible(this->debugView==3);
			ppButton* mainNormalButton = (ppButton*)this->gui->GetControl("mainnormalbtn");
			mainNormalButton->SetText((ims->GetSound("main_normal")->IsPlaying())?"Stop":"Play");
			mainNormalButton->SetVisible(this->debugView==3);
			this->gui->GetControl("main_low")->SetVisible(this->debugView==3);
			ppButton* mainLowButton = (ppButton*)this->gui->GetControl("mainlowbtn");
			mainLowButton->SetText((ims->GetSound("main_low")->IsPlaying())?"Stop":"Play");
			mainLowButton->SetVisible(this->debugView==3);
			this->gui->GetControl("heroic")->SetVisible(this->debugView==3);
			ppButton* heroicButton = (ppButton*)this->gui->GetControl("heroicbtn");
			heroicButton->SetText((ims->GetSound("heroic")->IsPlaying())?"Stop":"Play");
			heroicButton->SetVisible(this->debugView==3);
			this->gui->GetControl("level")->SetVisible(this->debugView==3);

			this->gui->GetControl("stopsw")->SetVisible(this->debugView==3);
			this->gui->GetControl("bridgesw")->SetVisible(this->debugView==3);
			this->gui->GetControl("mainnormalsw")->SetVisible(this->debugView==3);
			this->gui->GetControl("mainlowsw")->SetVisible(this->debugView==3);
			this->gui->GetControl("heroicsw")->SetVisible(this->debugView==3 && !ims->GetSwitch("level")->IsStingerTrigger("heroic"));
		}else{
			DebugButtonListener* btnListener = new DebugButtonListener(this);
			/////////////////////
			// Filter and RTPC //
			/////////////////////
			ppRTPC* water_rtpc = ims->CreateRTPC("water_rtpc");
			ppFilter* water_filter = ims->CreateFilter("water_filter", ppFilterType::LOW_PASS);
			water_filter->AddRTPC(water_rtpc, ppRTPCEffect::GAINHF, new ppLinearEasing(1, -1));

			///////////////////
			// Sound Effects //
			///////////////////
			ims->CreateSound("bee", ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Kameleon/SFX/bee.wav"))->SetLoop(-1);
			ppGenericSound* heal_sound = ims->CreateSound("heal", ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Kameleon/SFX/heal.wav"));
			heal_sound->SetLoop(-1);
			heal_sound->AddRTPC(water_rtpc, ppRTPCEffect::GAIN, new ppLinearEasing());
			ims->CreateSound("jump", ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Kameleon/SFX/jump.wav"));
			ims->CreateSound("ouch", ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Kameleon/SFX/ouch.wav"));
			ims->CreateSound("out_water", ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Kameleon/SFX/out_water.wav"));
			ims->CreateSound("splash", ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Kameleon/SFX/splash.wav"));
			ims->CreateSound("thub", ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Kameleon/SFX/thub.wav"));

			//////////////////
			// Bridge Track //
			//////////////////
			ppFormat* b1f = ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Kameleon/Music/l4_s3-01.wav");
			ppSound* b1s = ims->CreateSound("bridge_sound1", b1f);
			ppSegment* b1seg = ims->CreateSegment("bridge_seg1");
			b1seg->AddSound(b1s);
			b1seg->SetEntryCue(b1f->TimeToPosition(1.125f));
			b1seg->SetExitCue(b1f->TimeToPosition(2.25f));
			ppFormat* b2f = ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Kameleon/Music/l4_s3-02.wav");
			ppSound* b2s = ims->CreateSound("bridge_sound2", b2f);
			ppSegment* b2seg = ims->CreateSegment("bridge_seg2");
			b2seg->AddSound(b2s);
			b2seg->SetEntryCue(b2f->TimeToPosition(1.125f));
			b2seg->SetExitCue(b2f->TimeToPosition(2.25f));
			ppFormat* b3f = ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Kameleon/Music/l4_s3-03.wav");
			ppSound* b3s = ims->CreateSound("bridge_sound3", b3f);
			ppSegment* b3seg = ims->CreateSegment("bridge_seg3");
			b3seg->AddSound(b3s);
			b3seg->SetEntryCue(b3f->TimeToPosition(1.125f));
			b3seg->SetExitCue(b3f->TimeToPosition(2.25f));
			ppFormat* b4f = ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Kameleon/Music/l4_s3-04.wav");
			ppSound* b4s = ims->CreateSound("bridge_sound4", b4f);
			ppSegment* b4seg = ims->CreateSegment("bridge_seg4");
			b4seg->AddSound(b4s);
			b4seg->SetEntryCue(b4f->TimeToPosition(1.125f));
			b4seg->SetExitCue(b4f->TimeToPosition(2.25f));
			ppFormat* b5f = ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Kameleon/Music/l4_s3-05.wav");
			ppSound* b5s = ims->CreateSound("bridge_sound5", b5f);
			ppSegment* b5seg = ims->CreateSegment("bridge_seg5");
			b5seg->AddSound(b5s);
			b5seg->SetEntryCue(b5f->TimeToPosition(1.125f));
			b5seg->SetExitCue(b5f->TimeToPosition(2.25f));
			ppFormat* b6f = ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Kameleon/Music/l4_s3-06.wav");
			ppSound* b6s = ims->CreateSound("bridge_sound6", b6f);
			ppSegment* b6seg = ims->CreateSegment("bridge_seg6");
			b6seg->AddSound(b6s);
			b6seg->SetEntryCue(b6f->TimeToPosition(1.125f));
			b6seg->SetExitCue(b6f->TimeToPosition(2.25f));
			ppFormat* b7f = ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Kameleon/Music/l4_s3-07.wav");
			ppSound* b7s = ims->CreateSound("bridge_sound7", b7f);
			ppSegment* b7seg = ims->CreateSegment("bridge_seg7");
			b7seg->AddSound(b7s);
			b7seg->SetEntryCue(b7f->TimeToPosition(1.125f));
			b7seg->SetExitCue(b7f->TimeToPosition(2.25f));
			ppFormat* b8f = ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Kameleon/Music/l4_s3-08.wav");
			ppSound* b8s = ims->CreateSound("bridge_sound8", b8f);
			ppSegment* b8seg = ims->CreateSegment("bridge_seg8");
			b8seg->AddSound(b8s);
			b8seg->SetEntryCue(b8f->TimeToPosition(1.125f));
			b8seg->SetExitCue(b8f->TimeToPosition(2.25f));
			ppFormat* b9f = ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Kameleon/Music/l4_s3-09.wav");
			ppSound* b9s = ims->CreateSound("bridge_sound9", b9f);
			ppSegment* b9seg = ims->CreateSegment("bridge_seg9");
			b9seg->AddSound(b9s);
			b9seg->SetEntryCue(b9f->TimeToPosition(1.125f));
			b9seg->SetExitCue(b9f->TimeToPosition(2.25f));
			ppFormat* b10f = ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Kameleon/Music/l4_s3-10.wav");
			ppSound* b10s = ims->CreateSound("bridge_sound10", b10f);
			ppSegment* b10seg = ims->CreateSegment("bridge_seg10");
			b10seg->AddSound(b10s);
			b10seg->SetEntryCue(b10f->TimeToPosition(1.125f));
			b10seg->SetExitCue(b10f->TimeToPosition(2.25f));
			ppFormat* b11f = ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Kameleon/Music/l4_s3-11.wav");
			ppSound* b11s = ims->CreateSound("bridge_sound11", b11f);
			ppSegment* b11seg = ims->CreateSegment("bridge_seg11");
			b11seg->AddSound(b11s);
			b11seg->SetEntryCue(b11f->TimeToPosition(1.125f));
			b11seg->SetExitCue(b11f->TimeToPosition(2.25f));
			ppFormat* b12f = ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Kameleon/Music/l4_s3-12.wav");
			ppSound* b12s = ims->CreateSound("bridge_sound12", b12f);
			ppSegment* b12seg = ims->CreateSegment("bridge_seg12");
			b12seg->AddSound(b12s);
			b12seg->SetEntryCue(b12f->TimeToPosition(1.125f));
			b12seg->SetExitCue(b12f->TimeToPosition(2.25f));

			ppPlaylist* bridgePlaylist = ims->CreatePlaylist("bridge");
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

			bridgePlaylist->SetTempo(80);
			bridgePlaylist->SetLoop(-1);
			bridgePlaylist->SetLocation(20, 50);
			bridgePlaylist->SetSize(100, 250);
			bridgePlaylist->SetVisible(false);
			this->gui->AddControl(bridgePlaylist);
			ppButton* bridgeButton = new ppButton("bridgebtn", 32, 300, 75, 20);
			bridgeButton->SetText("Play");
			bridgeButton->SetListener(btnListener);
			bridgeButton->SetVisible(false);
			this->gui->AddControl(bridgeButton);

			/////////////////////////////
			// Bridge->Main Transition //
			/////////////////////////////
			ppFormat* b2m_f = ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Kameleon/Music/l4_s3--l4_a2.wav");
			ppSound* b2m_s = ims->CreateSound("bridge2main_sound", b2m_f);
			ppSegment* b2m_seg = ims->CreateSegment("bridge2main_seg");
			b2m_seg->AddSound(b2m_s);
			b2m_seg->SetEntryCue(b2m_f->TimeToPosition(1.125f));
			b2m_seg->SetExitCue(b2m_f->TimeToPosition(2.25f));

			////////////////////////////////
			// Main Track Sounds (normal) //
			////////////////////////////////
			ppFormat* mn1f = ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Kameleon/Music/l4_a2-01.wav");
			ppSound* mn1s = ims->CreateSound("main_normal_sound1", mn1f);
			ppSegment* mn1seg = ims->CreateSegment("main_normal_seg1");
			mn1seg->AddSound(mn1s);
			mn1seg->SetEntryCue(mn1f->TimeToPosition(1.125f));
			mn1seg->SetExitCue(mn1f->TimeToPosition(7.5f));

			ppFormat* mn2f = ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Kameleon/Music/l4_a2-02.wav");
			ppSound* mn2s = ims->CreateSound("main_normal_sound2", mn2f);
			ppSegment* mn2seg = ims->CreateSegment("main_normal_seg2");
			mn2seg->AddSound(mn2s);
			mn2seg->SetEntryCue(mn2f->TimeToPosition(0.375f));
			mn2seg->SetExitCue(mn2f->TimeToPosition(7.5f));

			ppFormat* mn3f = ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Kameleon/Music/l4_a2-03.wav");
			ppSound* mn3s = ims->CreateSound("main_normal_sound3", mn3f);
			ppSegment* mn3seg = ims->CreateSegment("main_normal_seg3");
			mn3seg->AddSound(mn3s);
			mn3seg->SetEntryCue(mn3f->TimeToPosition(0.375f));
			mn3seg->SetExitCue(mn3f->TimeToPosition(7.5f));

			ppFormat* mn4f = ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Kameleon/Music/l4_a2-04.wav");
			ppSound* mn4s = ims->CreateSound("main_normal_sound4", mn4f);
			ppSegment* mn4seg = ims->CreateSegment("main_normal_seg4");
			mn4seg->AddSound(mn4s);
			mn4seg->SetEntryCue(mn4f->TimeToPosition(0.375f));
			mn4seg->SetExitCue(mn4f->TimeToPosition(7.5f));

			ppFormat* mn5f = ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Kameleon/Music/l4_a2-05.wav");
			ppSound* mn5s = ims->CreateSound("main_normal_sound5", mn5f);
			ppSegment* mn5seg = ims->CreateSegment("main_normal_seg5");
			mn5seg->AddSound(mn5s);
			mn5seg->SetEntryCue(mn5f->TimeToPosition(1.875f));
			mn5seg->SetExitCue(mn5f->TimeToPosition(7.5f));

			ppFormat* mn6f = ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Kameleon/Music/l4_a2-06.wav");
			ppSound* mn6s = ims->CreateSound("main_normal_sound6", mn6f);
			ppSegment* mn6seg = ims->CreateSegment("main_normal_seg6");
			mn6seg->AddSound(mn6s);
			mn6seg->SetEntryCue(mn6f->TimeToPosition(1.125f));
			mn6seg->SetExitCue(mn6f->TimeToPosition(6.0f));

			ppFormat* mn7f = ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Kameleon/Music/l4_a2-07.wav");
			ppSound* mn7s = ims->CreateSound("main_normal_sound7", mn7f);
			ppSegment* mn7seg = ims->CreateSegment("main_normal_seg7");
			mn7seg->AddSound(mn7s);
			mn7seg->SetEntryCue(mn7f->TimeToPosition(1.125f));
			mn7seg->SetExitCue(mn7f->TimeToPosition(6.0f));

			ppFormat* mn8f = ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Kameleon/Music/l4_a2-08.wav");
			ppSound* mn8s = ims->CreateSound("main_normal_sound8", mn8f);
			ppSegment* mn8seg = ims->CreateSegment("main_normal_seg8");
			mn8seg->AddSound(mn8s);
			mn8seg->SetEntryCue(mn8f->TimeToPosition(0.375f));
			mn8seg->SetExitCue(mn8f->TimeToPosition(6.0f));

			ppFormat* mn9f = ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Kameleon/Music/l4_a2-09.wav");
			ppSound* mn9s = ims->CreateSound("main_normal_sound9", mn9f);
			ppSegment* mn9seg = ims->CreateSegment("main_normal_seg9");
			mn9seg->AddSound(mn9s);
			mn9seg->SetEntryCue(mn9f->TimeToPosition(1.125f));
			mn9seg->SetExitCue(mn9f->TimeToPosition(6.0f));

			ppFormat* mn10f = ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Kameleon/Music/l4_a2-10.wav");
			ppSound* mn10s = ims->CreateSound("main_normal_sound10", mn10f);
			ppSegment* mn10seg = ims->CreateSegment("main_normal_seg10");
			mn10seg->AddSound(mn10s);
			mn10seg->SetEntryCue(mn10f->TimeToPosition(1.125f));
			mn10seg->SetExitCue(mn10f->TimeToPosition(7.5f));

			ppFormat* mn11f = ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Kameleon/Music/l4_a2-11.wav");
			ppSound* mn11s = ims->CreateSound("main_normal_sound11", mn11f);
			ppSegment* mn11seg = ims->CreateSegment("main_normal_seg11");
			mn11seg->AddSound(mn11s);
			mn11seg->SetEntryCue(mn11f->TimeToPosition(1.125f));
			mn11seg->SetExitCue(mn11f->TimeToPosition(7.5f));

			ppFormat* mn12f = ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Kameleon/Music/l4_a2-12.wav");
			ppSound* mn12s = ims->CreateSound("main_normal_sound12", mn12f);
			ppSegment* mn12seg = ims->CreateSegment("main_normal_seg12");
			mn12seg->AddSound(mn12s);
			mn12seg->SetEntryCue(mn12f->TimeToPosition(0.375f));
			mn12seg->SetExitCue(mn12f->TimeToPosition(6.0f));

			ppFormat* mn13f = ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Kameleon/Music/l4_a2-13.wav");
			ppSound* mn13s = ims->CreateSound("main_normal_sound13", mn13f);
			ppSegment* mn13seg = ims->CreateSegment("main_normal_seg13");
			mn13seg->AddSound(mn13s);
			mn13seg->SetEntryCue(mn13f->TimeToPosition(1.125f));
			mn13seg->SetExitCue(mn13f->TimeToPosition(6.0f));

			ppPlaylist* mainNormalPlaylist = ims->CreatePlaylist("main_normal");
			mainNormalPlaylist->AddSound(mn1seg);
			mainNormalPlaylist->AddSound(mn2seg);
			mainNormalPlaylist->AddSound(mn3seg);
			mainNormalPlaylist->AddSound(mn4seg);
			mainNormalPlaylist->AddSound(mn5seg);
			mainNormalPlaylist->AddSound(mn6seg);
			mainNormalPlaylist->AddSound(mn7seg);
			mainNormalPlaylist->AddSound(mn8seg);
			mainNormalPlaylist->AddSound(mn9seg);
			mainNormalPlaylist->AddSound(mn10seg);
			mainNormalPlaylist->AddSound(mn11seg);
			mainNormalPlaylist->AddSound(mn12seg);
			mainNormalPlaylist->AddSound(mn13seg);

			mainNormalPlaylist->SetTempo(80);
			mainNormalPlaylist->SetLoop(-1);
			mainNormalPlaylist->SetLocation(130, 50);
			mainNormalPlaylist->SetSize(100, 250);
			mainNormalPlaylist->SetVisible(false);
			mainNormalPlaylist->SetFilter(water_filter);
			this->gui->AddControl(mainNormalPlaylist);
			ppButton* mainNormalButton = new ppButton("mainnormalbtn", 142, 300, 75, 20);
			mainNormalButton->SetText("Play");
			mainNormalButton->SetListener(btnListener);
			mainNormalButton->SetVisible(false);
			this->gui->AddControl(mainNormalButton);

			////////////////////////////////////
			// Main Track Sounds (low health) //
			////////////////////////////////////
			ppFormat* ml1f = ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Kameleon/Music/l4_a4-01.wav");
			ppSound* ml1s = ims->CreateSound("main_low_sound1", ml1f);
			ppSegment* ml1seg = ims->CreateSegment("main_low_seg1");
			ml1seg->AddSound(ml1s);
			ml1seg->SetEntryCue(ml1f->TimeToPosition(1.125f));
			ml1seg->SetExitCue(ml1f->TimeToPosition(7.5f));

			ppFormat* ml2f = ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Kameleon/Music/l4_a4-02.wav");
			ppSound* ml2s = ims->CreateSound("main_low_sound2", ml2f);
			ppSegment* ml2seg = ims->CreateSegment("main_low_seg2");
			ml2seg->AddSound(ml2s);
			ml2seg->SetEntryCue(ml2f->TimeToPosition(0.375f));
			ml2seg->SetExitCue(ml2f->TimeToPosition(7.5f));

			ppFormat* ml3f = ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Kameleon/Music/l4_a4-03.wav");
			ppSound* ml3s = ims->CreateSound("main_low_sound3", ml3f);
			ppSegment* ml3seg = ims->CreateSegment("main_low_seg3");
			ml3seg->AddSound(ml3s);
			ml3seg->SetEntryCue(ml3f->TimeToPosition(0.375f));
			ml3seg->SetExitCue(ml3f->TimeToPosition(7.5f));

			ppFormat* ml4f = ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Kameleon/Music/l4_a4-04.wav");
			ppSound* ml4s = ims->CreateSound("main_low_sound4", ml4f);
			ppSegment* ml4seg = ims->CreateSegment("main_low_seg4");
			ml4seg->AddSound(ml4s);
			ml4seg->SetEntryCue(ml4f->TimeToPosition(0.375f));
			ml4seg->SetExitCue(ml4f->TimeToPosition(7.5f));

			ppFormat* ml5f = ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Kameleon/Music/l4_a4-05.wav");
			ppSound* ml5s = ims->CreateSound("main_low_sound5", ml5f);
			ppSegment* ml5seg = ims->CreateSegment("main_low_seg5");
			ml5seg->AddSound(ml5s);
			ml5seg->SetEntryCue(ml5f->TimeToPosition(1.875f));
			ml5seg->SetExitCue(ml5f->TimeToPosition(7.5f));

			ppFormat* ml6f = ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Kameleon/Music/l4_a4-06.wav");
			ppSound* ml6s = ims->CreateSound("main_low_sound6", ml6f);
			ppSegment* ml6seg = ims->CreateSegment("main_low_seg6");
			ml6seg->AddSound(ml6s);
			ml6seg->SetEntryCue(ml6f->TimeToPosition(0.75f));
			ml6seg->SetExitCue(ml6f->TimeToPosition(6.0f));

			ppFormat* ml7f = ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Kameleon/Music/l4_a4-07.wav");
			ppSound* ml7s = ims->CreateSound("main_low_sound7", ml7f);
			ppSegment* ml7seg = ims->CreateSegment("main_low_seg7");
			ml7seg->AddSound(ml7s);
			ml7seg->SetEntryCue(ml7f->TimeToPosition(1.125f));
			ml7seg->SetExitCue(ml7f->TimeToPosition(6.0f));

			ppFormat* ml8f = ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Kameleon/Music/l4_a4-08.wav");
			ppSound* ml8s = ims->CreateSound("main_low_sound8", ml8f);
			ppSegment* ml8seg = ims->CreateSegment("main_low_seg8");
			ml8seg->AddSound(ml8s);
			ml8seg->SetEntryCue(ml8f->TimeToPosition(0.375f));
			ml8seg->SetExitCue(ml8f->TimeToPosition(6.0f));

			ppFormat* ml9f = ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Kameleon/Music/l4_a4-09.wav");
			ppSound* ml9s = ims->CreateSound("main_low_sound9", ml9f);
			ppSegment* ml9seg = ims->CreateSegment("main_low_seg9");
			ml9seg->AddSound(ml9s);
			ml9seg->SetEntryCue(ml9f->TimeToPosition(1.5f));
			ml9seg->SetExitCue(ml9f->TimeToPosition(6.0f));

			ppFormat* ml10f = ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Kameleon/Music/l4_a4-10.wav");
			ppSound* ml10s = ims->CreateSound("main_low_sound10", ml10f);
			ppSegment* ml10seg = ims->CreateSegment("main_low_seg10");
			ml10seg->AddSound(ml10s);
			ml10seg->SetEntryCue(ml10f->TimeToPosition(1.125f));
			ml10seg->SetExitCue(ml10f->TimeToPosition(7.5f));

			ppFormat* ml11f = ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Kameleon/Music/l4_a4-11.wav");
			ppSound* ml11s = ims->CreateSound("main_low_sound11", ml11f);
			ppSegment* ml11seg = ims->CreateSegment("main_low_seg11");
			ml11seg->AddSound(ml11s);
			ml11seg->SetEntryCue(ml11f->TimeToPosition(1.125f));
			ml11seg->SetExitCue(ml11f->TimeToPosition(7.5f));

			ppFormat* ml12f = ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Kameleon/Music/l4_a4-12.wav");
			ppSound* ml12s = ims->CreateSound("main_low_sound12", ml12f);
			ppSegment* ml12seg = ims->CreateSegment("main_low_seg12");
			ml12seg->AddSound(ml12s);
			ml12seg->SetEntryCue(ml12f->TimeToPosition(1.875f));
			ml12seg->SetExitCue(ml12f->TimeToPosition(6.0f));

			ppFormat* ml13f = ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Kameleon/Music/l4_a4-13.wav");
			ppSound* ml13s = ims->CreateSound("main_low_sound13", ml13f);
			ppSegment* ml13seg = ims->CreateSegment("main_low_seg13");
			ml13seg->AddSound(ml13s);
			ml13seg->SetEntryCue(ml13f->TimeToPosition(1.5f));
			ml13seg->SetExitCue(ml13f->TimeToPosition(6.0f));

			ppPlaylist* mainLowPlaylist = ims->CreatePlaylist("main_low");
			mainLowPlaylist->AddSound(ml1seg);
			mainLowPlaylist->AddSound(ml2seg);
			mainLowPlaylist->AddSound(ml3seg);
			mainLowPlaylist->AddSound(ml4seg);
			mainLowPlaylist->AddSound(ml5seg);
			mainLowPlaylist->AddSound(ml6seg);
			mainLowPlaylist->AddSound(ml7seg);
			mainLowPlaylist->AddSound(ml8seg);
			mainLowPlaylist->AddSound(ml9seg);
			mainLowPlaylist->AddSound(ml10seg);
			mainLowPlaylist->AddSound(ml11seg);
			mainLowPlaylist->AddSound(ml12seg);
			mainLowPlaylist->AddSound(ml13seg);

			mainLowPlaylist->SetTempo(80);
			mainLowPlaylist->SetLoop(-1);
			mainLowPlaylist->SetLocation(240, 50);
			mainLowPlaylist->SetSize(100, 250);
			mainLowPlaylist->SetVisible(false);
			mainLowPlaylist->SetFilter(water_filter);
			this->gui->AddControl(mainLowPlaylist);
			ppButton* mainLowButton = new ppButton("mainlowbtn", 252, 300, 75, 20);
			mainLowButton->SetText("Play");
			mainLowButton->SetListener(btnListener);
			mainLowButton->SetVisible(false);
			this->gui->AddControl(mainLowButton);

			//////////////////////////
			// Main->End Transition //
			//////////////////////////
			ppFormat* m2e_f = ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Kameleon/Music/l4_a2--l4_am1.wav");
			ppSound* m2e_s = ims->CreateSound("main2end_sound", m2e_f);
			ppSegment* m2e_seg = ims->CreateSegment("main2end_seg");
			m2e_seg->AddSound(m2e_s);
			m2e_seg->SetEntryCue(m2e_f->TimeToPosition(0.75f));
			m2e_seg->SetExitCue(m2e_f->TimeToPosition(12.75f));
			m2e_seg->SetFilter(water_filter);

			////////////////////
			// Heroic Stinger //
			////////////////////
			ppFormat* h1f = ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Kameleon/Music/l4_a3-14.wav");
			ppSound* h1s = ims->CreateSound("heroic_sound1", h1f);
			ppSegment* h1seg = ims->CreateSegment("heroic_seg1");
			h1seg->AddSound(h1s);
			h1seg->SetEntryCue(h1f->TimeToPosition(0.75f));
			h1seg->SetExitCue(h1f->TimeToPosition(7.5f));
			ppFormat* h2f = ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Kameleon/Music/l4_a3-15.wav");
			ppSound* h2s = ims->CreateSound("heroic_sound2", h2f);
			ppSegment* h2seg = ims->CreateSegment("heroic_seg2");
			h2seg->AddSound(h2s);
			h2seg->SetEntryCue(h2f->TimeToPosition(0.75f));
			h2seg->SetExitCue(h2f->TimeToPosition(7.5f));
			ppFormat* h3f = ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Kameleon/Music/l4_a3-16.wav");
			ppSound* h3s = ims->CreateSound("heroic_sound3", h3f);
			ppSegment* h3seg = ims->CreateSegment("heroic_seg3");
			h3seg->AddSound(h3s);
			h3seg->SetEntryCue(h3f->TimeToPosition(1.125f));
			h3seg->SetExitCue(h3f->TimeToPosition(7.5f));
			ppFormat* h4f = ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/Kameleon/Music/l4_a3-17.wav");
			ppSound* h4s = ims->CreateSound("heroic_sound4", h4f);
			ppSegment* h4seg = ims->CreateSegment("heroic_seg4");
			h4seg->AddSound(h4s);
			h4seg->SetEntryCue(h4f->TimeToPosition(0.375f));
			h4seg->SetExitCue(h4f->TimeToPosition(7.5f));

			ppPlaylist* heroicPlaylist = ims->CreatePlaylist("heroic");
			heroicPlaylist->AddSound(h1seg);
			heroicPlaylist->AddSound(h2seg);
			heroicPlaylist->AddSound(h3seg);
			heroicPlaylist->AddSound(h4seg);

			heroicPlaylist->SetTempo(80);
			heroicPlaylist->SetLocation(350, 50);
			heroicPlaylist->SetSize(100, 100);
			heroicPlaylist->SetVisible(false);
			heroicPlaylist->SetFilter(water_filter);
			this->gui->AddControl(heroicPlaylist);
			ppButton* heroicButton = new ppButton("heroicbtn", 362, 150, 75, 20);
			heroicButton->SetText("Play");
			heroicButton->SetListener(btnListener);
			heroicButton->SetVisible(false);
			this->gui->AddControl(heroicButton);

			ppSwitch* sw = ims->CreateSwitch("level");
			//////////////////////////////
			// Transitions and Stingers //
			//////////////////////////////

			ppTransition* bridge2mainNormal = sw->CreateTransition(0, bridgePlaylist, mainNormalPlaylist);
			bridge2mainNormal->SetSourceCurve(NULL); // No Fade
			bridge2mainNormal->SetDestinationCurve(NULL); // No Fade
			bridge2mainNormal->SetTransitionTrack(b2m_seg);
			bridge2mainNormal->SetSourcePosition(ppTransitionSourcePosition::EXIT_CUE);

			ppTransition* bridge2mainLow = sw->CreateTransition(0, bridgePlaylist, mainLowPlaylist);
			bridge2mainLow->SetSourceCurve(NULL); // No Fade
			bridge2mainLow->SetDestinationCurve(NULL); // No Fade
			bridge2mainLow->SetTransitionTrack(b2m_seg);
			bridge2mainLow->SetSourcePosition(ppTransitionSourcePosition::EXIT_CUE);

			ppTransition* normal2low = sw->CreateTransition(0, mainNormalPlaylist, mainLowPlaylist);
			normal2low->SetSourceCurve(new ppExpoEasing());
			normal2low->SetDestinationCurve(new ppExpoEasing());
			normal2low->SetSourceDuration(2.5f);
			normal2low->SetDestinationDuration(2.5f);
			normal2low->SetSourcePosition(ppTransitionSourcePosition::EXIT_CUE);
			normal2low->SetDestinationPosition(ppTransitionDestinationPosition::SAME_TIME);

			ppTransition* low2normal = sw->CreateTransition(0, mainLowPlaylist, mainNormalPlaylist);
			low2normal->SetSourceCurve(new ppExpoEasing());
			low2normal->SetDestinationCurve(new ppExpoEasing());
			low2normal->SetSourceDuration(2.5f);
			low2normal->SetDestinationDuration(2.5f);
			low2normal->SetSourcePosition(ppTransitionSourcePosition::EXIT_CUE);
			low2normal->SetDestinationPosition(ppTransitionDestinationPosition::SAME_TIME);

			ppTransition* mainNormal2end = sw->CreateTransition(0, mainNormalPlaylist, NULL);
			mainNormal2end->SetSourceCurve(NULL); // No Fade
			mainNormal2end->SetDestinationCurve(NULL); // No Fade
			mainNormal2end->SetTransitionTrack(m2e_seg);
			mainNormal2end->SetSourcePosition(ppTransitionSourcePosition::EXIT_CUE);

			ppTransition* mainLow2end = sw->CreateTransition(0, mainLowPlaylist, NULL);
			mainLow2end->SetSourceCurve(NULL); // No Fade
			mainLow2end->SetDestinationCurve(NULL); // No Fade
			mainLow2end->SetTransitionTrack(m2e_seg);
			mainLow2end->SetSourcePosition(ppTransitionSourcePosition::EXIT_CUE);

			ppTransition* defaultTransition = sw->CreateTransition(0, NULL, NULL);
			defaultTransition->SetSourceDuration(1);
			defaultTransition->SetDestinationDuration(1);

			sw->CreateStinger("heroic", heroicPlaylist, ppStingerTriggerPosition::ENTRY_CUE);

			//////////////////////////////

			sw->SetLocation(470, 50);
			sw->SetSize(150, 20);
			sw->SetVisible(false);
			this->gui->AddControl(sw);

			ppButton* stopsw = new ppButton("stopsw", this->GetGame()->GetWidth()-80, 90, 75, 20);
			stopsw->SetText("Stop");
			stopsw->SetListener(btnListener);
			stopsw->SetVisible(false);
			this->gui->AddControl(stopsw);

			ppButton* bridgesw = new ppButton("bridgesw", this->GetGame()->GetWidth()-80, 115, 75, 20);
			bridgesw->SetText("Bridge");
			bridgesw->SetListener(btnListener);
			bridgesw->SetVisible(false);
			this->gui->AddControl(bridgesw);

			ppButton* mainnormalsw = new ppButton("mainnormalsw", this->GetGame()->GetWidth()-80, 140, 75, 20);
			mainnormalsw->SetText("Main [Normal]");
			mainnormalsw->SetListener(btnListener);
			mainnormalsw->SetVisible(false);
			this->gui->AddControl(mainnormalsw);

			ppButton* mainlowsw = new ppButton("mainlowsw", this->GetGame()->GetWidth()-80, 165, 75, 20);
			mainlowsw->SetText("Main [Low]");
			mainlowsw->SetListener(btnListener);
			mainlowsw->SetVisible(false);
			this->gui->AddControl(mainlowsw);

			ppButton* heroicsw = new ppButton("heroicsw", this->GetGame()->GetWidth()-80, 200, 75, 20);
			heroicsw->SetText("Heroic");
			heroicsw->SetListener(btnListener);
			heroicsw->SetVisible(false);
			this->gui->AddControl(heroicsw);

			ppButton* debugButton = new ppButton("debugbtn", this->GetGame()->GetWidth()-105, this->GetGame()->GetHeight()-25, 100, 20);
			debugButton->SetText("Toggle Debug");
			debugButton->SetListener(btnListener);
			debugButton->SetVisible(true);
			this->gui->AddControl(debugButton);
		}
	}
	this->gui->Update(input);
	if(input->IsKeyDown(SDL_SCANCODE_R)){
		ims->ClearSound();
		ims->ClearSwitch();
		this->GetGame()->EnterState("ims");
	}
	this->gameState->OnUpdate(input, delta);
}
