#ifndef SPRITESHEET_HEADER
#define SPRITESHEET_HEADER

#include <ParticlePlay/ParticlePlay.hpp>
#include "Tile.hpp"

class Tile;
class Spritesheet {
protected:
	ppImage* image;
	int tileWidth;
	int tileHeight;
	float scale;
public:
	Spritesheet(ppImage* image, int tileWidth, int tileHeight, float scale);
	int GetTotalCells();
	int GetTileWidth();
	int GetTileHeight();
	int GetWidth();
	int GetHeight();
	Tile* GetTile(int xTile, int yTile);
	Tile* GetTile(int tileId);
	ppImage* GetSheet();
};

#endif
