/*
* Copyright (c) Digital Particle. All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Sirisak Lueangsaksri <spywhere@digitalparticle.com>
*
* File: IngameState.cpp
* Created on: 2016-01-10 13:28:49
* Last modified on: 2016-01-10 17:06:48
* Last modified by: Sirisak Lueangsaksri
*/

#include "IngameState.hpp"

#include <sstream>

void IngameState::OnInit(){
	this->gui = new ppGUI();
	this->gui->AddControl(new ppLabel("text", 10, 50));
}

void IngameState::OnRender(ppGraphics* graphics, int delta){
	graphics->PushContext();
	graphics->IdentityContext();
	std::stringstream ss;
	ss << "FPS: " << this->GetGame()->GetFPS() << " [" << this->GetGame()->GetAvgRenderTime() << "ms]\n";
	ss << "UPS: " << this->GetGame()->GetUPS() << " [" << this->GetGame()->GetAvgUpdateTime() << "ms]\n";
	if(this->gui->GetDefaultFont()){
		this->gui->GetDefaultFont()->Render(10, 10, ss.str().c_str(), graphics);
	}
	graphics->PopContext();

	graphics->SetVertex(50, 50);
	graphics->SetVertex(75, 75);
	graphics->SetVertex(25, 100);
	graphics->SetVertex(50, 125);
	graphics->DrawStrip();

	graphics->SetVertex(150, 50);
	graphics->SetVertex(175, 75);
	graphics->SetVertex(125, 100);
	graphics->SetVertex(150, 125);
	graphics->DrawLines();

	graphics->SetVertex(250, 50);
	graphics->SetVertex(275, 75);
	graphics->SetVertex(225, 100);
	graphics->SetVertex(250, 125);
	graphics->DrawPoints();

	graphics->DrawLoopArc(350, 50, 50, 50, 0, 135);
	graphics->FillArc(450, 50, 50, 50, 0, 135);

	ppImage* image = new ppImage("tmpres/Kameleon/Assets/Image 2325.png");
	graphics->Rotate(0.01f);
	image->Render(graphics, 550, 50);
}

void IngameState::OnUpdate(ppInput* input, int delta){

}
