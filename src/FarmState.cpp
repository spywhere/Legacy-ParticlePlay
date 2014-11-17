#include "FarmState.hpp"

#include <sstream>

void FarmState::OnInit(){
	this->gui = new ppGUI();
	this->image = new ppImage("res/image.jpg");
}

void FarmState::OnRender(SDL_Renderer* renderer, int delta){
	std::stringstream ss;
	ss << "FPS: " << this->GetGame()->GetFPS() << " [" << this->GetGame()->GetAvgRenderTime() << "ms]\n";
	ss << "UPS: " << this->GetGame()->GetUPS() << " [" << this->GetGame()->GetAvgUpdateTime() << "ms]\n";
	if(this->gui->GetDefaultFont()){
		glColor3f(1 ,1 ,1);
		this->gui->GetDefaultFont()->Render(10, 10, ss.str().c_str(), renderer);
	}
	this->gui->Render(renderer);
	if(!this->graphics){
		this->graphics = new ppGraphics(renderer);
	}
	this->image->Render(renderer, 200, 200);
}

void FarmState::OnUpdate(ppInput* input, int delta){
	this->gui->Update(input);
}
