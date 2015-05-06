#include "GameState.hpp"

#include <sstream>

class kContactListener : public b2ContactListener {
protected:
	GameState* game;
public:
	kContactListener(GameState* game) : b2ContactListener(){
		this->game = game;
	};

	void BeginContact(b2Contact* contact){
		if(!this->game->bee->body){
			return;
		}
		b2Body* bodyA = contact->GetFixtureA()->GetBody();
		b2Body* bodyB = contact->GetFixtureB()->GetBody();
		if((bodyA == this->game->bee->body && bodyB == this->game->player->boxBody) || (bodyA == this->game->player->boxBody && bodyB == this->game->bee->body)){
			b2Vec2 deltaPoint = this->game->bee->body->GetPosition()-this->game->player->boxBody->GetPosition();
			this->game->bee->body->ApplyForce(12500.0f*this->game->bee->body->GetWorldVector(deltaPoint), this->game->bee->body->GetWorldPoint(b2Vec2(0, 0)), true);
			this->game->player->boxBody->ApplyForce(-this->game->player->boxBody->GetWorldVector(deltaPoint), this->game->player->boxBody->GetWorldPoint(b2Vec2(0, 0)), true);
			this->game->bee->Attack();
			this->game->player->Attack();
		}
	};
};

void GameState::OnInit(){
	this->gui = new ppGUI();
	this->physics = new ppPhysics(0, 50);
	this->physics->SetPTM(10);
	this->level = new Level(this->physics);
	this->player = new kPlayer(this->physics, 575, 360);
	this->bee = new Bee(this->physics, 0, 300);
	this->physics->SetPTM(15);
	this->physics->GetWorld()->SetContactListener(new kContactListener(this));
	this->tx = 0;
	this->ty = -350;
	this->debugView = 0;
	this->revealTime = 0;
	this->triggerHeroic = false;

	this->background = new ppImage("tmpres/Kameleon/Assets/Image 2306.jpg");
}

void GameState::OnRender(SDL_Renderer* renderer, int delta){
	this->background->Render(renderer, ((-this->player->GetX()+600)*98/4000)-60, 0, 900, 585);
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
		ss << "Tracking: " << (10/this->bee->GetTrackingLength()) << "\n";
		ss << "Health: " << this->player->GetHealth() << " - " << this->bee->GetHealth();
		if(this->gui->GetDefaultFont()){
			glColor3f(1 ,1 ,1);
			this->gui->GetDefaultFont()->Render(10, 35, ss.str().c_str(), renderer);
		}
	}else if(this->level->GetReveal() > 0 && this->bee->GetHealth() > 0){
		glEnable(GL_BLEND);
	    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4f(0.25f, 0.25f, 0.25f, 1-this->level->GetReveal());
		glBegin(GL_QUADS);
			glVertex2f(20, 50);
			glVertex2f(170, 50);
			glVertex2f(170, 70);
			glVertex2f(20, 70);
		glEnd();
		glColor4f(0.5f, 0.5f, 1, 1-this->level->GetReveal());
		glBegin(GL_QUADS);
			glVertex2f(20, 50);
			glVertex2f(20+(this->player->GetHealth()*1.5f), 50);
			glVertex2f(20+(this->player->GetHealth()*1.5f), 70);
			glVertex2f(20, 70);
		glEnd();

		glColor4f(0.25f, 0.25f, 0.25f, 1-this->level->GetReveal());
		glBegin(GL_QUADS);
			glVertex2f(470, 50);
			glVertex2f(620, 50);
			glVertex2f(620, 70);
			glVertex2f(470, 70);
		glEnd();
		glColor4f(1, 0.5f, 0.5f, 1-this->level->GetReveal());
		glBegin(GL_QUADS);
			glVertex2f(470, 50);
			glVertex2f(470+(this->bee->GetHealth()*1.5f), 50);
			glVertex2f(470+(this->bee->GetHealth()*1.5f), 70);
			glVertex2f(470, 70);
		glEnd();
		glDisable(GL_BLEND);
	}
	this->gui->Render(renderer);
}

void GameState::OnUpdate(ppInput* input, int delta){
	ppIMS* ims = input->GetGame()->GetInteractiveMusicSystem();
	if(!ims || !ims->GetSwitch("level")){
		return;
	}
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

	if(this->bee->GetHealth() <= 0 && !ims->GetSwitch("level")->IsTransitioning() && ims->GetSwitch("level")->GetCurrentState() != ""){
		ims->GetSound("bee")->Stop();
		if(!ims->GetSwitch("level")->IsTransitioning() && !ims->GetSwitch("level")->GetStinger("heroic")->IsTriggering()){
			ims->GetSwitch("level")->SwitchState("");
		}
	}

	if(this->player->GetHealth() < 25 && ims->GetSwitch("level")->GetCurrentState() == "main_normal"){
		ims->GetSwitch("level")->SwitchState("main_low");
	}else if(this->player->GetHealth() > 25 && ims->GetSwitch("level")->GetCurrentState() == "main_low"){
		ims->GetSwitch("level")->SwitchState("main_normal");
	}
	if(!this->triggerHeroic && this->bee->GetHealth() < 35 && this->level->GetReveal() < 0.1f && !ims->GetSwitch("level")->IsTransitioning()){
		ims->GetSwitch("level")->TriggerStinger("heroic");
	}
	this->triggerHeroic = this->triggerHeroic || ims->GetSwitch("level")->GetStinger("heroic")->IsTriggering();

	if(input->IsKeyDown(SDL_SCANCODE_SPACE, 30) && this->level->GetReveal() < 0.1f){
		this->bee->Attack();
		this->bee->Attack();
	}

	if(this->debugView > 1 && this->debugView < 4){
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
		this->bee->SetTracking(b2Vec2(this->physics->PixelToWorld(this->player->GetX()), this->physics->PixelToWorld(fminf(500, this->player->GetY()))));
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
