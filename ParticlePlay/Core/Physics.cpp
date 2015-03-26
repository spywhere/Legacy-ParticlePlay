#include "Physics.hpp"

ppPhysics::ppPhysics(float gx, float gy){
	this->ptm = 30;
	b2Vec2 gravity;
	gravity.Set(gx, gy);
	this->world = new b2World(gravity);
	this->world->SetWarmStarting(true);
	this->world->SetAutoClearForces(true);
}

void ppPhysics::SetPTM(float ptm){
	this->ptm = ptm;
}

float ppPhysics::GetPTM(){
	return this->ptm;
}

float ppPhysics::PixelToWorld(float pixel){
	return pixel/this->ptm;
}

float ppPhysics::WorldToPixel(float world){
	return world*this->ptm;
}

b2World* ppPhysics::GetWorld(){
	return this->world;
}

void ppPhysics::Update(int delta){
	this->world->Step(delta/1000.0f, 3, 8);
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
