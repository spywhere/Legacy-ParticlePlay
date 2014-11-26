#include "Chicken.hpp"

#include <iostream>
#include <cmath>

const double PI = std::acos(-1);

Chicken::Chicken(Spritesheet* spritesheet, int startX, int startY) : Entity(spritesheet, startX, startY){
	this->spritesheet = new Spritesheet(spritesheet->GetSheet(), 16, 16, 3.5f);
	this->angle = 180;
}

void Chicken::Render(SDL_Renderer* renderer){
	int xTile = 0;
	SDL_RendererFlip flip = ppImage::NO_FLIP;
	int offsetY = 0;
	if(this->GetDirection() > 0){
		if(this->GetDirection() == 2){
			flip = (SDL_RendererFlip)(flip | ppImage::FLIP_HORIZONTAL);
		}
		if((this->GetPositionX()+this->GetPositionY())%25 > 12){
			xTile += 1;
			offsetY += 3;
		}
	}else{
		xTile = 2;
		if((this->GetPositionX()+this->GetPositionY())%25 > 12){
			xTile += 1;
		}
	}

	Tile *entityTile = this->spritesheet->GetTile(xTile, 14);
	if(this->inWater){
		entityTile->SetClip(1.0f, 0.5f);
		offsetY += 20;
	}
	entityTile->Render(renderer, this->GetPositionX()-entityTile->GetWidth()/2, offsetY+this->GetPositionY()-entityTile->GetHeight()/2, flip);
}

void Chicken::Update(ppInput* input, int delta){
	Entity::Update(input, delta);
	ppRandomizer* randomizer = input->GetGame()->GetRandomizer();
	if(randomizer->NextInt(1000) < 1){
		ppGenericSound* sound = input->GetGame()->GetInteractiveMusicSystem()->GetSound(this->soundName);
		if(sound && sound->IsStop()){
			sound->Play();
		}
	}
	this->angle += randomizer->NextInt(-5, 5);
	this->angle %= 360;
	if(this->GetPositionY() < 20 && std::cos(this->angle/180.0f*PI) < 0){
		this->angle += 180;
	}else if(this->GetPositionY() >= input->GetGame()->GetHeight()-20 && std::cos(this->angle/180.0f*PI) > 0){
		this->angle += 180;
	}else if(this->GetPositionX() < 20 && std::sin(this->angle/180.0f*PI) < 0){
		this->angle += 180;
	}else if(this->GetPositionX() >= input->GetGame()->GetWidth()-20 && std::sin(this->angle/180.0f*PI) > 0){
		this->angle += 180;
	}
	this->MoveY((int)(std::cos(this->angle/180.0f*PI)*2.0f));
	this->MoveX((int)(std::sin(this->angle/180.0f*PI)*2.0f));
}
