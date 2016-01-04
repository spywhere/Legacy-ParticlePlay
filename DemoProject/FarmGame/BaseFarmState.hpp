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
	void RenderNumber(ppGraphics* graphics, int x, int y, int number);
	void RenderText(ppGraphics* graphics, int x, int y, const char *time);
	std::string FormatTime(int time);
	std::string FormatNumber(int number);
public:
	virtual void InitEntities()=0;
	virtual void RenderEntities(ppGraphics* graphics, int delta)=0;
	virtual void Render(ppGraphics* graphics, int delta);
	virtual void UpdateEntities(ppInput* input, int delta)=0;
	virtual void Update(ppInput* input, int delta)=0;
	virtual void InitSounds()=0;
	virtual void InitMusic()=0;
	void OnInit();
	void OnRender(ppGraphics* graphics, int delta);
	void OnUpdate(ppInput* input, int delta);
};

#endif
