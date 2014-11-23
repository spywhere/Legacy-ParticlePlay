#ifndef FARMSTATE_HEADER
#define FARMSTATE_HEADER

#include "../ParticlePlay/ParticlePlay.hpp"
#include "Spritesheet.hpp"
#include "Tile.hpp"
#include "Player.hpp"

class FarmState : public ppState {
protected:
	ppGraphics* graphics;
	ppGUI* gui;
	ppIMS* ims;
	Spritesheet* spritesheet;
	Tile* tile;
	Player* player;
public:
	void OnInit();
	void OnRender(SDL_Renderer* renderer, int delta);
	void OnUpdate(ppInput* input, int delta);
};

#endif
