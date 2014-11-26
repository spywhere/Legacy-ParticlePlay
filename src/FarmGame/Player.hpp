#ifndef PLAYER_HEADER
#define PLAYER_HEADER

#include "../ParticlePlay/ParticlePlay.hpp"
#include "Spritesheet.hpp"
#include "Tile.hpp"

class Player {
protected:
	Spritesheet* spritesheet;
	int px, py, vx, vy;
	int direction;
	bool inWater;
public:
	Player(Spritesheet* spritesheet, int startX, int startY);
	void Render(SDL_Renderer* renderer);
	void MoveX(int vx);
	void MoveY(int vy);
	void Update();
	void SetInWater(bool inWater);
	bool IsInside(int x, int y, int width, int height);
};

#endif
