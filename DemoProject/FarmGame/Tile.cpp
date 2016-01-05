#include "Tile.hpp"

Tile::Tile(Spritesheet* spritesheet, int xOffset, int yOffset, float scale){
	this->spritesheet = spritesheet;
	this->xOffset = xOffset;
	this->yOffset = yOffset;
	this->scale = scale;
	this->clipX = 1.0f;
	this->clipY = 1.0f;
}

void Tile::Render(ppGraphics* graphics, int x, int y, double angle, SDL_Point* center, SDL_RendererFlip flip){
	this->spritesheet->GetSheet()->Render(graphics, this->xOffset, this->yOffset, x, y, (int)(this->GetTileWidth()*this->clipX), (int)(this->GetTileHeight()*this->clipY), (int)(this->GetWidth()*this->clipX), (int)(this->GetHeight()*this->clipY), angle, center, flip);
}

void Tile::Render(ppGraphics* graphics, int x, int y, double angle, SDL_RendererFlip flip){
	this->Render(graphics, x, y, angle, ppImage::NO_CENTER, flip);
}

void Tile::Render(ppGraphics* graphics, int x, int y, double angle, SDL_Point* center){
	this->Render(graphics, x, y, angle, center, ppImage::NO_FLIP);
}

void Tile::Render(ppGraphics* graphics, int x, int y, SDL_RendererFlip flip){
	this->Render(graphics, x, y, 0.0, ppImage::NO_CENTER, flip);
}

void Tile::Render(ppGraphics* graphics, int x, int y, double angle){
	this->Render(graphics, x, y, angle, ppImage::NO_CENTER, ppImage::NO_FLIP);
}

void Tile::Render(ppGraphics* graphics, int x, int y){
	this->Render(graphics, x, y, 0.0, ppImage::NO_CENTER, ppImage::NO_FLIP);
}

void Tile::Update(ppInput* input, int delta){
	// Pure virtual
	// This class don't have to do anything
}

void Tile::SetClip(float cx, float cy){
	this->clipX = cx;
	this->clipY = cy;
}

int Tile::GetTileWidth(){
	return this->spritesheet->GetTileWidth();
}

int Tile::GetTileHeight(){
	return this->spritesheet->GetTileHeight();
}

int Tile::GetWidth(){
	return this->GetTileWidth()*this->scale;
}

int Tile::GetHeight(){
	return this->GetTileHeight()*this->scale;
}
