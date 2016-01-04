#include "BasicFarmState.hpp"

#include <iostream>
#include "Chicken.hpp"
#include "Player.hpp"

void BasicFarmState::InitEntities(){
	// Initialize entities
	this->player = new Player(this->spritesheet, this->GetGame()->GetWidth()/2, this->GetGame()->GetHeight()/2);
	this->chicken = new Chicken(this->spritesheet, this->GetGame()->GetWidth()/2, this->GetGame()->GetHeight()/8);
}

void BasicFarmState::RenderEntities(ppGraphics* graphics, int delta){
	// Render entities
	this->chicken->Render(graphics);
	this->player->Render(graphics);
}

void BasicFarmState::UpdateEntities(ppInput* input, int delta){
	// Set the entity rendering properties
	this->chicken->SetInWater(this->chicken->IsInside(0, (int)(2.5f*this->spritesheet->GetHeight()), 4*this->spritesheet->GetWidth(), (int)(5.8f*this->spritesheet->GetHeight())));
	this->player->SetInWater(this->player->IsInside(0, (int)(2.5f*this->spritesheet->GetHeight()), 4*this->spritesheet->GetWidth(), (int)(5.8f*this->spritesheet->GetHeight())));

	// Update entity position
	this->chicken->Update(input, delta);
	this->player->Update(input, delta);
}

void BasicFarmState::InitSounds(){
	// Initialize Chicken sound effect
	ppFormat* chickenFormat = this->ims->CreateFormat(ppAudioFormat::WAVE, "tmpres/FarmGame/Chicken.wav");
	this->ims->CreateSound("chickenSound", chickenFormat);
	// Assign sound effect to entity
	this->chicken->SetSound("chickenSound");
}

void BasicFarmState::Update(ppInput* input, int delta){
	if(this->gameTime >= 360 && this->gameTime < 840 && this->ims->GetSound("dawnTrack")->IsStop()){
		std::cout << "Dawn Track" << std::endl;
		this->ims->GetSound("dawnTrack")->Play();
		this->ims->GetSound("nightTrack")->Stop();
		this->ims->GetSound("predawnTrack")->Stop();
	}else if(this->gameTime >= 840 && this->gameTime < 1320 && this->ims->GetSound("nightTrack")->IsStop()){
		std::cout << "Night Track" << std::endl;
		this->ims->GetSound("dawnTrack")->Stop();
		this->ims->GetSound("nightTrack")->Play();
		this->ims->GetSound("predawnTrack")->Stop();
	}else if((this->gameTime >= 1320 || this->gameTime < 360) && this->ims->GetSound("predawnTrack")->IsStop()){
		std::cout << "PreDawn Track" << std::endl;
		this->ims->GetSound("dawnTrack")->Stop();
		this->ims->GetSound("nightTrack")->Stop();
		this->ims->GetSound("predawnTrack")->Play();
	}
}

void BasicFarmState::InitMusic(){
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

	dawnSegment->AddSound(dawnSound);
	dawnSegment2->AddSound(dawnSound2);
	nightSegment->AddSound(nightSound);
	nightSegment2->AddSound(nightSound2);
	predawnSegment->AddSound(predawnSound);
	predawnSegment2->AddSound(predawnSound2);

	dawnSegment->SetExitCue(dawnFormat->TimeToPosition(22.75f));
	dawnSegment2->SetExitCue(dawnFormat->TimeToPosition(22.75f));
	nightSegment->SetExitCue(nightFormat->TimeToPosition(22.75f));
	nightSegment2->SetExitCue(nightFormat->TimeToPosition(22.75f));
	predawnSegment->SetExitCue(predawnFormat->TimeToPosition(22.75f));
	predawnSegment2->SetExitCue(predawnFormat->TimeToPosition(22.75f));

	ppPlaylist* dawnPlaylist = this->ims->CreatePlaylist("dawnTrack");
	dawnPlaylist->AddSound(dawnSegment);
	dawnPlaylist->AddSound(dawnSegment2);
	dawnPlaylist->SetLoop(-1);
	ppPlaylist* nightPlaylist = this->ims->CreatePlaylist("nightTrack");
	nightPlaylist->AddSound(nightSegment);
	nightPlaylist->AddSound(nightSegment2);
	nightPlaylist->SetLoop(-1);
	ppPlaylist* predawnPlaylist = this->ims->CreatePlaylist("predawnTrack");
	predawnPlaylist->AddSound(predawnSegment);
	predawnPlaylist->AddSound(predawnSegment2);
	predawnPlaylist->SetLoop(-1);
}
