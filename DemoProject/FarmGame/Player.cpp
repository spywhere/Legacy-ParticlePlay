#include "Player.hpp"

#include "Tile.hpp"

Player::Player(Spritesheet* spritesheet, int startX, int startY) : Entity(spritesheet, startX, startY){
	this->spritesheet = new Spritesheet(spritesheet->GetSheet(), 16, 16, 3.5f);
}

void Player::Render(ppGraphics* graphics){
	int xTile = this->GetDirection() & 1;
	SDL_RendererFlip flip = ppImage::NO_FLIP;
	if((this->GetDirection() >> 1) == 1){
		xTile = 2;
		if(GetDirection() == 3){
			flip = (SDL_RendererFlip)(flip | ppImage::FLIP_HORIZONTAL);
		}
		if(this->GetPositionX()%50 > 25){
			xTile += 1;
		}
	}else if(this->GetPositionY()%70 > 35){
		flip = (SDL_RendererFlip)(flip | ppImage::FLIP_HORIZONTAL);
	}

	Tile *entityTile = this->spritesheet->GetTile(xTile, 15);
	int offsetY = 0;
	if(this->inWater){
		entityTile->SetClip(1.0f, 0.5f);
		offsetY += 20;
	}
	entityTile->Render(graphics, this->GetPositionX()-entityTile->GetWidth()/2, offsetY+this->GetPositionY()-entityTile->GetHeight()/2, flip);
}

void Player::Update(ppInput* input, int delta){
	Entity::Update(input, delta);
	if(input->IsKeyDown(SDL_SCANCODE_W) || input->IsKeyDown(SDL_SCANCODE_UP)){
		this->MoveY(-2);
	}else if(input->IsKeyDown(SDL_SCANCODE_S) || input->IsKeyDown(SDL_SCANCODE_DOWN)){
		this->MoveY(2);
	}else{
		this->MoveY(0);
	}
	if(input->IsKeyDown(SDL_SCANCODE_A) || input->IsKeyDown(SDL_SCANCODE_LEFT)){
		this->MoveX(-2);
	}else if(input->IsKeyDown(SDL_SCANCODE_D) || input->IsKeyDown(SDL_SCANCODE_RIGHT)){
		this->MoveX(2);
	}else{
		this->MoveX(0);
	}
}
