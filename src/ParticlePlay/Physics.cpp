#include "Physics.hpp"

#include <Box2D/Box2D.h>

ppPhysics::ppPhysics(int fps, float gx, float gy){
	this->fps = fps;
	b2Vec2 gravity;
	gravity.Set(gx, gy);
	this->world = new b2World(gravity);
	this->world->SetWarmStarting(true);
	this->world->SetAutoClearForces(true);
}

b2World* ppPhysics::GetWorld(){
	return this->world;
}

void ppPhysics::Update(){
	this->world->Step(1.0f/this->fps, 3, 8);
}

void ppPhysics::UpdateAllBody(){
	for(b2Body* bd=this->world->GetBodyList();bd!=NULL;bd=bd->GetNext()){
		bd->SetAwake(true);
		bd->SetActive(true);
	}
}

ppPhysics::~ppPhysics(){
	delete this->world;
	this->world = NULL;
}
