#ifndef TESTIMS_HEADER
#define TESTIMS_HEADER

#include <ParticlePlay/ParticlePlay.hpp>

class TestIMS : public ppState {
protected:
	ppGUI* gui;
	ppIMS* ims;
	int test;
	int playlist_track;
	void DrawRect(int x, int y, int w, int h);
	void DrawFillRect(int x, int y, int w, int h);
public:
	void OnInit();
	void OnRender(ppGraphics* graphics, int delta);
	void OnUpdate(ppInput* input, int delta);
};

#endif
