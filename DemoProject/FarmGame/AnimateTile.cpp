#include "AnimateTile.hpp"

AnimateTile::AnimateTile(Spritesheet* spritesheet, int* xOffsets, int* yOffsets, int animationSize, int animationDelay, float scale) : Tile(spritesheet, 0, 0, scale){
	this->xOffsets = xOffsets;
	this->yOffsets = yOffsets;
	this->animationSize = animationSize;
	this->animationDelay = animationDelay;
	this->currentFrame = 0;
	this->frameTime = 0;
}

void AnimateTile::Render(ppGraphics* graphics, int x, int y, double angle, SDL_Point* center, SDL_RendererFlip flip){
	this->spritesheet->GetTile(this->xOffsets[this->currentFrame], this->yOffsets[this->currentFrame])->Render(graphics, x, y);
}

void AnimateTile::Update(ppInput* input, int delta){
	this->frameTime += delta;
	if(this->frameTime >= this->animationDelay){
		this->frameTime %= this->animationDelay;
		this->currentFrame = (this->currentFrame+1)%this->animationSize;
	}
}
