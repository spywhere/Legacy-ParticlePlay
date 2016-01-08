/*
* Copyright (c) Digital Particle. All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Sirisak Lueangsaksri <spywhere@digitalparticle.com>
*
* File: PewPew.cpp
* Created on: 2016-01-08 13:48:25
* Last modified on: 2016-01-08 13:51:38
* Last modified by: Sirisak Lueangsaksri
*/

#include "PewPew.hpp"

#include <iostream>

int main(int argc, char const *argv[]){
	PewPew* game = new PewPew();

	game->SetSize(800, 600);
	#ifdef FULL
	game->SetTitle("Pew-Pew");
	#else
	game->SetTitle("Pew-Pew [Demo]");
	#endif
	std::cout << "Build: " << __DATE__ << " " << __TIME__ << std::endl;



	return game->StartGame();
}
