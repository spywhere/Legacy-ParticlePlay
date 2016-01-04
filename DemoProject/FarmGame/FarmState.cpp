#include "FarmState.hpp"

#include <iostream>
#include "Chicken.hpp"
#include "Player.hpp"

void FarmState::InitEntities(){
	// Initialize entities
	this->player = new Player(this->spritesheet, this->GetGame()->GetWidth()/2, this->GetGame()->GetHeight()/2);
	this->chicken = new Chicken(this->spritesheet, this->GetGame()->GetWidth()/2, this->GetGame()->GetHeight()/8);
}

void FarmState::Render(ppGraphics* graphics, int delta){
	if(this->ims){
		ppGenericSound* track = this->ims->GetSound("dawnTrack");
		if(track && !track->IsPlaying()){
			track = this->ims->GetSound("nightTrack");
			if(track && !track->IsPlaying()){
				track = this->ims->GetSound("predawnTrack");
			}
		}
		if(track && track->GetCurrentBar()%2 == 0){
			this->RenderText(graphics, this->GetGame()->GetWidth()-40, this->GetGame()->GetHeight()-40, "o");
		}else{
			this->RenderText(graphics, this->GetGame()->GetWidth()-40, this->GetGame()->GetHeight()-40, "O");
		}
	}
}

void FarmState::RenderEntities(ppGraphics* graphics, int delta){
	// Render entities
	this->chicken->Render(graphics);
	this->player->Render(graphics);
}

void FarmState::UpdateEntities(ppInput* input, int delta){
	// Set the entity rendering properties
	this->chicken->SetInWater(this->chicken->IsInside(0, (int)(2.5f*this->spritesheet->GetHeight()), 4*this->spritesheet->GetWidth(), (int)(5.8f*this->spritesheet->GetHeight())));
	this->player->SetInWater(this->player->IsInside(0, (int)(2.5f*this->spritesheet->GetHeight()), 4*this->spritesheet->GetWidth(), (int)(5.8f*this->spritesheet->GetHeight())));

	// Update entity position
	this->chicken->Update(input, delta);
	this->player->Update(input, delta);
}

void FarmState::InitSounds(){
	// Create music switch
	//    TODO: Switch variable name
	this->ims->CreateSwitch("farmSwitch");

	// Initialize bird sound effect
	//    TODO: Create bird format and sound

	// Create bird stinger from bird sound
	//    TODO: Create bird stinger

	// Initialize chicken sound effect
	ppFormat* chickenFormat = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/FarmGame/Chicken.wav");
	this->ims->CreateSound("chickenSound", chickenFormat);

	// Assign sound effect to entity
	this->chicken->SetSound("chickenSound");
}

void FarmState::Update(ppInput* input, int delta){
	// Keypress for bird sound effect
	//    TODO: Check for spacebar, then trigger the bird stinger

	// Change music depends on ingame time
	if(this->gameTime >= 360 && this->gameTime < 840 && this->ims->GetSound("dawnTrack")->IsStop()){
		std::cout << "Dawn Track" << std::endl;
		this->ims->GetSwitch("farmSwitch")->SwitchState("dawnTrack");
	}else if(this->gameTime >= 840 && this->gameTime < 1320 && this->ims->GetSound("nightTrack")->IsStop()){
		std::cout << "Night Track" << std::endl;
		this->ims->GetSwitch("farmSwitch")->SwitchState("nightTrack");
	}else if((this->gameTime >= 1320 || this->gameTime < 360) && this->ims->GetSound("predawnTrack")->IsStop()){
		std::cout << "PreDawn Track" << std::endl;
		this->ims->GetSwitch("farmSwitch")->SwitchState("predawnTrack");
	}
}

void FarmState::InitMusic(){
	// Setup music
	ppFormat* dawnFormat = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/FarmGame/Dawn.wav");
	ppFormat* nightFormat = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/FarmGame/Night.wav");
	ppFormat* predawnFormat = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/FarmGame/PreDawn.wav");

	ppSound* dawnSound = this->ims->CreateSound("dawnSound", dawnFormat);
	ppSound* dawnSound2 = this->ims->CreateSound("dawnSound2", dawnFormat);
	ppSound* nightSound = this->ims->CreateSound("nightSound", nightFormat);
	ppSound* nightSound2 = this->ims->CreateSound("nightSound2", nightFormat);
	ppSound* predawnSound = this->ims->CreateSound("predawnSound", predawnFormat);
	ppSound* predawnSound2 = this->ims->CreateSound("predawnSound2", predawnFormat);

	ppSegment* dawnSegment = this->ims->CreateSegment("dawnSeg1");
	ppSegment* dawnSegment2 = this->ims->CreateSegment("dawnSeg2");
	ppSegment* nightSegment = this->ims->CreateSegment("nightSeg1");
	ppSegment* nightSegment2 = this->ims->CreateSegment("nightSeg2");
	ppSegment* predawnSegment = this->ims->CreateSegment("predawnSeg1");
	ppSegment* predawnSegment2 = this->ims->CreateSegment("predawnSeg2");

	// Add sound to segment
	dawnSegment->AddSound(dawnSound);
	dawnSegment2->AddSound(dawnSound2);
	nightSegment->AddSound(nightSound);
	nightSegment2->AddSound(nightSound2);
	predawnSegment->AddSound(predawnSound);
	predawnSegment2->AddSound(predawnSound2);

 	// Setup segments
	dawnSegment->SetExitCue(dawnFormat->TimeToPosition(22.75f));
	dawnSegment2->SetExitCue(dawnFormat->TimeToPosition(22.75f));
	nightSegment->SetExitCue(nightFormat->TimeToPosition(22.75f));
	nightSegment2->SetExitCue(nightFormat->TimeToPosition(22.75f));
	predawnSegment->SetExitCue(predawnFormat->TimeToPosition(22.75f));
	predawnSegment2->SetExitCue(predawnFormat->TimeToPosition(22.75f));

	// Create playlists
	ppPlaylist* dawnPlaylist = this->ims->CreatePlaylist("dawnTrack");
	dawnPlaylist->AddSound(dawnSegment);
	dawnPlaylist->AddSound(dawnSegment2);
	dawnPlaylist->SetLoop(-1);
	dawnPlaylist->SetTimeSignature(1, 4);
	dawnPlaylist->SetTempo(100);
	ppPlaylist* nightPlaylist = this->ims->CreatePlaylist("nightTrack");
	nightPlaylist->AddSound(nightSegment);
	nightPlaylist->AddSound(nightSegment2);
	nightPlaylist->SetLoop(-1);
	nightPlaylist->SetTimeSignature(1, 4);
	nightPlaylist->SetTempo(100);
	ppPlaylist* predawnPlaylist = this->ims->CreatePlaylist("predawnTrack");
	predawnPlaylist->AddSound(predawnSegment);
	predawnPlaylist->AddSound(predawnSegment2);
	predawnPlaylist->SetLoop(-1);
	predawnPlaylist->SetTimeSignature(1, 4);
	predawnPlaylist->SetTempo(100);

	// Change how default transition behave
	ppTransition* transition = this->ims->GetSwitch("farmSwitch")->GetDefaultTransition();
	transition->SetSourceDuration(0.1f);
	transition->SetDestinationDuration(0.1f);
}
