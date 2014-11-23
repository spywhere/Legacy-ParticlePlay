#include "Spritesheet.hpp"

Spritesheet::Spritesheet(ppImage* image, int tileWidth, int tileHeight, float scale){
	this->image = image;
	this->tileWidth = tileWidth;
	this->tileHeight = tileHeight;
	this->scale = scale;
}

int Spritesheet::GetTotalCells(){
	return (this->image->GetWidth()/this->tileWidth)*(this->image->GetHeight()/this->tileHeight);
}

int Spritesheet::GetTileWidth(){
	return this->tileWidth;
}

int Spritesheet::GetTileHeight(){
	return this->tileHeight;
}

Tile* Spritesheet::GetTile(int xTile, int yTile){
	return new Tile(this, xTile*this->tileWidth, yTile*this->tileHeight, this->scale);
}

Tile* Spritesheet::GetTile(int tileId){
	return this->GetTile(tileId/this->tileWidth, tileId%this->tileWidth);
}

ppImage* Spritesheet::GetSheet(){
	return this->image;
}
