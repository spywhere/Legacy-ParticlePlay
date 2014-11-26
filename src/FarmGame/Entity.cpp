#include "Entity.hpp"

Entity::Entity(Spritesheet* spritesheet, int startX, int startY){
	this->spritesheet = new Spritesheet(spritesheet->GetSheet(), 8, 8, 5.0f);
	this->px = startX;
	this->py = startY;
	this->vx = 0;
	this->vy = 0;
	this->direction = 1;
	this->inWater = false;
	this->soundName = NULL;
}

void Entity::MoveX(int vx){
	this->vx = vx;
	if(vx > 0){
		this->direction = 2;
	}else if(vx < 0){
		this->direction = 3;
	}
}

void Entity::MoveY(int vy){
	this->vy = vy;
	if(vy > 0){
		this->direction = 1;
	}else if(vy < 0){
		this->direction = 0;
	}
}

int Entity::GetDirection(){
	return this->direction;
}

int Entity::GetPositionX(){
	return this->px;
}

int Entity::GetPositionY(){
	return this->py;
}

void Entity::SetSound(const char *soundName){
	this->soundName = soundName;
}

bool Entity::IsInside(int x, int y, int width, int height){
	return this->px >= x && this->px <= x+width && this->py >= y && this->py <= y+height;
}

void Entity::Update(ppInput* input, int delta){
	this->px += this->vx;
	this->py += this->vy;
}

void Entity::SetInWater(bool inWater){
	this->inWater = inWater;
}
