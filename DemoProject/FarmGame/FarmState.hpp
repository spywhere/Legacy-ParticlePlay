#ifndef FARMSTATE_HEADER
#define FARMSTATE_HEADER

#include "BaseFarmState.hpp"

class FarmState : public BaseFarmState {
protected:
	Entity* player, *chicken;
public:
	void InitEntities();
	void Render(ppGraphics* graphics, int delta);
	void RenderEntities(ppGraphics* graphics, int delta);
	void UpdateEntities(ppInput* input, int delta);
	void Update(ppInput* input, int delta);
	void InitSounds();
	void InitMusic();
};

#endif
