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
		SDL_Delay(5);
	}
	scene->loading = false;
	return 0;
}

void TestScene::OnRender(ppGraphics* graphics, int delta){
	std::stringstream ss;
	ss << "FPS: " << this->GetGame()->GetFPS() << " [" << this->GetGame()->GetAvgRenderTime() << "ms]\n";
	ss << "UPS: " << this->GetGame()->GetUPS() << " [" << this->GetGame()->GetAvgUpdateTime() << "ms]\n";
	if(this->gui->GetDefaultFont()){
		this->gui->GetDefaultFont()->Render(10, 10, ss.str().c_str(), graphics);
	}

	if(this->loading){
		this->gui->GetDefaultFont()->Render(100, 180, "Loading...", graphics);
		graphics->SetColor(new ppColor(1.0f, 1.0f, 1.0f));
		graphics->DrawRect(100, 200, 300, 20);
		graphics->SetColor(new ppColor(0.5f, 0.5f, 1.0f));
		graphics->FillRect(100, 200, (this->percent*300/100), 20);
		return;
	}

	graphics->SetColor(new ppColor(1.0f, 0.0f, 0.0f, 1.0f));
	graphics->FillRect(200, 200, 200, 200);

	graphics->SetColor(new ppColor(0.0f, 1.0f, 0.0f, 0.5f));
	graphics->FillRect(300, 300, 200, 200);

	graphics->SetColor(new ppColor(1.0f, 0.0f, 0.0f));
	// graphics->DrawLine(350, 350, 250, 450);
	// graphics->DrawLine(250, 450, 450, 450);
	// graphics->DrawLine(450, 450, 350, 350);
	graphics->FillTriangle(350, 350, 250, 450, 450);

	// glBegin(GL_QUADS);
	// 	glColor3f(1, 0, 0); glVertex3f(this->posx, this->posy, 0);
	// 	glColor3f(1, 1, 0); glVertex3f(this->posx+100, this->posy, 0);
	// 	glColor3f(1, 0, 1); glVertex3f(this->posx+100, this->posy+100, 0);
	// 	glColor3f(1, 1, 1); glVertex3f(this->posx, this->posy+100, 0);
	// glEnd();

	graphics->SetColor(new ppColor(1.0f, 1.0f, 1.0f));
	graphics->FillRect(this->posx+40, this->posy+40, 20, 20);
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
