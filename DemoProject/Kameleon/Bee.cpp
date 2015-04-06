#include "Bee.hpp"

#include <iostream>
#include <cmath>
const float TO_RAD = 0.017453f;

Bee::Bee(ppPhysics* physics, int x, int y) : PhysicsObject(physics) {
	this->health = 100;
	this->tracking = false;
	this->trackingPoint = b2Vec2(this->physics->PixelToWorld(x), this->physics->PixelToWorld(y));

	b2BodyDef* myBodyDef = new b2BodyDef();
	myBodyDef->type = b2_dynamicBody;
	myBodyDef->position.Set(this->physics->PixelToWorld(x), this->physics->PixelToWorld(y));
	myBodyDef->fixedRotation = true;
	myBodyDef->angularVelocity = 0;
	myBodyDef->angularDamping = 0;
	myBodyDef->linearDamping = 1;
	myBodyDef->gravityScale = 0;
	this->body = this->physics->GetWorld()->CreateBody(myBodyDef);

	b2PolygonShape boxShape;
	boxShape.SetAsBox(4.5f, 3);

	b2FixtureDef boxFixtureDef;
	boxFixtureDef.shape = &boxShape;
	boxFixtureDef.density = 1;
	this->body->CreateFixture(&boxFixtureDef);

	this->flyPose = new AnimateImage(75);
	this->flyPose->AddImage(new ppImage("tmpres/Kameleon/Assets/Image 2325.png"));
	this->flyPose->AddImage(new ppImage("tmpres/Kameleon/Assets/Image 2328.png"), -20, 48);
	this->flyPose->AddImage(new ppImage("tmpres/Kameleon/Assets/Image 2331.png"), -5, 72);
	this->flyPose->AddImage(new ppImage("tmpres/Kameleon/Assets/Image 2334.png"), -20, 50);
}

void Bee::Render(SDL_Renderer* renderer){
	if(!this->body){
		return;
	}
	if(this->debugView){
		this->RenderBody(this->body);
		glColor4f(1, 1, 1, 1);
		glBegin(GL_LINES);
			glVertex2f(this->physics->WorldToPixel(this->body->GetPosition().x), this->physics->WorldToPixel(this->body->GetPosition().y));
			glVertex2f(this->physics->WorldToPixel(this->trackingPoint.x), this->physics->WorldToPixel(this->trackingPoint.y));
		glEnd();
	}

	glColor4f(1, 1, 1, 1);
	this->flyPose->Render(renderer, this->physics->WorldToPixel(this->body->GetPosition().x)+10, this->physics->WorldToPixel(this->body->GetPosition().y)-75, ppImage::NO_FLIP);
}

void Bee::Update(ppInput* input, int delta){
	if(!this->body){
		return;
	}
	if(this->health < 0){
		this->physics->GetWorld()->DestroyBody(this->body);
		this->body = NULL;
		this->health = 0;
		return;
	}
	ppRandomizer* randomizer = input->GetGame()->GetRandomizer();
	this->flyPose->Update(delta);

	if(this->tracking){
		if(this->health < 100){
			this->health += 0.025f;
		}
		b2Vec2 deltaPoint = this->trackingPoint-this->body->GetPosition();

		float angle = std::atan2(deltaPoint.y, deltaPoint.x);
		angle += randomizer->NextFloat(-25*TO_RAD, 25*TO_RAD);
		b2Vec2 trackingForce = b2Vec2(std::cos(angle), std::sin(angle));
		trackingForce *= fminf(550, deltaPoint.Length()*550);

		this->body->ApplyForce(this->body->GetWorldVector(trackingForce), this->body->GetWorldPoint(b2Vec2(0, 0)), true);
	}
}

void Bee::Attack(){
	if(!this->body || this->health <= 0){
		return;
	}
	this->health -= 10;
}

void Bee::SetTracking(b2Vec2 point){
	this->trackingPoint = point;
}

void Bee::StartTracking(){
	this->tracking = true;
}

float Bee::GetTrackingLength(){
	if(this->health <= 0){
		return 0;
	}
	return (this->trackingPoint-this->body->GetPosition()).Length();
}

float Bee::GetHealth(){
	return this->health;
}
