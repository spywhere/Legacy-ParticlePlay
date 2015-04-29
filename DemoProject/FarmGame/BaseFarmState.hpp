#ifndef BASEFARMSTATE_HEADER
#define BASEFARMSTATE_HEADER

#include <string>
#include <ParticlePlay/ParticlePlay.hpp>
#include "Spritesheet.hpp"
#include "Tile.hpp"
#include "Entity.hpp"

class BaseFarmState : public ppState {
protected:
	ppGUI* gui;
	ppIMS* ims;
	Spritesheet* spritesheet;
	Tile* grassTile, *dirtTile, *waterTile;
	int gameTime, timeSec, timeSpeed;
	void RenderNumber(SDL_Renderer* renderer, int x, int y, int number);
	void RenderText(SDL_Renderer* renderer, int x, int y, const char *time);
	std::string FormatTime(int time);
	std::string FormatNumber(int number);
public:
	virtual void InitEntities()=0;
	virtual void RenderEntities(SDL_Renderer* renderer, int delta)=0;
	virtual void Render(SDL_Renderer* renderer, int delta);
	virtual void UpdateEntities(ppInput* input, int delta)=0;
	virtual void Update(ppInput* input, int delta)=0;
	virtual void InitSounds()=0;
	virtual void InitMusic()=0;
	void OnInit();
	void OnRender(SDL_Renderer* renderer, int delta);
	void OnUpdate(ppInput* input, int delta);
};

#endif
