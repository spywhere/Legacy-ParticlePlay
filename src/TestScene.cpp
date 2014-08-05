#include "TestScene.hpp"

#include <iostream>
#include <sstream>
#include "ParticlePlay/GUI/Controls.hpp"

void TestScene::OnInit(){
	this->gui = new ppGUI();
	this->gui->AddControl(new ppLabel("text", 10, 50));
	this->posx = 10;
	this->posy = 10;
	this->SetNeedInit(true);

	this->loading = true;
	this->percent = 0;

	SDL_Thread *thread = SDL_CreateThread(TestScene::RunLoader, "TestThread", this);
	SDL_DetachThread(thread);
}

int TestScene::RunLoader(void* data){
	TestScene* scene = static_cast<TestScene*>(data);
	while(++scene->percent<100){
		SDL_Delay(50);
	}
	scene->loading = false;
	return 0;
}

void TestScene::OnRender(SDL_Renderer* renderer, int delta){
	std::stringstream ss;
	ss << "FPS: " << this->GetGame()->GetFPS() << " [" << this->GetGame()->GetAvgRenderTime() << "ms]\n";
	ss << "UPS: " << this->GetGame()->GetUPS() << " [" << this->GetGame()->GetAvgUpdateTime() << "ms]\n";
	if(this->gui->GetDefaultFont()){
		this->gui->GetDefaultFont()->Render(10, 10, ss.str().c_str(), renderer);
	}

	if(this->loading){
		this->gui->GetDefaultFont()->Render(100, 180, "Loading...", renderer);
		glBegin(GL_QUADS);
			glColor3f(1, 1, 1);
			glVertex3f(100, 200, 0);
			glVertex3f(100+300, 200, 0);
			glVertex3f(100+300, 200+20, 0);
			glVertex3f(100, 200+20, 0);
		glEnd();
		glBegin(GL_QUADS);
			glColor3f(0.5f, 0.5f, 1);
			glVertex3f(100, 200, 0);
			glVertex3f(100+(this->percent*300/100), 200, 0);
			glVertex3f(100+(this->percent*300/100), 200+20, 0);
			glVertex3f(100, 200+20, 0);
		glEnd();
		return;
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
		this->GetGame()->EnterState(this);
	}
	this->gui->Update(input);
}
