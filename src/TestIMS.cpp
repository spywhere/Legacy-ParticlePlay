#include "TestIMS.h"

#include <iostream>
#include <cmath>
#include <sstream>
#include "ParticlePlay/IMS/Filters.h"
#include "ParticlePlay/IMS/IMS.h"
#include "ParticlePlay/IMS/Sound.h"
#include "ParticlePlay/GUI/Controls.h"
#include "ParticlePlay/GUI/GUIType.h"

#define TEST1 "cHiPiE"
#define TEST2 "Sky Above"
#define TEST3 "Falk Demo Reel"
#define TEST4 "Music Gameplay"
#define TEST5 "Plants vs. Zombies Track 1"
#define TEST6 "Wwise Stress"

void TestIMS::OnInit(){
	this->gui = new ppGUI();
	this->gui->AddControl("filter", new ppLabel(10, 135));
	this->gui->AddControl("sound1", new ppLabel(10, 150));
	this->gui->AddControl("sound2", new ppLabel(10, 165));
	this->gui->AddControl("sound3", new ppLabel(10, 180));
	this->gui->AddControl("sound4", new ppLabel(10, 195));

	if(this->gui->GetControl("filter")->GetType()==GUI_LABEL){
		ppLabel* label = (ppLabel*)this->gui->GetControl("filter");
		label->SetText("LPF");
		label->SetVisible(false);
	}
	if(this->gui->GetControl("sound1")->GetType()==GUI_LABEL){
		ppLabel* label = (ppLabel*)this->gui->GetControl("sound1");
		label->SetText("");
		label->SetVisible(false);
	}
	if(this->gui->GetControl("sound2")->GetType()==GUI_LABEL){
		ppLabel* label = (ppLabel*)this->gui->GetControl("sound2");
		label->SetText("");
		label->SetVisible(false);
	}
	if(this->gui->GetControl("sound3")->GetType()==GUI_LABEL){
		ppLabel* label = (ppLabel*)this->gui->GetControl("sound3");
		label->SetText("");
		label->SetVisible(false);
	}
	if(this->gui->GetControl("sound4")->GetType()==GUI_LABEL){
		ppLabel* label = (ppLabel*)this->gui->GetControl("sound4");
		label->SetText("");
		label->SetVisible(false);
	}

	this->lpf = NULL;
	this->cooldown = 0;
	this->test = 0;
	this->currentTime = -1;
	this->totalTime = -1;
	this->soundInit = false;
	this->isPause = false;
	this->posx = 0;
	this->posy = 0;
	this->SetNeedInit(true);
}

void TestIMS::DrawRect(int x, int y, int w, int h){
	glBegin(GL_LINE_LOOP);
		glVertex3f(x, y, 0);
		glVertex3f(x+w, y, 0);
		glVertex3f(x+w, y+h, 0);
		glVertex3f(x, y+h, 0);
	glEnd();
}

void TestIMS::DrawFillRect(int x, int y, int w, int h){
	glBegin(GL_QUADS);
		glVertex3f(x, y, 0);
		glVertex3f(x+w, y, 0);
		glVertex3f(x+w, y+h, 0);
		glVertex3f(x, y+h, 0);
	glEnd();
}

void TestIMS::OnRender(SDL_Renderer* renderer, int delta){
	std::stringstream ss;
	ss << "FPS: " << this->GetGame()->GetFPS() << " [" << this->GetGame()->GetAvgRenderTime() << "ms]\n";
	ss << "UPS: " << this->GetGame()->GetUPS() << " [" << this->GetGame()->GetAvgUpdateTime() << "ms]\n";

	if(this->test<1||!this->soundInit){
		ss << "\nSelect Test:\n";
		ss << " 1) " << TEST1 << "\n";
		ss << " 2) " << TEST2 << "\n";
		ss << " 3) " << TEST3 << "\n";
		ss << " 4) " << TEST4 << "\n";
		ss << " 5) " << TEST5 << "\n";
		ss << " 6) " << TEST6 << "\n";
	}else{
		if(this->test==1){
			ss << "\n" << TEST1 << (this->isPause?" [PAUSED]":"");
		}else if(this->test==2){
			ss << "\n" << TEST2 << (this->isPause?" [PAUSED]":"");
		}else if(this->test==3){
			ss << "\n" << TEST3 << (this->isPause?" [PAUSED]":"");
		}else if(this->test==4){
			ss << "\n" << TEST4 << (this->isPause?" [PAUSED]":"");
		}else if(this->test==5){
			ss << "\n" << TEST5 << (this->isPause?" [PAUSED]":"");
		}else if(this->test==6){
			ss << "\n" << TEST6 << (this->isPause?" [PAUSED]":"");
		}
		ss << "\n\nPress 'R' to restart a test\n";
		ss << "\nPlaying " << this->currentTime << "/" << this->totalTime << "\n";

		if(this->lpf){
			if(this->posy==0){
				glColor3f(0.5f, 0.5f, 1);
			}else{
				glColor3f(1, 1, 1);
			}
			this->DrawRect(100, 135, 110, 10);
			this->DrawFillRect(200-this->lpf->GetGainHF()*100, 135, 10, 10);
		}

		if(this->posy==1){
			glColor3f(0.5f, 0.5f, 1);
		}else{
			glColor3f(1, 1, 1);
		}
		this->DrawRect(100, 150, 110, 10);
		if(this->test==1||this->test==6){
			this->DrawFillRect(100+this->GetGame()->GetInteractiveMusicSystem()->GetSound("Bass")->GetVolumn()*100, 150, 10, 10);
		}else if(this->test==2){
			this->DrawFillRect(100+this->GetGame()->GetInteractiveMusicSystem()->GetSound("Drum")->GetVolumn()*100, 150, 10, 10);
		}else if(this->test==3){
			this->DrawFillRect(100+this->GetGame()->GetInteractiveMusicSystem()->GetSound("BeCool")->GetVolumn()*100, 150, 10, 10);
		}else if(this->test==4||this->test==5){
			this->DrawFillRect(100+this->GetGame()->GetInteractiveMusicSystem()->GetSound("Base")->GetVolumn()*100, 150, 10, 10);
		}
		if(this->posy==2){
			glColor3f(0.5f, 0.5f, 1);
		}else{
			glColor3f(1, 1, 1);
		}
		this->DrawRect(100, 165, 110, 10);
		if(this->test==1){
			this->DrawFillRect(100+this->GetGame()->GetInteractiveMusicSystem()->GetSound("Drum_Bass")->GetVolumn()*100, 165, 10, 10);
		}else if(this->test==2){
			this->DrawFillRect(100+this->GetGame()->GetInteractiveMusicSystem()->GetSound("Base")->GetVolumn()*100, 165, 10, 10);
		}else if(this->test==3){
			this->DrawFillRect(100+this->GetGame()->GetInteractiveMusicSystem()->GetSound("BeWild")->GetVolumn()*100, 165, 10, 10);
		}else if(this->test==4){
			this->DrawFillRect(100+this->GetGame()->GetInteractiveMusicSystem()->GetSound("Critical")->GetVolumn()*100, 165, 10, 10);
		}else if(this->test==5){
			this->DrawFillRect(100+this->GetGame()->GetInteractiveMusicSystem()->GetSound("Drum")->GetVolumn()*100, 165, 10, 10);
		}else if(this->test==6){
			this->DrawFillRect(100+this->GetGame()->GetInteractiveMusicSystem()->GetSound("Orchestra")->GetVolumn()*100, 165, 10, 10);
		}
		if(this->test!=3){
			if(this->posy==3){
				glColor3f(0.5f, 0.5f, 1);
			}else{
				glColor3f(1, 1, 1);
			}
			this->DrawRect(100, 180, 110, 10);
			if(this->test==1){
				this->DrawFillRect(100+this->GetGame()->GetInteractiveMusicSystem()->GetSound("Drum_Snare")->GetVolumn()*100, 180, 10, 10);
			}else if(this->test==2){
				this->DrawFillRect(100+this->GetGame()->GetInteractiveMusicSystem()->GetSound("Melody")->GetVolumn()*100, 180, 10, 10);
			}else if(this->test==4){
				this->DrawFillRect(100+this->GetGame()->GetInteractiveMusicSystem()->GetSound("Battle")->GetVolumn()*100, 180, 10, 10);
			}else if(this->test==5){
				this->DrawFillRect(100+this->GetGame()->GetInteractiveMusicSystem()->GetSound("Tamborine")->GetVolumn()*100, 180, 10, 10);
			}else if(this->test==6){
				this->DrawFillRect(100+this->GetGame()->GetInteractiveMusicSystem()->GetSound("Percussion")->GetVolumn()*100, 180, 10, 10);
			}
			if(this->test!=3&&this->test!=5){
				if(this->posy==4){
					glColor3f(0.5f, 0.5f, 1);
				}else{
					glColor3f(1, 1, 1);
				}
				this->DrawRect(100, 195, 110, 10);
				if(this->test==1){
					this->DrawFillRect(100+this->GetGame()->GetInteractiveMusicSystem()->GetSound("Melody")->GetVolumn()*100, 195, 10, 10);
				}else if(this->test==2){
					this->DrawFillRect(100+this->GetGame()->GetInteractiveMusicSystem()->GetSound("Melody2")->GetVolumn()*100, 195, 10, 10);
				}else if(this->test==4){
					this->DrawFillRect(100+this->GetGame()->GetInteractiveMusicSystem()->GetSound("All")->GetVolumn()*100, 195, 10, 10);
				}else if(this->test==6){
					this->DrawFillRect(100+this->GetGame()->GetInteractiveMusicSystem()->GetSound("Various")->GetVolumn()*100, 195, 10, 10);
				}
			}
		}
		glColor3f(1, 1, 1);
	}
	if(this->gui->GetDefaultFont()){
		this->gui->GetDefaultFont()->Render(10, 10, ss.str().c_str(), renderer);
	}
	this->gui->Render(renderer);
}

void TestIMS::OnUpdate(ppInput* input, int delta){
	ppIMS* ims = this->GetGame()->GetInteractiveMusicSystem();
	if(this->test<1&&!this->soundInit){
		if(input->IsKeyDown(SDL_SCANCODE_1)){
			this->test = 1;

			if(this->gui->GetControl("sound1")->GetType()==GUI_LABEL){
				ppLabel* label = (ppLabel*)this->gui->GetControl("sound1");
				label->SetText("Bass");
				label->SetVisible(true);
			}
			if(this->gui->GetControl("sound2")->GetType()==GUI_LABEL){
				ppLabel* label = (ppLabel*)this->gui->GetControl("sound2");
				label->SetText("Drum Bass");
				label->SetVisible(true);
			}
			if(this->gui->GetControl("sound3")->GetType()==GUI_LABEL){
				ppLabel* label = (ppLabel*)this->gui->GetControl("sound3");
				label->SetText("Drum Snare");
				label->SetVisible(true);
			}
			if(this->gui->GetControl("sound4")->GetType()==GUI_LABEL){
				ppLabel* label = (ppLabel*)this->gui->GetControl("sound4");
				label->SetText("Melody");
				label->SetVisible(true);
			}

			ppSound* sound = ims->NewSound("Bass", "res/cHiPiE/cHiPiE_bass.wav", 0);
			ppSound* sound2 = ims->NewSound("Drum_Bass", "res/cHiPiE/cHiPiE_drum_base.wav", 0);
			ppSound* sound3 = ims->NewSound("Drum_Snare", "res/cHiPiE/cHiPiE_drum_snare.wav", 0);
			ppSound* sound4 = ims->NewSound("Melody", "res/cHiPiE/cHiPiE_melody.wav", 0);
			this->lpf = new ppLowPassFilter();
			ims->ApplyFilter(this->lpf);
			if(sound&&sound2&&sound3&&sound4){
				ims->SetLoop(true);
				this->soundInit = true;
				ims->Play();
			}

		}else if(input->IsKeyDown(SDL_SCANCODE_2)){
			this->test = 2;

			if(this->gui->GetControl("sound1")->GetType()==GUI_LABEL){
				ppLabel* label = (ppLabel*)this->gui->GetControl("sound1");
				label->SetText("Drum");
				label->SetVisible(true);
			}
			if(this->gui->GetControl("sound2")->GetType()==GUI_LABEL){
				ppLabel* label = (ppLabel*)this->gui->GetControl("sound2");
				label->SetText("Base");
				label->SetVisible(true);
			}
			if(this->gui->GetControl("sound3")->GetType()==GUI_LABEL){
				ppLabel* label = (ppLabel*)this->gui->GetControl("sound3");
				label->SetText("Melody");
				label->SetVisible(true);
			}
			if(this->gui->GetControl("sound4")->GetType()==GUI_LABEL){
				ppLabel* label = (ppLabel*)this->gui->GetControl("sound4");
				label->SetText("Melody2");
				label->SetVisible(true);
			}

			ppSound* sound = ims->NewSound("Drum", "res/skyabove/skyabove_drum.wav", 0);
			ppSound* sound2 = ims->NewSound("Base", "res/skyabove/skyabove_base.wav", 0);
			ppSound* sound3 = ims->NewSound("Melody", "res/skyabove/skyabove_melody.wav", 0);
			ppSound* sound4 = ims->NewSound("Melody2", "res/skyabove/skyabove_melody2.wav", 0);
			this->lpf = new ppLowPassFilter();
			ims->ApplyFilter(this->lpf);
			if(sound&&sound2&&sound3&&sound4){
				ims->SetLoop(true);
				this->soundInit = true;
				ims->Play();
			}

		}else if(input->IsKeyDown(SDL_SCANCODE_3)){
			this->test = 3;

			if(this->gui->GetControl("sound1")->GetType()==GUI_LABEL){
				ppLabel* label = (ppLabel*)this->gui->GetControl("sound1");
				label->SetText("Be Wild");
				label->SetVisible(true);
			}
			if(this->gui->GetControl("sound2")->GetType()==GUI_LABEL){
				ppLabel* label = (ppLabel*)this->gui->GetControl("sound2");
				label->SetText("Be Cool");
				label->SetVisible(true);
			}

			ppSound* bewild = ims->NewSound("BeWild", "res/FalkDemo.wav", 0);
			ppSound* becool = ims->NewSound("BeCool", "res/FalkDemo.wav", 1);
			this->lpf = new ppLowPassFilter();
			ims->ApplyFilter(this->lpf);
			if(bewild&&becool){
				ims->GetSound("BeCool")->SetVolumn(0);

				this->soundInit = true;
				ims->Play();
			}
		}else if(input->IsKeyDown(SDL_SCANCODE_4)){
			this->test = 4;

			if(this->gui->GetControl("sound1")->GetType()==GUI_LABEL){
				ppLabel* label = (ppLabel*)this->gui->GetControl("sound1");
				label->SetText("Base");
				label->SetVisible(true);
			}
			if(this->gui->GetControl("sound2")->GetType()==GUI_LABEL){
				ppLabel* label = (ppLabel*)this->gui->GetControl("sound2");
				label->SetText("Critical");
				label->SetVisible(true);
			}
			if(this->gui->GetControl("sound3")->GetType()==GUI_LABEL){
				ppLabel* label = (ppLabel*)this->gui->GetControl("sound3");
				label->SetText("Battle");
				label->SetVisible(true);
			}
			if(this->gui->GetControl("sound4")->GetType()==GUI_LABEL){
				ppLabel* label = (ppLabel*)this->gui->GetControl("sound4");
				label->SetText("All");
				label->SetVisible(true);
			}

			ppSound* base = ims->NewSound("Base", "res/Music_Gameplay.wav", 0);
			ppSound* critical = ims->NewSound("Critical", "res/Music_Gameplay.wav", 1);
			ppSound* battle = ims->NewSound("Battle", "res/Music_Gameplay.wav", 2);
			ppSound* all = ims->NewSound("All", "res/Music_Gameplay.wav", 3);
			this->lpf = new ppLowPassFilter();
			ims->ApplyFilter(this->lpf);
			if(base&&critical&&battle&&all){
				ims->SetLoop(true);
				ims->GetSound("Critical")->SetVolumn(0);
				ims->GetSound("Battle")->SetVolumn(0);
				ims->GetSound("All")->SetVolumn(0);

				this->soundInit = true;
				ims->Play();
			}
		}else if(input->IsKeyDown(SDL_SCANCODE_5)){
			this->test = 5;

			if(this->gui->GetControl("sound1")->GetType()==GUI_LABEL){
				ppLabel* label = (ppLabel*)this->gui->GetControl("sound1");
				label->SetText("Base");
				label->SetVisible(true);
			}
			if(this->gui->GetControl("sound2")->GetType()==GUI_LABEL){
				ppLabel* label = (ppLabel*)this->gui->GetControl("sound2");
				label->SetText("Drum");
				label->SetVisible(true);
			}
			if(this->gui->GetControl("sound3")->GetType()==GUI_LABEL){
				ppLabel* label = (ppLabel*)this->gui->GetControl("sound3");
				label->SetText("Tamborine");
				label->SetVisible(true);
			}

			ppSound* base = ims->NewSound("Base", "res/PvZ/PvZ_T1_Base.wav", 0);
			ppSound* drum = ims->NewSound("Drum", "res/PvZ/PvZ_T1_Drum.wav", 0);
			ppSound* tamborine = ims->NewSound("Tamborine", "res/PvZ/PvZ_T1_Tamborine.wav", 0);
			this->lpf = new ppLowPassFilter();
			ims->ApplyFilter(this->lpf);
			if(base&&drum&&tamborine){
				this->soundInit = true;
				ims->Play();
			}
		}else if(input->IsKeyDown(SDL_SCANCODE_6)){
			this->test = 6;

			if(this->gui->GetControl("sound1")->GetType()==GUI_LABEL){
				ppLabel* label = (ppLabel*)this->gui->GetControl("sound1");
				label->SetText("Bass");
				label->SetVisible(true);
			}
			if(this->gui->GetControl("sound2")->GetType()==GUI_LABEL){
				ppLabel* label = (ppLabel*)this->gui->GetControl("sound2");
				label->SetText("Orchestra");
				label->SetVisible(true);
			}
			if(this->gui->GetControl("sound3")->GetType()==GUI_LABEL){
				ppLabel* label = (ppLabel*)this->gui->GetControl("sound3");
				label->SetText("Percussion");
				label->SetVisible(true);
			}
			if(this->gui->GetControl("sound4")->GetType()==GUI_LABEL){
				ppLabel* label = (ppLabel*)this->gui->GetControl("sound4");
				label->SetText("Various");
				label->SetVisible(true);
			}

			ppSound* sound = ims->NewSound("Bass", "res/wwise/Stress_Bass.wav", 0);
			ppSound* sound2 = ims->NewSound("Orchestra", "res/wwise/Stress_Orchestra.wav", 0);
			ppSound* sound3 = ims->NewSound("Percussion", "res/wwise/Stress_Percussion.wav", 0);
			ppSound* sound4 = ims->NewSound("Various", "res/wwise/Stress_Various.wav", 0);
			this->lpf = new ppLowPassFilter();
			ims->ApplyFilter(this->lpf);
			if(sound&&sound2&&sound3&&sound4){
				this->soundInit = true;
				ims->Play();
			}
		}
	}
	if(this->test>0&&this->soundInit){
		ppSound* sound = NULL;
		ppSound* mixSound = NULL;
		if(this->test==1){
			sound = ims->GetSound("Bass");

			if(this->posy==1){
				mixSound = ims->GetSound("Bass");
			}else if(this->posy==2){
				mixSound = ims->GetSound("Drum_Bass");
			}else if(this->posy==3){
				mixSound = ims->GetSound("Drum_Snare");
			}else if(this->posy==4){
				mixSound = ims->GetSound("Melody");
			}
		}else if(this->test==2){
			sound = ims->GetSound("Drum");

			if(this->posy==1){
				mixSound = ims->GetSound("Drum");
			}else if(this->posy==2){
				mixSound = ims->GetSound("Base");
			}else if(this->posy==3){
				mixSound = ims->GetSound("Melody");
			}else if(this->posy==4){
				mixSound = ims->GetSound("Melody2");
			}
		}else if(this->test==3){
			sound = ims->GetSound("BeWild");

			if(this->posy==1){
				mixSound = ims->GetSound("BeCool");
			}else if(this->posy==2){
				mixSound = ims->GetSound("BeWild");
			}
		}else if(this->test==4){
			sound = ims->GetSound("Base");

			if(this->posy==1){
				mixSound = ims->GetSound("Base");
			}else if(this->posy==2){
				mixSound = ims->GetSound("Critical");
			}else if(this->posy==3){
				mixSound = ims->GetSound("Battle");
			}else if(this->posy==4){
				mixSound = ims->GetSound("All");
			}
		}else if(this->test==5){
			sound = ims->GetSound("Base");

			if(this->posy==1){
				mixSound = ims->GetSound("Base");
			}else if(this->posy==2){
				mixSound = ims->GetSound("Drum");
			}else if(this->posy==3){
				mixSound = ims->GetSound("Tamborine");
			}
		}else if(this->test==6){
			sound = ims->GetSound("Bass");

			if(this->posy==1){
				mixSound = ims->GetSound("Bass");
			}else if(this->posy==2){
				mixSound = ims->GetSound("Orchestra");
			}else if(this->posy==3){
				mixSound = ims->GetSound("Percussion");
			}else if(this->posy==4){
				mixSound = ims->GetSound("Various");
			}
		}
		if(sound&&sound->IsPlaying()&&this->cooldown--<=0){
			if(this->gui->GetControl("filter")->GetType()==GUI_LABEL){
				ppLabel* label = (ppLabel*)this->gui->GetControl("filter");
				label->SetVisible(true);
			}
			this->currentTime = sound->GetCurrentTime();
			this->totalTime = sound->GetTimeLength();
			this->cooldown=10;
		}
		ims->Update();

		int soundmax = 4;
		if(this->test==3){
			soundmax = 2;
		}else if(this->test==5){
			soundmax = 3;
		}

		if(input->IsKeyDown(SDL_SCANCODE_UP, 10)){
			if(--this->posy<0){
				this->posy = soundmax;
			}
		}else if(input->IsKeyDown(SDL_SCANCODE_DOWN, 10)){
			if(++this->posy>soundmax){
				this->posy = 0;
			}
		}
		if(input->IsKeyDown(SDL_SCANCODE_LEFT, 1)){
			if(this->posy==0){
				if(this->lpf->GetGainHF()<1){
					this->lpf->SetGainHF(this->lpf->GetGainHF()+0.01f);
				}
			}else if(mixSound){
				if(mixSound->GetVolumn()>0){
					mixSound->SetVolumn(mixSound->GetVolumn()-0.01f);
					if(this->test==3){
						if(this->posy==1){
							ims->GetSound("BeWild")->SetVolumn(1.0f-mixSound->GetVolumn());
						}else{
							ims->GetSound("BeCool")->SetVolumn(1.0f-mixSound->GetVolumn());
						}
					}
				}
			}
		}else if(input->IsKeyDown(SDL_SCANCODE_RIGHT, 1)){
			if(this->posy==0){
				if(this->lpf->GetGainHF()>0){
					this->lpf->SetGainHF(this->lpf->GetGainHF()-0.01f);
				}
			}else if(mixSound){
				if(mixSound->GetVolumn()<1){
					mixSound->SetVolumn(mixSound->GetVolumn()+0.01f);
					if(this->test==3){
						if(this->posy==1){
							ims->GetSound("BeWild")->SetVolumn(1.0f-mixSound->GetVolumn());
						}else{
							ims->GetSound("BeCool")->SetVolumn(1.0f-mixSound->GetVolumn());
						}
					}
				}
			}
		}

		if(input->IsKeyDown(SDL_SCANCODE_R)){
			ims->Stop();
			ims->ClearSound();
			this->GetGame()->EnterScene(this);
		}
		if(input->IsKeyDown(SDL_SCANCODE_P, 10)){
			if(sound->IsPause()){
				ims->Play();
			}else{
				ims->Pause();
			}
			this->isPause = sound->IsPause();
		}
	}
	this->gui->Update(input);
}