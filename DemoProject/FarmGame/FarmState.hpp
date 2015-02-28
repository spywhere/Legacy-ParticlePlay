#ifndef FARMSTATE_HEADER
#define FARMSTATE_HEADER

#include <string>
#include <ParticlePlay/ParticlePlay.hpp>
#include "Spritesheet.hpp"
#include "Tile.hpp"
#include "Entity.hpp"

class FarmState : public ppState {
protected:
	ppGUI* gui;
	ppIMS* ims;
	Spritesheet* spritesheet;
	Tile* grassTile, *dirtTile, *waterTile;
	Entity* player, *chicken;
	int gameTime, timeSec, timeSpeed;
	void RenderNumber(SDL_Renderer* renderer, int x, int y, int number);
	void RenderText(SDL_Renderer* renderer, int x, int y, const char *time);
	std::string FormatTime(int time);
	std::string FormatNumber(int number);
public:
	void OnInit();
	void OnRender(SDL_Renderer* renderer, int delta);
	void OnUpdate(ppInput* input, int delta);
};

#endif
