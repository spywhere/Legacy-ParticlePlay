#ifndef SCENE_HEADER
#define SCENE_HEADER

#include "Includes.h"
#include "Input.h"
#include "Game.h"

class ppGame;
class ppScene{
private:
	ppGame* game;
	const char* name;
protected:
	bool needInit;
public:
	ppScene();
	bool IsNeedInit();
	void SetNeedInit(bool needInit);
	const char* GetName();
	void SetName(const char* name);
	ppGame* GetGame();
	void SetGame(ppGame* game);
	virtual void OnInit()=0;
	virtual void OnRender(SDL_Renderer* renderer, int delta)=0;
	virtual void OnUpdate(ppInput* input, int delta)=0;
	virtual void OnRestart();
	virtual void OnRestore();
	virtual bool OnEvent(SDL_Event* event);
	virtual ~ppScene();
};

#endif