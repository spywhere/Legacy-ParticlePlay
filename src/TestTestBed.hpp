#ifndef TESTTESTBED_HEADER
#define TESTTESTBED_HEADER

#include "ParticlePlay/TestBed.hpp"

class TestTestbed : public ppTestBed{
public:
	void OnInit();
	void OnRender(SDL_Renderer* renderer, int delta);
	void OnUpdate(ppInput* input, int delta);
};

#endif
