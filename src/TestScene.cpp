#include "TestScene.h"

#include <iostream>
#include <sstream>
#include "ParticlePlay/GUI/Controls.h"
#include "ParticlePlay/GUI/GUIType.h"

void TestScene::OnInit(){
	this->gui = new ppGUI();
	this->gui->AddControl("text", new ppLabel(10, 50));
	this->posx = 10;
	this->posy = 10;
	this->SetNeedInit(true);
}

void TestScene::OnRender(SDL_Renderer* renderer, int delta){
	std::stringstream ss;
	ss << "FPS: " << this->GetGame()->GetFPS() << " [" << this->GetGame()->GetAvgRenderTime() << "ms]\n";
	ss << "UPS: " << this->GetGame()->GetUPS() << " [" << this->GetGame()->GetAvgUpdateTime() << "ms]\n";
	if(this->gui->GetDefaultFont()){
		this->gui->GetDefaultFont()->Render(10, 10, ss.str().c_str(), renderer);
	}

	glBegin(GL_QUADS);
	glColor3f(1, 0, 0); glVertex3f(this->posx, this->posy, 0);
	glColor3f(1, 1, 0); glVertex3f(this->posx+100, this->posy, 0);
	glColor3f(1, 0, 1); glVertex3f(this->posx+100, this->posy+100, 0);
	glColor3f(1, 1, 1); glVertex3f(this->posx, this->posy+100, 0);
	glEnd();

	SDL_Rect* rect = new SDL_Rect;
	rect->x = this->posx+40;
	rect->y = this->posy+40;
	rect->w = 20;
	rect->h = 20;
	this->gui->Render(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, rect);
}

void TestScene::OnUpdate(ppInput* input, int delta){
	if(input->IsKeyDown(SDL_SCANCODE_A)){
		this->posx -= 5;
	}else if(input->IsKeyDown(SDL_SCANCODE_D)){
		this->posx += 5;
	}
	if(input->IsKeyDown(SDL_SCANCODE_W)){
		this->posy -= 5;
	}else if(input->IsKeyDown(SDL_SCANCODE_S)){
		this->posy += 5;
	}
	if(input->IsKeyDown(SDLK_RETURN)){
		this->GetGame()->EnterScene(this);
	}
	this->gui->Update(input);
}