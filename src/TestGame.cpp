#include "TestGame.hpp"

#include <iostream>
#include <string>
#include "TestScene.hpp"
#include "TestIMS.hpp"
#include "TestTestbed.hpp"

// void printOffset(int level){
// 	for(int i=0;i<level;i++){
// 		std::cout << "  ";
// 	}
// }

// void printYAML(YAML::Node node, int level){
// 	if(node.IsMap()){
// 		std::cout << std::endl;
// 		for(auto it=node.begin();it!=node.end();++it) {
// 			printOffset(level);
// 			std::cout << it->first.as<std::string>() << ": ";
// 			printYAML(it->second, level+1);
// 			if(it->second.IsScalar() || it->second.IsSequence()){
// 				std::cout << std::endl;
// 			}
// 		}
// 	}else if(node.IsSequence()){
// 		std::cout << "[";
// 		for(auto it=node.begin();it!=node.end();++it) {
// 			if(it!=node.begin()){
// 				std::cout << ", ";
// 			}
// 			printYAML(*it, level+1);
// 		}
// 		std::cout << "]";
// 	}else if(node.IsScalar()){
// 		std::cout << node.as<std::string>();
// 	}else{
// 		std::cout << "What?" << std::endl;
// 	}
// }

int main(int argc, char* argv[]) {
	TestGame* game = new TestGame();

	// YAML::Node config = YAML::Load(game->GetGameIO()->ReadFile("config.yaml").c_str());
	// printYAML(config, 0);

	// game->SetShowFPS(true);
	game->SetResizable(true);
	#ifdef FULL
	game->SetTitle("ParticlePlay Game Test");
	#else
	game->SetTitle("ParticlePlay Game Test [Demo]");
	#endif
	std::cout << "Build: " << __DATE__ << " " << __TIME__ << std::endl;
	game->AddState("main", new TestScene());
	game->AddState("ims", new TestIMS());
	game->AddState("testbed", new TestTestbed());
	// game->EnterState("main");
	game->EnterState("ims");
	// game->EnterState("testbed");
	return game->StartGame();
}
