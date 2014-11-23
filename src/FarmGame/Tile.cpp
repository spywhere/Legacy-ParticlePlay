#include "Tile.hpp"

Tile::Tile(Spritesheet* spritesheet, int xOffset, int yOffset, float scale){
	this->spritesheet = spritesheet;
	this->xOffset = xOffset;
	this->yOffset = yOffset;
	this->scale = scale;
}

void Tile::Render(SDL_Renderer *renderer, int x, int y, double angle, SDL_Point* center, SDL_RendererFlip flip){
	this->spritesheet->GetSheet()->Render(renderer, this->xOffset, this->yOffset, x, y, this->GetTileWidth(), this->GetTileHeight(), this->GetWidth(), this->GetHeight(), angle, center, flip);
}

void Tile::Render(SDL_Renderer *renderer, int x, int y, double angle, SDL_RendererFlip flip){
	this->Render(renderer, x, y, angle, ppImage::NO_CENTER, flip);
}

void Tile::Render(SDL_Renderer *renderer, int x, int y, double angle, SDL_Point* center){
	this->Render(renderer, x, y, angle, center, ppImage::NO_FLIP);
}

void Tile::Render(SDL_Renderer *renderer, int x, int y, SDL_RendererFlip flip){
	this->Render(renderer, x, y, 0.0, ppImage::NO_CENTER, flip);
}

void Tile::Render(SDL_Renderer *renderer, int x, int y, double angle){
	this->Render(renderer, x, y, angle, ppImage::NO_CENTER, ppImage::NO_FLIP);
}

void Tile::Render(SDL_Renderer *renderer, int x, int y){
	this->Render(renderer, x, y, 0.0, ppImage::NO_CENTER, ppImage::NO_FLIP);
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
