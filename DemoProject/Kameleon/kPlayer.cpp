#include "kPlayer.hpp"

kPlayer::kPlayer(ppPhysics* physics, int x, int y) : PhysicsObject(physics) {
	b2BodyDef* myBodyDef = new b2BodyDef();
	myBodyDef->type = b2_dynamicBody;
	myBodyDef->position.Set(this->physics->PixelToWorld(x), this->physics->PixelToWorld(y)+1);
	myBodyDef->angle = 0;
	myBodyDef->angularVelocity = 2;
	this->circleBody = this->physics->GetWorld()->CreateBody(myBodyDef);

	myBodyDef->type = b2_dynamicBody;
	myBodyDef->position.Set(this->physics->PixelToWorld(x), this->physics->PixelToWorld(y));
	myBodyDef->fixedRotation = true;
	myBodyDef->angularVelocity = 0;
	this->boxBody = this->physics->GetWorld()->CreateBody(myBodyDef);

	b2CircleShape circleShape;
	circleShape.m_radius = 1;

	this->circleBody->CreateFixture(&circleShape, 1.0f);

	b2PolygonShape boxShape;
	boxShape.SetAsBox(1, 1);

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
}

void kPlayer::Render(SDL_Renderer* renderer){
	this->RenderBody(this->boxBody);
	this->RenderBody(this->circleBody);
}

void kPlayer::Update(ppInput* input){

}
