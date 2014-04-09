#include "TestGame.h"

#include <iostream>
#include "TestScene.h"
#include "TestIMS.h"
#include "TestTestbed.h"

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
    theApp->AddScene("main", new TestScene());
    theApp->AddScene("ims", new TestIMS());
    theApp->AddScene("testbed", new TestTestbed());
    theApp->EnterScene("ims");
    return theApp->StartGame();
}