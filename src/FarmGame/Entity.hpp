#ifndef ENTITY_HEADER
#define ENTITY_HEADER

#include "../ParticlePlay/ParticlePlay.hpp"
#include "Spritesheet.hpp"

class Entity {
private:
	int px, py, vx, vy;
	int direction;
protected:
	Spritesheet* spritesheet;
	const char *soundName;
	bool inWater;
public:
	Entity(Spritesheet* spritesheet, int startX, int startY);
	virtual void Render(SDL_Renderer* renderer)=0;
	virtual void Update(ppInput* input, int delta);
	int GetDirection();
	int GetPositionX();
	int GetPositionY();
	void MoveX(int vx);
	void MoveY(int vy);
	void SetSound(const char *soundName);
	bool IsInside(int x, int y, int width, int height);
	void SetInWater(bool inWater);
};

#endif
