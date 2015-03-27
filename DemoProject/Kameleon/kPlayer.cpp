#include "kPlayer.hpp"

kPlayer::kPlayer(ppPhysics* physics, int x, int y) : PhysicsObject(physics) {
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
	glColor3f(1, 1, 1);
	glBegin(GL_LINES);
		glVertex3f(this->physics->WorldToPixel(this->circleBody->GetPosition().x-1), this->physics->WorldToPixel(this->circleBody->GetPosition().y+1), 0);
		glVertex3f(this->physics->WorldToPixel(this->circleBody->GetPosition().x+1), this->physics->WorldToPixel(this->circleBody->GetPosition().y+1), 0);
	glEnd();

	glColor3f(1, 1, 1);
	glBegin(GL_LINES);
		glVertex3f(this->physics->WorldToPixel(this->circleBody->GetPosition().x-1), this->physics->WorldToPixel(40), 0);
		glVertex3f(this->physics->WorldToPixel(this->circleBody->GetPosition().x+1), this->physics->WorldToPixel(40), 0);
	glEnd();
}

void kPlayer::Update(ppInput* input){
	b2Vec2 vel = this->boxBody->GetLinearVelocity();
	if(this->circleBody->GetPosition().y+1 > 40 && vel.y > 0){
		vel.y -= 1;
	}
	if(input->IsKeyDown(SDL_SCANCODE_W)){
		if(vel.y > -0.01f && vel.y < 0.01f){
			vel.y = -55;
		}else if(this->circleBody->GetPosition().y+1 > 40){
			vel.y = -15;
		}
	}
	if(input->IsKeyDown(SDL_SCANCODE_A)){
		if(this->boxBody->GetLinearVelocity().x > -10){
			vel.x -= 15;
		}
	}else if(input->IsKeyDown(SDL_SCANCODE_D)){
		if(this->boxBody->GetLinearVelocity().x < 10){
			vel.x += 15;
		}
	}else{
		vel.x = 0;
	}
	this->boxBody->SetLinearVelocity(vel);
}
