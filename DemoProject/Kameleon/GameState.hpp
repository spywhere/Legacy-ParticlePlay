#ifndef GAMESTATE_HEADER
#define GAMESTATE_HEADER

#include <ParticlePlay/ParticlePlay.hpp>
#include "kPlayer.hpp"
#include "Level.hpp"

class GameState {
protected:
	ppGame* game;
	ppGUI* gui;
	ppPhysics* physics;
	kPlayer* player;
	Level* level;
	int tx, ty;
public:
	GameState(ppGame* game);
	void OnInit();
	void OnRender(SDL_Renderer* renderer, int delta);
	void OnUpdate(ppInput* input, int delta);
};

#endif
