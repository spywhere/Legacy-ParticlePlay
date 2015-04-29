#include "TestGame.hpp"

#include <iostream>
#include <string>
#include "FarmGame/BasicFarmState.hpp"
#include "FarmGame/FarmState.hpp"
#include "Kameleon/KameleonState.hpp"
#include "TestScene.hpp"
#include "TestIMS.hpp"
#include "TestTestbed.hpp"

int main(int argc, char* argv[]) {
	TestGame* game = new TestGame();

	// game->SetShowFPS(true);
	game->SetResizable(true);
	#ifdef FULL
	game->SetTitle("ParticlePlay Game Test");
	#else
	game->SetTitle("ParticlePlay Game Test [Demo]");
	#endif
	std::cout << "Build: " << __DATE__ << " " << __TIME__ << std::endl;
	game->AddState("basicfarmstate", new BasicFarmState());
	game->AddState("farmstate", new FarmState());
	game->AddState("kameleon", new KameleonState());
	game->AddState("main", new TestScene());
	game->AddState("ims", new TestIMS());
	game->AddState("testbed", new TestTestbed());
	// game->EnterState("main");
	game->EnterState("ims");
	// game->EnterState("kameleon");
	// game->EnterState("testbed");
	return game->StartGame();
}
