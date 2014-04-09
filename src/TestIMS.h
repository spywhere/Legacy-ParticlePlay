#ifndef TESTIMS_HEADER
#define TESTIMS_HEADER

#include "ParticlePlay/Includes.h"
#include "ParticlePlay/GUI/GUI.h"
#include "ParticlePlay/IMS/IMS.h"
#include "ParticlePlay/IMS/Filters.h"
#include "ParticlePlay/IMS/Sound.h"
#include "ParticlePlay/Scene.h"
#include "ParticlePlay/Input.h"


class TestIMS : public ppScene{
private:
	ppGUI* gui;
	IMS* ims;
	LowPassFilter* lpf;
	bool soundInit;
	int posx, posy;
	int test;
	int cooldown;
	float currentTime;
	float totalTime;
public:
	void OnInit();
	void OnRender(SDL_Renderer* renderer, int delta);
	void OnUpdate(ppInput* input, int delta);
};

#endif