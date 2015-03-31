#include "GameState.hpp"

#include <sstream>

void GameState::OnInit(){
	this->gui = new ppGUI();
	this->physics = new ppPhysics(0, 50);
	this->physics->SetPTM(10);
	this->level = new Level(this->physics);
	this->player = new kPlayer(this->physics, 575, 360);
	this->bee = new Bee(this->physics, 0, 300);
	this->physics->SetPTM(15);
	this->tx = 0;
	this->ty = -350;
	this->debugView = 0;
	this->revealTime = 0;

	this->background = new ppImage("tmpres/Kameleon/Assets/Image 2306.jpg");
}

void GameState::OnRender(SDL_Renderer* renderer, int delta){
	this->background->Render(renderer, ((-this->player->GetX()+600)*98/4000)-60, 0, 738, 480);
	glPushMatrix();
	glTranslatef(this->tx+320, this->ty, 0);
	this->level->Render(renderer);
	this->bee->Render(renderer);
	this->player->Render(renderer);
	this->level->RenderMask(renderer);
	glPopMatrix();

	if(this->debugView != 0){
		std::stringstream ss;
		ss << "Translate: " << this->tx << ", " << this->ty << "\n";
		ss << "Zoom Factor: " << this->physics->GetPTM() << "\n";
		ss << "Background: " << ((-this->player->GetX()+600)*98/4000-49) << "\n";
		ss << "Water Level: " << (int(this->player->GetWaterLevel()*1000)/1000.0f) << "\n";
		ss << "Player: " << this->player->GetX() << ", " << this->player->GetY() << "\n";
		ss << "Tracking: " << (10/this->bee->GetTrackingLength());
		if(this->gui->GetDefaultFont()){
			glColor3f(1 ,1 ,1);
			this->gui->GetDefaultFont()->Render(10, 35, ss.str().c_str(), renderer);
		}
	}
	this->gui->Render(renderer);
}

void GameState::OnUpdate(ppInput* input, int delta){
	ppIMS* ims = input->GetGame()->GetInteractiveMusicSystem();
	this->gui->Update(input);
	this->physics->Update(delta);
	this->level->SetDebugView(this->debugView != 0);
	this->player->SetDebugView(this->debugView != 0);
	this->bee->SetDebugView(this->debugView != 0);
	this->level->Update(input);
	this->player->Update(input, delta);
	this->bee->Update(input, delta);

	if(this->revealTime > SDL_GetTicks()){
		this->level->Reveal(this->revealTime - SDL_GetTicks());
	}else if(this->player->GetX() < 490 && this->revealTime == 0){
		this->revealTime = SDL_GetTicks() + 3000;
		this->bee->StartTracking();
		ims->GetSound("bee")->Stop();
		ims->GetSound("bee")->Play();
		ims->GetSwitch("level")->SwitchState("main_normal");
	}

	if(this->debugView > 1){
		int scrolly = input->GetScrollY();
		if(scrolly!=0){
			this->physics->SetPTM(this->physics->GetPTM()+scrolly);
			if(this->physics->GetPTM()<1){
				this->physics->SetPTM(1);
			}
		}
		if(input->IsMouseDown(SDL_BUTTON_RIGHT)){
			this->tx += input->GetDeltaMouseX();
			this->ty += input->GetDeltaMouseY();
		}
		if(input->IsMouseDown(SDL_BUTTON_MIDDLE)){
			this->bee->SetTracking(b2Vec2(this->physics->PixelToWorld(input->GetMouseX()), this->physics->PixelToWorld(input->GetMouseY()))-b2Vec2(this->physics->PixelToWorld(this->tx+320), this->physics->PixelToWorld(this->ty)));
		}
	}else{
		this->physics->SetPTM(15);
		this->tx = -this->player->GetX();
		this->ty = -this->player->GetY() + 240;
		this->bee->SetTracking(b2Vec2(this->physics->PixelToWorld(this->player->GetX()), this->physics->PixelToWorld(this->player->GetY())));
	}

	if(ims->GetRTPC("water_rtpc")){
		ims->GetRTPC("water_rtpc")->SetOffset(this->player->GetWaterLevel());
	}
	if(ims->GetRTPC("tracking_rtpc")){
		ims->GetRTPC("tracking_rtpc")->SetOffset(fminf(1, 10/this->bee->GetTrackingLength()));
	}
}

void GameState::SetDebugView(int debugView){
	this->debugView = debugView;
}
