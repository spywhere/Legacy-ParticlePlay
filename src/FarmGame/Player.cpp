#include "Player.hpp"

Player::Player(Spritesheet* spritesheet, int startX, int startY){
	this->spritesheet = new Spritesheet(spritesheet->GetSheet(), 16, 16, 3.5f);
	this->px = startX;
	this->py = startY;
	this->vx = 0;
	this->vy = 0;
	this->direction = 1;
}

void Player::MoveX(int vx){
	this->vx = vx;
	if(vx > 0){
		this->direction = 2;
	}else if(vx < 0){
		this->direction = 3;
	}
}

void Player::MoveY(int vy){
	this->vy = vy;
	if(vy > 0){
		this->direction = 1;
	}else if(vy < 0){
		this->direction = 0;
	}
}

void Player::Render(SDL_Renderer* renderer){
	int xTile = this->direction & 1;
	SDL_RendererFlip flip = ppImage::NO_FLIP;
	if((this->direction >> 1) == 1){
		xTile = 2;
		if(direction == 3){
			flip = (SDL_RendererFlip)(flip | ppImage::FLIP_HORIZONTAL);
		}
		if(px%50 > 25){
			xTile += 1;
		}
	}else if(py%70 > 35){
		flip = (SDL_RendererFlip)(flip | ppImage::FLIP_HORIZONTAL);
	}

	Tile *playerTile = this->spritesheet->GetTile(xTile, 15);
	playerTile->Render(renderer, this->px-playerTile->GetWidth()/2, this->py-playerTile->GetHeight()/2, flip);
}

void Player::Update(){
	this->px += this->vx;
	this->py += this->vy;
}
