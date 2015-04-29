#ifndef BASICFARMSTATE_HEADER
#define BASICFARMSTATE_HEADER

#include "BaseFarmState.hpp"

class BasicFarmState : public BaseFarmState {
protected:
	Entity* player, *chicken;
public:
	void InitEntities();
	void RenderEntities(SDL_Renderer* renderer, int delta);
	void UpdateEntities(ppInput* input, int delta);
	void Update(ppInput* input, int delta);
	void InitSounds();
	void InitMusic();
};

#endif
