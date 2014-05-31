#include "TestGame.hpp"

#include <iostream>
#include "TestScene.hpp"
#include "TestIMS.hpp"
#include "TestTestbed.hpp"

int main(int argc, char* argv[]) {
    TestGame* theApp = new TestGame();
    // theApp->SetShowFPS(true);
    theApp->SetResizable(true);
    #ifdef FULL
    theApp->SetTitle("ParticlePlay Game Test");
    #else
    theApp->SetTitle("ParticlePlay Game Test [Demo]");
    #endif
    std::cout << "Build: " << __DATE__ << " " << __TIME__ << std::endl;
    theApp->AddState("main", new TestScene());
    theApp->AddState("ims", new TestIMS());
    theApp->AddState("testbed", new TestTestbed());
    theApp->EnterState("testbed");
    return theApp->StartGame();
}
