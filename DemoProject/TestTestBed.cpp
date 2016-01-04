#include "TestTestbed.hpp"

#include <iostream>
#include <sstream>

void TestTestbed::OnInit(){
	ppTestBed::OnInit();
	b2BodyDef* myBodyDef = new b2BodyDef();

	myBodyDef->type = b2_staticBody;
	myBodyDef->position.Set(0, this->physics->PixelToWorld(470));
	b2Body* groundBody = this->physics->GetWorld()->CreateBody(myBodyDef);

	myBodyDef->type = b2_dynamicBody;
	myBodyDef->position.Set(this->physics->PixelToWorld(280), 0);
	myBodyDef->angle = 0;
	b2Body* circleBody = this->physics->GetWorld()->CreateBody(myBodyDef);

	myBodyDef->type = b2_dynamicBody;
	myBodyDef->position.Set(this->physics->PixelToWorld(320), 3);
	myBodyDef->angle = 0;
	b2Body* boxBody = this->physics->GetWorld()->CreateBody(myBodyDef);

	b2EdgeShape edgeShape;
	b2Vec2 l(0,0), r(this->physics->PixelToWorld(this->GetGame()->GetWidth()),0);
	edgeShape.Set(l, r);

	groundBody->CreateFixture(&edgeShape, 1.0f);

	b2CircleShape circleShape;
	circleShape.m_radius = 1;

	circleBody->CreateFixture(&circleShape, 1.0f);

	b2PolygonShape boxShape;
	boxShape.SetAsBox(1,1);

	b2FixtureDef boxFixtureDef;
	boxFixtureDef.shape = &boxShape;
	boxFixtureDef.density = 1;
	boxBody->CreateFixture(&boxFixtureDef);
}

void TestTestbed::OnRender(ppGraphics* graphics, int delta){
	ppTestBed::OnRender(graphics, delta);
}

void TestTestbed::OnUpdate(ppInput* input, int delta){
	ppTestBed::OnUpdate(input, delta);
}
