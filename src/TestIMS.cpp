#include "TestIMS.h"

#include <iostream>
#include <cmath>
#include <sstream>
#include "ParticlePlay/IMS/Filters.h"
#include "ParticlePlay/IMS/IMS.h"
#include "ParticlePlay/IMS/Sound.h"

#define TEST1 "cHiPiE"
#define TEST2 "Sky Above"
#define TEST3 "Falk Demo Reel"
#define TEST4 "Music Gameplay"
#define TEST5 "Plants vs. Zombies Track 1"

void TestIMS::OnInit(){
	this->gui = new ppGUI();
	this->lpf = NULL;
	this->cooldown = 0;
	this->test = 0;
	this->currentTime = -1;
	this->totalTime = -1;
	this->soundInit = false;
	this->SetNeedInit(true);
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
	}else{
		if(this->test==1){
			ss << "\n" << TEST1;
		}else if(this->test==2){
			ss << "\n" << TEST2;
		}else if(this->test==3){
			ss << "\n" << TEST3;
		}else if(this->test==4){
			ss << "\n" << TEST4;
		}else if(this->test==5){
			ss << "\n" << TEST5;
		}
		ss << "\n\nPress 'R' to restart a test\n";
		ss << "\nPlaying " << this->currentTime << "/" << this->totalTime << "\n";

		if(this->test==4){
			ss << "\n" << ((this->GetGame()->GetInteractiveMusicSystem()->GetSound("Base")->GetVolumn()>0)?">":"") << " Base\n";
			ss << ((this->GetGame()->GetInteractiveMusicSystem()->GetSound("Critical")->GetVolumn()>0)?">":"") << " Critical\n";
			ss << ((this->GetGame()->GetInteractiveMusicSystem()->GetSound("Battle")->GetVolumn()>0)?">":"") << " Battle\n";
			ss << ((this->GetGame()->GetInteractiveMusicSystem()->GetSound("All")->GetVolumn()>0)?">":"") << " All\n";
		}
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

			ppSound* sound = ims->NewSound("Bass", "res/cHiPiE/cHiPiE_bass.wav", 0);
			ppSound* sound2 = ims->NewSound("Drum_Bass", "res/cHiPiE/cHiPiE_drum_base.wav", 0);
			ppSound* sound3 = ims->NewSound("Drum_Snare", "res/cHiPiE/cHiPiE_drum_snare.wav", 0);
			ppSound* sound4 = ims->NewSound("Melody", "res/cHiPiE/cHiPiE_melody.wav", 0);
			this->lpf = new ppLowPassFilter();
			ims->ApplyFilter(this->lpf);
			if(sound&&sound2&&sound3&&sound4){
				ims->GetSound("Drum_Bass")->SetVolumn(0);
				ims->GetSound("Drum_Snare")->SetVolumn(0);
				ims->GetSound("Melody")->SetVolumn(0);

				this->soundInit = true;
				ims->Play();
			}

		}else if(input->IsKeyDown(SDL_SCANCODE_2)){
			this->test = 2;

			ppSound* sound = ims->NewSound("Drum", "res/skyabove/skyabove_drum.wav", 0);
			ppSound* sound2 = ims->NewSound("Base", "res/skyabove/skyabove_base.wav", 0);
			ppSound* sound3 = ims->NewSound("Melody", "res/skyabove/skyabove_melody.wav", 0);
			ppSound* sound4 = ims->NewSound("Melody2", "res/skyabove/skyabove_melody2.wav", 0);
			this->lpf = new ppLowPassFilter();
			ims->ApplyFilter(this->lpf);
			if(sound&&sound2&&sound3&&sound4){
				ims->SetLoop(true);
				ims->GetSound("Base")->SetVolumn(0);
				ims->GetSound("Melody")->SetVolumn(0);
				ims->GetSound("Melody2")->SetVolumn(0);

				this->soundInit = true;
				ims->Play();
			}

		}else if(input->IsKeyDown(SDL_SCANCODE_3)){
			this->test = 3;

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

			ppSound* base = ims->NewSound("Base", "res/Music_Gameplay.wav", 0);
			ppSound* critical = ims->NewSound("Critical", "res/Music_Gameplay.wav", 1);
			ppSound* battle = ims->NewSound("Battle", "res/Music_Gameplay.wav", 2);
			ppSound* all = ims->NewSound("All", "res/Music_Gameplay.wav", 3);
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

			ppSound* base = ims->NewSound("Base", "res/PvZ/PvZ_T1_Base.wav", 0);
			ppSound* drum = ims->NewSound("Drum", "res/PvZ/PvZ_T1_Drum.wav", 0);
			ppSound* tamborine = ims->NewSound("Tamborine", "res/PvZ/PvZ_T1_Tamborine.wav", 0);
			if(base&&drum&&tamborine){
				ims->GetSound("Drum")->SetVolumn(0);
				ims->GetSound("Tamborine")->SetVolumn(0);

				this->soundInit = true;
				ims->Play();
			}
		}
	}
	if(this->test>0&&this->soundInit){
		ppSound* sound = NULL;
		if(this->test==1){
			sound = ims->GetSound("Bass");

			if(currentTime>=15&&currentTime<20){
				ims->GetSound("Melody")->SetVolumn((sound->GetCurrentTime()-15)/5.0f);
			}
			if(currentTime>=30&&currentTime<35){
				ims->GetSound("Drum_Bass")->SetVolumn((sound->GetCurrentTime()-30)/5.0f);
			}
			if(currentTime>=45&&currentTime<50){
				ims->GetSound("Drum_Snare")->SetVolumn((sound->GetCurrentTime()-45)/5.0f);
			}
			if(currentTime>=50&&currentTime<55){
				this->lpf->SetGainHF(1.0f-(sound->GetCurrentTime()-50)/5.0f);
			}
			if(currentTime>=55&&currentTime<60){
				this->lpf->SetGainHF((sound->GetCurrentTime()-55)/5.0f);
			}
		}else if(this->test==2){
			sound = ims->GetSound("Drum");

			if(currentTime>=15&&currentTime<20){
				ims->GetSound("Base")->SetVolumn((sound->GetCurrentTime()-15)/5.0f);
			}
			if(currentTime>=30&&currentTime<35){
				ims->GetSound("Melody")->SetVolumn((sound->GetCurrentTime()-30)/5.0f);
			}
			if(currentTime>=70&&currentTime<75){
				ims->GetSound("Melody2")->SetVolumn((sound->GetCurrentTime()-70)/5.0f);
			}
			if(currentTime>=50&&currentTime<55){
				lpf->SetGainHF(1.0f-(sound->GetCurrentTime()-50)/5.0f);
			}
			if(currentTime>=55&&currentTime<60){
				lpf->SetGainHF((sound->GetCurrentTime()-55)/5.0f);
			}
			if(currentTime>=95&&currentTime<100){
				ims->GetSound("Melody2")->SetVolumn(1.0f-(sound->GetCurrentTime()-95)/5.0f);
			}
			if(currentTime>=100&&currentTime<105){
				ims->GetSound("Melody")->SetVolumn(1.0f-(sound->GetCurrentTime()-100)/5.0f);
			}
			if(currentTime>=100&&currentTime<105){
				ims->GetSound("Base")->SetVolumn(1.0f-(sound->GetCurrentTime()-100)/5.0f);
			}
		}else if(this->test==3){
			sound = ims->GetSound("BeWild");

			if(currentTime>=30&&currentTime<35){
				ims->GetSound("BeWild")->SetVolumn(1.0f-(sound->GetCurrentTime()-30)/5.0f);
				ims->GetSound("BeCool")->SetVolumn((sound->GetCurrentTime()-30)/5.0f);
			}
			if(currentTime>=45&&currentTime<50){
				ims->GetSound("BeWild")->SetVolumn((sound->GetCurrentTime()-45)/5.0f);
				ims->GetSound("BeCool")->SetVolumn(1.0f-(sound->GetCurrentTime()-45)/5.0f);
			}
			if(currentTime>=60&&currentTime<65){
				ims->GetSound("BeWild")->SetVolumn(1.0f-(sound->GetCurrentTime()-60)/5.0f);
				ims->GetSound("BeCool")->SetVolumn((sound->GetCurrentTime()-60)/5.0f);
			}
			if(currentTime>=75&&currentTime<80){
				ims->GetSound("BeWild")->SetVolumn((sound->GetCurrentTime()-75)/5.0f);
				ims->GetSound("BeCool")->SetVolumn(1.0f-(sound->GetCurrentTime()-75)/5.0f);
			}
			if(currentTime>=50&&currentTime<55){
				lpf->SetGainHF(1.0f-(sound->GetCurrentTime()-50)/5.0f);
			}
			if(currentTime>=55&&currentTime<60){
				lpf->SetGainHF((sound->GetCurrentTime()-55)/5.0f);
			}
		}else if(this->test==4){
			sound = ims->GetSound("Base");

			if(currentTime<15){
				ims->GetSound("Base")->SetVolumn(1);
				ims->GetSound("Critical")->SetVolumn(0);
				ims->GetSound("Battle")->SetVolumn(0);
				ims->GetSound("All")->SetVolumn(0);
			}
			if(currentTime>=15&&currentTime<20){
				ims->GetSound("Base")->SetVolumn(1.0f-(sound->GetCurrentTime()-15)/5.0f);
				ims->GetSound("Critical")->SetVolumn((sound->GetCurrentTime()-15)/5.0f);
			}
			if(currentTime>=20&&currentTime<30){
				ims->GetSound("Base")->SetVolumn(0);
			}
			if(currentTime>=30&&currentTime<35){
				ims->GetSound("Critical")->SetVolumn(1.0f-(sound->GetCurrentTime()-30)/5.0f);
				ims->GetSound("Battle")->SetVolumn((sound->GetCurrentTime()-30)/5.0f);
			}
			if(currentTime>=35&&currentTime<45){
				ims->GetSound("Critical")->SetVolumn(0);
			}
			if(currentTime>=45&&currentTime<50){
				ims->GetSound("Battle")->SetVolumn(1.0f-(sound->GetCurrentTime()-45)/5.0f);
				ims->GetSound("All")->SetVolumn((sound->GetCurrentTime()-45)/5.0f);
			}
			if(currentTime>=50&&currentTime<55){
				ims->GetSound("Battle")->SetVolumn(0);
			}
			if(currentTime>=55&&currentTime<60){
				ims->GetSound("All")->SetVolumn(1.0f-(sound->GetCurrentTime()-55)/5.0f);
				ims->GetSound("Base")->SetVolumn((sound->GetCurrentTime()-55)/5.0f);
			}
		}else if(this->test==5){
			sound = ims->GetSound("Base");

			if(currentTime>=30&&currentTime<33){
				ims->GetSound("Tamborine")->SetVolumn((sound->GetCurrentTime()-30)/3.0f);
			}
			if(currentTime>=33&&currentTime<35){
				ims->GetSound("Drum")->SetVolumn((sound->GetCurrentTime()-33)/2.0f);
			}
			if(currentTime>=60&&currentTime<63){
				ims->GetSound("Drum")->SetVolumn(1.0f-(sound->GetCurrentTime()-60)/3.0f);
			}
			if(currentTime>=63&&currentTime<65){
				ims->GetSound("Tamborine")->SetVolumn(1.0f-(sound->GetCurrentTime()-63)/2.0f);
			}
			if(currentTime>=120&&currentTime<123){
				ims->GetSound("Tamborine")->SetVolumn((sound->GetCurrentTime()-120)/3.0f);
			}
			if(currentTime>=123&&currentTime<125){
				ims->GetSound("Drum")->SetVolumn((sound->GetCurrentTime()-123)/2.0f);
			}
			if(currentTime>=145&&currentTime<158){
				ims->GetSound("Drum")->SetVolumn(1.0f-(sound->GetCurrentTime()-145)/3.0f);
			}
			if(currentTime>=148&&currentTime<150){
				ims->GetSound("Tamborine")->SetVolumn(1.0f-(sound->GetCurrentTime()-148)/2.0f);
			}
		}
		if(sound&&sound->IsPlaying()&&this->cooldown--<=0){
			this->currentTime = sound->GetCurrentTime();
			this->totalTime = sound->GetTimeLength();
			this->cooldown=10;
		}
		ims->Update();
		if(input->IsKeyDown(SDL_SCANCODE_R)){
			ims->Stop();
			this->GetGame()->EnterScene(this);
		}
	}
	this->gui->Update(input);
}