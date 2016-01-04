#ifndef TESTTESTBED_HEADER
#define TESTTESTBED_HEADER

#include <ParticlePlay/ParticlePlay.hpp>

class TestTestbed : public ppTestBed {
public:
	void OnInit();
	void OnRender(ppGraphics* graphics, int delta);
	void OnUpdate(ppInput* input, int delta);
};

#endif
