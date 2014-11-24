#ifndef FARMSTATE_HEADER
#define FARMSTATE_HEADER

#include <string>
#include "../ParticlePlay/ParticlePlay.hpp"
#include "Spritesheet.hpp"
#include "Tile.hpp"
#include "Player.hpp"

class FarmState : public ppState {
protected:
	ppGUI* gui;
	ppIMS* ims;
	Spritesheet* spritesheet;
	Tile* tile;
	Player* player;
	int gameTime, timeSec;
public:
	void OnInit();
	void OnRender(SDL_Renderer* renderer, int delta);
	void OnUpdate(ppInput* input, int delta);
	void RenderNumber(SDL_Renderer* renderer, int x, int y, int number);
	void RenderTime(SDL_Renderer* renderer, int x, int y, const char *time);
	std::string FormatTime(int time);
};

#endif
