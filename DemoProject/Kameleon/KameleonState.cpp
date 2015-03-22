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
		if(this->ims->GetSound("level")){

		}else{

		}
	}

	if(input->IsKeyDown(SDL_SCANCODE_R)){
		this->ims->ClearSound();
		this->ims->ClearSwitch();
		this->GetGame()->EnterState("ims");
	}
}
