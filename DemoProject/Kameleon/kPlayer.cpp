#include "kPlayer.hpp"

kPlayer::kPlayer(ppGame* game, ppPhysics* physics, int x, int y) : PhysicsObject(physics) {
	this->game = game;
	b2BodyDef* myBodyDef = new b2BodyDef();
	myBodyDef->type = b2_dynamicBody;
	myBodyDef->position.Set(this->physics->PixelToWorld(x), this->physics->PixelToWorld(y)+1);
	myBodyDef->angle = 0;
	myBodyDef->angularVelocity = 2;
	myBodyDef->angularDamping = 2;
	this->circleBody = this->physics->GetWorld()->CreateBody(myBodyDef);

	myBodyDef->type = b2_dynamicBody;
	myBodyDef->position.Set(this->physics->PixelToWorld(x), this->physics->PixelToWorld(y));
	myBodyDef->fixedRotation = true;
	myBodyDef->angularVelocity = 0;
	myBodyDef->angularDamping = 0;
	this->boxBody = this->physics->GetWorld()->CreateBody(myBodyDef);

	b2CircleShape circleShape;
	circleShape.m_radius = 1;

	this->circleBody->CreateFixture(&circleShape, 1.0f);

	b2PolygonShape boxShape;
	boxShape.SetAsBox(1, 0.5f);

	b2FixtureDef boxFixtureDef;
	boxFixtureDef.shape = &boxShape;
	boxFixtureDef.density = 1;
	this->boxBody->CreateFixture(&boxFixtureDef);

	b2RevoluteJointDef* joint = new b2RevoluteJointDef();
	joint->bodyA = this->boxBody;
	joint->bodyB = this->circleBody;
	joint->collideConnected = false;
	joint->referenceAngle = 0;
	joint->localAnchorA.Set(0, 1);
	joint->localAnchorB.Set(0, 0);
	this->physics->GetWorld()->CreateJoint(joint);

	this->playerFlip = ppImage::NO_FLIP;

	this->idlePose = new AnimateImage(400);
	this->idlePose->AddImage(new ppImage("tmpres/Kameleon/Assets/Image 303.png"), 0, -1);
	this->idlePose->AddImage(new ppImage("tmpres/Kameleon/Assets/Image 305.png"), 1, 0);
	this->idlePose->AddImage(new ppImage("tmpres/Kameleon/Assets/Image 307.png"), 0, -1);
	this->idlePose->AddImage(new ppImage("tmpres/Kameleon/Assets/Image 309.png"), 0, -1);
	this->idlePose->AddImage(new ppImage("tmpres/Kameleon/Assets/Image 311.png"), 1, 1);
	this->idlePose->AddImage(new ppImage("tmpres/Kameleon/Assets/Image 313.png"));

	this->runPose = new AnimateImage(100);
	this->runPose->AddImage(new ppImage("tmpres/Kameleon/Assets/Image 315.png"), 0, 5);
	this->runPose->AddImage(new ppImage("tmpres/Kameleon/Assets/Image 317.png"), 0, 5);
	this->runPose->AddImage(new ppImage("tmpres/Kameleon/Assets/Image 319.png"), 0, 5);
	this->runPose->AddImage(new ppImage("tmpres/Kameleon/Assets/Image 321.png"), 0, 5);
	this->runPose->AddImage(new ppImage("tmpres/Kameleon/Assets/Image 323.png"), 0, 5);
	this->runPose->AddImage(new ppImage("tmpres/Kameleon/Assets/Image 325.png"), 0, 5);

	this->swimPose = new AnimateImage(150);
	this->swimPose->AddImage(new ppImage("tmpres/Kameleon/Assets/Image 343.png"), 0, 15);
	this->swimPose->AddImage(new ppImage("tmpres/Kameleon/Assets/Image 345.png"), 0, 15);
	this->swimPose->AddImage(new ppImage("tmpres/Kameleon/Assets/Image 347.png"), 0, 15);
	this->swimPose->AddImage(new ppImage("tmpres/Kameleon/Assets/Image 349.png"), 2, 17);

	this->jumpPose = new AnimateImage(-1);
	this->jumpPose->AddImage(new ppImage("tmpres/Kameleon/Assets/Image 359.png"), 0, -5);
	this->jumpPose->AddImage(new ppImage("tmpres/Kameleon/Assets/Image 369.png"), 0, -3);
	this->jumpPose->AddImage(new ppImage("tmpres/Kameleon/Assets/Image 371.png"), 0, -2);
	this->jumpPose->AddImage(new ppImage("tmpres/Kameleon/Assets/Image 373.png"));

	this->fallPose = new AnimateImage(100);
	this->fallPose->AddImage(new ppImage("tmpres/Kameleon/Assets/Image 375.png"), 0, -5);
	this->fallPose->AddImage(new ppImage("tmpres/Kameleon/Assets/Image 377.png"), 0, -5);

	this->currentPose = this->idlePose;
}

void kPlayer::Render(SDL_Renderer* renderer){
	if(this->debugView){
		this->RenderBody(this->boxBody);
		this->RenderBody(this->circleBody);
		glColor3f(1, 1, 1);
		glBegin(GL_LINES);
			glVertex3f(this->physics->WorldToPixel(this->circleBody->GetPosition().x-1), this->physics->WorldToPixel(this->circleBody->GetPosition().y+1), 0);
			glVertex3f(this->physics->WorldToPixel(this->circleBody->GetPosition().x+1), this->physics->WorldToPixel(this->circleBody->GetPosition().y+1), 0);
		glEnd();

		glColor3f(1, 1, 1);
		glBegin(GL_LINES);
			glVertex3f(this->physics->WorldToPixel(this->circleBody->GetPosition().x-1), this->physics->WorldToPixel(40.25f), 0);
			glVertex3f(this->physics->WorldToPixel(this->circleBody->GetPosition().x+1), this->physics->WorldToPixel(40.25f), 0);
		glEnd();
	}

	glColor3f(1, 1, 1);
	this->currentPose->Render(renderer, this->physics->WorldToPixel(this->circleBody->GetPosition().x), this->physics->WorldToPixel(this->circleBody->GetPosition().y), this->playerFlip);
}

float kPlayer::GetWaterLevel(){
	if(this->circleBody->GetPosition().y+1 > 40.25f){
		return (this->circleBody->GetPosition().y+1-40.25f)/10;
	}
	return 0;
}

int kPlayer::GetX(){
	return this->physics->WorldToPixel(this->circleBody->GetPosition().x);
}

int kPlayer::GetY(){
	return this->physics->WorldToPixel(this->circleBody->GetPosition().y);
}

void kPlayer::Update(ppInput* input, int delta){
	ppIMS* ims = this->game->GetInteractiveMusicSystem();
	b2Vec2 vel = this->circleBody->GetLinearVelocity();
	if(vel.x < 0){
		this->playerFlip = ppImage::FLIP_HORIZONTAL;
	}else if(vel.x > 0){
		this->playerFlip = ppImage::NO_FLIP;
	}

	ims->GetSound("heal")->SetVolume(this->GetWaterLevel());

	if(this->circleBody->GetPosition().y+1 <= 40.25f && this->currentPose == this->swimPose){
		ims->GetSound("out_water")->Stop();
		ims->GetSound("out_water")->Play();
		ims->GetSound("heal")->Stop();
	}

	if(this->circleBody->GetPosition().y+1 > 40.25f){
		if(this->currentPose != this->swimPose){
			ims->GetSound("splash")->Stop();
			ims->GetSound("splash")->Play();
			ims->GetSound("heal")->Play();
		}
		this->currentPose = this->swimPose;
	}else if(vel.x < 0.15f && vel.x > -0.15f && vel.y < 0.15f && vel.y > -0.15f){
		if(this->currentPose == this->fallPose){
			ims->GetSound("thub")->Stop();
			ims->GetSound("thub")->Play();
		}
		this->currentPose = this->idlePose;
	}else if(vel.x != 0 && vel.y < 0.15f && vel.y > -0.15f){
		if(this->currentPose == this->fallPose){
			ims->GetSound("thub")->Stop();
			ims->GetSound("thub")->Play();
		}
		this->currentPose = this->runPose;
	}else if(vel.y < -10){
		this->jumpPose->SetCurrentFrame(0);
		this->currentPose = this->jumpPose;
	}else if(vel.y < 0){
		this->jumpPose->SetCurrentFrame(2);
		this->currentPose = this->jumpPose;
	}else if(vel.y > 15){
		this->currentPose = this->fallPose;
	}else if(vel.y > 10){
		this->jumpPose->SetCurrentFrame(3);
		this->currentPose = this->jumpPose;
	}else if(vel.y > 0){
		this->jumpPose->SetCurrentFrame(1);
		this->currentPose = this->jumpPose;
	}

	if(this->circleBody->GetPosition().y+1 > 40.25f && vel.y > 0){
		vel.y -= 1;
	}
	if(input->IsKeyDown(SDL_SCANCODE_W) || input->IsKeyDown(SDL_SCANCODE_UP)){
		if(this->circleBody->GetPosition().y+1 > 40.25f){
			if(vel.y > -15){
				vel.y -= 2.5f;
			}
		}else if(vel.y > -0.01f && vel.y < 0.01f){
			ims->GetSound("jump")->Stop();
			ims->GetSound("jump")->Play();
			vel.y = -50;
		}
	}
	if(input->IsKeyDown(SDL_SCANCODE_A) || input->IsKeyDown(SDL_SCANCODE_LEFT)){
		if(this->circleBody->GetPosition().y+1 > 40.25f){
			vel.x = -12;
		}else{
			vel.x = -15;
		}
	}else if(input->IsKeyDown(SDL_SCANCODE_D) || input->IsKeyDown(SDL_SCANCODE_RIGHT)){
		if(this->circleBody->GetPosition().y+1 > 40.25f){
			vel.x = 12;
		}else{
			vel.x = 15;
		}
	}else{
		vel.x = 0;
	}
	this->circleBody->SetLinearVelocity(vel);

	this->idlePose->Update(delta);
	this->runPose->Update(delta);
	this->swimPose->Update(delta);
	this->jumpPose->Update(delta);
	this->fallPose->Update(delta);
}
