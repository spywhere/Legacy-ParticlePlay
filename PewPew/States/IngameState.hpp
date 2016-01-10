/*
* Copyright (c) Digital Particle. All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Sirisak Lueangsaksri <spywhere@digitalparticle.com>
*
* File: IngameState.hpp
* Created on: 2016-01-10 13:28:59
* Last modified on: 2016-01-10 16:53:05
* Last modified by: Sirisak Lueangsaksri
*/

#ifndef INGAME_STATE_HEADER
#define INGAME_STATE_HEADER

#include <ParticlePlay/ParticlePlay.hpp>

class IngameState : public ppState {
private:
	ppGUI* gui;
public:
	void OnInit();
	void OnRender(ppGraphics* graphics, int delta);
	void OnUpdate(ppInput* input, int delta);
};

#endif
