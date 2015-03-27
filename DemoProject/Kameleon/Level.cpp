#include "Level.hpp"

Level::Level(ppPhysics* physics) : PhysicsObject(physics){
	b2BodyDef* myBodyDef = new b2BodyDef();

	myBodyDef->type = b2_staticBody;
	myBodyDef->position.Set(this->physics->PixelToWorld(0), this->physics->PixelToWorld(0));
	this->body = this->physics->GetWorld()->CreateBody(myBodyDef);

	b2ChainShape* chainShape = new b2ChainShape();
	b2Vec2 vs[50];
	int index=0;
    vs[index++].Set(this->physics->PixelToWorld(650), this->physics->PixelToWorld(20));
    vs[index++].Set(this->physics->PixelToWorld(650), this->physics->PixelToWorld(400));
    vs[index++].Set(this->physics->PixelToWorld(350), this->physics->PixelToWorld(400));
    vs[index++].Set(this->physics->PixelToWorld(350), this->physics->PixelToWorld(325));
    vs[index++].Set(this->physics->PixelToWorld(300), this->physics->PixelToWorld(325));
    vs[index++].Set(this->physics->PixelToWorld(300), this->physics->PixelToWorld(400));
    vs[index++].Set(this->physics->PixelToWorld(150), this->physics->PixelToWorld(400));
    vs[index++].Set(this->physics->PixelToWorld(150), this->physics->PixelToWorld(500));
    vs[index++].Set(this->physics->PixelToWorld(-150), this->physics->PixelToWorld(500));
    vs[index++].Set(this->physics->PixelToWorld(-150), this->physics->PixelToWorld(400));
    vs[index++].Set(this->physics->PixelToWorld(-400), this->physics->PixelToWorld(400));
    vs[index++].Set(this->physics->PixelToWorld(-400), this->physics->PixelToWorld(20));
    chainShape->CreateChain(vs, index);

	this->body->CreateFixture(chainShape, 1.0f);
}

void Level::Render(SDL_Renderer* renderer){
	this->RenderBody(this->body);
}

void Level::Update(ppInput* input){

}
